# Utilisation de g++ car clang++ n'est pas trouvé
CXX = g++

# Fichiers source du projet
SRCS = ReglesJeu.cpp EtatMorte.cpp EtatVivante.cpp Jeu.cpp Grille.cpp Cellule.cpp main.cpp VueGraphique.cpp VueConsole.cpp

# Options de compilation (inclus les liens vers SFML)
CXXFLAGS = -g -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system

# Cible principale : création de l'exécutable 'jeu_vie'
all: jeu_vie

jeu_vie: $(SRCS)
    <-- C'est ici qu'il y a la TABULATION -->
	$(CXX) $(CXXFLAGS) $^ -o $@

# Cible de nettoyage
clean:
    <-- C'est ici qu'il y a la TABULATION -->
	rm -f jeu_vie