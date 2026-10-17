CXX ?= g++
CXXFLAGS ?= -O3 -g -fno-omit-frame-pointer -std=c++17

ROOT := $(CURDIR)
SRC := $(ROOT)/src/CSR_SpMV_benchmark_kernel_PMU.cpp
BUILD := $(ROOT)/build
RUNNER := $(ROOT)/run.sh

BASELINE := $(BUILD)/spmv_profile
PMU_COL4 := $(BUILD)/spmv_profile_pmu_col4
PMU_COL16 := $(BUILD)/spmv_profile_pmu_col16

.PHONY: all run clean

all: $(BASELINE) $(PMU_COL4) $(PMU_COL16)

$(BUILD):
	mkdir -p $@

$(BASELINE): $(SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

$(PMU_COL4): $(SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

$(PMU_COL16): $(SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) -DNCOLS_MULTIPLIER=16 $< -o $@

run: all
	$(RUNNER)

clean:
	rm -rf $(BUILD) $(ROOT)/perf $(ROOT)/log
