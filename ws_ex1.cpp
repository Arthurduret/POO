#include <iostream>
#include <cmath>
using namespace std;

class Circle {

public:
    double x; //position x
    double y; //position y
    double r; //rayon

    Circle(double x1, double y1, double r1) : x(x1), y(y1), r(r1) {}

    void set_pos(double x, double y) {
        this->x = x;
        this->y = y;
    }

    double perimeter() {
        return 2 * M_PI * this->r;
    }

    double area() {
        return M_PI * this->r * this->r;
    }
};


class Rectangle {
public:
    double x;
    double y;
    double w;
    double h;
    
    Rectangle(double x1, double y1, double w1, double h1) : x(x1), y(y1), w(w1), h(h1) {}
    
    void set_pos(double x, double y) {
        this->x = x;
        this->y = y;
    }

    double perimeter() {
        return 2 * (this->w + this->h);
    }

    double area() {
        return this->w * this->h;
    }

};

int main() {
    Circle c{0, 0, 1};
    std::cout << c.perimeter() << std::endl;
    std::cout << c.area() << std::endl;
    c.set_pos(1, 1);
    std::cout << "Coordinates of the center: (" << c.x << ", " << c.y << ")" << std::endl;
    Rectangle r{0, 0, 1, 2};
    std::cout << r.perimeter() << std::endl;
    std::cout << r.area() << std::endl;
    r.set_pos(-1, -1);
    std::cout << "Coordinates of the top left corner: (" << r.x << ", " << r.y << ")" << std::endl;
    return 0;
}