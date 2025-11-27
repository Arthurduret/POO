#include "EtatVivant.hpp"
#include "EtatMort.hpp" 

ReglesConway EtatVivant::regles;

EtatCellule* EtatVivant::calculerProchainEtat(int voisins) {
    if (regles.verifierSurvie(voisins, true)) { 
        return EtatVivant::getInstance(); 
    }
    return EtatMort::getInstance();
}

EtatVivant* EtatVivant::getInstance() {
    static EtatVivant instance;
    return &instance;
}