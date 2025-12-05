#ifndef JEU_H
#define JEU_H

#include "Grille.hpp"
#include "ObservateurGrille.hpp"
#include <vector>
#include <string>
#include <algorithm> // NÉCESSAIRE pour std::find

using namespace std;
using GridData = vector<vector<int>>;



class JeuDeLaVie {
    private : 
        Grille* grille;
        vector<ObservateurGrille*> observateurs;
        string nomFichierSortie;

        std::vector<std::string> historiqueEtats; 
        const size_t maxHistorySize = 10;
        
    public :
        JeuDeLaVie(const string& nomFichierConfig);

        ~JeuDeLaVie();

        void ajouterObservateur(ObservateurGrille* obs);

        GridData lireConfiguration(const string& nomFichier);

        void lancer(int generations);

        void sauvegarderGrille(const Grille& grille,int generation) const;
};

#endif