#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <vector>
#include <cstddef>
#include <algorithm>
#include "Cellule.hpp"
#include "ObservateurGrille.hpp"
#include "Jeu.cpp"
using namespace std;

class Grille {
    public:
        Grille(size_t largeur = 10, size_t hauteur = 10);

        // Accesseurs dimensionnels
        size_t getLongueur() const;
        size_t getHauteur() const;

        void init(const GridData& donnees){

        }
    

};

#endif