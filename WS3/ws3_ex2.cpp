#include <iostream>
#include <string>
using namespace std;

class piece {
    private :
        int nb_windows;
        string color;

    public :
        piece (int nb_windows , string color) : nb_windows(nb_windows) , color(color) {}
        
        int get_nb_windows () {
            return nb_windows;
        }

        string get_color () {
            return color;
        }

        void set_nb_windows (int new_nb_windows) {
            nb_windows = new_nb_windows;
        }

        void set_color (string new_color) {
            new_color = color;
        }

        virtual bool estChambre () {return false;}
        virtual bool estSalleDeBain () {return false;}

};

class salle_de_bain : public piece {
    private :
        bool has_Shower;
    public :
        salle_de_bain (int nb_windows, string color, bool has_Shower) : piece(nb_windows, color), has_Shower(has_Shower) {}

        int get_has_Shower () {
            return has_Shower;
        }

        void set_has_Shower (bool new_has_Shower) {
            has_Shower = new_has_Shower;
        }

        bool estSalleDeBain () override {return true;}
};

class chambre : public piece {
    private :
        int nb_beds;
    public :
        chambre (int nb_windows, string color, int nb_beds) : piece(nb_windows, color), nb_beds(nb_beds) {}

        int get_nb_beds () {
            return nb_beds;
        }

        void set_nb_beds (int new_nb_beds) {
            nb_beds = new_nb_beds;
        }

        bool estChambre () override {return true;}
};


class maison {
    private :
        piece** rooms;
        int nb_pieces;
        int count;

    public :
        maison(int nb_pieces1) : nb_pieces(nb_pieces1) {
        rooms = new piece *[nb_pieces];
        count = 0;
        }

        void set_nb_pieces (int new_nb_pieces) {
            nb_pieces = new_nb_pieces;
        }

        int get_nb_pieces () {
            return nb_pieces;
        }

        void add_room (piece* new_room) {
            if (count < nb_pieces) {
                rooms[count] = new_room;
                count++;
            } else {
                cout << "Maison pleine, impossible d'ajouter une nouvelle piece." << endl;
            }
        }

    void getNbOfBathroom () {
        int nb_bathroom = 0;
        for (int i = 0; i < count; i++) { 
            if (rooms[i]->estSalleDeBain()) { 
                nb_bathroom+=1;
            }
        }
        cout << "Nombre de salles de bain : " << nb_bathroom << endl;
    }

    void getNbOfBedroom () {
        int nb_bedroom = 0;
        for (int i = 0; i < count; i++) { 
            if (rooms[i]->estChambre()) { 
                nb_bedroom+=1;
            }
        }
        cout << "Nombre de chambres : " << nb_bedroom << endl;
    }
};

int main() {
    // 1. Création de la maison avec une capacité de 5 pièces
    // L'allocation du tableau de pointeurs piece* est faite ici.
    cout << "--- Initialisation : Creation de la maison avec 5 emplacements ---" << endl;
    maison ma_maison_test(5); 

    // 2. Création et ajout des pièces (allouées dynamiquement)
    // Nous utilisons 'new' pour creer les objets sur le tas (heap)
    cout << "--- Remplissage : Ajout des pieces ---" << endl;
    
    // Pièce 1 : Salle de Bain avec douche
    cout << "Ajout de SDB 1 (Douche)..." << endl;
    ma_maison_test.add_room(new salle_de_bain(1, "Blanc", true)); 
    
    // Pièce 2 : Chambre (2 lits)
    cout << "Ajout de Chambre 1 (2 lits)..." << endl;
    ma_maison_test.add_room(new chambre(2, "Bleu Ciel", 2)); 
    
    // Pièce 3 : Chambre (1 lit)
    cout << "Ajout de Chambre 2 (1 lit)..." << endl;
    ma_maison_test.add_room(new chambre(3, "Jaune Soleil", 1)); 
    
    // Pièce 4 : Salle de Bain sans douche
    cout << "Ajout de SDB 2 (Baignoire)..." << endl;
    ma_maison_test.add_room(new salle_de_bain(1, "Gris", false)); 

    // 3. Affichage des détails de chaque pièce (Test du Polymorphisme)
    // ma_maison_test.display_all_rooms(); 

    // 4. Test des méthodes de la Question c) (Comptage Polymorphique)
    cout << "\n--- Comptage des Pieces (Question c) ---" << endl;
    ma_maison_test.getNbOfBathroom(); // Devrait afficher 2
    ma_maison_test.getNbOfBedroom();  // Devrait afficher 2
    
    // 5. La destruction de 'ma_maison_test' à la fin de 'main' appelle le destructeur ~maison().
    // Ce destructeur s'occupe de la liberation de TOUTE la memoire allouee (tableau rooms + toutes les pieces).
    cout << "\n--- Fin de l'execution ---" << endl;
    cout << "L'objet 'ma_maison_test' est detruit, liberant toute la memoire (grace au destructeur et au destructeur virtuel de 'piece')." << endl;
    
    return 0;
}