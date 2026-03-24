CXX      := g++
LDFLAGS  := -I$(ARMPL_DIR)/include -L$(ARMPL_DIR)/lib \
            $(ARMPL_DIR)/lib/libarmpl.so -lm -lamath

BUILD_TYPE ?= Release

CXX      := g++
CXXFLAGS := -mcpu=native --std=c++20 -I../include

ifeq ($(BUILD_TYPE),Debug)
  CXXFLAGS += -O0 -g
else ifeq ($(BUILD_TYPE),Release)
  CXXFLAGS += -O2
else
  $(error Unknown BUILD_TYPE '$(BUILD_TYPE)'; use Debug or Release)
endif

BUILD_DIR := build

TARGET_A  := arm-perf-lib

COMMON := vect.cpp vec1d.cpp rectangle.cpp

SOURCES_A := main.cpp $(COMMON)

OUT_A := $(BUILD_DIR)/$(TARGET_A)

.PHONY: all clean
all: $(TARGET_A) 

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUT_A): $(SOURCES_A) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(TARGET_A): $(OUT_A)

clean:
	rm -rf $(BUILD_DIR)