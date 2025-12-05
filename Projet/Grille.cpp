#include "Grille.hpp"
#include "Cellule.hpp"
#include "EtatVivante.hpp"
#include "EtatMorte.hpp"
#include "EtatObstacleVivant.hpp"
#include "EtatObstacleMort.hpp"
#include "ReglesJeu.hpp" 
#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory> // AJOUTÉ : Nécessaire pour std::unique_ptr et std::make_unique
#include <utility> // AJOUTÉ : Nécessaire pour std::move
#include <sstream> // NÉCESSAIRE pour construire la chaîne de l'etat stable

using namespace std;

const int OBSTACLE_VIVANT = 2;
const int OBSTACLE_MORT = 3;


Grille::Grille(int longueur, int hauteur): longueur(longueur), hauteur(hauteur) {}

int Grille::getLongueur() const { return longueur; }
int Grille::getHauteur() const { return hauteur; }

void Grille::init(const GridData& donnees) {
    if (donnees.empty() || donnees[0].empty()) {
        throw std::runtime_error("Configuration de grille invalide.");
        }

    int hauteur_config = (int)donnees.size();
    int longueur_config = (int)donnees[0].size(); 

    cellules.resize(hauteur_config);

    for (int y = 0; y < hauteur_config; ++y) {
        cellules[y].reserve(longueur_config); 
        for (int x = 0; x < longueur_config; ++x) {
            // Utilisation de std::make_unique pour allouer la Cellule
            CellPtr nouvelle_cellule = make_unique<Cellule>();
            EtatCellule* nouvel_etat = nullptr;

            int config_val = donnees[y][x];

            // CHOISIR L'ÉTAT INITIAL EN INCLUANT LES OBSTACLES 
            if (config_val == 1) { 
                nouvel_etat = new EtatVivante(); // Cellule Vivante 
            } else if (config_val == 0) {
                nouvel_etat = new EtatMorte();   // Cellule Morte 
            } else if (config_val == 2) { //  Obstacle Vivant
                nouvel_etat = new EtatObstacleVivant();
            } else if (config_val == 3) { //  Obstacle Mort
                nouvel_etat = new EtatObstacleMort();
            } else {
                // Valeur inconnue
                nouvel_etat = new EtatMorte();
            }

            if (nouvel_etat != nullptr) {
                nouvelle_cellule->setEtat(nouvel_etat);
            }

        // Ajouter et transférer la propriété (std::move)
            cellules[y].push_back(std::move(nouvelle_cellule));
        }
    }
    this->hauteur = hauteur_config;
    this->longueur = longueur_config;
}


Cellule* Grille::getCellule(int x, int y) const {
    if (cellules.empty()) {
        return nullptr;
    }
    
    // Géométrie Toroidale : assure le wrapping
    int y_toroidal = (y % hauteur + hauteur) % hauteur;
    int x_toroidal = (x % longueur + longueur) % longueur;
    
    return cellules[y_toroidal][x_toroidal].get();
}


int Grille::getVoisinsVivants(int x, int y) const {
    int voisinsVivants = 0;
    
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) {
                continue;
            }

            Cellule* voisin = getCellule(x + dx, y + dy);
            
            if (voisin && voisin->estVivante()) {
                voisinsVivants++;
            }
        }
    }
    return voisinsVivants;
}


void Grille::evoluer() {
    if (cellules.empty()) return;

    ReglesJeu regles;
    vector<vector<EtatCellule*>> prochainsEtats(hauteur, vector<EtatCellule*>(longueur));
    
    // 1. Calculer les états futurs (sans modifier la grille actuelle)
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < longueur; ++x) {
            Cellule* celluleActuelle = cellules[y][x].get();
            int voisins = getVoisinsVivants(x, y);
            
            EtatCellule* etatFutur = regles.appliquerRegles(celluleActuelle->getEtat(), voisins);
            
            if (etatFutur == celluleActuelle->getEtat()) {
                prochainsEtats[y][x] = nullptr; 
            } else {
                prochainsEtats[y][x] = etatFutur; 
            }
        }
    }
    
    // 2. Appliquer les nouveaux états
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < longueur; ++x) {
            EtatCellule* nouvelEtat = prochainsEtats[y][x];
            
            if (nouvelEtat != nullptr) {
                cellules[y][x]->setEtat(nouvelEtat);
            }
        }
    }
}

string Grille::getSnapshot() const {
    stringstream ss;

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < longueur; ++x) {
            Cellule* cell = getCellule(x, y);
            
            // Utilise les memes valeurs que la sauvegarde (0, 1, 2, 3) pour l'unicité
            if (cell->estObstacle()) {
                ss << (cell->estVivante() ? '2' : '3');
            } else {
                ss << (cell->estVivante() ? '1' : '0');
            }
        }
    }
    return ss.str();
}


void Grille::afficherGrille() const {
    std::cout << "--- Affichage de la Grille ---" << std::endl;
    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < longueur; x++) {
            Cellule* cell = getCellule(x, y);

            if (cell && cell->estObstacle()) {
                if (cell->estVivante()) {
                    cout << "X";
                }
                else {
                    cout << "0";
                }
            }
            else if (cell && cell->estVivante()) {
                cout << "■";
            }
            else {
                cout << "□";
            }
        }
        cout << endl;
    }
}