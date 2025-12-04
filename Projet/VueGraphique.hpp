#ifndef VUEGRAPHIQUE_HPP
#define VUEGRAPHIQUE_HPP

#include "ObservateurGrille.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

class Grille;
class JeuDeLaVie; // Déclaration anticipée

class VueGraphique : public ObservateurGrille {
    public:
        VueGraphique(unsigned int width, unsigned int height, float cellSize, JeuDeLaVie* jeu); 
        ~VueGraphique() override = default;

        bool isWindowOpen() const;
        void gererEvenements(); // Nécessaire pour la réactivité (clics, fermeture)
        void draw(const Grille& grille);
        void notifierChangement(const Grille& grille) override;

        void setCellSize(float s) { cellSize = s; }
        float getCellSize() const { return cellSize; }
        
    private:
        std::unique_ptr<sf::RenderWindow> window;
        float cellSize;
        
        JeuDeLaVie* jeu; 

        // Boutons de contrôle (implémente vos 4 fonctionnalités)
        sf::RectangleShape pauseResumeButton; // Démarrer/Arrêter (Toggle)
        sf::RectangleShape resetButton;       // Redémarrer
        sf::RectangleShape plusButton;        // Plus Vite
        sf::RectangleShape minusButton;       // Moins Vite

        sf::Font font;
        sf::Text pauseResumeText;
        sf::Text resetText;
        sf::Text plusText;
        sf::Text minusText;
        sf::Text delayText; // Affichage de la vitesse

        void setupUI(unsigned int width, unsigned int height);
        void handleButtonClick(sf::Vector2f clickPos);
        void updateDelayText();
        void updatePauseResumeButton(); // Alternance du texte et de la couleur
};

#endif