#include <iostream>
#include <string>
#include <vector>
#include <ostream>


using namespace std;




#include <iostream>
#include <vector>
#include <algorithm> // Non essentiel ici, mais bonne pratique

using namespace std;

// --- 1. Fonction d'affichage dédiée ---
// Affiche le contenu du vecteur de manière lisible.
void afficher_tableau(const vector<int>& tab) {
    cout << "[";
    for (size_t i = 0; i < tab.size(); ++i) {
        cout << tab[i];
        if (i < tab.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}

// --- 2. Fonction de Tri par Insertion ---
void tri_insertion (vector<int> &l) {
    
    cout << "--- DEBUT DU TRI PAR INSERTION ---" << endl;
    cout << "Tableau initial : ";
    afficher_tableau(l);
    cout << endl;

    // La boucle commence à i=1 (le 2e élément)
    for (size_t i = 1; i < l.size(); ++i) { 
        int v = l[i];
        int j = (int)i; 
        
        // Phase de décalage et de comparaison
        while (j > 0 && l[j - 1] > v) {
            l[j] = l[j - 1];
            j = j - 1;
        }
        
        // Phase d'insertion
        l[j] = v;
        
        // Affichage de l'état après l'insertion de l'élément l[i]
        cout << "  > Étape " << i << " : ";
        afficher_tableau(l);
        cout << endl;
    }

    cout << "--- FIN DU TRI ---" << endl;
};

int main () {
    vector<int> Test = {9,6,8,7,1,3,4,5,2,0};
    tri_insertion(Test);
    return 0;
};

