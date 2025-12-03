#include "Jeu.hpp"
#include "Grille.hpp"
#include "ReglesJeu.hpp"
#include <iostream>
#include <fstream>
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

JeuDeLaVie::JeuDeLaVie(const string& nomFichierConfig) {
    GridData config = lireConfiguration(nomFichierConfig);
    
    if (config.empty() || config[0].empty()) {
        grille = nullptr;
        throw runtime_error("Le fichier de configuration est vide.");
    }

    // Étape 2 : Calculer la hauteur et la longueur
    int hauteur = config.size();         
    int longueur = config[0].size(); 

    this->grille = new Grille(longueur, hauteur); 

    // Étape 4 : INITIALISER les Cellules
    // On appelle la méthode init() de l'objet Grille pour qu'il
    // remplisse sa matrice de Cellule avec les états 1 ou 0.
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
        cout << "n\--- Generation " << i + 1 << "---" << endl;

        for (ObservateurGrille* obs : observateurs) {
            obs->notifierChangement(*grille);
        }

        Grille* Grille::calculerProchaineGeneration(Grille&);
        
    }
}
