#include "ReglesJeu.hpp"
#include "EtatCellule.hpp"
#include "EtatMorte.hpp"
#include "EtatVivante.hpp"


EtatCellule* ReglesJeu::appliquerRegles(EtatCellule* etat_actuel, int voisines_vivantes) {
    
    if (etat_actuel->estObstacle()) {
        return etat_actuel; 
    }

    if (etat_actuel -> estVivante() == true) { 

        if (voisines_vivantes == 2 || voisines_vivantes == 3) {
            return etat_actuel; 
        } else {
            return new EtatMorte(); 
        }
    } else if (etat_actuel -> estVivante() == false) { 
        if (voisines_vivantes == 3) {
            return new EtatVivante();
        } else {
            return etat_actuel; 
        }
    }
};
