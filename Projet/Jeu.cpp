#include "Jeu.hpp"
#include <iostream>

Jeu::Jeu(int longueur, int hauteur) : grille(longueur, hauteur) {}

void Jeu::initialiserJeu(const std::vector<std::vector<int>>& donnees) {
    grille.init(donnees);
}

// Affichage
void Jeu::afficherGrille() const {
    std::cout << "\n--- GRILLE ACTUELLE ---\n";
    for (int y = 0; y < grille.getHauteur(); ++y) {
        for (int x = 0; x < grille.getLongueur(); ++x) {
            // Utilise getCellule pour vérifier l'état
            if (grille.getCellule(x, y) && grille.getCellule(x, y)->estVivant()) {
                std::cout << "█ "; 
            } else {
                std::cout << ". "; 
            }
        }
        std::cout << std::endl;
    }
}

// Boucle principale
void Jeu::lancer(int generations) {
    for (int i = 0; i < generations; ++i) {
        std::cout << "\nGeneration " << i + 1 << std::endl;
        afficherGrille();
        grille.evoluer(); // Demande à la grille de passer à la génération suivante
    }
}