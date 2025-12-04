# Makefile pour /home/rthur/POO/Projet
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I.
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := jeu

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
    rm -f $(OBJS) $(TARGET)

run: $(TARGET)
    ./$(TARGET)