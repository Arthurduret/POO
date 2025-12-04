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
    if (!jeu) return;

    // 1. Charger la police (Assurez-vous d'avoir 'arial.ttf' dans votre répertoire Projet)
    if (!font.loadFromFile("arial.ttf")) {
        // Optionnel : Ajouter un message d'erreur si la police n'est pas trouvée
    }

    float buttonWidth = 150.f;
    float buttonHeight = 40.f;
    float margin = 25.f;
    float startX = GAME_AREA_WIDTH + (UI_WIDTH - buttonWidth) / 2;
    float currentY = margin;

    // --- Bouton PAUSE/REPRISE (Toggle) ---
    pauseResumeButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    pauseResumeButton.setPosition(startX, currentY);
    
    pauseResumeText.setFont(font);
    pauseResumeText.setCharacterSize(20);
    pauseResumeText.setFillColor(sf::Color::White);
    updatePauseResumeButton(); // Initialise la couleur et le texte (REPRENDRE/PAUSE)
    currentY += buttonHeight + margin;


    // --- Bouton REDÉMARRER ---
    resetButton.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    resetButton.setPosition(startX, currentY);
    resetButton.setFillColor(sf::Color(100, 100, 100)); // Gris
    
    resetText.setFont(font);
    resetText.setString("REDÉMARRER");
    resetText.setCharacterSize(20);
    resetText.setFillColor(sf::Color::White);
    resetText.setPosition(startX + (buttonWidth - resetText.getLocalBounds().width) / 2, currentY + 5.f);
    currentY += buttonHeight + margin;

    // --- Texte du Délai ---
    delayText.setFont(font);
    delayText.setCharacterSize(16);
    delayText.setFillColor(sf::Color::Black);
    updateDelayText();
    currentY = resetButton.getPosition().y + resetButton.getSize().y + margin; 

    // --- Bouton MOINS VITE (Ralentir) ---
    minusButton.setSize(sf::Vector2f(buttonWidth / 3, buttonHeight));
    minusButton.setPosition(startX + buttonWidth / 2 - minusButton.getSize().x - 5.f, currentY);
    minusButton.setFillColor(sf::Color(0, 100, 150)); // Bleu
    
    minusText.setFont(font);
    minusText.setString("<<");
    minusText.setCharacterSize(24);
    minusText.setFillColor(sf::Color::White);
    minusText.setPosition(minusButton.getPosition().x + 10.f, currentY + 5.f);
    
    // --- Bouton PLUS VITE (Accélérer) ---
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
    
    float textX = GAME_AREA_WIDTH + (UI_WIDTH - delayText.getLocalBounds().width) / 2;
    float textY = resetButton.getPosition().y + resetButton.getSize().y + 5.f;
    delayText.setPosition(textX, textY);
}

/**
 * Met à jour l'apparence du bouton Pause/Reprise.
 */
void VueGraphique::updatePauseResumeButton() {
    if (!jeu) return;
    
    if (jeu->estEnPause) {
        pauseResumeButton.setFillColor(sf::Color(0, 150, 0)); // Vert (Démarrer/Reprendre)
        pauseResumeText.setString("REPRENDRE");
    } else {
        pauseResumeButton.setFillColor(sf::Color(150, 0, 0)); // Rouge (Arrêter/Pause)
        pauseResumeText.setString("PAUSE");
    }
    
    float buttonWidth = pauseResumeButton.getSize().x;
    float buttonX = pauseResumeButton.getPosition().x;
    pauseResumeText.setPosition(buttonX + (buttonWidth - pauseResumeText.getLocalBounds().width) / 2, pauseResumeButton.getPosition().y + 5.f);
}


/**
 * Gère le clic sur les boutons.
 */
void VueGraphique::handleButtonClick(sf::Vector2f clickPos) {
    if (!jeu) return;

    // 1. Démarrer/Arrêter (Toggle)
    if (pauseResumeButton.getGlobalBounds().contains(clickPos)) {
        if (jeu->estEnPause) {
            jeu->reprendre();
        } else {
            jeu->pause();
        }
    }
    // 2. Redémarrer
    else if (resetButton.getGlobalBounds().contains(clickPos)) {
        jeu->resetGrille(); 
    }
    // 3. Plus Vite (Accélérer)
    else if (plusButton.getGlobalBounds().contains(clickPos)) {
        // Diminue le délai (accélère)
        jeu->setDelai(jeu->getDelai() * 0.8f); 
        updateDelayText();
    }
    // 4. Moins Vite (Ralentir)
    else if (minusButton.getGlobalBounds().contains(clickPos)) {
        // Augmente le délai (ralentit)
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
        // Initialiser en pause par défaut pour attendre l'action de l'utilisateur
        jeu->pause(); 
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
 * Cette méthode est cruciale et doit être appelée fréquemment.
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

    window->clear(sf::Color::White); 

    // Dessin de la zone de contrôle (séparateur)
    sf::RectangleShape separator(sf::Vector2f(2.f, window->getSize().y));
    separator.setPosition(GAME_AREA_WIDTH, 0);
    separator.setFillColor(sf::Color::Black);
    window->draw(separator);
    
    // Dessin des éléments d'interface
    updatePauseResumeButton(); // Mise à jour dynamique du texte
    window->draw(pauseResumeButton);
    window->draw(resetButton);
    window->draw(plusButton);
    window->draw(minusButton);
    window->draw(pauseResumeText);
    window->draw(resetText);
    window->draw(plusText);
    window->draw(minusText);
    updateDelayText();
    window->draw(delayText);


    // Dessin de la grille
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
    
    // ESSENTIEL : Traite les événements (clics, fermeture) quand le jeu est en cours
    gererEvenements();
    
    draw(grille);
    
    if (jeu) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(jeu->getDelai() * 1000)));
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}