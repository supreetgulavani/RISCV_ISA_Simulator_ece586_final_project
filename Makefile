###############################################################
# ECE586 - Computer Architecture
#			RISC-V ISA SIMULATOR
#
# Group 9: Supreet Gulavani, Yashodhan Wagle,
#			Ramaa Potnis, Preksha Gandhi
###############################################################

# Target
TARGET		:= ece586_isa_simulator

# Directories for source files and builds
SRC_DIR 	:= src
BUILD_DIR 	:= build
OBJ_DIR		:= $(BUILD_DIR)/obj
INCLUDE 	:= -Iinclude/

# Sources and objects
SRCS	:= $(wildcard $(SRC_DIR)/*.cpp)
OBJS	:= $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
DEPS	:= $(OBJS:.o=.d)

# Compiler
CXX			= g++
CXXFLAGS 	=  -Wall  -std=c++11

# Build Recipies
all: build $(TARGET)

# Build all the object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^

build:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -g -DDEBUG
debug: all

release: CXXFLAGS += -O2
release: all

.PHONY: all clean debug release build info

.DEFAULT_GOAL := release

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Cleanup done!"

info:
	@echo "Application:\t" $(TARGET)
	@echo "Object Dir:\t" $(OBJ_DIR)
	@echo "Sources:\t" $(SRCS)
	@echo "Objects:\t" $(OBJS)
	@echo "Dependencies:\t" $(DEPS)

##define verbose
#$(if $(V),$(info $(1)))
#endef

#$(call verbose,SRCS = $(SRCS))

