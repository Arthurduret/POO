#include "TestsUnitaires.hpp"
#include "Cellule.hpp"
#include "ReglesJeu.hpp" 
#include <iostream>
#include <memory> 
#include <vector>

void TestUnitaires::afficherEtatGrille(const Grille& grille, const std::string& titre) {
    std::cout << "\n--- " << titre << " ---" << std::endl;
    for (int y = 0; y < grille.getHauteur(); ++y) {
        for (int x = 0; x < grille.getLongueur(); ++x) {
            Cellule* cell = grille.getCellule(x, y);

            // N\u00e9cessite que Cellule::estObstacle() et Cellule::estVivante() existent.
            if (cell->estObstacle()) {
                if (cell->estVivante()) {
                    std::cout << "X "; // Obstacle Vivant
                } else {
                    std::cout << "0 "; // Obstacle Mort
                }
            } else if (cell->estVivante()) {
                std::cout << "■ "; // Cellule standard Vivante
            } else {
                std::cout << "□ "; // Cellule standard Morte
            }
        }
        std::cout << std::endl;
    }
}


bool TestUnitaires::comparerGrille(const Grille& grille, const GridData& attendu) {
    if (grille.getHauteur() != (int)attendu.size() || grille.getLongueur() != (int)attendu[0].size()) {
        std::cerr << "Erreur: Les dimensions de la grille ne correspondent pas aux donn\u00e9es attendues." << std::endl;
        return false;
    }

    for (int y = 0; y < grille.getHauteur(); ++y) {
        for (int x = 0; x < grille.getLongueur(); ++x) {
            if (attendu[y][x] == 1 || attendu[y][x] == 0) { 
                Cellule* cell = grille.getCellule(x, y);
                
                if (!cell) continue;

                bool estVivante = cell->estVivante();
                bool estVivanteAttendue = (attendu[y][x] == 1);
                
                if (estVivante != estVivanteAttendue) {
                    std::cerr << "TEST ECHOUE A la position (" << x << ", " << y << "). "
                              << "Attendu: " << (estVivanteAttendue ? "Vivant" : "Mort")
                              << ", Reel: " << (estVivante ? "Vivant" : "Mort") << std::endl;
                    return false;
                }
            }
        }
    }
    return true;
}


bool TestUnitaires::testEvolutionBlinker() {
    std::cout << "\n[TEST] Lancement du Test Unitaire: Clignotant (Blinker) " << std::endl;

    GridData initial = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0}, 
        {0, 0, 1, 0, 0}, 
        {0, 0, 1, 0, 0}, 
        {0, 0, 0, 0, 0}
    };
    
    GridData attendu = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0}, 
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    std::unique_ptr<Grille> grille_ptr = std::make_unique<Grille>(5, 5); 
    grille_ptr->init(initial); 

    afficherEtatGrille(*grille_ptr, "ETAT INITIAL (t=0)");

    grille_ptr->evoluer();

    afficherEtatGrille(*grille_ptr, "ETAT FINAL (t=1)");

    if (comparerGrille(*grille_ptr, attendu)) {
        std::cout << " Reussite : Le Clignotant a correctement evolue." << std::endl;
        return true;
    } else {
        std::cerr << " ECHEC : Le Clignotant n'a PAS evolue comme prevu." << std::endl;
        return false;
    }
}


int TestUnitaires::lancerTestsUnitaires() {
    std::cout << " LANCEMENT DES TESTS UNITAIRES " << std::endl;

    bool result = testEvolutionBlinker();
    
    if (result) {
        std::cout << "RESUME : TOUS LES TESTS SONT PASSES." << std::endl;
        return 0;
    } else {
        std::cerr << "RESUME : UN OU PLUSIEURS TESTS ONT ECHOUE." << std::endl;
        return 1;
    }
}