#include "EtatObstacle.hpp"

bool EtatObstacle::estVivante() const {
    return est_vivante_fixe; 
}

bool EtatObstacle::estObstacle() const {
    return true; 
}