#ifndef VUECONSOLE_H
#define VUECONSOLE_H
#include <ObservateurGrille.hpp>

class VueConsole : public ObservateurGrille {
    protected :

    public :

        void notifierChangement(const Grille& grille) override;

};





#endif