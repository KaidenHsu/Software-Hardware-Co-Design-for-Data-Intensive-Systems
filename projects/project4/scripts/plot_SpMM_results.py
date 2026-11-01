#!/usr/bin/env python3
"""Produce self-contained SVG plot(s) from SPMM summary.csv; no third-party modules."""

import csv,sys
from pathlib import Path
from html import escape

# Render series of (label, [(x, y), ...]) pairs as a standalone SVG file.
def plot(filename,title,xlabel,ylabel,series):

    # Determine data bounds and reserve headroom above the largest value.
    W,H=960,590
    vals=[v for _,data in series for _,v in data]
    if not vals:raise SystemExit('No numeric data in summary.csv')
    ymax=max(vals)*1.15 if max(vals)>0 else 1
    xs=[x for _,data in series for x,_ in data]
    x0,x1=min(xs),max(xs)
    if x1==x0:x1=x0+1

    # Map data coordinates into the plot area; SVG y coordinates increase downward.
    X=lambda x:90+760*(x-x0)/(x1-x0)
    Y=lambda y:500-395*y/ymax
    colors=['#167f81','#b65a32','#4d63a3','#9163a4']

    # Build the SVG frame, axes, and escaped titles without external plotting packages.
    parts=['<svg xmlns="http://www.w3.org/2000/svg" width="960" height="590" viewBox="0 0 960 590">',
           '<rect width="960" height="590" fill="white"/>',
           '<text x="480" y="40" font-size="24" font-family="Arial" text-anchor="middle">'+escape(title)+'</text>',
           '<path d="M90,105V500H850" stroke="black" stroke-width="2" fill="none"/>',
           '<text x="480" y="550" text-anchor="middle" font-family="Arial" font-size="16">'+escape(xlabel)+'</text>',
           '<text x="24" y="300" transform="rotate(-90 24 300)" text-anchor="middle" font-family="Arial" font-size="16">'+escape(ylabel)+'</text>']

    # Add horizontal grid lines and tick labels at five evenly spaced y values.
    for t in range(5):
        val=ymax*t/4; y=Y(val)
        parts.append(f'<line x1="90" y1="{y}" x2="850" y2="{y}" stroke="#ddd"/>')
        parts.append(f'<text x="78" y="{y+5}" text-anchor="end" font-family="Arial" font-size="12">{val:.3g}</text>')

    # Label each distinct x value shared by the series.
    for x in sorted(set(xs)):
        parts.append(f'<text x="{X(x)}" y="520" text-anchor="middle" font-family="Arial" font-size="12">{x:g}</text>')

    # Draw each nonempty series in x order, with points and a matching legend entry.
    for j,(label,pts) in enumerate(series):
        if not pts:continue
        pts=sorted(pts); color=colors[j%len(colors)]
        coords=' '.join(f'{X(x):.2f},{Y(y):.2f}' for x,y in pts)
        parts.append(f'<polyline fill="none" stroke="{color}" stroke-width="3" points="{coords}"/>')
        for x,y in pts:parts.append(f'<circle fill="{color}" cx="{X(x)}" cy="{Y(y)}" r="4"/>')

        # Arrange legend entries in two columns above the plotting area.
        legx=105+(j%2)*370; legy=66+(j//2)*22
        parts.append(f'<line x1="{legx}" x2="{legx+25}" y1="{legy}" y2="{legy}" stroke="{color}" stroke-width="4"/>')
        parts.append(f'<text x="{legx+31}" y="{legy+5}" font-family="Arial" font-size="13">{escape(label)}</text>')

    # Close and save the SVG beside the input summary CSV.
    parts.append('</svg>')
    filename.write_text('\n'.join(parts));print('PLOT_CREATED='+str(filename))

# Read the summary CSV supplied on the command line.
def main():
    if len(sys.argv)!=2:raise SystemExit('Usage: python3 scripts/plot_SpMM_results.py results/5_full_sweep/csv/summary.csv')
    p=Path(sys.argv[1]);rows=list(csv.DictReader(p.open()))
    if not rows:raise SystemExit('Empty summary.csv')
    plot_dir=p.parent.parent/'plots'
    plot_dir.mkdir(parents=True,exist_ok=True)

    # Compare layouts and feature widths against feature-table size in MiB.
    # There are four columns per CSR row, with eight bytes per double feature.
    series=[(f'F={f} {pattern}',[(int(r['rows'])*4*f*8/1048576,float(r['median_normalized_ns'])) for r in rows if r['pattern']==pattern and int(r['features'])==f and r['median_normalized_ns']]) for f in (8,32) for pattern in ('local','permuted')]
    plot(plot_dir/'SpMM_time_vs_X_MiB.svg','SpMM: feature-table footprint','X payload (MiB)','Median ns/edge-feature',series)

    # For the 131072-row workload, also compare time against feature width.
    subset=[r for r in rows if int(r['rows'])==131072]
    series=[(pattern,[(int(r['features']),float(r['median_normalized_ns'])) for r in subset if r['pattern']==pattern and r['median_normalized_ns']]) for pattern in ('local','permuted')]
    if any(s[1] for s in series):plot(plot_dir/'SpMM_time_vs_F.svg','SpMM: effect of feature width','Features per vertex','Median ns/edge-feature',series)

# Generate plots only when invoked directly.
if __name__=='__main__':main()
