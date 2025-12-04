#ifndef JEU_H
#define JEU_H

#include "Grille.hpp"
#include "ObservateurGrille.hpp"
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;
using GridData = vector<vector<int>>;


class JeuDeLaVie {
    private : 
        Grille* grille;
        vector<ObservateurGrille*> observateurs;
        // AJOUT: Stocker le nom du fichier pour le redémarrage
        string nomFichierConfig;
        
    public :
        bool estEnPause = true; // Initialiser en pause par défaut pour la démo
        float delaiJeu = 0.5f; 

        JeuDeLaVie(const string& nomFichierConfig);

        ~JeuDeLaVie();

        void ajouterObservateur(ObservateurGrille* obs);

        GridData lireConfiguration(const string& nomFichier);

        void lancer(int generations);
        
        // NOUVEAU: Méthode pour réinitialiser la grille
        void resetGrille();

        void pause() { estEnPause = true; }
        void reprendre() { estEnPause = false; }
        void setDelai(float d) { delaiJeu = std::max(0.01f, d); }
        float getDelai() const { return delaiJeu; }
};

#endif