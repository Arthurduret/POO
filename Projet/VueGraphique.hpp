#ifndef VUEGRAPHIQUE_HPP
#define VUEGRAPHIQUE_HPP

#include "ObservateurGrille.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

class Grille;
class JeuDeLaVie; // Déclaration anticipée

class VueGraphique : public ObservateurGrille {
    public:
        // MODIFICATION : Ajout du pointeur JeuDeLaVie* dans le constructeur
        VueGraphique(unsigned int width, unsigned int height, float cellSize, JeuDeLaVie* jeu); 
        ~VueGraphique() override = default;

        bool isWindowOpen() const;
        void gererEvenements();
        void draw(const Grille& grille);
        void notifierChangement(const Grille& grille) override;

        void setCellSize(float s) { cellSize = s; }
        float getCellSize() const { return cellSize; }
        
        // Suppression des méthodes set/getDelai locales
        // void setDelai(float d) { delai = d; }
        // float getDelai() const { return delai; }

    private:
        std::unique_ptr<sf::RenderWindow> window;
        float cellSize;
        // float delai; // SUPPRIME
        
        // AJOUT : Pointeur vers le contrôleur de jeu
        JeuDeLaVie* jeu; 

        // AJOUT : Éléments d'interface utilisateur SFML
        sf::RectangleShape startButton;
        sf::RectangleShape stopButton;
        sf::RectangleShape plusButton;
        sf::RectangleShape minusButton;

        sf::Font font;
        sf::Text startText;
        sf::Text stopText;
        sf::Text plusText;
        sf::Text minusText;
        sf::Text delayText;

        void setupUI(unsigned int width, unsigned int height);
        void handleButtonClick(sf::Vector2f clickPos);
        void updateDelayText();
};

#endif