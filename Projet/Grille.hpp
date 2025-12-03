#ifndef GRILLE_H
#define GRILLE_H

#include "Cellule.hpp"
#include <vector> 
#include <memory> // Pour std::unique_ptr

// Définitions de types pour plus de clarté
using CellPtr = std::unique_ptr<Cellule>;
using GridRow = std::vector<CellPtr>;
using GridData = std::vector<std::vector<int>>; 

class Grille {
private:
    // La matrice de cellules est gérée par des vecteurs de pointeurs uniques (RAII)
    std::vector<GridRow> cellules; 
    int longueur;
    int hauteur;
    
public:
    Grille(int longueur, int hauteur);
    // Le destructeur par défaut (~Grille() = default;) est suffisant, 
    // car std::vector et std::unique_ptr s'occupent de la libération de toutes les Cellules.
    ~Grille() = default; 

    // L'allocation et l'initialisation sont combinées
    void init(const GridData& donnees); 
 
    int getVoisinsVivants(int x, int y) const;
    void evoluer();

    // Renvoie un pointeur brut (non responsable de la mémoire) pour consultation
    Cellule* getCellule(int x, int y) const; 
    
    int getLongueur() const;
    int getHauteur() const;
    void afficherGrille() const; // Ajout pour la démonstration
};

#endif