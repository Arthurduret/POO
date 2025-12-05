#ifndef TESTSUNITAIRES_HPP
#define TESTSUNITAIRES_HPP

#include "Grille.hpp"
#include <vector>

using GridData = std::vector<std::vector<int>>;

class TestUnitaires {
private:
    static bool comparerGrille(const Grille& grille, const GridData& attendu);

    static void afficherEtatGrille(const Grille& grille, const std::string& titre);
    
    static bool testEvolutionBlinker();

    static bool testCompterVoisinsVivants();

public:
    static int lancerTestsUnitaires();
};

#endif 