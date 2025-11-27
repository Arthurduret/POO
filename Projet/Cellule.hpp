#ifndef CELLULE_H
#define CELLULE_H

#include "EtatCellule.hpp"

class Cellule {
private:
    int x;
    int y;
    EtatCellule* etatActuel;

public:
    Cellule(int x, int y, EtatCellule* etat);
    ~Cellule(); 

    void majEtat(EtatCellule* nouvelEtat);
    bool estVivant() const;

    int getX() const;
    int getY() const;
    EtatCellule* getEtat() const;
};

#endif