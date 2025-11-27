#include <iostream>
#include <string>
using namespace std;

class GestionObjets {
    private :
            objet** boite;
            int taille
            int count;

    public :
        GestionObjets(int nb_objet) : {
            boite = new objet *[nb_objet];
            count = 0;
        }

        void ajouterObjet() {

        } 



}


class objet {
    private :

    public :
    
        virtual double aire() const = 0;

        virtual double perimetre() const = 0;

        virtual void afficheInfo() const = 0;
};


class Rectangle : public objet {
    private :
        double longueur;
        double largeur;
    
    public :
        Rectangle(double l, double lg) : longueur(lg), largeur(l) {}
        
        double getLargeur() {
            return largeur;
        }

        double getLongueur() {
            return longueur;
        }

        double aire() const override{
            return longueur * largeur;
        }

        double perimetre() const override {
            return 2 * longueur + 2 * largeur;
        }

        void afficheInfo() const override {
            cout << "La longeur du rectangle est " << longueur << " et la largeur est " << largeur << endl;
        }
};

class Carre : public objet {
    private :
        double cote;

    public :
        Carre(double c) : cote(c) {}
        
        double getCote() {
            return cote;
        }

        double aire() const override {
            return cote * cote;
        }

        double perimetre() const override {
            return 4 * cote;
        }

        void afficheInfo() const override {
            cout << "Le côté du carré fait " << cote << endl;
        }

};

