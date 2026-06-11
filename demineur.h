//
// Created by romain on 25/05/2026.
//

#ifndef PROJET_IF2_DEMINEUR_H
#define PROJET_IF2_DEMINEUR_H

#endif //PROJET_IF2_DEMINEUR_H



/**
 * @brief Structure représentant une position sur la grille.
 *
 * Cette structure contient les coordonnées x et y d'une case sur la grille, ainsi que l'action à effectuer sur cette case.
 */

typedef struct {
    int x;
    int y;
    int action; // 1 = Révéler, 2 = Drapeau
}position;



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

position position_x_y(int pos, int taille_grille);






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

void afficherGrille(int taille_grille, char grille_utilisateur[taille_grille][taille_grille], int mines[taille_grille][taille_grille], int tours_brouillage);




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

position entree_utilisateur(int taille_grille);




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

void revelerCase(int x, int y, int taille_grille, int mines[taille_grille][taille_grille], char grille_utilisateur[taille_grille][taille_grille]);


void appliquerBonusMalus(int valeur_case, int *vies, int *tours_brouillage, char *case_utilisateur);
int gererExplosionMine(int *vies, char *case_utilisateur);
