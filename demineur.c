#include "demineur.h"

#include <stdio.h>



/**
 * @brief Convertit une position linéaire en coordonnées de grille (x, y).
 *
 * Cette fonction prend une position linéaire (un entier) et la convertit en ses
 * coordonnées correspondantes dans une grille carrée. Elle gère également les
 * cas où la position est hors des limites de la grille.
 *
 * @param pos La position linéaire à convertir.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @return Une structure `position` contenant les coordonnées x et y de la cellule correspondante dans la grille.
 */

position position_x_y(int pos, int taille_grille) {
    // Déclare une variable de type 'position' pour stocker les coordonnées x et y.
    position Position;

    // Initialise la coordonnée x avec la valeur passée en argument 'pos'.
    Position.x = pos;

    // Initialise la coordonnée y à 0.
    Position.y = 0;

    // Calcule la coordonnée y en partant de zéro et en incrémentant jusqu'à ce que la coordonnée x soit dans les limites de la grille.
    int y = 0;
    while ((Position.x - taille_grille) > 0) {
        // Décrémente la coordonnée x de la taille de la grille.
        Position.x = Position.x - taille_grille;
        // Incrémente la coordonnée y.
        Position.y++;
    }

    // Retourne l'objet 'Position' contenant les coordonnées x et y.
    return Position;
}


/**
 * @brief Affiche la grille de jeu dans la console.
 *
 * Cette fonction affiche l'état actuel de la grille du jeu, y compris les numéros des cases,
 * l'état des cases révélées (bombes, drapeaux, vides) et les cases brouillées.
 *
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @param grille_utilisateur Un tableau 2D représentant la grille "utilisateur".
 *                           Chaque case contient un caractère indiquant son état : 'B' pour bombe,
 *                           'D' pour drapeau, 'V' pour case révélée sans mine, ' ' pour brouillard,
 *                           et des chiffres (1-9) pour indiquer le nombre de mines autour.
 * @param mines Un tableau 2D représentant la grille "solution".  Chaque case contient le
 *               nombre de mines à l'intersection de la ligne et de la colonne correspondante.
 */

void afficherGrille(int taille_grille, char grille_utilisateur[taille_grille][taille_grille], int mines[taille_grille][taille_grille], int tours_brouillage) {
    printf("\n    ");
    for (int i = 1; i <= taille_grille; i++) {
        printf("%2d ", i);
    }
    printf("\n   ");
    for (int i = 0; i <= taille_grille; i++) {
        printf("___");
    }
    printf("\n");

    for (int i = 0; i < taille_grille; i++) {
        printf("%2d |", i + 1);
        for (int j = 0; j < taille_grille; j++) {
            // RÈGLE BONUS/MALUS : Si brouillage actif, on masque tout par des '?'
            if (tours_brouillage > 0) {
                printf(" ? ");
            } else {
                switch (grille_utilisateur[i][j]) {
                    case 'B': printf(" X "); break;
                    case 'D': printf(" D "); break;
                    case 'V': printf("   "); break;
                    case ' ': printf(" . "); break;
                    case 'M': printf(" @ "); break; // Case Malus activée
                    case 'U': printf(" U "); break; // Case Bonus activée
                    default:  printf(" %c ", grille_utilisateur[i][j]); break;
                }
            }
        }
        printf("\n");
    }
}


/**
 * @brief Obtient l'entrée de l'utilisateur pour une action sur la grille.
 *
 * Cette fonction permet à l'utilisateur d'interagir avec le jeu en choisissant
 * une action (révéler une case, mettre un drapeau, sauvegarder et quitter) et
 * en spécifiant la position de la case sur laquelle effectuer l'action.
 *
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @return Une structure `position` contenant les coordonnées x et y de la case
 *         cliquée par l'utilisateur.
 */

position entree_utilisateur(int taille_grille) {
    // Déclare une variable de type 'position' pour stocker les actions et coordonnées de l'utilisateur.
    position clic;

    // Demande à l'utilisateur de choisir son action initiale.
    do {
        printf("Voulez vous :\n1) reveler la case\n2) mettre un drapeau sur la case\n3) sauvegarder et quitter la partie\n");
        scanf("%d", &clic.action);
    } while (clic.action != 1 && clic.action != 2 && clic.action != 3); // Continue de demander à l'utilisateur jusqu'à ce qu'il entre 1, 2 ou 3.

    // Si l'utilisateur n'a pas choisi de sauvegarder et quitter (action 3), on lui demande les coordonnées de la case.
    if (clic.action != 3) {
        // Demande à l'utilisateur d'entrer les coordonnées x et y de la case.
        do {
            printf("Quelle est la position en x de la case que tu veux cliquer? ");
            scanf("%d", &clic.x);
            printf("Quelle est la position en y de la case que tu veux cliquer? ");
            scanf("%d", &clic.y);

            // Vérifie si les coordonnées sont valides (dans les limites de la grille).
            if (clic.x > taille_grille || clic.x < 1 || clic.y > taille_grille || clic.y < 1) {
                printf("Position invalide. Entrez une valeur entre 1 et %d.\n", taille_grille); // Affiche un message d'erreur si les coordonnées sont invalides.
            }
        } while (clic.x > taille_grille || clic.x < 1 || clic.y > taille_grille || clic.y < 1); // Continue de demander aux coordonnées jusqu'à ce qu'elles soient valides.

        // Ajuste les coordonnées pour qu'elles commencent à 0 (car les indices des tableaux commencent à 0).
        clic.x = clic.x - 1;
        clic.y = clic.y - 1;
    }

    // Retourne l'objet 'clic' contenant les actions et coordonnées de l'utilisateur.
    return clic;
}




/**
 * @brief Révèle une case sur la grille de jeu.
 *
 * Cette fonction permet de révéler le contenu d'une case spécifique de la grille du jeu,
 * en tenant compte du nombre de mines adjacentes à cette case et des règles de révélations
 * en cascade (si une case révélée ne contient aucune mine, toutes les cases adjacentes sont également révélées).
 *
 * @param x La position horizontale de la case à révéler.
 * @param y La position verticale de la case à révéler.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @param mines Un tableau 2D représentant la grille "solution" (nombre de mines à chaque case).
 * @param grille_utilisateur Un tableau 2D représentant la grille "utilisateur".
 */

void revelerCase(int x, int y, int taille_grille, int mines[taille_grille][taille_grille], char grille_utilisateur[taille_grille][taille_grille]) {
    // Vérifie si les coordonnées sont dans les limites de la grille.
    if (y >= 0 && y < taille_grille && x >= 0 && x < taille_grille) {
        // Vérifie si la case est actuellement brouillard (' ').
        if (grille_utilisateur[y][x] == ' ') {

            // Récupère la valeur de la mine à cette position.
            int valeur = mines[y][x];

            // Si la case contient un nombre (mine), on l'affiche.
            if (valeur > 0) {
                grille_utilisateur[y][x] = '0' + valeur; // Convertit le nombre en caractère correspondant.
            } else {
                // Si la case est vide et qu'elle n'est pas une mine, on l'affiche comme révélée ('V').
                grille_utilisateur[y][x] = 'V';

                // Effectue une révélation récursive des cases adjacentes.
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        // Vérifie si la case voisine est dans les limites de la grille et n'est pas un mur.
                        if (i != 0 || j != 0) { // Évite de révéler les cases directement adjacentes à la case actuelle.
                            revelerCase(x + j, y + i, taille_grille, mines, grille_utilisateur); // Appelle récursivement la fonction pour révéler la case voisine.
                        }
                    }
                }
            }
        }
    }
}




/**
 * @brief Gère l'activation des bonus (1UP) et malus (Brouillage).
 */
void appliquerBonusMalus(int valeur_case, int *vies, int *tours_brouillage, char *case_utilisateur) {
    if (valeur_case == 10) {
        *tours_brouillage = 2;
        printf("\nMALUS ! Brouillage active ! Vous ne voyez plus rien pendant 2 tours !\n");
    }
    else if (valeur_case == 11) {
        (*vies)++;
        printf("\nBONUS ! +1 UP obtenu ! Vous gagnez une vie (Total : %d vies)\n", *vies);
    }
}

/**
 * @brief Gère l'explosion d'une mine en vérifiant si le joueur possède une vie bonus.
 * @return 0 si le joueur est sauvé par un 1UP, -1 si c'est la défaite définitive.
 */


int gererExplosionMine(int *vies, char *case_utilisateur) {
    (*vies)--;
    if (*vies > 0) {
        *case_utilisateur = 'B';
        printf("\nBOOM ! Vous avez touche une mine ! Heureusement une vie vous sauve (Reste : %d vies)\n", *vies);
        return 0;
    } else {
        *case_utilisateur = '*';
        printf("\nGAME OVER ! Vous n'avez plus de vies.\n");
        return -1;
    }
}
