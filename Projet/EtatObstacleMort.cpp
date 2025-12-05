#include "EtatObstacleMort.hpp"

bool EtatObstacleMort::estVivante() const {
    return false; 
}

bool EtatObstacleMort::estObstacle() const {
    return true; 
}