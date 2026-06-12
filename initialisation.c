//
// Created by romain on 29/05/2026.
//

#include "initialisation.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Obtient le choix de l'utilisateur dans un menu.
 *
 * Cette fonction affiche un menu d'options et attend que l'utilisateur entre un choix valide.
 * Elle utilise une boucle `do...while` pour s'assurer que l'utilisateur entre bien une valeur valide.
 *
 * @return Le choix de l'utilisateur (1, 2 ou 3).
 */

int selectionnerOptionMenu() {
    // Affiche le menu principal aux joueurs.
    printf("================ Menu ===============\n");
    printf("1) Demarrer une partie\n");
    printf("2) Reprendre une partie\n");
    printf("3) Quitter\n");
    printf("===========================================\n");

    // Demande à l'utilisateur de faire un choix.
    printf("Votre choix : ");

    // Lit le choix de l'utilisateur et le stocke dans la variable 'choix'.
    int choix;
    scanf("%d", &choix);

    // Boucle tant que le choix n'est pas 1, 2 ou 3.  Cette boucle assure
    // que l'utilisateur entre une option valide du menu.
    while (choix != 1 && choix != 2 && choix != 3)
    {
        printf("Choix invalide. Veuillez choisir parmi 1, 2 ou 3.\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
    }
    

    // Retourne le choix de l'utilisateur.  Ceci est la valeur qui sera utilisée
    // par le code appelant pour déterminer quelle action effectuer.
    return choix;
}


/**
 * @brief Configure les paramètres d'une partie de jeu.
 *
 * Cette fonction permet à l'utilisateur de choisir le mode de jeu, la dimension du champ de mine et la difficulté.
 * Elle utilise des boucles `do...while` pour s'assurer que l'utilisateur entre des valeurs valides pour chaque paramètre.
 *
 * @return Une structure `regle` contenant les paramètres configurés par l'utilisateur.
 */


regle configurationPartie() {
    // Déclare une variable de type 'regle' pour stocker les paramètres de configuration de la partie.
    regle Configuration;

    // Première boucle : permet à l'utilisateur de choisir le mode de jeu.
    do {
        printf("================ Mode de jeu ===============\n");
        printf("1) Mode de jeu Classique\n");
        printf("2) Mode de Jeu Bonus/Malus\n");
        printf("===========================================\n");
        printf("Votre choix : ");

        // Lit le choix de l'utilisateur et le stocke dans la variable 'Configuration.mode'.
        scanf("%d", &Configuration.mode);
    } while (Configuration.mode != 1 && Configuration.mode != 2); // Continue de demander à l'utilisateur jusqu'à ce qu'il entre 1 ou 2.

    // Deuxième boucle : permet à l'utilisateur de choisir la dimension du champ de mine.
    do {
        printf("================ Dimension du champ de mine ===============\n");
        printf("Le champ de mine peut avoir des dimensions de 6x6 a 12x12\n");
        printf("===========================================\n");
        printf("Votre choix : ");

        // Lit le choix de l'utilisateur et le stocke dans la variable 'Configuration.dimmnsion'.
        scanf("%d", &Configuration.dimension);
    } while (Configuration.dimension < 6 || Configuration.dimension > 12); // Continue de demander à l'utilisateur jusqu'à ce que la dimension soit comprise entre 6 et 12.

    // Troisième boucle : permet à l'utilisateur de choisir la difficulté.
    do {
        printf("\n=============== Difficulte ===============\n");
        printf("1) Facile\n");
        printf("2) Moyen\n");
        printf("3) Difficile\n");
        printf("===========================================\n");
        printf("Votre choix : ");

        // Lit le choix de l'utilisateur et le stocke dans la variable 'Configuration.difficulte'.
        scanf("%d", &Configuration.difficulte);
    } while (Configuration.difficulte < 1 || Configuration.difficulte > 3); // Continue de demander à l'utilisateur jusqu'à ce que la difficulté soit comprise entre 1 et 3.

    // Affiche des messages de débogage pour vérifier les valeurs des variables.
    printf("DEBUG: Dans la fonction, difficulte vaut : %d\n", Configuration.difficulte);
    printf("DEBUG: Dans la fonction, mode vaut : %d\n", Configuration.mode);
    printf("DEBUG: Dans la fonction, dimension vaut : %d\n", Configuration.dimension);

    // Retourne l'objet 'Configuration' contenant les paramètres de configuration de la partie.
    return Configuration;
}



/**
 * @brief Calcule le nombre de mines pour une partie donnée en fonction de la difficulté.
 *
 * Cette fonction calcule le nombre de mines à placer sur la grille, en fonction du mode de jeu et de la difficulté choisis par l'utilisateur.
 * Elle utilise des formules différentes pour chaque niveau de difficulté.
 *
 * @param Configuration La structure `regle` contenant les paramètres de configuration de la partie.
 * @return Le nombre de mines à placer sur la grille (entier).
 */

int mineDifficulte(regle Configuration) {
    // Déclare une variable de type float pour stocker le nombre de mines.
    float nb_mine = 0.0;

    // Utilise un switch statement pour déterminer le nombre de mines en fonction du niveau de difficulté.
    switch (Configuration.difficulte) {
        case 1: // Facile
            // Calcule le nombre de mines en fonction de la dimension du champ de mine et du niveau de difficulté (0,2 * dimension * dimension).
            nb_mine = 0.2 * Configuration.dimension * Configuration.dimension;
            break;
        case 2: // Moyen
            // Calcule le nombre de mines en fonction de la dimension du champ de mine et du niveau de difficulté (0,25 * dimension * dimension).
            nb_mine = 0.25 * Configuration.dimension * Configuration.dimension;
            break;
        case 3: // Difficile
            // Calcule le nombre de mines en fonction de la dimension du champ de mine et du niveau de difficulté (0,3 * dimension * dimension).
            nb_mine = 0.3 * Configuration.dimension * Configuration.dimension;
            break;
    }

    // Affiche le nombre de mines calculé à des fins de débogage.
    printf("%f \n", nb_mine);

    // Convertit la valeur float du nombre de mines en un entier et retourne cette valeur.
    return (int)roundf(nb_mine);
}



/**
 * @brief Génère les positions des mines sur la grille.
 *
 * Cette fonction génère un tableau de positions pour les mines, en s'assurant qu'il n'y ait pas deux mines à la même position.
 * Elle utilise une boucle `do...while` pour s'assurer que chaque position est unique.
 *
 * @param nb_mine Le nombre de mines à placer sur la grille.
 * @param valeur_mines Un tableau (par référence) dans lequel les positions des mines seront stockées.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 */

void generePositionMines(int nb_mine, int valeur_mines[nb_mine], int taille_grille) {
    // Affiche le nombre de mines et la taille de la grille pour information.
    printf("%d  mines\n", nb_mine);
    printf("%d  taille\n", taille_grille);

    // Boucle pour placer chaque mine à une position aléatoire sur la grille.
    for (int i = 0; i < nb_mine; ++i) {
        // Initialise la position 'x' de la mine avec une valeur aléatoire dans les limites de la grille.
        int x;
        do {
            // Génère un nombre aléatoire entre 0 et (taille_grille * taille_grille - 1).
            x = rand() % (taille_grille * taille_grille);

            // Vérifie si la position 'x' est déjà occupée par une autre mine.
            for (int j = 0; j < nb_mine; ++j) {
                if (valeur_mines[j] == x) {
                    // Si la position est déjà occupée, génère un nouveau nombre aléatoire.
                    x = -1; // Indique que la position doit être recalculée.
                }
            }
        } while (x == -1);

        // Assigne la valeur de 'x' (la position de la mine) à l'élément 'i' du tableau valeur_mines.
        valeur_mines[i] = x;
    }
}


/**
 * @brief Calcule le nombre de mines adjacentes à chaque case et incrémente les valeurs si nécessaire.
 *
 * Cette fonction parcourt la grille et pour chaque case qui contient une mine (valeur = 9), elle compte le nombre de mines
 * adjacentes à cette case.  Si une case adjacente a déjà un nombre de mines, elle l'incrémente. Si elle est la première fois qu'elle détecte
 * une mine adjacente, elle initialise le compteur à 1.
 *
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @param mines Un tableau 2D représentant la grille "solution".  Chaque case contient le nombre de mines à l'intersection de la ligne et de la colonne correspondante.
 */

void valeurCaseAutourMine(int taille_grille, int mines[taille_grille][taille_grille]) {
    // Parcourt chaque case de la grille pour mettre à jour le nombre de mines autour d'elle.
    for (int ligne = 0; ligne < taille_grille; ligne++) {
        for (int colonne = 0; colonne < taille_grille; colonne++) {
            // Vérifie si la case actuelle est une mine (valeur 9).
            if (mines[ligne][colonne] == 9) {

                // Parcourt les cases adjacentes à la mine (8 directions : haut, bas, gauche, droite et diagonales).
                for (int ligne_adjacente = -1; ligne_adjacente <= 1; ligne_adjacente++) {
                    for (int colonne_adjacente = -1; colonne_adjacente <= 1; colonne_adjacente++) {

                        // Calcule les coordonnées de la case voisine.
                        int voisin_ligne = ligne + ligne_adjacente;
                        int voisin_colonne = colonne + colonne_adjacente;

                        // Vérifie si la case voisine est dans les limites de la grille.
                        if (voisin_ligne >= 0 && voisin_ligne < taille_grille && voisin_colonne >= 0 && voisin_colonne < taille_grille) {

                            // Si la case voisine n'est pas une mine, on incrémente le compteur de mines autour de cette case.
                            if (mines[voisin_ligne][voisin_colonne] != 9) {
                                mines[voisin_ligne][voisin_colonne]++; // Incrémente le nombre de mines à côté de la mine.
                            }
                        }
                    }
                }
            }
        }
    }
}




/**
 * @brief Génère les positions des cases brouillées sur la grille.
 *
 * Cette fonction génère un tableau de positions pour les cases brouillées, en s'assurant qu'il n'y ait pas deux cases brouillées à la même position.
 * Elle utilise une boucle `do...while` pour s'assurer que chaque position est unique.
 *
 * @param nb_caseBrouillard Le nombre de cases à brouiller sur la grille.
 * @param valeur_brouillard Un tableau (par référence) dans lequel les positions des cases brouillées seront stockées.
 * @param valeur_cible La valeur cible à vérifier lors de la génération des positions.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @param mines Un tableau 2D représentant la grille "solution".  Chaque case contient le nombre de mines à l'intersection de la ligne et de la colonne correspondante.
 */


void generePositionBrouillage(int nb_caseBrouillard, int taille_grille, int mines[taille_grille][taille_grille], int objets[taille_grille][taille_grille]) {
    for (int i = 0; i < nb_caseBrouillard; ++i) {
        int rx, ry;
        do {
            int pos = rand() % (taille_grille * taille_grille);
            rx = pos % taille_grille;
            ry = pos / taille_grille;
        } while (mines[ry][rx] == 9 || objets[ry][rx] != 0); // Pas sur une mine, pas sur un autre objet
        objets[ry][rx] = 10; // 10 = Brouillage
    }
}



/**
 * @brief Génère les positions des cases "UP" (cases révélées sans mine) sur la grille.
 *
 * Cette fonction génère un tableau de positions pour les cases "UP", en s'assurant qu'il n'y ait pas deux cases "UP" à la même position.
 * Elle utilise une boucle `do...while` pour s'assurer que chaque position est unique.
 *
 * @param nb_caseUP Le nombre de cases "UP" à placer sur la grille.
 * @param valeur_UP Un tableau (par référence) dans lequel les positions des cases "UP" seront stockées.
 * @param valeur_cible La valeur cible à vérifier lors de la génération des positions.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @param mines Un tableau 2D représentant la grille "solution".  Chaque case contient le nombre de mines à l'intersection de la ligne et de la colonne correspondante.
 */
/////////////////////////////////////

void generePosition1UP(int nb_caseUP, int taille_grille, int mines[taille_grille][taille_grille], int objets[taille_grille][taille_grille]) {
    for (int i = 0; i < nb_caseUP; ++i) {
        int rx, ry;
        do {
            int pos = rand() % (taille_grille * taille_grille);
            rx = pos % taille_grille;
            ry = pos / taille_grille;
        } while (mines[ry][rx] == 9 || objets[ry][rx] != 0); // Pas sur une mine, pas sur un autre objet
        objets[ry][rx] = 11; // 11 = 1UP
    }
}
///////////////////////////////




/**
 * @brief Vérifie si une valeur cible est présente dans un tableau 2D.
 *
 * Cette fonction parcourt un tableau 2D et vérifie si une valeur spécifique est présente à l'une de ses positions.
 * Si la valeur est trouvée, elle retourne 1 ; sinon, elle retourne 0.
 *
 * @param valeur_cible La valeur à rechercher dans le tableau.
 * @param taille_grille La dimension du tableau (nombre de lignes et de colonnes).
 * @param tabAverif Le tableau 2D à parcourir.
 * @return 1 si la valeur cible est trouvée dans le tableau, 0 sinon.
 */

int verificationTableau (int valeur_cible, int taille_grille, int tabAverif[taille_grille][taille_grille]) {
    int x = 0;
    for (int i = 0; i < taille_grille; i++) {
        for (int j = 0; j < taille_grille; j++) {
            if (tabAverif[i][j] == valeur_cible) {
                x = 1;
            }
        }
    } return x;
}

