#include "EtatMort.hpp"
#include "EtatVivant.hpp" 

ReglesConway EtatMort::regles;

EtatCellule* EtatMort::calculerProchainEtat(int voisins) {
    if (regles.verifierSurvie(voisins, false)) { 
        return EtatVivant::getInstance(); 
    }
    return EtatMort::getInstance();
}

EtatMort* EtatMort::getInstance() {
    static EtatMort instance;
    return &instance;
}