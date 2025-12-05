#ifndef ETATOBSTACLEVIVANT_HPP
#define ETATOBSTACLEVIVANT_HPP

#include "EtatCellule.hpp"

class EtatObstacleVivant : public EtatCellule {
    public:
    EtatObstacleVivant() {}
    
    ~EtatObstacleVivant() override = default;

    bool estVivante() const override; 
    
    bool estObstacle() const override; 
};

#endif 