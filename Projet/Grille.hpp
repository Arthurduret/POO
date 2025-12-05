#ifndef GRILLE_H
#define GRILLE_H

#include "Cellule.hpp"
#include <vector> 
#include <memory> // Pour std::unique_ptr
#include <stdexcept> // Pour std::runtime_error (bonne pratique même si non utilisé directement par Grille::hpp)

// Définitions de types pour plus de clarté
using CellPtr = std::unique_ptr<Cellule>;
using GridRow = std::vector<CellPtr>;
using GridData = std::vector<std::vector<int>>; 

class Grille {
private:
    // La matrice de cellules est gérée par des vecteurs de pointeurs uniques (RAII)
    std::vector<GridRow> cellules; 
    int longueur; // Corrigé : Type int pour être cohérent avec l'implémentation
    int hauteur;  // Corrigé : Type int pour être cohérent avec l'implémentation
    
public:
    // Constructeur
    Grille(int longueur, int hauteur);

    // Destructeur par défaut : suffisant grâce à std::unique_ptr
    ~Grille() = default; 

    // L'allocation et l'initialisation sont combinées
    void init(const GridData& donnees); 
 
    // Mises à jour du jeu de la vie
    int getVoisinsVivants(int x, int y) const;
    void evoluer(); // Déclaration de la fonction d'évolution

    // Accesseur avec gestion toroïdale
    Cellule* getCellule(int x, int y) const; 
    
    // Accesseurs
    int getLongueur() const;
    int getHauteur() const;

    // Verifier etat stable
    std::string getSnapshot() const; 
    
    // Affichage pour la console (utilisé par VueConsole)
    void afficherGrille() const; 
};

#endif