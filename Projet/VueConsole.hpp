#ifndef VUECONSOLE_H
#define VUECONSOLE_H
#include "ObservateurGrille.hpp"
#include <chrono>
#include <thread>

class VueConsole : public ObservateurGrille {
    public :
        // MODIFICATION: Suppression du délai local et des méthodes associées
        VueConsole() {} 

        void notifierChangement(const Grille& grille) override;

    // private: // SUPPRIME
    //    float delai; // SUPPRIME
};


#endif