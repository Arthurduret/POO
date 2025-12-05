#ifndef ETATOBSTACLEMORT_HPP
#define ETATOBSTACLEMORT_HPP

#include "EtatCellule.hpp"

class EtatObstacleMort : public EtatCellule {
    public:
    EtatObstacleMort() {}
    
    ~EtatObstacleMort() override = default;

    bool estVivante() const override; 
    
    bool estObstacle() const override; 
};

#endif 