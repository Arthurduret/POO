#include "Jeu.hpp"
#include "VueGraphique.hpp"
#include "VueConsole.hpp"
#include <iostream>

int main() {
    try {
        // Créer le jeu
        JeuDeLaVie jeu("configuration.txt");

        // Créer les vues
        VueGraphique vueGraphique(800, 600, 10.f);
        VueConsole vueConsole;

        // Ajouter les observateurs
        jeu.ajouterObservateur(&vueGraphique);
        jeu.ajouterObservateur(&vueConsole);

        // Lancer le jeu (100 générations)
        jeu.lancer(100);

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}