# Variables at the top
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -MMD -MP
TARGET = main
SOURCE = $(wildcard *.cpp)
OBJ = $(SOURCE:.cpp=.o)
DEP = $(SOURCE:.cpp=.d)

# Phony declarations
.PHONY: all clean

# Build rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o *.d *.gch a.out
print:
	@echo "Sources: $(SOURCE)"
	@echo "Objects: $(OBJ)"
	@echo "Dependencies: $(DEP)"
	@echo "Target: $(TARGET)"

-include $(DEP)