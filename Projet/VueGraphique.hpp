#ifndef VUEGRAPHIQUE_H
#define VUEGRAPHIQUE_H
#include "ObservateurGrille.hpp"

class VueGraphique : public ObservateurGrille {
    protected :

    public :
        void notifierChangement(const Grille& grille) override;

};



#endif