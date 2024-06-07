CXX = clang++
CXXFLAGS = -arch arm64 -std=c++17 -mmacosx-version-min=10.15 -Wall
FRAMEWORKS = -framework OpenGL -framework GLUT -framework Carbon
INCLUDES = -I/opt/homebrew/include
LIBS = -L/opt/homebrew/lib -lpng

TARGET = output
SOURCES = main.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(FRAMEWORKS) $(INCLUDES) $(LIBS) $^ -o $@

clean:
	rm -f $(TARGET)