#ifndef ETATOBSTACLE_HPP
#define ETATOBSTACLE_HPP

#include "EtatCellule.hpp"

class EtatObstacle : public EtatCellule {
private:
    const bool est_vivante_fixe;

public:
    EtatObstacle(bool est_vivante_init) : est_vivante_fixe(est_vivante_init) {}
    
    ~EtatObstacle() override = default;

    bool estVivante() const override; 
    
    bool estObstacle() const override; 
};

#endif 