#ifndef ETATMORTE_HPP
#define ETATMORTE_HPP

#include "EtatCellule.hpp"

class EtatMorte : public EtatCellule {
    public:
        EtatMorte() {}

        bool estVivante() const override; 

        ~EtatMorte() override = default;
};

#endif 