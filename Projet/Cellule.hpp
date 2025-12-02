#ifndef CELLULE_H
#define CELLULE_H

#include "EtatCellule.hpp"

class Cellule {
    protected :
        EtatCellule* etat_actuel;
    
    public :
        Cellule() : etat_actuel(nullptr) {}
        // on fait nullptr pour l'initialiser sur un poiteur null

        EtatCellule* getEtat() const {
            return etat_actuel;
        }

        ~Cellule() {}
};


#endif