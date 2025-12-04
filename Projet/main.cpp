#include "Jeu.hpp"
#include "VueGraphique.hpp"
#include "VueConsole.hpp"
#include <iostream>
#include <string>
#include <algorithm> 

int main() {
    try {
        std::string configFile;
        int iterations = 0;
        int choice = 0;
        
        float initialDelai = 0.5f; 
        
        std::cout << "=== Jeu de la Vie ===" << std::endl;
        std::cout << "Entrez le fichier de configuration (défaut: configuration.txt) : ";
        std::getline(std::cin, configFile);
        if (configFile.empty()) {
            configFile = "configuration.txt";
        }

        // Créer le jeu
        JeuDeLaVie jeu(configFile);
        jeu.setDelai(initialDelai);


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
        VueConsole* vueConsole = nullptr;
        VueGraphique* vueGraphique = nullptr;

        if (choice == 1 || choice == 3) {
            // MODIFICATION: Taille ajustée (600x600 pour la grille + 200 pour UI) et passage de '&jeu'
            vueGraphique = new VueGraphique(600, 600, 10.f, &jeu);
            jeu.ajouterObservateur(vueGraphique);
            std::cout << "Vue Graphique activée (délai initial: " << jeu.getDelai() << "s). Contrôles par boutons." << std::endl;
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
        std::cout << "Le jeu est initialisé en PAUSE. Utilisez le bouton 'REPRENDRE' ou 'REDÉMARRER' dans la fenêtre graphique pour commencer." << std::endl;


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