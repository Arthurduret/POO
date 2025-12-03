#ifndef CELLULE_HPP
#define CELLULE_HPP

#include "EtatCellule.hpp"

class Cellule {
protected:
    EtatCellule* etat_actuel = nullptr; 
    
public:
    Cellule() {}; 
    
    virtual ~Cellule(); 

    EtatCellule* getEtat() const;

    void setEtat(EtatCellule* new_etat);
    
    bool estVivante() const;
};

#endif 