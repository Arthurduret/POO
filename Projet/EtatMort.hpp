#ifndef ETATMORT_H
#define ETATMORT_H

#include "EtatCellule.hpp"

class EtatMort : public EtatCellule {
private:
    static ReglesConway regles; 
    EtatMort() = default; 

public:
    EtatCellule* calculerProchainEtat(int voisins) override; 
    
    static EtatMort* getInstance();
    
    EtatMort(const EtatMort&) = delete; 
    void operator=(const EtatMort&) = delete;
};

#endif 