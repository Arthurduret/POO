#ifndef JEU_H
#define JEU_H

#include "Grille.hpp"
#include "ObservateurGrille.hpp"
#include <vector>
#include <string>
#include <algorithm> // Pour std::max
using namespace std;
using GridData = vector<vector<int>>;


class JeuDeLaVie {
    private : 
        Grille* grille;
        vector<ObservateurGrille*> observateurs;
        string nomFichierConfig; // Pour le redémarrage
        
    public :
        // Éléments de contrôle
        bool estEnPause = true; // Démarre en pause
        float delaiJeu = 0.5f; 

        JeuDeLaVie(const string& nomFichierConfig);

        ~JeuDeLaVie();

        void ajouterObservateur(ObservateurGrille* obs);

        GridData lireConfiguration(const string& nomFichier);

        void lancer(int generations);
        
        // Méthodes de contrôle
        void resetGrille();
        void pause() { estEnPause = true; }
        void reprendre() { estEnPause = false; }
        void setDelai(float d) { delaiJeu = std::max(0.01f, d); } // Délai min de 0.01s
        float getDelai() const { return delaiJeu; }
};

#endif