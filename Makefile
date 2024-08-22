CXX=clang++

SOURCEDIR=src
SOURCES=$(wildcard $(SOURCEDIR)/*.cpp)

OBJECTDIR=build
OBJECTS=$(patsubst $(SOURCEDIR)/%.cpp,$(OBJECTDIR)/%.o,$(SOURCES))


CXXFLAGS=-std=c++17 -g -O3

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o build/main

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@