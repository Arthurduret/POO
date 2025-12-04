#include "Jeu.hpp"
#include "VueGraphique.hpp"
#include "VueConsole.hpp"
#include <iostream>
#include <string>
#include <algorithm> // AJOUT: Pour std::min/max/clamp si nécessaire

int main() {
    try {
        std::string configFile;
        int iterations = 0;
        int choice = 0;
        
        // AJOUT/MODIFICATION: Délai initial fixé sur JeuDeLaVie.
        float initialDelai = 0.5f; 
        
        // Demander le fichier de configuration
        std::cout << "=== Jeu de la Vie ===" << std::endl;
        std::cout << "Entrez le fichier de configuration (défaut: configuration.txt) : ";
        std::getline(std::cin, configFile);
        if (configFile.empty()) {
            configFile = "configuration.txt";
        }

        // Créer le jeu
        JeuDeLaVie jeu(configFile);
        // AJOUT: Définir le délai initial sur l'objet JeuDeLaVie
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

        // Suppression du prompt du délai

        // Créer et ajouter les observateurs
        VueConsole* vueConsole = nullptr;
        VueGraphique* vueGraphique = nullptr;

        if (choice == 1 || choice == 3) {
            // MODIFICATION: Taille ajustée pour laisser de l'espace à l'interface (600x600 pour la grille + 200 pour UI) et passage de 'jeu'
            vueGraphique = new VueGraphique(600, 600, 10.f, &jeu);
            jeu.ajouterObservateur(vueGraphique);
            std::cout << "Vue Graphique activée (délai initial: " << jeu.getDelai() << "s). La vitesse peut être contrôlée via les boutons de l'interface." << std::endl;
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
        std::cout << "Utilisez les boutons 'PAUSE' et 'REPRENDRE' sur la fenêtre graphique." << std::endl;


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