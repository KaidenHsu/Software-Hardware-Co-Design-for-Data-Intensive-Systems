// SpMV guided-project benchmark, C++17, Linux optional PMU.
// Files di_common.hpp and di_kernel_pmu.hpp must be in the same directory.
// Output is a checksum of deterministic exact binary-fraction results.
#include "di_common.hpp"
#include "di_kernel_pmu.hpp"
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#if defined(__GNUC__) || defined(__clang__)
__attribute__((noinline))
#endif
static void csr_spmv(const std::vector<std::size_t>& rp,
                     const std::vector<std::uint32_t>& ci,
                     const std::vector<double>& val,
                     const std::vector<double>& x,
                     std::vector<double>& y) {
    for (std::size_t r=0;r+1<rp.size();++r) {
        double sum=0;
        for(std::size_t k=rp[r];k<rp[r+1];++k) sum+=val[k]*x[ci[k]];
        y[r]=sum;
    }
}

static void selftest() {
    // Independent CSR oracle with negative and missing entries.
    const std::vector<std::size_t> rp{0,2,4,5};
    const std::vector<std::uint32_t> ci{0,3,1,2,0};
    const std::vector<double> val{2,1,-1,3,4};
    const std::vector<double> x{1,2,3,4};
    std::vector<double> y(3);

    csr_spmv(rp,ci,val,x,y);

    if (y!=std::vector<double>{6,7,4}) throw std::runtime_error("spmv oracle mismatch");

    for (std::size_t n=16; n<=65536; n*=4) {
        std::vector<std::uint8_t> used(n,0);
        for(std::size_t i=0;i<n;++i) {
            const auto p=scrambled_id(i,n);
            if(p>=n || used[p]) throw std::runtime_error("permutation not bijective");
            used[p]=1;
        }
    }

    std::cout << "SELFTEST=PASS CSR_ORACLE=PASS SCRAMBLE_BIJECTION=PASS\n";
}

int main(int argc,char** argv) {
    try {
        std::size_t rows=65536,nnzrow=8,iters=500;
        std::string pattern="local";
        bool pmu_flag=false,pmu_levels_flag=false,do_selftest=false;

        for (int a=1;a<argc;++a) {
            const std::string arg=argv[a];
            if(arg=="--pmu") {pmu_flag=true;continue;}
            if(arg=="--pmu-levels") {pmu_levels_flag=true;continue;}
            if(arg=="--selftest") {do_selftest=true;continue;}
            if(a+1>=argc) throw std::runtime_error("Missing argument to "+arg);
            if(arg=="--rows") rows=positive_arg(argv[++a],"rows");
            else if(arg=="--nnz-per-row") nnzrow=positive_arg(argv[++a],"nnz-per-row");
            else if(arg=="--iters") iters=positive_arg(argv[++a],"iters");
            else if(arg=="--pattern") pattern=argv[++a];
            else throw std::runtime_error("Unknown flag: "+arg);
        }

        if(do_selftest) {selftest();return 0;}
        if(pattern!="local" && pattern!="permuted") throw std::runtime_error("Pattern must be local or permuted");
        if(!power_of_two(rows) || rows<4 || rows>2097152) throw std::runtime_error("rows must be a power of two between 4 and 2097152");
        if(nnzrow>1024 || rows>std::numeric_limits<std::uint32_t>::max()/4)
            throw std::runtime_error("Unsupported matrix dimensions");
        if(rows>std::numeric_limits<std::size_t>::max()/nnzrow) throw std::runtime_error("NNZ overflow");

        const std::size_t ncols=rows*4, nnz=rows*nnzrow;



        // ==================== SETUP START ====================
        const auto t0=std::chrono::steady_clock::now();

        std::vector<std::size_t> rp(rows+1);
        std::vector<std::uint32_t> ci(nnz);
        std::vector<double> v(nnz),x(ncols),y(rows),expected(rows);

        for(std::size_t logical=0;logical<ncols;++logical) {
            const auto physical=pattern=="local"?logical:scrambled_id(logical,ncols);
            x[physical]=deterministic_x(logical);
        }

        for(std::size_t r=0;r<rows;++r) {
            rp[r]=r*nnzrow;
            double reference=0;
            for(std::size_t j=0;j<nnzrow;++j) {
                const auto k=r*nnzrow+j;
                const auto logical=k%ncols;
                ci[k]=static_cast<std::uint32_t>(pattern=="local"?logical:scrambled_id(logical,ncols));
                v[k]=deterministic_weight(j);
                reference+=deterministic_weight(j)*deterministic_x(logical);
            }
            expected[r]=reference;
        }
        rp[rows]=nnz;

        const auto t1=std::chrono::steady_clock::now();
        // ===================== SETUP END =====================



        csr_spmv(rp,ci,v,x,y); // correctness-checked warm-up

        if(y!=expected) throw std::runtime_error("Warm-up differs from independent logical oracle");
        if (pmu_flag && pmu_levels_flag) throw std::runtime_error("Choose --pmu OR --pmu-levels, not both");

        KernelPmu counters(pmu_flag || pmu_levels_flag,"timed_spmv_loop_user_only",
                           pmu_levels_flag ? KernelPmu::Mode::Levels : KernelPmu::Mode::Core);



        // ==================== KERNEL START ===================
        counters.prepare();
        counters.start();
        const auto start=std::chrono::steady_clock::now();

        for(std::size_t it=0;it<iters;++it) csr_spmv(rp,ci,v,x,y);

        const auto stop=std::chrono::steady_clock::now();
        counters.stop();
        // ===================== KERNEL END ====================



        if(y!=expected) throw std::runtime_error("Final output differs from logical oracle");

        double checksum=0;
        for(const auto item:y) checksum+=item;

        const double secs=std::chrono::duration<double>(stop-start).count();

        std::cout << std::fixed << std::setprecision(6)
                  << "CORRECT=PASS kernel=SpMV pattern=" << pattern << " rows=" << rows
                  << " ncols=" << ncols << " nnz=" << nnz << " iters=" << iters
                  << " checksum=" << checksum << "\n"
                  << "setup_s=" << std::chrono::duration<double>(t1-t0).count()
                  << " timed_kernel_s=" << secs
                  << " ms_per_iter=" << secs*1000.0/static_cast<double>(iters)
                  << " ns_per_nnz=" << secs*1e9/(static_cast<double>(nnz)*iters)
                  << " x_MiB=" << 8.0*ncols/1048576.0 << "\n";

        counters.report();
        return 0;
    } catch(const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";return 2;
    }
}
