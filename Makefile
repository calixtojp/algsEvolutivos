CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lGL -lGLU -lglut

SRC_DIR = src
BUILD_DIR = build

# List of source files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/host.cpp $(SRC_DIR)/meme.cpp $(SRC_DIR)/food.cpp $(SRC_DIR)/interactManager.cpp $(SRC_DIR)/utils.cpp

# List of header files
HEADERS = $(SRC_DIR)/host.h $(SRC_DIR)/meme.h $(SRC_DIR)/food.h $(SRC_DIR)/interactManager.h $(SRC_DIR)/utils.h

# Object files will be generated in the build directory
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable name
EXECUTABLE = myprogram

.PHONY: all clean

all: $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

