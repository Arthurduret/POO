#include <iostream>
#include <string>

using namespace std;


class Instrument {
public:

    virtual void jouer() const = 0; 
    virtual ~Instrument() {}
};


class Saxophone : public Instrument {
public:
    void jouer() const override {
        cout << "🎷 Le Saxophone joue : Doo-wop... J'ai le son chaleureux du jazz !" << endl;
    }
    ~Saxophone() override {
        cout << "Le Saxophone est détruit." << endl;
    }
};

class Piano : public Instrument {
    public:
        void jouer() const override {
            cout << "🎹 Le Piano joue : Ding-dong-ping... J'ai le son classique et percutant." << endl;
        }
        ~Piano() override {
            cout << "Le Piano est détruit." << endl;
        }
};


class Sex : public Instrument {
    public :
        void jouer() const override {
            cout << "🔞 Le matis baise : hammmmmmm hammmmmmm... J'ai le son de Candice" << endl;
        }

        ~Sex() override {
            cout << "Le sex est finis, il a tout sortis !!" << endl;
        }
};


int main() {
    string choix;
    Instrument* instrumentChoisi = nullptr; 

    cout << "Quel instrument souhaitez-vous jouer ?" << endl;
    cout << "Options : [Saxophone] ou [Piano] ou [Sex]" << endl;
    cout << "> ";
    cin >> choix;

    if (choix == "Saxophone" || choix == "saxophone" || choix == "saxo" || choix == "Saxo" || choix == "Sax" || choix == "sax") {
        instrumentChoisi = new Saxophone(); 
        cout << "Un Saxophone a été alloué." << endl;
    } 
    else if (choix == "Piano" || choix == "piano") {
        // Alloue un objet Piano sur le tas (heap)
        instrumentChoisi = new Piano();
        cout << "\nUn Piano a été alloué." << endl;
    } 

    else if (choix == "Sex" || choix == "sex") {
        // Alloue un objet Piano sur le tas (heap)
        instrumentChoisi = new Sex();
        cout << "\nUne baise est en cours." << endl;
    } 
    else {
        cout << "❌ Choix non reconnu. Le programme se termine." << endl;
        return 1;
    }

    // --- 3. Appel Polymorphique ---
    // Si l'allocation a réussi (le pointeur n'est pas NULL)
    if (instrumentChoisi != nullptr) {
        cout << "--- Le concert commence ---" << endl;
        // L'appel à jouer() est dirigé vers la méthode appropriée 
        // (Saxophone::jouer ou Piano::jouer) grâce au mot-clé 'virtual'.
        instrumentChoisi->jouer();
        cout << "---------------------------\n" << endl;
    }

    // --- 4. Libération de la Mémoire ---
    // Étape CRUCIALE : On utilise 'delete' sur le pointeur de la classe de base.
    // Grâce au destructeur virtuel, le destructeur de la classe dérivée correcte 
    // est appelé, puis celui de la classe de base.
    if (instrumentChoisi != nullptr) {
        cout << "Libération de la mémoire allouée : " << endl;
        delete instrumentChoisi;
    }

    return 0;
}