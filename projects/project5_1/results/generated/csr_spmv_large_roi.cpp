// Week8 kernel ROI harness. Includes the canonical local Week7 reference source.
// The framework builds this as a gem5 guest with real ROI markers enabled.

// --- Reuse reference helpers while supplying a separate benchmark entry point. ---
#define main week7_preserved_main
#include "week7_spmv_lab.cpp"
#undef main

#include <cstdint>
#include <cstdlib>
#include <limits>
#include <numeric>

// Optional manual native builds can disable markers; the framework leaves this undefined.
#ifdef W8_NATIVE_TEST
static inline void m5_work_begin(uint64_t,uint64_t) {}
static inline void m5_work_end(uint64_t,uint64_t) {}
#else
#include <gem5/m5ops.h>
#endif

// --- Deterministic index generation: only locality changes between cases. ---
// Scramble the nonzero index reproducibly; unsigned arithmetic wraps modulo 2^32.
// This is input generation outside the ROI, not part of the measured kernel.
static uint32_t mix32(uint32_t x) {
    x ^= x >> 16; x *= 0x7feb352du;
    x ^= x >> 15; x *= 0x846ca68bu;
    x ^= x >> 16;
    return x;
}

// --- Measured kernel: preserve the reference accumulation order. ---
// The TWO original Week7 accumulation statements, with output preallocated.
// Everything before and after this function is excluded from gem5 ROI.
__attribute__((noinline))
static void csr_spmv_kernel_only(const Ints& row_ptr, const Ints& col_idx,
                                 const Ints& values, const Ints& x, Ints& y) {
    // y is already zeroed: exclude output allocation/initialization from measurement.
    for (size_t row = 0; row < y.size(); ++row)
        for (int k = row_ptr[row]; k < row_ptr[row + 1]; ++k)
            y[row] += values[k] * x[col_idx[k]];
}

// --- Benchmark driver: setup, measured compute, then independent verification. ---
int main(int argc, char** argv) {
  try {
    // --- Parse dimensions and bound allocations before entering the ROI. ---
    int rows=32768, per=16, cols=262144;
    std::string pattern="scattered";

    // Consume flag/value pairs; require() reports malformed or unsupported inputs.
    for (int a=1;a<argc;a+=2) {
        require(a+1<argc, "missing option value");
        std::string flag(argv[a]), val(argv[a+1]);
        if (flag=="--pattern") pattern=val;
        else {
            size_t pos=0;
            long long n=std::stoll(val,&pos);
            require(pos==val.size() && n>0 && n<=10000000,
                    "invalid positive option value: "+val);
            if(flag=="--rows") rows=(int)n;
            else if(flag=="--nnz-per-row") per=(int)n;
            else if(flag=="--cols") cols=(int)n;
            else throw std::runtime_error("unknown option: "+flag);
        }
    }

    // Validate dimensions before calculating offsets or allocating the CSR arrays.
    require(pattern=="scattered" || pattern=="clustered", "invalid pattern");
    require(per<=64 && rows<=1000000 && cols>=4096, "out-of-range dimensions");
    const int64_t nz=(int64_t)rows*per;
    require(nz <= (int64_t)std::numeric_limits<int>::max(), "nnz overflow");

    // Explicit memory budget; smaller than gem5 SE assigned 512MiB RAM.
    const int64_t bytes = 4LL*(nz*2+rows*2LL+1+cols);
    require(bytes <= (96LL<<20), "benchmark exceeds 96 MiB array budget");

    // --- Allocate and initialize all arrays; this work is not measured. ---
    Ints row_ptr((size_t)rows+1), col_idx((size_t)nz), val((size_t)nz),
         x((size_t)cols), y((size_t)rows,0);
    for (int c=0;c<cols;++c) x[c]=(c%11)-5;
    for (int r=0;r<=rows;++r) row_ptr[r]=r*per;

    // Keep values and nonzero counts identical; vary only the x working set.
    // Clustered indices address 2048 entries, while scattered indices span cols.
    for (int64_t k=0;k<nz;++k) {
       uint32_t h=mix32((uint32_t)k ^ 0x9e3779b9u);
       col_idx[(size_t)k]=(int)(h % (uint32_t)(pattern=="clustered" ? 2048 : cols));
       val[(size_t)k]=(int)(k%5)-2;
    }

    validate_csr(row_ptr,col_idx,val,x); // BEFORE ROI
    std::cout << "W8_LARGE_INPUT rows=" << rows << " nnz=" << nz
              << " cols=" << cols << " pattern=" << pattern
              << " array_bytes=" << bytes << std::endl;

    // --- Measurement boundary: accumulation and its CPU/cache effects only. ---
    m5_work_begin(0,0);
    csr_spmv_kernel_only(row_ptr,col_idx,val,x,y);
    m5_work_end(0,0);

    // --- Post-ROI verification and evidence output: excluded from timing. ---
    // Strong numerical check against the ORIGINAL Week7 function AFTER ROI.
    Ints original=csr_spmv(row_ptr,col_idx,val,x);
    require(original==y, "W8_LARGE_CSR_ORACLE=FAIL");

    // Print a compact result signature after the full vector comparison succeeds.
    int64_t checksum=std::accumulate(y.begin(),y.end(),int64_t{0});
    std::cout << "W8_LARGE_CSR_ORACLE=PASS rows=" << rows
              << " nnz=" << nz << " checksum=" << checksum
              << " y0=" << y[0] << " y_last=" << y.back() << std::endl;
    return 0;

  } catch(const std::exception& ex) {
    std::cerr << "W8_LARGE_CSR_FATAL=" << ex.what() << std::endl;
    return 1;
  }
}
