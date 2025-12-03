 // --- 1. Compter les voisines vivantes (Comptage Toroidal) ---
int ReglesJeu::compterVoisinesVivantes(int ligne, int colonne, const Grid& grille) {
    int live_neighbors = 0;
    int rows = grille.size();
    if (rows == 0) return 0;
    int cols = grille[0].size();

    // Parcourir les 9 positions autour de la cellule
    for (int r = ligne - 1; r <= ligne + 1; ++r) {
        for (int c = colonne - 1; c <= colonne + 1; ++c) {
            
            // Ignorer la cellule centrale
            if (r == ligne && c == colonne) {
                continue;
            }

            // Gestion Toroidale : assure que r_toroidal et c_toroidal sont toujours dans les limites [0, rows/cols - 1]
            int r_toroidal = (r + rows) % rows;
            int c_toroidal = (c + cols) % cols;
            
            live_neighbors += grille[r_toroidal][c_toroidal];
        }
    }
    return live_neighbors;
}

// --- 3. Calculer le prochain tour ---
Grid ReglesJeu::prochainTour(const Grid& grille_actuelle) {
    if (grille_actuelle.empty()) return {};
    int lignes = grille_actuelle.size();
    int colonnes = grille_actuelle[0].size();

    // Création de la grille future
    Grid grille_future(lignes, std::vector<int>(colonnes)); 

    // Boucle sur chaque cellule
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            
            int N = compterVoisinesVivantes(i, j, grille_actuelle);
            int etat_actuel = grille_actuelle[i][j];
            
            // Appliquer la logique et stocker dans la grille future
            grille_future[i][j] = appliquerRegles(etat_actuel, N);
        }
    }
    
    return grille_future; 
}