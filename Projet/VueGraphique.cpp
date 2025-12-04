#include "VueGraphique.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

/**
 * Constructeur
 * Rôle : Initialiser la fenêtre SFML.
 * @param width Largeur totale de la fenêtre en pixels.
 * @param height Hauteur totale de la fenêtre en pixels.
 */
VueGraphique::VueGraphique(unsigned int width, unsigned int height, float cellSize)
    : window(std::make_unique<sf::RenderWindow>(

    // Initialisation du unique_ptr vers sf::RenderWindow
          sf::VideoMode(width, height), 
          "Jeu de la Vie (SFML) - Observateur", 
          sf::Style::Close | sf::Style::Titlebar
      )),
      cellSize(cellSize),
      delai(0.5f)
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
        
        // autres événements possibles à gérer ici
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

    // Parcours de la grille
    for (int y = 0; y < grille.getHauteur(); ++y) {
        // Fixe l'erreur de syntaxe en ajoutant un point-virgule (;)
        for (int x = 0; x < grille.getLongueur(); ++x) { 
            // NOTE : ici on utilise ->estVivante() en supposant que getCellule retourne un pointeur.
            // Si getCellule retourne une référence (Cellule&), remplacez "->" par "."
            
            // Fixe l'erreur de pointeur en utilisant "->" à la place de "." 
            // et simplifie les arguments, car x et y sont déjà des int.
            if (grille.getCellule(x, y)->estVivante()) { 
                sf::RectangleShape cellShape;
                cellShape.setSize(sf::Vector2f(cellSize, cellSize));
                cellShape.setPosition(x * cellSize, y * cellSize);
                cellShape.setFillColor(sf::Color::Black);
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
    if (!isWindowOpen()) return;
    gererEvenements();
    draw(grille);
    
    // Pause selon le délai choisi
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delai * 1000)));
}