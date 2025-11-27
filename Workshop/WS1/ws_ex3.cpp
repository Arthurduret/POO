#include <iostream>
#include <random>
#include <string>
using namespace std;


class Creature {
    private :
        int pv; // Points de vie
        int pa; // Point d'attaque
        int niveau; //Niveau de la créature

    
    public : 
        static int cpt;
        Creature () {cpt += 1;}
        Creature (int pv, int pa, int niv) : pv(pv), pa(pa), niveau(niv) {cpt += 1;}
        
        void affiche() const {
            cout << "Creature - PV : " << pv << ", PA : " << pa << ", Niveau : " << niveau << endl;
        }

        double attaque(){
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1, pa);
            cout << dis(gen) << " sont les DMG du monstre "<< endl;
            return dis(gen);   
        }

        void subitDegat (int degat){
            pv -= degat;
            if (pv < 0) pv = 0;
        }

        bool estVivant () const {
            if (pv <= 0){
                return false;
            }
            else (pv);
                return true;
        }

};

int Creature::cpt = 0;


class Heros {
    private :
        string nom;
        int pv;
        int pa;

    public :
        Heros (string nom, int pv, int pa) : nom(nom), pv(pv), pa(pa) {}
        Heros () {}
        
        void affiche () const {
            cout << "Heros - Nom : " << nom << ", PV : " << pv << ", PA : " << pa << endl;
        }

        double attaque(){
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1, pa);
            cout << dis(gen) << " sont les DMG du monstre "<< endl;
            return dis(gen);   
        }

        void subitDegat(int degat){
            pv -= degat;
        }

        bool estVivant () const {
            if (pv <= 0){
                return false;
            }
            else (pv);
                return true;
        }

};

// int main () {
//     Heros Matis("Matis", 10, 10);
//     Creature Baptiste(20, 10, 5);
//     while (Matis.estVivant() && Baptiste.estVivant()){
//         int save_dmg_personnage = Matis.attaque();
//         int save_dmg_monstre = Baptiste.attaque();

//         Matis.affiche();
//         Baptiste.affiche();

//         cout << "\n" << endl;

//         Baptiste.subitDegat(save_dmg_personnage);
//         Matis.subitDegat(save_dmg_monstre);

//         Matis.affiche();
//         Baptiste.affiche();

//     }
//     if (!Matis.estVivant() && !Baptiste.estVivant()) {
//     cout << "Match nul : ils tombent ensemble." << endl;
//     } else if (!Matis.estVivant()) {
//     cout << "Matis est mort ... et Baptiste la Créature l'a mangé 😂😂" << endl;
//     } else if (!Baptiste.estVivant()) {
//     cout << "Matis a triomphé !" << endl;
//     }

// };

void foo() {
    Creature c3;
    cout << "Nombre de créatures: " << Creature::cpt << endl;
}

void test1() {
    cout << "Test 1: \n";
    Creature c1;
    Creature c2(10, 2, 2);
    cout << "Nombre de créatures: " << Creature::cpt << endl;
    foo();
    cout << "Nombre de créatures: " << Creature::cpt << endl;
}

void bar(Creature c1) {
    Creature c2;
    cout << "Nombre de créatures: " << Creature::cpt << endl;
}

void test2() {
    cout << "Test 2: \n";
    Creature c1;
    Creature c2(10, 2, 2);
    cout << "Nombre de créatures: " << Creature::cpt << endl;
    bar(c2);
    cout << "Nombre de créatures: " << Creature::cpt << endl;
}


int main() {
    test1();
    test2();
    return 0;
}
