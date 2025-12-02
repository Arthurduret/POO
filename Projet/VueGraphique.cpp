#include "VueGraphique.hpp"
#include "Grille.hpp" 
#include "Cellule.hpp" 
#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * Constructeur
 * Rôle : Initialiser la fenêtre SFML.
 * @param width Largeur totale de la fenêtre en pixels.
 * @param height Hauteur totale de la fenêtre en pixels.
 */
VueGraphique::VueGraphique(unsigned int width, unsigned int height) : window(std::make_unique<sf::RenderWindow>(

    // Initialisation du unique_ptr vers sf::RenderWindow
          sf::VideoMode(width, height), 
          "Jeu de la Vie (SFML) - Observateur", 
          sf::Style::Close | sf::Style::Titlebar
      ))
{
    // Fixer la limite de rafraîchissement à 60 FPS.
    if (window) {
        window->setFramerateLimit(60); 
    }
}

/**
 * Vérifie si la fenêtre SFML est ouverte.
 */
bool VueGraphique::isWindowOpen() const {
    return window && window->isOpen();
}

/**
 * Gère les événements utilisateur (fermeture de fenêtre, clavier, souris).
 */
void VueGraphique::gererEvenements() {
    if (!window) return;
    
    sf::Event event;
    // Parcourir tous les événements en attente
    while (window->pollEvent(event)) {
        
        // L'utilisateur demande la fermeture de la fenêtre
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        
        // Gestion future des extensions (touches du clavier, souris)
        if (event.type == sf::Event::KeyPressed) {
            // Logique de placement de motifs/contrôles à ajouter ici
        }
    }
}

/**
 * Logique de Dessin
 * Rôle : Effacer, dessiner les cellules vivantes et afficher le rendu.
 */
void VueGraphique::draw(const Grille& grille) {
    if (!window) return;

    // 1. Vider l'écran avec une couleur de fond (Blanc)
    window->clear(sf::Color::White); 

    // Récupérer la taille des cellules en pixels
    float cell_size = this->cellSize;

    // 2. Boucles imbriquées pour parcourir la grille
    for (int y = 0; y < grille.getHauteur(); ++y) {
        for (int x = 0; x < grille.getLargeur(); ++x) {
            
            // 3. Interroger l'état via le polymorphisme Cellule::estVivante()
            // getCellule retourne ici un pointeur : utiliser ->estVivante()
            if (grille.getCellule(x, y)->estVivante()) {
                
                // Configuration de l'objet SFML (Carré)
                sf::RectangleShape cellShape;
                cellShape.setSize(sf::Vector2f(cell_size, cell_size));
                
                // Positionnement : x * taille, y * taille
                cellShape.setPosition(x * cell_size, y * cell_size);
                
                // Cellule Vivante = Couleur Noire
                cellShape.setFillColor(sf::Color::Black);
                
                // Dessiner le carré dans la mémoire tampon
                window->draw(cellShape);
            }
        }
    }
    
    // 4. Afficher le contenu de la mémoire tampon à l'écran
    window->display();
}

/**
 * Implémentation du Contrat Observateur
 * Rôle : Appelé par la Grille lors d'un changement d'état. Orchestre l'affichage.
 */
void VueGraphique::notifierChangement(const Grille& grille) {
    if (isWindowOpen()) {
        gererEvenements(); // Gère les entrées utilisateur
        draw(grille);      // Dessine la nouvelle génération
    }
}