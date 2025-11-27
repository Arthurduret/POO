
#include <iostream>
using namespace std;


class Creature {

    public:

        Creature() {} // Constructeur par défaut sans paramètre
        Creature(const Creature &c) {// Constructeur par copie
        cout << "A creature has been duplicated" << endl;
    }

        ~Creature() {// Destructeur
            cout << "A Creature has been destroyed" << endl;
        }
};

// void foo(Creature c) {
//     cout << "foo" << endl;
// }


// int main(int argc, char const *argv[]){
//     Creature ogre;
//     Creature shrek = ogre;
//     cout << "before foo" << endl;
//     foo(shrek);
//     cout << "after foo" << endl;
//     return 0;
// }

void foo(Creature &c) {
    cout << "foo" << endl;
    Creature a = c;
}

int main(int argc, char const *argv[])
{
    Creature ogre;
    cout << "before foo" << endl;
    foo(ogre);
    cout << "after foo" << endl;
    return 0;
}
