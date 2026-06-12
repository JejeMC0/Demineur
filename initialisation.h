//
// Created by romain on 29/05/2026.
//

#ifndef PROJET_IF2_INITIALISATION_H
#define PROJET_IF2_INITIALISATION_H


/**
 * @brief Structure contenant les paramètres de configuration d'une partie de jeu.
 *
 * Cette structure stocke les informations relatives à une partie de jeu, telles que sa dimension, sa difficulté et son mode de jeu.
 */

typedef struct {
    int dimension;
    int difficulte;
    int mode;
}regle;



/**
 * @brief Obtient le choix de l'utilisateur dans un menu.
 *
 * Cette fonction affiche un menu d'options et attend que l'utilisateur entre un choix valide.
 * Elle utilise une boucle `do...while` pour s'assurer que l'utilisateur entre bien une valeur valide.
 *
 * @return Le choix de l'utilisateur (1, 2 ou 3).
 */

int selectionnerOptionMenu();






/**
 * @brief Configure les paramètres d'une partie de jeu.
 *
 * Cette fonction permet à l'utilisateur de choisir le mode de jeu, la dimension du champ de mine et la difficulté.
 * Elle utilise des boucles `do...while` pour s'assurer que l'utilisateur entre des valeurs valides pour chaque paramètre.
 *
 * @return Une structure `regle` contenant les paramètres configurés par l'utilisateur.
 */

regle configurationPartie();




/**
 * @brief Calcule le nombre de mines pour une partie donnée en fonction de la difficulté.
 *
 * Cette fonction calcule le nombre de mines à placer sur la grille, en fonction du mode de jeu et de la difficulté choisis par l'utilisateur.
 * Elle utilise des formules différentes pour chaque niveau de difficulté.
 *
 * @param Configuration La structure `regle` contenant les paramètres de configuration de la partie.
 * @return Le nombre de mines à placer sur la grille (entier).
 */

int mineDifficulte(regle Configuration);




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

void generePositionMines(int nb_mine, int valeur_mines[nb_mine], int taille_grille);





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

void valeurCaseAutourMine(int taille_grille, int mines[taille_grille][taille_grille]);





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

void generePositionBrouillage(int nb_caseBrouillard, int taille_grille, int mines[taille_grille][taille_grille], int objets[taille_grille][taille_grille]);




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

void generePosition1UP(int nb_caseUP, int taille_grille, int mines[taille_grille][taille_grille], int objets[taille_grille][taille_grille]);



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

int verificationTableau (int valeur_cible ,int taille_grille, int tabAverif[taille_grille][taille_grille]);


#endif //PROJET_IF2_INITIALISATION_H
