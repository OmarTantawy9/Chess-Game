CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I"C:/Program Files/SFML-3.0.0/include"
LDFLAGS = -L"C:/Program Files/SFML-3.0.0/lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRC_DIR = src
OBJ_DIR = obj
TARGET = main

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean