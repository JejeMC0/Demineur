#include "demineur.h"

#include <stdio.h>



/**
 * @brief Convertit un index dans une grille en coordonnées (x, y).
 *
 * Cette fonction prend un index unique représentant une case dans la grille et le convertit en un couple de coordonnées (x, y)
 * qui indiquent la position de cette case sur la grille. Elle gère les grilles dont la taille est supérieure à 1.
 *
 * @param pos L'index unique de la case dans la grille.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @return Un objet 'position' contenant les coordonnées (x, y) de la case.
 */

position position_x_y(int pos, int taille_grille) {
    position Position; // Déclare une variable de type 'position' pour stocker les coordonnées x et y.

    // Initialise la coordonnée x avec la valeur passée en argument 'pos'.
    Position.x = pos; // Assigne la valeur de 'pos' à l'attribut 'x' de l'objet 'Position'.

    // Initialise la coordonnée y à 0.
    Position.y = 0; // Assigne la valeur 0 à l'attribut 'y' de l'objet 'Position'.

    // Calcule la coordonnée y en partant de zéro et en incrémentant jusqu'à ce que la coordonnée x soit dans les limites de la grille.
    int y = 0;
    while ((Position.x - taille_grille) > 0) { // Tant que la coordonnée x est inférieure à la taille de la grille...
        // Décrémente la coordonnée x de la taille de la grille.
        Position.x = Position.x - taille_grille;
        // Incrémente la coordonnée y.
        Position.y++;
    }

    // Retourne l'objet 'Position' contenant les coordonnées x et y.
    return Position; // Renvoie l'objet 'Position' au code appelant.
}


/**
 * @brief Affiche la grille de jeu, incluant les cases avec des mines, des bonus/malus et le brouillard.
 *
 * Cette fonction affiche la grille de jeu dans un format lisible pour l'utilisateur. Elle utilise des caractères spéciaux pour
 * représenter les différentes catégories de cases (mines, bonus/malus, cellules vides, etc.).  Elle prend en compte
 * si le mode brouillard est actif et masque toutes les cases si c'est le cas.
 *
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @param grille_utilisateur Un tableau 2D représentant la grille utilisateur.
 *                           `grille_utilisateur[i][j]` représente un chiffre (0, 1, ou 2) indiquant
 *                           le nombre de mines adjacentes à l'intersection de la ligne `i` et de la colonne `j`.
 * @param mines Un tableau 2D représentant la configuration des mines.
 *               `mines[i][j]` indique le nombre de mines à l'intersection de la ligne `i` et de la colonne `j`.
 * @param tours_brouillage Le nombre de tours de brouillard effectués par le joueur.
 */
void afficherGrille(int taille_grille, char grille_utilisateur[taille_grille][taille_grille], int mines[taille_grille][taille_grille], int tours_brouillage) {
    printf("\n    "); // Ajoute un espace pour l'alignement.
    for (int i = 1; i <= taille_grille; i++) {
        printf("%2d ", i); // Affiche le numéro de chaque colonne avec une largeur de 2 caractères.
    }
    printf("\n   ");
    for (int i = 0; i <= taille_grille; i++) {
        printf("___"); // Crée une ligne de tirets en dessous du numéro des colonnes.
    }
    printf("\n");

    for (int i = 0; i < taille_grille; i++) {
        printf("%2d |", i + 1); // Affiche le numéro de chaque ligne avec une largeur de 2 caractères.
        for (int j = 0; j < taille_grille; j++) {
            // RÈGLE BONUS/MALUS : Si brouillage actif, on masque tout par des '?'
            if (tours_brouillage > 0) {
                printf(" ? "); // Affiche un point d'interrogation si le mode brouillage est activé.
            } else {
                switch (grille_utilisateur[i][j]) {
                    case 'B': printf(" X "); break; // Affiche "X" pour une case bonus.
                    case 'D': printf(" D "); break; // Affiche "D" pour une case malus.
                    case 'V': printf("   "); break; // Affiche un espace vide pour les cases vides.
                    case ' ': printf(" . "); break; // Affiche "." pour les cases vides.
                    case 'M': printf(" @ "); break; // Affiche "@" pour une case mine.
                    case 'U': printf(" U "); break; // Affiche "U" pour une case bonus.
                    default:  printf(" %c ", grille_utilisateur[i][j]); break; // Affiche le caractère correspondant à la case si elle n'est ni une mine, ni un bonus/malus.
                }
            }
        }
        printf("\n"); // Ajoute un saut de ligne à la fin de chaque ligne de la grille.
    }
}


/**
 * @brief Permet à l'utilisateur d'entrer une action et des coordonnées pour interagir avec la grille de jeu.
 *
 * Cette fonction guide l'utilisateur dans le choix de son action (reveler, mettre un drapeau, sauvegarder et quitter)
 * et lui demande les coordonnées x et y de la case sur laquelle il souhaite cliquer. Elle valide les entrées de l'utilisateur
 * pour s'assurer qu'elles sont dans les limites de la grille.
 *
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @return Un objet 'position' contenant l'action choisie par l'utilisateur, ainsi que ses coordonnées x et y.
 */


position entree_utilisateur(int taille_grille) {
    position clic; // Déclare une variable de type 'position' pour stocker les actions et coordonnées de l'utilisateur.

    // Demande à l'utilisateur de choisir son action initiale.
    do {
        printf("Voulez vous :\n1) reveler la case\n2) mettre un drapeau sur la case\n3) sauvegarder et quitter la partie\n"); // Affiche le menu des actions possibles.
        scanf("%d", &clic.action); // Lit l'action choisie par l'utilisateur depuis l'entrée standard.
    } while (clic.action != 1 && clic.action != 2 && clic.action != 3); // Continue de demander à l'utilisateur jusqu'à ce qu'il entre 1, 2 ou 3.

    // Si l'utilisateur n'a pas choisi de sauvegarder et quitter (action 3), on lui demande les coordonnées de la case.
    if (clic.action != 3) {
        // Demande à l'utilisateur d'entrer les coordonnées x et y de la case.
        do {
            printf("Quelle est la position en x de la case que tu veux cliquer? "); // Demande la coordonnée x.
            scanf("%d", &clic.x); // Lit la valeur entrée par l'utilisateur pour la coordonnée x.
            printf("Quelle est la position en y de la case que tu veux cliquer? "); // Demande la coordonnée y.
            scanf("%d", &clic.y); // Lit la valeur entrée par l'utilisateur pour la coordonnée y.

            // Vérifie si les coordonnées sont valides (dans les limites de la grille).
            if (clic.x > taille_grille || clic.x < 1 || clic.y > taille_grille || clic.y < 1) { // Vérifie que les valeurs sont dans les limites du tableau.
                printf("Position invalide. Entrez une valeur entre 1 et %d.\n", taille_grille); // Affiche un message d'erreur si les coordonnées sont invalides.
            }
        } while (clic.x > taille_grille || clic.x < 1 || clic.y > taille_grille || clic.y < 1); // Continue de demander aux coordonnées jusqu'à ce qu'elles soient valides.

        // Ajuste les coordonnées pour qu'elles commencent à 0 (car les indices des tableaux commencent à 0).
        clic.x = clic.x - 1; // Soustrait 1 à la coordonnée x pour la convertir en indice de tableau.
        clic.y = clic.y - 1; // Soustrait 1 à la coordonnée y pour la convertir en indice de tableau.
    }

    // Retourne l'objet 'clic' contenant les actions et coordonnées de l'utilisateur.
    return clic; // Renvoie l'objet 'clic' au code appelant.
}




/**
 * @brief Révèle une case sur la grille de jeu, et effectue une révélations récursives si nécessaire.
 *
 * Cette fonction prend les coordonnées d'une case et révèle sa valeur si elle contient une mine ou un nombre de mines adjacentes.
 * Si la case révélée a des cases adjacentes non révélées, elle effectue une révélation récursive sur ces cases.
 *
 * @param x La coordonnée x de la case à révéler.
 * @param y La coordonnée y de la case à révéler.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @param mines Un tableau 2D représentant la configuration des mines.
 *               `mines[i][j]` indique le nombre de mines à l'intersection de la ligne `i` et de la colonne `j`.
 * @param grille_utilisateur Un tableau 2D représentant la grille utilisateur.
 *                             `grille_utilisateur[i][j]` sera mis à jour pour afficher la valeur de la case révélée.
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
 * @brief Applique un bonus ou un malus à la partie.
 *
 * Cette fonction traite les valeurs spécifiques des cases bonus/malus et met à jour les variables correspondantes
 * (nombre de vies, nombre de tours de brouillage) en conséquence.
 *
 * @param valeur_case La valeur de la case (10 pour le malus, 11 pour le bonus).
 * @param vies Un pointeur vers l'entier qui contiendra le nombre de vies restantes du joueur.
 * @param tours_brouillage Un pointeur vers l'entier qui contiendra le nombre de tours de brouillage effectués par le joueur.
 * @param case_utilisateur Un pointeur vers la variable char contenant la valeur de la case (utilisé pour afficher un message).
 */

void appliquerBonusMalus(int valeur_case, int *vies, int *tours_brouillage, char *case_utilisateur) {
    if (valeur_case == 10) { // Si le bonus est actif (valeur 10).
        *tours_brouillage = 3; // Active le brouillard en augmentant la valeur de tours_brouillage.
        printf("\nMALUS ! Brouillage active ! Vous ne voyez plus rien pendant 2 tours !\n"); // Affiche un message indiquant que le brouillard est actif.
    } else if (valeur_case == 11) { // Si le bonus est actif (valeur 11).
        (*vies)++; // Incrémente le nombre de vies du joueur.
        printf("\nBONUS ! +1 UP obtenu ! Vous gagnez une vie (Total : %d vies)\n", *vies); // Affiche un message indiquant que le bonus a été appliqué et affiche le nouveau nombre de vies.
    }
}

/**
 * @brief Gère l'explosion d'une mine sur la grille.
 *
 * Cette fonction réduit le nombre de vies du joueur lorsqu'il touche une mine, et gère la fin de partie si le nombre de
 * vies tombe à zéro.
 *
 * @param vies Un pointeur vers l'entier qui contiendra le nombre de vies restantes du joueur.
 * @param case_utilisateur Un pointeur vers la variable char contenant la valeur de la case (pour mettre à jour la case touchée par une mine).
 * @return 0 si le joueur survit, -1 si le joueur est mort.
 */


int gererExplosionMine(int *vies, char *case_utilisateur) {
    (*vies)--; // Décrémente le nombre de vies du joueur.

    if (*vies > 0) { // Si le joueur a encore des vies...
        *case_utilisateur = 'B'; // Change la valeur de la case touchée en 'B' (pour marque d'explosion).
        printf("\nBOOM ! Vous avez touche une mine ! Heureusement une vie vous sauve (Reste : %d vies)\n", *vies); // Affiche un message indiquant que le joueur a touché une mine et qu'il conserve une vie.
        return 0; // Retourne 0 pour indiquer que l'explosion n'a pas conduit à la fin de partie.
    } else {
        *case_utilisateur = '*'; // Change la valeur de la case touchée en '*' (pour indiquer que la case est détruite).
        printf("\nGAME OVER ! Vous n'avez plus de vies.\n"); // Affiche un message indiquant que le joueur a perdu.
        return -1; // Retourne -1 pour indiquer que l'explosion a conduit à la fin de partie.
    }
}