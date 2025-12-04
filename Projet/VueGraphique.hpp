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
        
    private:
        std::unique_ptr<sf::RenderWindow> window;
        float cellSize;
        
        JeuDeLaVie* jeu; 

        // AJOUT/MODIFICATION : Éléments d'interface utilisateur SFML
        sf::RectangleShape pauseResumeButton; // Remplace startButton et stopButton
        sf::RectangleShape resetButton;       // Nouveau bouton "Redémarrer"

        sf::Font font;
        sf::Text pauseResumeText;
        sf::Text resetText;
        sf::Text plusText;
        sf::Text minusText;
        sf::Text delayText;

        void setupUI(unsigned int width, unsigned int height);
        void handleButtonClick(sf::Vector2f clickPos);
        void updateDelayText();
        void updatePauseResumeButton(); // Nouveau pour alterner le texte et la couleur
};

#endif