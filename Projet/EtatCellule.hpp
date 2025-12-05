#ifndef ETATCELLULE_H
#define ETATCELLULE_H

class EtatCellule {

    public:

        EtatCellule() {} 
    
        virtual bool estVivante() const = 0; 

        virtual bool estObstacle() const = 0;
    
        virtual ~EtatCellule() = default;
};

#endif