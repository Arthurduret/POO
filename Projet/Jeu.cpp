#include "Jeu.hpp"
#include "Grille.hpp"
#include "ReglesJeu.hpp"
#include <iostream>
#include <fstream>
#include <vector> 
#include <chrono>   // AJOUT
#include <thread>   // AJOUT

using namespace std;
using GridData = vector<vector<int>>;

// ... (lireConfiguration, JeuDeLaVie::JeuDeLaVie, JeuDeLaVie::~JeuDeLaVie, JeuDeLaVie::ajouterObservateur inchangés)

GridData JeuDeLaVie::lireConfiguration(const string& nomFichier) { /* ... (inchangé) ... */
    GridData configuration; 
    ifstream fichier(nomFichier);
    if (!fichier.is_open()) {   
    throw runtime_error("Impossible d'ouvrir le fichier de configuration : " + nomFichier);
    }
    string ligne;
    while (getline(fichier, ligne)) {
        vector<int> row;
        for (char c : ligne) {
            if (c == '1' || c == 'X') {
                row.push_back(1); // Cellule vivante
            } else if (c == '0' || c == '.') {
                row.push_back(0); // Cellule morte
            }
        }
        if (!row.empty()) {
            configuration.push_back(row);
        }
    }

    return configuration;
}

JeuDeLaVie::JeuDeLaVie(const string& nomFichierConfig) {
    GridData config = lireConfiguration(nomFichierConfig);
    
    if (config.empty() || config[0].empty()) {
        grille = nullptr;
        throw runtime_error("Le fichier de configuration est vide.");
    }

    // Étape 2 : Calculer la hauteur et la longueur
    int hauteur = (int)config.size();         
    int longueur = (int)config[0].size(); 

    this->grille = new Grille(longueur, hauteur); 

    // Étape 4 : INITIALISER les Cellules
    this->grille->init(config);
}

JeuDeLaVie::~JeuDeLaVie() {
    delete grille;
}

void JeuDeLaVie::ajouterObservateur(ObservateurGrille* vue) {
    observateurs.push_back(vue);
}


void JeuDeLaVie::lancer(int generations) {
    if (!grille) {
        cerr << "Erreur: Le jeu ne peut pas être lancé car la grille est invalide." << endl;
        return;
    }

    cout << "Demarrage du Jeu de la Vie de Conway pour " << generations << " generations.\n";

    for (int i = 0; i<generations; i++) {
        // AJOUT: Gestion de l'état de pause
        while (estEnPause) {
            // Dormir brièvement pour libérer la main et laisser VueGraphique gérer les événements
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        // Correction de l'affichage de la génération
        cout << "\n--- Generation " << i + 1 << "---" << endl; 

        // 1. Notifier les observateurs de l'état actuel (AVANT l'évolution)
        for (ObservateurGrille* obs : observateurs) {
            obs->notifierChangement(*grille);
        }

        // 2. Faire évoluer la grille
        grille->evoluer();
        
    }
    
    // Ajout : Afficher la dernière génération après que la boucle de jeu soit finie
    cout << "\n--- Fin du jeu ---" << endl;
    for (ObservateurGrille* obs : observateurs) {
        obs->notifierChangement(*grille);
    }
}