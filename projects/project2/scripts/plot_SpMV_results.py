#!/usr/bin/env python3
"""Produce self-contained SVG plots from summary.csv without third-party modules."""

import csv
import sys
from html import escape
from pathlib import Path


def plot(filename, title, xlabel, ylabel, series):
    """Write one SVG line chart for the supplied series."""
    # The chart uses a fixed canvas so generated plots are easy to compare.
    width, height = 960, 590

    values = [value for _, data in series for _, value in data]
    if not values:
        raise SystemExit("No numeric data in summary.csv")

    # Add headroom above the largest point and provide a fallback for all-zero data.
    ymax = max(values) * 1.15 if max(values) > 0 else 1

    x_values = [x for _, data in series for x, _ in data]
    x_min, x_max = min(x_values), max(x_values)
    if x_max == x_min:
        x_max = x_min + 1

    # Convert data coordinates into positions inside the SVG plotting area.
    X = lambda x: 90 + 760 * (x - x_min) / (x_max - x_min)
    Y = lambda y: 500 - 395 * y / ymax

    colors = ["#167f81", "#b65a32", "#4d63a3", "#9163a4"]

    parts = [
        '<svg xmlns="http://www.w3.org/2000/svg" width="960" height="590" '
        'viewBox="0 0 960 590">',
        '<rect width="960" height="590" fill="white"/>',
        '<text x="480" y="40" font-size="24" font-family="Arial" '
        'text-anchor="middle">'
        + escape(title)
        + "</text>",
        '<path d="M90,105V500H850" stroke="black" stroke-width="2" fill="none"/>',
        '<text x="480" y="550" text-anchor="middle" font-family="Arial" '
        'font-size="16">'
        + escape(xlabel)
        + "</text>",
        '<text x="24" y="300" transform="rotate(-90 24 300)" '
        'text-anchor="middle" font-family="Arial" font-size="16">'
        + escape(ylabel)
        + "</text>",
    ]

    # Add five horizontal grid lines and their labels.
    for tick in range(5):
        value = ymax * tick / 4
        y = Y(value)
        parts.append(f'<line x1="90" y1="{y}" x2="850" y2="{y}" stroke="#ddd"/>')
        parts.append(
            f'<text x="78" y="{y+5}" text-anchor="end" '
            f'font-family="Arial" font-size="12">{value:.3g}</text>'
        )

    # Label each distinct x-axis value.
    for x in sorted(set(x_values)):
        parts.append(
            f'<text x="{X(x)}" y="520" text-anchor="middle" '
            f'font-family="Arial" font-size="12">{x:g}</text>'
        )

    # Draw each input series, including its line, points, and legend entry.
    for index, (label, points) in enumerate(series):
        if not points:
            continue

        points = sorted(points)
        color = colors[index % len(colors)]
        coordinates = " ".join(
            f"{X(x):.2f},{Y(y):.2f}" for x, y in points
        )

        parts.append(
            f'<polyline fill="none" stroke="{color}" stroke-width="3" '
            f'points="{coordinates}"/>'
        )

        for x, y in points:
            parts.append(
                f'<circle fill="{color}" cx="{X(x)}" cy="{Y(y)}" r="4"/>'
            )

        legend_x = 105 + (index % 2) * 370
        legend_y = 66 + (index // 2) * 22
        parts.append(
            f'<line x1="{legend_x}" x2="{legend_x+25}" '
            f'y1="{legend_y}" y2="{legend_y}" stroke="{color}" '
            f'stroke-width="4"/>'
        )
        parts.append(
            f'<text x="{legend_x+31}" y="{legend_y+5}" '
            f'font-family="Arial" font-size="13">{escape(label)}</text>'
        )

    parts.append("</svg>")
    filename.write_text("\n".join(parts))
    print("PLOT_CREATED=" + str(filename))


def main():
    """Read summary.csv and create a plot for local and permuted layouts."""
    if len(sys.argv) != 2:
        raise SystemExit(
            "Usage: python3 scripts/plot_SpMV_results.py results/summary.csv"
        )

    summary_path = Path(sys.argv[1])
    rows = list(csv.DictReader(summary_path.open()))

    if not rows:
        raise SystemExit("Empty summary.csv")

    # Convert row footprint into MiB and group measurements by layout pattern.
    series = [
        (
            pattern,
            [
                (
                    int(row["rows"]) * 32 / 1048576,
                    float(row["median_normalized_ns"]),
                )
                for row in rows
                if row["pattern"] == pattern and row["median_normalized_ns"]
            ],
        )
        for pattern in ("local", "permuted")
    ]

    plot(
        summary_path.parent / "SpMV_time_vs_x_MiB.svg",
        "SpMV: operand layout and footprint",
        "x payload (MiB)",
        "Median ns/nonzero",
        series,
    )


if __name__ == "__main__":
    main()

