#include "Jeu.hpp"
#include "Grille.hpp"
#include "ReglesJeu.hpp"
#include "VueGraphique.hpp" // AJOUT: Pour le dynamic_cast dans la boucle de pause
#include <iostream>
#include <fstream>
#include <vector> 
#include <chrono>   
#include <thread>   
#include <algorithm> 

using namespace std;
using GridData = vector<vector<int>>;


GridData JeuDeLaVie::lireConfiguration(const string& nomFichier) { 
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

// MODIFICATION: Initialisation de nomFichierConfig
JeuDeLaVie::JeuDeLaVie(const string& nomFichierConfig) : nomFichierConfig(nomFichierConfig) { 
    GridData config = lireConfiguration(nomFichierConfig);
    
    if (config.empty() || config[0].empty()) {
        grille = nullptr;
        throw runtime_error("Le fichier de configuration est vide.");
    }

    int hauteur = (int)config.size();         
    int longueur = (int)config[0].size(); 

    this->grille = new Grille(longueur, hauteur); 

    this->grille->init(config);
}

JeuDeLaVie::~JeuDeLaVie() {
    delete grille;
}

void JeuDeLaVie::ajouterObservateur(ObservateurGrille* vue) {
    observateurs.push_back(vue);
}

// NOUVEAU: Logique pour réinitialiser la grille
void JeuDeLaVie::resetGrille() {
    if (!grille) return;
    
    // 1. Lire la configuration initiale
    GridData config = lireConfiguration(nomFichierConfig);
    
    if (config.empty() || config[0].empty()) {
        cerr << "Erreur: Impossible de recharger la configuration de la grille." << endl;
        return;
    }

    // 2. Supprimer l'ancienne grille et en créer une nouvelle
    delete grille; 
    
    int hauteur = (int)config.size();         
    int longueur = (int)config[0].size(); 

    this->grille = new Grille(longueur, hauteur); 
    this->grille->init(config);
    
    // 3. Reprendre le jeu (si l'utilisateur clique sur Redémarrer, il veut relancer)
    reprendre();
    
    // 4. Forcer un affichage immédiat de la grille réinitialisée
    for (ObservateurGrille* obs : observateurs) {
        obs->notifierChangement(*grille);
    }
    
    cout << "\n--- Grille réinitialisée (Redémarrage) ---" << endl;
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
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            
            // Permet à la VueGraphique de continuer à gérer les événements (clics de souris) pendant la pause
            for (ObservateurGrille* obs : observateurs) {
                if (VueGraphique* vg = dynamic_cast<VueGraphique*>(obs)) {
                    vg->gererEvenements();
                }
            }
        }
        
        cout << "\n--- Generation " << i + 1 << "---" << endl; 

        // 1. Notifier les observateurs de l'état actuel (AVANT l'évolution)
        for (ObservateurGrille* obs : observateurs) {
            obs->notifierChangement(*grille);
        }

        // 2. Faire évoluer la grille
        grille->evoluer();
        
    }
    
    cout << "\n--- Fin du jeu ---" << endl;
    
    // Après la fin du jeu, on s'assure que la dernière vue est affichée.
    for (ObservateurGrille* obs : observateurs) {
        obs->notifierChangement(*grille);
    }
}