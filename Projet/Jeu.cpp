#include "Jeu.hpp"
#include "Grille.hpp"
#include "ReglesJeu.hpp"
#include "EtatObstacleVivant.hpp"
#include "EtatObstacleMort.hpp"

#include <algorithm> // NÉCESSAIRE pour std::find
#include <iostream>
#include <fstream>
#include <sstream> // NÉCESSAIRE pour construire le nom de fichier de sortie
#include <filesystem>   // NÉCESSAIRE pour créer le dossier
#include <vector> // Nécessaire pour GridData

using namespace std;
using GridData = vector<vector<int>>;


GridData JeuDeLaVie::lireConfiguration(const string& nomFichier) { 
    GridData configuration; 
    ifstream fichier(nomFichier);
    std::cerr << "Tente d'ouvrir le fichier : [" << nomFichier << "]" << std::endl;
    if (!fichier.is_open()) {   
    throw runtime_error("Impossible d'ouvrir le fichier de configuration : " + nomFichier);
    }
    string ligne;
    while (getline(fichier, ligne)) {
        vector<int> row;
        for (char c : ligne) {
            if (c == '1') {
                row.push_back(1); // Cellule vivante
            }
            
            if (c == '2') {
                row.push_back(2); //Obstacle vivant
            }

            if (c== '3') {
                row.push_back(3); //Obstacle mort
            }
            
            else if (c == '0') {
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

    // Calculer la hauteur et la longueur
    int hauteur = (int)config.size();         
    int longueur = (int)config[0].size(); 

    this->grille = new Grille(longueur, hauteur); 

    // INITIALISER les Cellules
    this->grille->init(config);

    this->nomFichierSortie = nomFichierConfig + "_out";
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

    // Initialisation de l'historique
    historiqueEtats.clear();
    
    for (int i = 0; i<generations; i++) {
        
        // Detection du cycle
        string etat_actuel_snapshot = grille->getSnapshot();
        
        // Recherche de l'état actuel dans l'historique
        auto it = find(historiqueEtats.begin(), historiqueEtats.end(), etat_actuel_snapshot);
        
        if (it != historiqueEtats.end()) {
            // Si un cycle a été trouvé 

            size_t generation_cycle = std::distance(historiqueEtats.begin(), it) + 1;

            cout << "SIMULATION ARRETEE : Etat stable ou oscillant detecte " << endl;
            cout << "L'état de la génération " << i + 1 << " est identique a celui de la generation " << generation_cycle << "." << endl;
            
            // Afficher l'état final avant l'arrêt
            for (ObservateurGrille* obs : observateurs) {
                obs->notifierChangement(*grille);
            }
            
            return; 
        }

        // Mise à jour de l'historique (si pas de cycle trouve)
        historiqueEtats.push_back(etat_actuel_snapshot);
        if (historiqueEtats.size() > maxHistorySize) {
            historiqueEtats.erase(historiqueEtats.begin()); // Supprimer l'état le plus ancien
        }


        // Affichage et évolution (comme avant)
        cout << "\n--- Generation " << i + 1 << "---" << endl; 
        for (ObservateurGrille* obs : observateurs) {
            obs->notifierChangement(*grille);
        }
        
        sauvegarderGrille(*grille, i + 1);
        grille->evoluer();
    }
    
    // Afficher la dernière génération après que la boucle de jeu soit finie
    cout << "\n--- Fin du jeu ---" << endl;
    for (ObservateurGrille* obs : observateurs) {
        obs->notifierChangement(*grille);
    }
}




void JeuDeLaVie::sauvegarderGrille(const Grille& grille, int generation) const {
    
    // Définir le chemin du dossier
    filesystem::path dir_path = this->nomFichierSortie;

    // Creer le dossier
    filesystem::create_directories(dir_path);
        
    
    // Creer le nom du fichier a l'interieur du dossier (ex: dossier/gen1.txt)
    stringstream ss;
    ss << "gen" << generation << ".txt";
    filesystem::path file_name = ss.str();
    
    // Chemin complet pour ofstream
    filesystem::path full_path = dir_path / file_name;

    ofstream fichier(full_path.string()); // Utilise .string() pour eviter les ambiguites avec ofstream
    
    // on teste si le fichier car il y avait une erreur et donc on rajoute dans le main un ignore
    if (!fichier.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier de sauvegarde: " << full_path.string() << std::endl;
        return;
    }

    for (int y = 0; y < grille.getHauteur(); ++y) {
        for (int x = 0; x < grille.getLongueur(); ++x) {
            Cellule* cell = grille.getCellule(x, y);
            
            if (cell->estObstacle()) {
                if (cell->estVivante()) {
                    fichier << "2"; 
                } else {
                    fichier << "3"; 
                }
            } else {
                if (cell->estVivante()) {
                    fichier << "1"; 
                } else {
                    fichier << "0"; 
                }
            }
        }
        fichier << "\n"; 
    }

    fichier.close();
    cout << "Sauvegarde de la generation " << generation << " dans [" << nomFichierSortie << "]" << endl;
}