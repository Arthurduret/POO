#ifndef JEU_H
#define JEU_H

#include "Grille.hpp"
#include <vector>

class Jeu {
private:
    Grille grille;
    // GuiManager* gui; // Attribut pour la gestion graphique future

public:
    // Constructeur : initialise la grille aux bonnes dimensions
    Jeu(int longueur, int hauteur);

    void initialiserJeu(const std::vector<std::vector<int>>& donnees);


    void afficherGrille() const;


    void lancer(int generations);
    
    // Les méthodes runConsoleMode() et runGuiMode() seraient définies ici.
};

#endif