#include "VueConsole.hpp"
#include <iostream>
#include "Grille.hpp"

using namespace std;

void VueConsole::notifierChangement(const Grille& grille){
    cout << "--- Nouvelle Génération ---" << endl;
    for (int y = 0; y < grille.getHauteur(); y++) {
        for (int x = 0; x < grille.getLongueur(); x++) {
            if (grille.getCellule(x, y)->estVivante()) {
                cout << "■";
            }
            else {
                cout << "□";
            }
        }
        cout << endl;
    }

    // Respecter le délai configuré pour la console
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delai * 1000)));
}


