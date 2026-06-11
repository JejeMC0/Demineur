#ifndef PROJET_IF2_SAUVEGARDE_H
#define PROJET_IF2_SAUVEGARDE_H



/**
 * @brief Sauvegarde l'état d'une partie de jeu dans un fichier.
 *
 * Cette fonction permet de sauvegarder les informations relatives à une partie
 * de jeu, notamment la taille de la grille, le nombre de mines, et les grilles
 * "solution" et "utilisateur".  Elle écrit ces données dans un fichier spécifié.
 *
 * @param nom_fichier Le nom du fichier dans lequel sauvegarder la partie.
 * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
 * @param nb_mine Le nombre de mines présentes sur la grille.
 * @param mines Un tableau 2D représentant la grille "solution" (mines cachées).
 *               `mines[i][j]` représente le nombre de mines à l'intersection de la ligne `i` et de la colonne `j`.
 * @param grille_utilisateur Un tableau 2D représentant la grille "utilisateur".
 *                           `grille_utilisateur[i][j]` représente l'état de la case à l'intersection de la ligne `i` et de la colonne `j` (ex: 'X', 'O', '.').
 */

void sauvegardePartie(const char *nom_fichier, int taille_grille, int nb_mine, int mines[taille_grille][taille_grille], char grille_utilisateur[taille_grille][taille_grille], int mode, int vies, int tours_brouillage, int objets[taille_grille][taille_grille], int temps_ecoule);


/**
 * @brief Charge l'état d'une partie de jeu depuis un fichier.
 *
 * Cette fonction permet de charger les informations relatives à une partie
 * de jeu, notamment la taille de la grille, le nombre de mines, et les grilles
 * "solution" et "utilisateur", à partir d'un fichier spécifié. Elle lit ces données du fichier.
 *
 * @param nom_fichier Le nom du fichier contenant l'état de la partie à charger.
 * @param taille_grille Un pointeur vers un entier qui sera initialisé avec la dimension de la grille (nombre de lignes et de colonnes).
 * @param nb_mines Un pointeur vers un entier qui sera initialisé avec le nombre de mines présentes sur la grille.
 * @param mines Un tableau 2D représentant la grille "solution".  Le pointeur `mines` est utilisé pour modifier le contenu de ce tableau.
 *               `mines[i][j]` représente le nombre de mines à l'intersection de la ligne `i` et de la colonne `j`.
 * @param grille_utilisateur Un tableau 2D représentant la grille "utilisateur".  Le pointeur `grille_utilisateur` est utilisé pour modifier le contenu de ce tableau.
 *                            `grille_utilisateur[i][j]` représente l'état de la case à l'intersection de la ligne `i` et de la colonne `j` (ex: 'X', 'O', '.').
 */

void chargerPartie(const char *nom_fichier, int *taille_grille, int *nb_mines, int mines[*taille_grille][*taille_grille], char grille_utilisateur[*taille_grille][*taille_grille], int *mode, int *vies, int *tours_brouillage, int objets[*taille_grille][*taille_grille], int *temps_ecoule);
#endif //PROJET_IF2_SAUVEGARDE_H
