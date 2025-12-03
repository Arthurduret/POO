#ifndef REGLESJEU_H
#define REGLESJEU_H


// ReglesJeu.hpp
#include <vector>

using Grid = std::vector<std::vector<int>>;

class ReglesJeu {
private:
    // Compte les voisines vivantes (méthode toroidale)
    int compterVoisinesVivantes(int ligne, int colonne, const Grid& grille);

    // Applique les règles de Conway
    int appliquerRegles(int etat_actuel, int voisines_vivantes);

public:
    // Calcule la nouvelle génération
    Grid prochainTour(const Grid& grille_actuelle);
};


#endif