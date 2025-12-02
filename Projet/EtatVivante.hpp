#ifndef ETATVIVANTE_HPP
#define ETATVIVANTE_HPP

#include "EtatCellule.hpp"

class EtatVivante : public EtatCellule {
    public :
        EtatVivante() {}

        bool estVivante() const override;

        ~EtatVivante() override = default;
};

#endif 