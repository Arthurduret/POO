#ifndef VUECONSOLE_H
#define VUECONSOLE_H
#include "ObservateurGrille.hpp"
#include <chrono>
#include <thread>

class VueConsole : public ObservateurGrille {
    public :
        VueConsole() : delai(0.5f) {}

        void notifierChangement(const Grille& grille) override;

        void setDelai(float d) { delai = d; }
        float getDelai() const { return delai; }

    private:
        float delai;
};





#endif