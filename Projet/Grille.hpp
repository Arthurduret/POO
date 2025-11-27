#ifndef GRILLE_H
#define GRILLE_H

#include "Cellule.hpp"
#include <vector> 

class Grille {
private:
    Cellule*** cellules;
    int longueur;
    int hauteur;
    
public:
    Grille(int longueur, int hauteur);
    ~Grille();

    void init(const std::vector<std::vector<int>>& donnees); 
 
    int getVoisinsVivants(int x, int y) const;
    
    void evoluer();

    Cellule* getCellule(int x, int y) const;
    int getLongueur() const;
    int getHauteur() const;
};

#endif