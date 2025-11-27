#ifndef ETATVIVANT_H
#define ETATVIVANT_H

#include "EtatCellule.hpp"

class EtatVivant : public EtatCellule {
private:
    static ReglesConway regles; 
    EtatVivant() = default; 

public:
    EtatCellule* calculerProchainEtat(int voisins) override; 
    
    static EtatVivant* getInstance();
    
    EtatVivant(const EtatVivant&) = delete;
    void operator=(const EtatVivant&) = delete;
};

#endif