all: main

CXX = clang++
override CXXFLAGS += -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -g -Wmost -Werror 

# Recherche de tous les fichiers .cpp dans le répertoire actuel (sauf .ccls-cache)
SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.cpp' -print | sed -e 's/ /\\ /g')

# Recherche de tous les fichiers .h
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

# Cible principale (Compilation)
main: $(SRCS) $(HEADERS)
## TAB (Remplacer ceci par une VRAIE tabulation)
	$(CXX) $(CXXFLAGS) $(SRCS) -o "$@"

# Cible de débogage (sans optimisation -O0)
main-debug: $(SRCS) $(HEADERS)
## TAB (Remplacer ceci par une VRAIE tabulation)
	$(CXX) $(CXXFLAGS) -U_FORTIFY_SOURCE -O0 $(SRCS) -o "$@"

# Cible de nettoyage
clean:
## TAB (Remplacer ceci par une VRAIE tabulation)
	rm -f main main-debug