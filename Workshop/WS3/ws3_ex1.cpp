#include <iostream>
#include <string>
using namespace std;

class Vehicule {
    private :
        int max_speed;
        int mileage;
    
    public : 
        Vehicule() : max_speed(240), mileage(0) {}
        
        void setmax_speed (int new_speed) {
            if (new_speed < 200) {
                max_speed = 240;
            }
            else {
                max_speed = new_speed;
            }
        
        }
        
        int getmax_speed () {
            return max_speed;
        }

        void setmileage (int new_mileage) {
            if (mileage < 0) {
                mileage = 0;
            }
            else {
                mileage = new_mileage;
            }
        }

        int getmileage () {
            return mileage;
        }

};

class Bus : public Vehicule {
    private :
        int seat_capacity;
    public :
        Bus () : seat_capacity(10) {}

        int getseating_capacity () {
            return seat_capacity;
        }

        void setseating_capacity (int new_seating_capacity) {
            if (new_seating_capacity <= 10 && new_seating_capacity >= 50) {
                seat_capacity = 50;
            }
            else {
                seat_capacity = new_seating_capacity;
            }

        }

        void get_info () {
            cout << "Il s'agit d'un bus d'une capacité de " << seat_capacity << " places, avec une vitesse maximale de " << getmax_speed() << " km/h et son kilométrage est de " << getmileage() << "km." << endl;
        }

};

int main (){
    Vehicule lambo;
    cout << lambo.getmileage() << endl;
    Bus fefe;
    fefe.get_info();
    return 0;
};
