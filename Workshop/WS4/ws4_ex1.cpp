#include <iostream>

using namespace std;

class Voiture {
    protected :
        int vitesseMax;
        int vitesse;
        int acceleration;
        static int nbObjets;


    public :
        Voiture() {
            init(100, 3);
        }

        Voiture(int vitesseMax, int acceleration) {
            init(vitesseMax, acceleration);  

        }

        void init (int newVitesseMax, int newAcceleration) {
            set_vitesseMax(newVitesseMax);
            set_acceleration(newAcceleration);
            nbObjets++;
        }

        int get_nbObjets() {
            return nbObjets;
        }

        int get_vitesseMax() {
            return vitesseMax;
        }

        int get_vitesse() {
            return vitesse;
        }

        int get_acceleration() {
            return acceleration;
        }

        void set_vitesseMax(int vMax) {
            if (vMax > 100) {
                vitesseMax = 100;
            }
            else {
                vitesseMax = vMax;  
            }
        }

        void set_vitesse(int v) {
            vitesse = v;
        }

        void set_acceleration(int accel) {
            if (accel > 3) {
                acceleration = 3;
            }
            else {
                acceleration = accel;
            }
        }
        
        virtual void accelerer() {
            if (vitesse + acceleration > vitesseMax) {
                vitesse = vitesseMax;
            }
            else {
                vitesse += acceleration;
            }
            cout << "La voiture roule à " << vitesse << " Km/h." << endl;
        }

};

class VoitureDeSport : public Voiture  {
    public :
        VoitureDeSport() {
            init(200,8);
        }

        VoitureDeSport(int vitesseMax, int acceleration) {
            init(vitesseMax, acceleration);
        }

        void init (int newVitesseMax, int newAcceleration) {
            set_vitesseMax(newVitesseMax);
            set_acceleration(newAcceleration);
            nbObjets++;
        }

        virtual void accelerer() override{
            if (vitesse + acceleration > vitesseMax) {
                vitesse = vitesseMax;
            }
            else {
                vitesse += acceleration;
            }
            cout << "La voiture de sport roule à " << vitesse << " Km/h." << endl;
        }



};

int Voiture::nbObjets = 0;

int main () {

    Voiture Matis(90,2);
    Matis.accelerer();

    Voiture Baptiste(100,3);
    Baptiste.accelerer();

    VoitureDeSport Arthur(200,7);
    Arthur.accelerer();

    return 0;
}