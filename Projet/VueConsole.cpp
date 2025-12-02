#include <VueConsole.hpp>
#include <iostream>
#include <Grille.hpp>
using namespace std;

VueConsole::notifierChangement(const Grille& grille){
    cout << "--- Nouvelle Génération ---" << endl;
    for (size_t y = 0; y < grille.getHauteur(); y++) {
        for (size_t x = 0; x < grille.getLargeur; x++) {
            if (grille.getCellule(x, y).estVivante()) {
                cout << "■";
            }
            else {
                cout << "□";
            }
        }
        cout << endl;
    }
};


