#include "Grille.hpp"
#include <stdexcept>
using namespace std;

// Constructeur : initialise la grille avec des cellules par défaut
Grille::Grille(size_t largeur, size_t hauteur)
    : largeur_(largeur), hauteur_(hauteur),
      cellules_(hauteur, vector<Cellule>(largeur))
{}

// Accesseurs dimensionnels
size_t Grille::getLargeur() const { return largeur_; }
size_t Grille::getHauteur() const { return hauteur_; }

// Accès aux cellules (vérification des bornes)
const Cellule& Grille::getCellule(size_t x, size_t y) const {
    if (x >= largeur_ || y >= hauteur_) {
        throw out_of_range("Grille::getCellule : indices hors limites");
    }
    return cellules_[y][x];
}

Cellule& Grille::getCellule(size_t x, size_t y) {
    if (x >= largeur_ || y >= hauteur_) {
        throw out_of_range("Grille::getCellule : indices hors limites");
    }
    return cellules_[y][x];
}

// Modifier l'état d'une cellule
void Grille::setCelluleVivante(size_t x, size_t y, bool vivante) {
    if (x >= largeur_ || y >= hauteur_) return;
    cellules_[y][x].setVivante(vivante); // adapte si la méthode a un autre nom
}

// Observateurs
void Grille::ajouterObservateur(ObservateurGrille* obs) {
    if (!obs) return;
    if (find(observateurs_.begin(), observateurs_.end(), obs) == observateurs_.end()) {
        observateurs_.push_back(obs);
    }
}

void Grille::retirerObservateur(ObservateurGrille* obs) {
    observateurs_.erase(remove(observateurs_.begin(), observateurs_.end(), obs), observateurs_.end());
}

void Grille::notifierObservateurs() const {
    for (auto obs : observateurs_) {
        if (obs) obs->notifierChangement(*this);
    }
}

// --- 1. Compter les voisines vivantes (Comptage Toroidal) ---
int ReglesJeu::compterVoisinesVivantes(int ligne, int colonne, const Grid& grille) {
    int live_neighbors = 0;
    int rows = grille.size();
    if (rows == 0) return 0;
    int cols = grille[0].size();

    // Parcourir les 9 positions autour de la cellule
    for (int r = ligne - 1; r <= ligne + 1; ++r) {
        for (int c = colonne - 1; c <= colonne + 1; ++c) {
            
            // Ignorer la cellule centrale
            if (r == ligne && c == colonne) {
                continue;
            }

            // Gestion Toroidale : assure que r_toroidal et c_toroidal sont toujours dans les limites [0, rows/cols - 1]
            int r_toroidal = (r + rows) % rows;
            int c_toroidal = (c + cols) % cols;
            
            live_neighbors += grille[r_toroidal][c_toroidal];
        }
    }
    return live_neighbors;
}

// --- 3. Calculer le prochain tour ---
Grid ReglesJeu::prochainTour(const Grid& grille_actuelle) {
    if (grille_actuelle.empty()) return {};
    int lignes = grille_actuelle.size();
    int colonnes = grille_actuelle[0].size();

    // Création de la grille future
    Grid grille_future(lignes, std::vector<int>(colonnes)); 

    // Boucle sur chaque cellule
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            
            int N = compterVoisinesVivantes(i, j, grille_actuelle);
            int etat_actuel = grille_actuelle[i][j];
            
            // Appliquer la logique et stocker dans la grille future
            grille_future[i][j] = appliquerRegles(etat_actuel, N);
        }
    }
    
    return grille_future; 
}