#include "VueConsole.hpp"
#include <iostream>
#include "Grille.hpp"

using namespace std;

void VueConsole::notifierChangement(const Grille& grille){
    cout << "--- Nouvelle Génération ---" << endl;
    for (int y = 0; y < grille.getHauteur(); y++) {
        for (int x = 0; x < grille.getLongueur(); x++) {
            Cellule* cell = grille.getCellule(x, y);

            if (cell->estObstacle()) {
                if (cell->estVivante()) {
                    cout << "X";
                } else {
                    cout << "0";
                }
            }
            else if (cell->estVivante()) { 
                cout << "■";
            }
            else { 
                cout << "□";
            }
        }
        cout << endl;
    }

    // Respecter le délai configuré pour la console
    this_thread::sleep_for(chrono::milliseconds(static_cast<int>(delai * 1000)));
}


