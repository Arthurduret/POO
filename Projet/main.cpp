#include "Jeu.hpp"               // Contient JeuDeLaVie
#include "VueConsole.hpp"        // Implémentation de la vue console
#include "VueGraphique.hpp"      // Implémentation de la vue graphique
#include "ObservateurGrille.hpp" // La classe abstraite (pour le polymorphisme)
#include <iostream>
#include <limits>
#include <string>
using namespace std;

int main() {
    
    // VARIABLES D'INITIALISATION
    string nomFichierConfig;
    ObservateurGrille* vueChoisie = nullptr; // Pointeur qui sera alloué dynamiquement
    int generations = 0;

    // --- 1. DEMANDER LE FICHIER ET TENTER L'INITIALISATION DU JEU ---
    cout << "--- DEMARRAGE DU JEU DE LA VIE ---" << std::endl;
    cout << "Entrez le nom du fichier de configuration (ex: glider.txt) : ";
    
    if (!(cin >> nomFichierConfig)) {
        cerr << "Erreur de saisie du nom de fichier." << std::endl;
        return 1;
    }
    
    try {
        // Tente de construire l'objet JeuDeLaVie, ce qui appelle lireConfiguration().
        // Si le fichier est inexistant ou mal forme, l'exception est levée ici.
        cout << "Tentative de chargement de la configuration: " << nomFichierConfig << "..." << endl;
        JeuDeLaVie game(nomFichierConfig);
        cout << "Configuration de la grille chargee avec succes." << endl;

        // --- 2. DEMANDER L'AFFICHAGE ET CRÉER LA VUE (Polymorphisme) ---
        string choix;
        cout << "\n----------------------------------------------------" << endl;
        cout << "Choisissez le mode d'affichage :" << endl;
        cout << " [C] pour Console" << endl;
        cout << " [G] pour Graphique" << endl;
        cout << "> ";
        cin >> choix;

        // Choix et allocation dynamique de l'objet Vue
        if (choix == "C" || choix == "c") {
            vueChoisie = new VueConsole();
        } 
        else if (choix == "G" || choix == "g") {
            // Utilisation d'une taille d'écran fixe pour la démo
            const int WINDOW_SIZE = 500; 
            vueChoisie = new VueGraphique(WINDOW_SIZE, WINDOW_SIZE); 
        } 
        else {
            cerr << "Choix d'affichage invalide. Le programme s'arrete." << endl;
            // On sort du try{} car l'état est invalide.
            throw runtime_error("Choix invalide."); 
        }
        
        // ATTACHER la vue choisie au moteur de jeu.
        game.ajouterObservateur(vueChoisie); 
        
        // --- 3. DEMANDER LE NOMBRE D'ITÉRATIONS ---
        cout << "\n----------------------------------------------------" << endl;
        cout << "Entrez le nombre d'iterations (generations) : ";
        
        // Vérification que l'utilisateur entre bien un nombre positif
        if (!(cin >> generations) || generations <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Saisie d'iterations invalide.");
        }

        // --- 4. LANCER LE JEU ---
        cout << "\n----------------------------------------------------" << endl;
        game.lancer(generations); 
        
    } catch (const exception& e) {
        // Gère toutes les erreurs (fichier manquant, saisie invalide, etc.)
        cerr << "\nERREUR CRITIQUE: " << e.what() << endl;
        
    }
    
    // --- 5. NETTOYAGE FINAL (CRUCIAL) ---
    // Libération de la mémoire de l'objet vue (VueConsole ou VueGraphique)
    // Ceci appelle le destructeur virtuel (~ObservateurGrille) pour éviter les fuites.
    if (vueChoisie != nullptr) {
        delete vueChoisie;
    }
    
    return 0;
}