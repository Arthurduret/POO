#ifndef ETATCELLULE_H
#define ETATCELLULE_H

class EtatMort;
class EtatVivant;

class EtatCellule {
public:
    virtual ~EtatCellule() = default;

    virtual EtatCellule* calculerProchainEtat(int voisins) = 0;
};


class EnsembleRegles {
public:
    virtual ~EnsembleRegles() = default;


    virtual bool verifierSurvie(int voisins, bool estVivant) = 0;
};


class ReglesConway : public EnsembleRegles {
public:
    bool verifierSurvie(int voisins, bool estVivant) override {
        if (estVivant) {
            return (voisins == 2 || voisins == 3); 
        } else {
            return (voisins == 3);
        }
    }
};

#endif