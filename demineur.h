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
 * @brief Convertit un index dans une grille en coordonnées (x, y).
 *
 * Cette fonction prend un index unique représentant une case dans la grille et le convertit en un couple de coordonnées (x, y)
 * qui indiquent la position de cette case sur la grille. Elle gère les grilles dont la taille est supérieure à 1.
 *
 * @param pos L'index unique de la case dans la grille.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @return Un objet 'position' contenant les coordonnées (x, y) de la case.
 */

position position_x_y(int pos, int taille_grille);






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


void afficherGrille(int taille_grille, char grille_utilisateur[taille_grille][taille_grille], int mines[taille_grille][taille_grille], int tours_brouillage);



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


position entree_utilisateur(int taille_grille);




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


void revelerCase(int x, int y, int taille_grille, int mines[taille_grille][taille_grille], char grille_utilisateur[taille_grille][taille_grille]);



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

void appliquerBonusMalus(int valeur_case, int *vies, int *tours_brouillage, char *case_utilisateur);



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

int gererExplosionMine(int *vies, char *case_utilisateur);