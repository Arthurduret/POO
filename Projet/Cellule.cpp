#include "Cellule.hpp"

Cellule::~Cellule() {
    delete etat_actuel;
}

EtatCellule* Cellule::getEtat() const {
    return etat_actuel;
}

void Cellule::setEtat(EtatCellule* new_etat) {
        if (new_etat != etat_actuel) { 
        delete etat_actuel;
        etat_actuel = new_etat;
    }
}

bool Cellule::estVivante() const {
    return this->etat_actuel->estVivante();
}

bool Cellule::estObstacle() const {
    return this->etat_actuel->estObstacle();
}