#ifndef JEU_H
#define JEU_H

#include "Grille.hpp"
#include "ObservateurGrille.hpp"
#include <vector>
#include <string>
using namespace std;
using GridData = vector<vector<int>>;



class JeuDeLaVie {
    private : 
        Grille* grille;
        vector<ObservateurGrille*> observateurs;
        
    public :
        JeuDeLaVie(const string& nomFichierConfig);

        ~JeuDeLaVie();

        void ajouterObservateur(ObservateurGrille* obs);

        GridData lireConfiguration(const string& nomFichier);

        void lancer(int generations);
};

#endif