# Utilisation de g++ 
CXX = g++

# Options de compilation
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Fichiers source du projet (découverte automatique pour inclure les derniers .cpp)
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := jeu_vie

.PHONY: all clean run

# Cible principale : création de l'exécutable 'jeu_vie'
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Cible de nettoyage
clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)