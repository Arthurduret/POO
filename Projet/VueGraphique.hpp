#ifndef VUEGRAPHIQUE_HPP
#define VUEGRAPHIQUE_HPP

#include "ObservateurGrille.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

class Grille;

class VueGraphique : public ObservateurGrille {
    public:
        VueGraphique(unsigned int width, unsigned int height, float cellSize = 10.f);
        ~VueGraphique() override = default;

        bool isWindowOpen() const;
        void gererEvenements();
        void draw(const Grille& grille);
        void notifierChangement(const Grille& grille) override;

        void setCellSize(float s) { cellSize = s; }
        float getCellSize() const { return cellSize; }

    private:
        std::unique_ptr<sf::RenderWindow> window;
        float cellSize;
};

#endif