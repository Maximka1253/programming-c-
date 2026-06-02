CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude
TARGET := words_game
BUILD_DIR := build
SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:src/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all build run clean

all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)/.dir
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/.dir:
	mkdir -p $(BUILD_DIR)
	touch $(BUILD_DIR)/.dir

run: build
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
