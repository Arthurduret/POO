#ifndef JEU_H
#define JEU_H

#include "Grille.hpp"
#include "ObservateurGrille.hpp"
#include <vector>
#include <string>
using namespace std;



class JeuDeLaVie {
    private : 
        Grille* grille;
        vector<ObservateurGrille*> observateurs;

    public :
        JeuDeLaVie(const string& nomFichierConfig);

        ~JeuDeLaVie();

        void ajouterObservateur(ObservateurGrille* obs);

        void lancer(int generations);
};

#endif