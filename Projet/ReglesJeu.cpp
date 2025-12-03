#include <iostream>
#include <vector>
#include <algorithm>
#include <ReglesJeu.hpp>
using namespace std;




int ReglesJeu::appliquerRegles(int etat_actuel, int voisines_vivantes) {
    if (etat_actuel == 1) { // VIVANTE
        // Survie si 2 OU 3 voisines
        if (voisines_vivantes == 2 || voisines_vivantes == 3) {
            return 1; 
        } else {
            return 0; // Mort
        }
    } else { // MORTE
        // Naissance si EXACTEMENT 3 voisines
        if (voisines_vivantes == 3) {
            return 1; // Naissance
        } else {
            return 0; // Reste Morte
        }
    }
}
