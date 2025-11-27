#include <iostream>
using namespace std;

/*
You can write your class Fraction here
*/

class Fraction {
private:
    int num;
    int denom;

public: 

    Fraction (int num, int denom) : num(num), denom(denom) {}
    Fraction () : num(1), denom(1) {}


    int getNumerateur() const {
        return num;
    }

    int getDenominateur() const {
        return denom;
    }

    Fraction add(const Fraction& autre) const{
        int n = num * autre.denom + autre.num * denom;
        int d = denom * autre.denom;
        return Fraction(n,d);
    }

    Fraction minus(const Fraction& autre) const{
        int n = num * autre.denom - autre.num * denom;
        int d = denom * autre.denom;
        return Fraction(n,d);
    }

    Fraction multiply(const Fraction& autre) const{
        int n = num * autre.num;
        int d = denom * autre.denom;
        return Fraction(n,d);   
    }

    Fraction divide(const Fraction& autre) const{
        int n = num * autre.denom;
        int d = denom * autre.num;
        return Fraction(n,d);   
    }

};

int main()
{
    /* Test constructors */
    Fraction f0;
    if (f0.getNumerateur() == 1 && f0.getDenominateur() == 1) {
        cout << f0 << endl;
    }
    else {
        cout << "[FAILURE] Default constructor doesn't work" << endl;
    }

    Fraction f1(1, 2);
    if (f1.getNumerateur() == 1 && f1.getDenominateur() == 2) {
        cout << "[OK] Constructor with parameters works" << endl;
    }
    else {
        cout << "[FAILURE] Constructor with parameters doesn't work" << endl;
    }

    Fraction f2(3, 4);

    /* Test add */
    Fraction f3 = f1.add(f2);

    if (f3.getNumerateur() == 10 && f3.getDenominateur() == 8) {
        cout << "[OK] Add method works" << endl;
    }
    else {
        cout << "[FAILURE] Add method doesn't work" << endl;
    }

    /* Test minus */
    f3 = f1.minus(f2);
    if (f3.getNumerateur() == -2 && f3.getDenominateur() == 8) {
        cout << "[OK] Minus method works" << endl;
    }
    else {
        cout << "[FAILURE] Minus method doesn't work" << endl;
    }

    /* Test multiply */
    f3 = f1.multiply(f2);
    if (f3.getNumerateur() == 3 && f3.getDenominateur() == 8) {
        cout << "[OK] Multiply method works" << endl;
    }
    else {
        cout << "[FAILURE] Multiply method doesn't work" << endl;
    }

    /* Test divide */
    f3 = f1.divide(f2);
    if (f3.getNumerateur() == 4 && f3.getDenominateur() == 6) {
        cout << "[OK] Divide method works" << endl;
    }
    else {
        cout << "[FAILURE] Divide method doesn't work" << endl;
    }

    return 0;
};
