#ifndef OBSERVATEURGRILLE_H
#define OBSERVATEURGRILLE_H

class Grille;

class ObservateurGrille {
    protected :

    public :
        virtual ~ObservateurGrille() = default; // Destructeur
        virtual void notifierChangement(const Grille& grille) = 0; //
}


#endif