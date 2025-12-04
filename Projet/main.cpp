#include "Jeu.hpp"
#include "VueGraphique.hpp"
#include "VueConsole.hpp"
#include <iostream>
#include <string>

int main() {
    try {
        std::string configFile;
        int iterations = 0;
        int choice = 0;

        // Demander le fichier de configuration
        std::cout << "=== Jeu de la Vie ===" << std::endl;
        std::cout << "Entrez le fichier de configuration (défaut: configuration.txt) : ";
        std::getline(std::cin, configFile);
        if (configFile.empty()) {
            configFile = "configuration.txt";
        }

        // Créer le jeu
        JeuDeLaVie jeu(configFile);

        // Demander le nombre d'itérations
        std::cout << "Nombre d'itérations (générations) : ";
        std::cin >> iterations;
        if (iterations <= 0) iterations = 10;

        // Demander la vue
        std::cout << "\nChoisissez la vue :" << std::endl;
        std::cout << "1 - Vue Graphique (SFML)" << std::endl;
        std::cout << "2 - Vue Console" << std::endl;
        std::cout << "3 - Les deux" << std::endl;
        std::cout << "Choix (1-3) : ";
        std::cin >> choice;

        // Créer et ajouter les observateurs
        VueGraphique* vueGraphique = nullptr;
        VueConsole* vueConsole = nullptr;

        if (choice == 1 || choice == 3) {
            vueGraphique = new VueGraphique(800, 600, 10.f);
            jeu.ajouterObservateur(vueGraphique);
            std::cout << "Vue Graphique activée." << std::endl;
        }

        if (choice == 2 || choice == 3) {
            vueConsole = new VueConsole();
            jeu.ajouterObservateur(vueConsole);
            std::cout << "Vue Console activée." << std::endl;
        }

        if (choice < 1 || choice > 3) {
            std::cerr << "Choix invalide. Vue Console par défaut." << std::endl;
            vueConsole = new VueConsole();
            jeu.ajouterObservateur(vueConsole);
        }

        std::cout << "\nLancement du jeu avec " << iterations << " itérations..." << std::endl;

        // Lancer le jeu
        jeu.lancer(iterations);

        // Libérer la mémoire
        delete vueGraphique;
        delete vueConsole;

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}