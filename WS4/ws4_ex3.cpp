#include <iostream>
using namespace std;

class Vehicule {
    virtual bool estLaver() const = 0;
};

class  Voiture : public Vehicule {
    public :
        Voiture(){}
    bool estLaver() const override {
        cout << "La voiture est lavée." << endl;
        return true;
    }
};

class Moto : public Vehicule {
    public :
        Moto(){}

    bool estLaver() const override {
        cout << "La moto est lavée." << endl;
        return true;
    }
};

class StationDeLavage {
    private :
        Vehicule** parc;
        int nbVehicule;
        int count;

    public :
        StationDeLavage(int nbVehicule) {
            parc = new Vehicule * [nbVehicule];
            count = 0;
        }

        bool addVehicule(Vehicule* ve) {
            if (count >= nbVehicule) return false; // plein
            parc[count++] = ve;
            return true;
        }

        void laverTousLesVehicules() {
            for (int k = 0; k < count; ++k) {
                if (parc[k] != nullptr) {
                    parc[k]->estLaver();
                }

        }
        }

};


int main () {

    Voiture maVoiture;
    Voiture laVoitureDeMatis;
    Moto maMoto;

    maVoiture.estLaver();

    return 0;
}