#include "Cellule.hpp"
#include "EtatVivant.hpp" 


Cellule::Cellule(int x, int y, EtatCellule* etat) : x(x), y(y), etatActuel(etat) {}


Cellule::~Cellule() {}

void Cellule::majEtat(EtatCellule* nouvelEtat) {
    etatActuel = nouvelEtat;
}

bool Cellule::estVivant() const {
    return etatActuel == EtatVivant::getInstance();
}

int Cellule::getX() const { return x; }
int Cellule::getY() const { return y; }
EtatCellule* Cellule::getEtat() const { return etatActuel; }