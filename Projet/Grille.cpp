// Grille.cpp

#include "Grille.hpp"
#include "EtatVivante.hpp" 
#include "EtatMorte.hpp"   
#include <iostream>
#include <stdexcept>
#include <utility> // Pour std::move, mais non requis avec make_unique

// Implémentation du Constructeur
Grille::Grille(int longueur, int hauteur) 
    : longueur(longueur), hauteur(hauteur) 
{
    // Rien à faire ici, les membres sont initialisés.
}

// Implémentation de l'Initialisation (Allocation et Création des Cellules)
void Grille::init(const GridData& donnees) {
    if (donnees.empty() || donnees[0].empty()) {
        throw std::invalid_argument("La configuration initiale est vide.");
    }
    
    int dataHauteur = donnees.size();
    int dataLongueur = donnees[0].size();
    
    if (dataHauteur != hauteur || dataLongueur != longueur) {
        throw std::invalid_argument("Dimensions de la configuration initiale incompatibles.");
    }

    // Réinitialisation de la grille vectorielle
    cellules.clear();
    cellules.resize(hauteur);
    
    for (int y = 0; y < hauteur; ++y) {
        cellules[y].reserve(longueur);
        for (int x = 0; x < longueur; ++x) {
            
            // On utilise les Singletons pour l'état initial (1 = Vivant, 0 = Mort)
            EtatCellule* etatInitial = (donnees[y][x] == 1) 
                                       ? EtatVivante::getInstance() 
                                       : EtatMorte::getInstance();
            
            // Création de Cellule via make_unique et insertion dans le vecteur
            cellules[y].push_back(std::make_unique<Cellule>(etatInitial));
        }
    }
}


// Implémentation de la logique spatiale (Calcul des voisins, identique)
int Grille::getVoisinsVivants(int x, int y) const {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; ++i) { 
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; 

            int voisinX = x + j;
            int voisinY = y + i;

            if (voisinX >= 0 && voisinX < longueur && 
                voisinY >= 0 && voisinY < hauteur) 
            {
                Cellule* voisin = getCellule(voisinX, voisinY);
                // Utilisation du proxy estVivant()
                if (voisin && voisin->estVivant()) { 
                    voisinsVivants++;
                }
            }
        }
    }
    return voisinsVivants;
}

// Implémentation de la logique temporelle (Application du Patron State)
void Grille::evoluer() {
    // PREMIÈRE PASSE : Calcul des états futurs
    // On stocke temporairement les pointeurs des Singletons des états futurs
    std::vector<std::vector<EtatCellule*>> futursEtats(hauteur, std::vector<EtatCellule*>(longueur));
    
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < longueur; ++x) {
            Cellule* celluleActuelle = cellules[y][x].get();
            int voisinsVivants = getVoisinsVivants(x, y); 
            
            // L'état actuel de la cellule calcule l'état futur (Polymorphisme)
            EtatCellule* nouvelEtat = celluleActuelle->calculerProchainEtat(voisinsVivants);
            futursEtats[y][x] = nouvelEtat;
        }
    }

    // DEUXIÈME PASSE : Application des nouveaux états
    // On met à jour le pointeur interne de chaque Cellule vers le nouveau Singleton
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < longueur; ++x) {
            cellules[y][x]->majEtat(futursEtats[y][x]);
        }
    }
}

// Implémentation des accesseurs
Cellule* Grille::getCellule(int x, int y) const {
    if (x >= 0 && x < longueur && y >= 0 && y < hauteur) {
        // Retourne le pointeur brut contenu dans l'unique_ptr
        return cellules[y][x].get(); 
    }
    return nullptr;
}

int Grille::getLongueur() const { return longueur; }
int Grille::getHauteur() const { return hauteur; }

// Ajout pour l'affichage (Vue simple)
void Grille::afficherGrille() const {
    std::cout << "--------------------" << std::endl;
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < longueur; ++x) {
            // Utilisation du proxy getRepresentation() (Polymorphisme)
            std::cout << cellules[y][x]->getRepresentation() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}