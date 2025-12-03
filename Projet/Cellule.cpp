#include "Cellule.hpp"

Cellule::~Cellule() {
    delete etat_actuel;
}

void Cellule::setEtat(EtatCellule* new_etat) {
    delete etat_actuel;
    
    etat_actuel = new_etat;
}

bool Cellule::estVivante() const {
    return this->etat_actuel->estVivante();
}