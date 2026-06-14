//
// Created by romain on 29/05/2026.
//

#include "initialisation.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Permet à l'utilisateur de choisir une option dans un menu principal.
 *
 * Cette fonction affiche un menu avec les options démarrer une partie, reprendre une partie
 * ou quitter le jeu. Elle valide ensuite l'entrée de l'utilisateur pour s'assurer qu'il choisit
 * une option valide (1, 2 ou 3).
 *
 * @return L'entier représentant le choix de l'utilisateur (1, 2 ou 3).
 */

int selectionnerOptionMenu() {
    printf("================ Menu ===============\n"); // Affiche le titre du menu.
    printf("1) Demarrer une partie\n"); // Décrit l'option 1.
    printf("2) Reprendre une partie\n"); // Décrit l'option 2.
    printf("3) Quitter\n"); // Décrit l'option 3.
    printf("===========================================\n"); // Affiche la fin du menu.

    // Demande à l'utilisateur de faire un choix.
    printf("Votre choix : ");

    // Lit le choix de l'utilisateur et le stocke dans la variable 'choix'.
    int choix;
    scanf("%d", &choix); // Lit un entier depuis l'entrée standard et l'assigne à la variable 'choix'.

    // Boucle tant que le choix n'est pas 1, 2 ou 3.  Cette boucle assure
    // que l'utilisateur entre une option valide du menu.
    while (choix != 1 && choix != 2 && choix != 3) // Tant que 'choix' n'est pas égal à 1, 2 ou 3...
    {
        printf("Choix invalide. Veuillez choisir parmi 1, 2 ou 3.\n"); // Affiche un message d'erreur si le choix est invalide.
        printf("Votre choix : "); // Demande à l'utilisateur de refaire son choix.
        scanf("%d", &choix); // Lit le nouveau choix de l'utilisateur et l'assigne à la variable 'choix'.
    }

    // Retourne le choix de l'utilisateur.  Ceci est la valeur qui sera utilisée
    // par le code appelant pour déterminer quelle action effectuer.
    return choix; // Renvoie la valeur de 'choix' au code appelant.
}


/**
 * @brief Permet à l'utilisateur de configurer les paramètres d'une partie (mode, dimension, difficulté).
 *
 * Cette fonction guide l'utilisateur dans le choix des options pour configurer une nouvelle partie.
 * Elle utilise des boucles `do-while` pour valider les entrées de l'utilisateur et s'assurer qu'elles
 * sont dans les plages autorisées.  Elle retourne un objet 'regle' contenant ces paramètres configurés.
 *
 * @return Un objet 'regle' contenant les paramètres de configuration de la partie (mode, dimension, difficulté).
 */

regle configurationPartie() {
    regle Configuration; // Déclare une variable de type 'regle' pour stocker les paramètres de configuration de la partie.

    // Première boucle : permet à l'utilisateur de choisir le mode de jeu.
    do {
        printf("================ Mode de jeu ===============\n"); // Affiche le titre du menu des modes de jeu.
        printf("1) Mode de jeu Classique\n"); // Décrit l'option 1 (Mode de jeu Classique).
        printf("2) Mode de Jeu Bonus/Malus\n"); // Décrit l'option 2 (Mode de Jeu Bonus/Malus).
        printf("===========================================\n"); // Affiche la fin du menu des modes de jeu.
        printf("Votre choix : "); // Demande à l'utilisateur de faire un choix.

        // Lit le choix de l'utilisateur et le stocke dans la variable 'Configuration.mode'.
        scanf("%d", &Configuration.mode); // Lit un entier depuis l'entrée standard et l'assigne à la variable 'Configuration.mode'.
    } while (Configuration.mode != 1 && Configuration.mode != 2); // Continue de demander à l'utilisateur jusqu'à ce qu'il entre 1 ou 2.

    // Deuxième boucle : permet à l'utilisateur de choisir la dimension du champ de mine.
    do {
        printf("================ Dimension du champ de mine ===============\n"); // Affiche le titre du menu des dimensions du champ de mine.
        printf("Le champ de mine peut avoir des dimensions de 6x6 a 12x12\n"); // Décrit les dimensions possibles du champ de mine.
        printf("===========================================\n"); // Affiche la fin du menu des dimensions du champ de mine.
        printf("Votre choix : "); // Demande à l'utilisateur de faire un choix.

        // Lit le choix de l'utilisateur et le stocke dans la variable 'Configuration.dimension'.
        scanf("%d", &Configuration.dimension); // Lit un entier depuis l'entrée standard et l'assigne à la variable 'Configuration.dimension'.
    } while (Configuration.dimension < 6 || Configuration.dimension > 12); // Continue de demander à l'utilisateur jusqu'à ce que la dimension soit comprise entre 6 et 12.

    // Troisième boucle : permet à l'utilisateur de choisir la difficulté.
    do {
        printf("\n=============== Difficulte ===============\n"); // Affiche le titre du menu des difficultés.
        printf("1) Facile\n"); // Décrit l'option 1 (Facile).
        printf("2) Moyen\n"); // Décrit l'option 2 (Moyen).
        printf("3) Difficile\n"); // Décrit l'option 3 (Difficile).
        printf("===========================================\n"); // Affiche la fin du menu des difficultés.
        printf("Votre choix : "); // Demande à l'utilisateur de faire un choix.

        // Lit le choix de l'utilisateur et le stocke dans la variable 'Configuration.difficulte'.
        scanf("%d", &Configuration.difficulte); // Lit un entier depuis l'entrée standard et l'assigne à la variable 'Configuration.difficulte'.
    } while (Configuration.difficulte < 1 || Configuration.difficulte > 3); // Continue de demander à l'utilisateur jusqu'à ce que la difficulté soit comprise entre 1 et 3.

    // Affiche des messages de débogage pour vérifier les valeurs des variables.
    printf("DEBUG: Dans la fonction, difficulte vaut : %d\n", Configuration.difficulte); // Affiche la valeur de 'Configuration.difficulte'.
    printf("DEBUG: Dans la fonction, mode vaut : %d\n", Configuration.mode); // Affiche la valeur de 'Configuration.mode'.
    printf("DEBUG: Dans la fonction, dimension vaut : %d\n", Configuration.dimension); // Affiche la valeur de 'Configuration.dimension'.

    // Retourne l'objet 'Configuration' contenant les paramètres de configuration de la partie.
    return Configuration; // Renvoie l'objet 'Configuration' au code appelant.
}



/**
 * @brief Détermine le nombre de mines à placer sur la grille en fonction de la difficulté sélectionnée.
 *
 * Cette fonction prend l'objet 'regle' contenant les paramètres de configuration de la partie et calcule
 * le nombre de mines nécessaires pour un niveau de difficulté donné. Elle utilise une structure `switch`
 * pour déterminer le nombre de mines approprié en fonction du choix de l'utilisateur (facile, moyen ou difficile).
 *
 * @param Configuration Un objet 'regle' contenant les paramètres de configuration de la partie (mode, dimension, difficulté).
 * @return Le nombre de mines calculé (un entier arrondi au plus proche).
 */

int mineDifficulte(regle Configuration) {
    float nb_mine = 0.0; // Déclare une variable de type float pour stocker le nombre de mines.

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
    printf("%f \n", nb_mine); // Affiche la valeur de 'nb_mine' pour aider au débogage.

    // Convertit la valeur float du nombre de mines en un entier et retourne cette valeur.
    return (int)roundf(nb_mine); // Convertit la valeur float en un entier, arrondie au plus près, et la retourne.
}



/**
 * @brief Génère les positions des mines sur la grille.
 *
 * Cette fonction place aléatoirement le nombre de mines spécifié sur une grille donnée. Elle utilise un algorithme
 * pour éviter que plusieurs mines ne soient placées aux mêmes coordonnées et stocke les positions des mines dans un tableau.
 *
 * @param nb_mine Le nombre de mines à placer sur la grille.
 * @param valeur_mines Un tableau 2D (en réalité, un tableau 1D) qui contiendra les coordonnées (indices) des mines.
 *                      `valeur_mines[i]` sera l'indice (ligne et colonne) d'une mine sur la grille.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 */

void generePositionMines(int nb_mine, int valeur_mines[nb_mine], int taille_grille) {
    // Affiche le nombre de mines et la taille de la grille pour information.
    printf("%d  mines\n", nb_mine); // Affiche le nombre de mines à placer.
    printf("%d  taille\n", taille_grille); // Affiche la taille de la grille.

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
 * @brief Calcule et met à jour les valeurs des cases autour des mines sur la grille.
 *
 * Cette fonction parcourt chaque case de la grille et, si une case est identifiée comme étant une mine (valeur 9),
 * elle incrémente le nombre de mines adjacentes à toutes les cases voisines (dans les huit directions).
 *
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @param mines Un tableau 2D représentant la configuration des mines.
 *               `mines[i][j]` indique le nombre de mines à l'intersection de la ligne `i` et de la colonne `j`.
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
 * @brief Génère les positions du brouillard (case brouillée) sur la grille.
 *
 * Cette fonction place aléatoirement le nombre de cases brouillées spécifié sur la grille, en s'assurant qu'elles ne se trouvent pas
 * sur des mines ou sur d'autres objets (bonus/malus). Elle utilise une boucle `do-while` pour garantir que chaque position
 * choisie est valide.
 *
 * @param nb_caseBrouillard Le nombre de cases à brouiller sur la grille.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @param mines Un tableau 2D représentant la configuration des mines.
 *               `mines[i][j]` indique le nombre de mines à l'intersection de la ligne `i` et de la colonne `j`.
 * @param objets Un tableau 2D représentant les bonus et malus appliqués au joueur.
 *               `objets[i][j]` indique le bonus ou malus appliqué à l'intersection de la ligne `i` et de la colonne `j`.
 */


void generePositionBrouillage(int nb_caseBrouillard, int taille_grille, int mines[taille_grille][taille_grille], int objets[taille_grille][taille_grille]) {
    for (int i = 0; i < nb_caseBrouillard; ++i) {
        int rx, ry; // x, y de la case brouillée.
        do {
            // Génère une position aléatoire sur la grille.
            int pos = rand() % (taille_grille * taille_grille);
            rx = pos % taille_grille; // Coordonnée x.
            ry = pos / taille_grille; // Coordonnée y.
        } while (mines[ry][rx] == 9 || objets[ry][rx] != 0); // Vérifie que la position n'est pas sur une mine ou un autre objet.

        // Définit la case brouillée.
        objets[ry][rx] = 10; // 10 est une valeur arbitraire pour représenter le brouillage.
    }
}



/**
 * @brief Génère les positions des cases 1UP (bonus) sur la grille.
 *
 * Cette fonction place aléatoirement le nombre de cases 1UP spécifié sur la grille, en s'assurant qu'elles ne se trouvent pas
 * sur des mines ou sur d'autres objets (bonus/malus). Elle utilise une boucle `do-while` pour garantir que chaque position
 * choisie est valide.
 *
 * @param nb_caseUP Le nombre de cases 1UP à placer sur la grille.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @param mines Un tableau 2D représentant la configuration des mines.
 *               `mines[i][j]` indique le nombre de mines à l'intersection de la ligne `i` et de la colonne `j`.
 * @param objets Un tableau 2D représentant les bonus et malus appliqués au joueur.
 *               `objets[i][j]` indique le bonus ou malus appliqué à l'intersection de la ligne `i` et de la colonne `j`.
 */

void generePosition1UP(int nb_caseUP, int taille_grille, int mines[taille_grille][taille_grille], int objets[taille_grille][taille_grille]) {
    for (int i = 0; i < nb_caseUP; ++i) {
        int rx, ry; // x, y de la case 1UP.
        do {
            // Génère une position aléatoire sur la grille.
            int pos = rand() % (taille_grille * taille_grille);
            rx = pos % taille_grille; // Coordonnée x.
            ry = pos / taille_grille; // Coordonnée y.
        } while (mines[ry][rx] == 9 || objets[ry][rx] != 0); // Vérifie que la position n'est pas sur une mine ou un autre objet.

        // Définit la case 1UP.
        objets[ry][rx] = 11; // 11 est une valeur arbitraire pour représenter le "1UP".
    }
}