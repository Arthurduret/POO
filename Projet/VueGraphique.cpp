#include "VueGraphique.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include "Jeu.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <algorithm>
#include <sstream>

// Dimensions de l'interface
#define UI_WIDTH 200.f
#define GAME_AREA_WIDTH 600.f

/**
 * Initialisation des éléments d'interface SFML (boutons, texte).
 */
void VueGraphique::setupUI(unsigned int width, unsigned int height) {
    // 1. Charger la police
    if (!font.loadFromFile("arial.ttf")) {
        // En cas d'échec de chargement de police
    }

    float buttonWidth = 150.f;
    float buttonHeight = 40.f;
    float margin = 25.f;
    float startX = GAME_AREA_WIDTH + (UI_WIDTH - buttonWidth) / 2;
    float currentY = margin;

    // --- Bouton REPRENDRE ---
    startButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    startButton.setPosition(startX, currentY);
    startButton.setFillColor(sf::Color(0, 150, 0)); // Vert foncé
    
    startText.setFont(font);
    startText.setString("REPRENDRE");
    startText.setCharacterSize(20);
    startText.setFillColor(sf::Color::White);
    // Centre le texte
    startText.setPosition(startX + (buttonWidth - startText.getLocalBounds().width) / 2, currentY + 5.f);
    currentY += buttonHeight + margin;

    // --- Bouton PAUSE ---
    stopButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    stopButton.setPosition(startX, currentY);
    stopButton.setFillColor(sf::Color(150, 0, 0)); // Rouge foncé
    
    stopText.setFont(font);
    stopText.setString("PAUSE");
    stopText.setCharacterSize(20);
    stopText.setFillColor(sf::Color::White);
    // Centre le texte
    stopText.setPosition(startX + (buttonWidth - stopText.getLocalBounds().width) / 2, currentY + 5.f);
    currentY += buttonHeight + margin;

    // --- Texte du Délai ---
    delayText.setFont(font);
    delayText.setCharacterSize(16);
    delayText.setFillColor(sf::Color::Black);
    updateDelayText();
    currentY += 10.f; 

    // --- Bouton MOINS VITE (ralentir) ---
    minusButton.setSize(sf::Vector2f(buttonWidth / 3, buttonHeight));
    minusButton.setPosition(startX + buttonWidth / 2 - minusButton.getSize().x - 5.f, currentY);
    minusButton.setFillColor(sf::Color(0, 100, 150)); // Bleu
    
    minusText.setFont(font);
    minusText.setString("<<");
    minusText.setCharacterSize(24);
    minusText.setFillColor(sf::Color::White);
    minusText.setPosition(minusButton.getPosition().x + 10.f, currentY + 5.f);
    
    // --- Bouton PLUS VITE (accélérer) ---
    plusButton.setSize(sf::Vector2f(buttonWidth / 3, buttonHeight));
    plusButton.setPosition(startX + buttonWidth / 2 + 5.f, currentY);
    plusButton.setFillColor(sf::Color(0, 100, 150)); // Bleu
    
    plusText.setFont(font);
    plusText.setString(">>");
    plusText.setCharacterSize(24);
    plusText.setFillColor(sf::Color::White);
    plusText.setPosition(plusButton.getPosition().x + 20.f, currentY + 5.f);
}

/**
 * Met à jour le texte affichant le délai actuel.
 */
void VueGraphique::updateDelayText() {
    if (!jeu) return;
    std::stringstream ss;
    ss.precision(2);
    ss << "Delai: " << jeu->getDelai() << " s";
    delayText.setString(ss.str());
    
    // Centrer le texte dans la zone de contrôle
    float textX = GAME_AREA_WIDTH + (UI_WIDTH - delayText.getLocalBounds().width) / 2;
    float textY = stopButton.getPosition().y + stopButton.getSize().y + 5.f;
    delayText.setPosition(textX, textY);
}

/**
 * Gère le clic sur les boutons.
 */
void VueGraphique::handleButtonClick(sf::Vector2f clickPos) {
    if (!jeu) return;

    // Vérifie le clic sur REPRENDRE
    if (startButton.getGlobalBounds().contains(clickPos)) {
        jeu->reprendre();
    }
    // Vérifie le clic sur PAUSE
    else if (stopButton.getGlobalBounds().contains(clickPos)) {
        jeu->pause();
    }
    // Vérifie le clic sur PLUS VITE (diminuer le délai * 0.8)
    else if (plusButton.getGlobalBounds().contains(clickPos)) {
        jeu->setDelai(jeu->getDelai() * 0.8f); 
        updateDelayText();
    }
    // Vérifie le clic sur MOINS VITE (augmenter le délai * 1.25)
    else if (minusButton.getGlobalBounds().contains(clickPos)) {
        jeu->setDelai(jeu->getDelai() * 1.25f); 
        updateDelayText();
    }
}

/**
 * Constructeur
 */
VueGraphique::VueGraphique(unsigned int width, unsigned int height, float cellSize, JeuDeLaVie* jeu)
    : window(std::make_unique<sf::RenderWindow>(
          sf::VideoMode(width + UI_WIDTH, height),
          "Jeu de la Vie (SFML) - Observateur", 
          sf::Style::Close | sf::Style::Titlebar
      )),
      cellSize(cellSize),
      jeu(jeu)
{
    if (window) {
        window->setFramerateLimit(60); 
    }
    setupUI(width, height);
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
    while (window->pollEvent(event)) {
        
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f clickPos = window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                handleButtonClick(clickPos);
            }
        }
    }
}

/**
 * Logique de Dessin
 */
void VueGraphique::draw(const Grille& grille) {
    if (!window) return;

    // 1. Vider l'écran avec une couleur de fond (Blanc)
    window->clear(sf::Color::White); 

    // 2. Dessin de la zone de contrôle (séparateur)
    sf::RectangleShape separator(sf::Vector2f(2.f, window->getSize().y));
    separator.setPosition(GAME_AREA_WIDTH, 0);
    separator.setFillColor(sf::Color::Black);
    window->draw(separator);
    
    // 3. Dessin des éléments d'interface
    window->draw(startButton);
    window->draw(stopButton);
    window->draw(plusButton);
    window->draw(minusButton);
    window->draw(startText);
    window->draw(stopText);
    window->draw(plusText);
    window->draw(minusText);
    updateDelayText();
    window->draw(delayText);


    // 4. Dessin de la grille (limité à GAME_AREA_WIDTH)
    for (int y = 0; y < grille.getHauteur(); ++y) {
        if (y * cellSize >= window->getSize().y) continue; 
        
        for (int x = 0; x < grille.getLongueur(); ++x) { 
             if (x * cellSize >= GAME_AREA_WIDTH) continue; 

            if (grille.getCellule(x, y)->estVivante()) { 
                sf::RectangleShape cellShape;
                cellShape.setSize(sf::Vector2f(cellSize, cellSize));
                cellShape.setPosition(x * cellSize, y * cellSize);
                cellShape.setFillColor(sf::Color::Black);
                window->draw(cellShape);
            }
        }
    }

    // 5. Afficher le contenu de la mémoire tampon à l'écran
    window->display();
}

/**
 * Implémentation du Contrat Observateur
 */
void VueGraphique::notifierChangement(const Grille& grille) {
    if (!isWindowOpen()) {
        if (jeu) jeu->pause(); 
        return;
    }
    gererEvenements();
    draw(grille);
    
    if (jeu) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(jeu->getDelai() * 1000)));
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}