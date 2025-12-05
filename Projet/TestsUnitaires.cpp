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



bool TestUnitaires::testCompterVoisinsVivants() {
    std::cout << "\n[TEST] Lancement du Test Unitaire: Compte des Voisins " << std::endl;

    // Grille 3x3 simple pour les tests
    GridData grille_test = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };
    
    // Initialisation
    std::unique_ptr<Grille> grille_ptr = std::make_unique<Grille>(3, 3);
    grille_ptr->init(grille_test); 

    afficherEtatGrille(*grille_ptr, "CONFIGURATION DE LA GRILLE TESTEE (3x3)");

    bool reussite = true;
    int resultat_reel;
    int attendu;

    attendu = 8;
    resultat_reel = grille_ptr->getVoisinsVivants(1, 1);
    
    std::cerr <<"Nombre de voisins trouvés : " << resultat_reel << ". Nombre de voisins attendus : " << attendu << std::endl;

    if (resultat_reel != attendu) {
        std::cerr << " ECHEC Voisinage. Attendu: " << attendu << ", Reel: " << resultat_reel << std::endl;
        reussite = false;
    } else {
        std::cout << " Reussite Voisinage." << std::endl;
    }

    return reussite;
}


int TestUnitaires::lancerTestsUnitaires() {
    std::cout << " LANCEMENT DES TESTS UNITAIRES " << std::endl;

    int total_tests = 0;
    int tests_echoues = 0;

    // Executer les tests
    if (!testCompterVoisinsVivants()) {
        tests_echoues++;
    }
    total_tests++;

    if (!testEvolutionBlinker()) {
        tests_echoues++;
    }
    total_tests++;

    
    if (tests_echoues == 0) {
        std::cout << " RESUME : TOUS LES " << total_tests << " TESTS SONT PASSES." << std::endl;
        return 0;
    } else {
        std::cerr << " RESUME : " << tests_echoues << "/" << total_tests << " TESTS ONT ECHOUE." << std::endl;
        return 1;
    }
}