#ifndef CELLULE_HPP
#define CELLULE_HPP

#include "EtatCellule.hpp"

class Cellule {
protected:
    EtatCellule* etat_actuel;
    
public:
    Cellule() : etat_actuel(nullptr) {}
    virtual ~Cellule(); 

    
    EtatCellule* getEtat() const {
        return etat_actuel;
    }

    void setEtat(EtatCellule* new_etat);
    bool estVivante() const;
};

#endif 