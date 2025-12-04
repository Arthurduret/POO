#ifndef REGLESJEU_HPP
#define REGLESJEU_HPP

#include "EtatCellule.hpp"

class ReglesJeu {
    public :
        
        ReglesJeu() {};

        EtatCellule* appliquerRegles(EtatCellule* etat_actuel, int voisines_vivantes);

        ~ReglesJeu() {};
};
#endif