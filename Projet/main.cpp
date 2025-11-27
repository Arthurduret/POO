#include "Jeu.hpp"
#include <iostream>

int main() {
    // 1. Définir une configuration initiale (Exemple du Glider 5x5)
    std::vector<std::vector<int>> configurationInitiale = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    try {
        // 2. Créer l'objet Jeu (5x5)
        Jeu game(5, 5);

        // 3. Initialiser la grille
        game.initialiserJeu(configurationInitiale);

        // 4. Lancer la simulation pour 10 générations
        std::cout << "Demarrage du Jeu de la Vie de Conway.\n";
        game.lancer(10);
    } catch (const std::exception& e) {
        std::cerr << "Erreur critique: " << e.what() << std::endl;
    }

    return 0;

    return 0;
}