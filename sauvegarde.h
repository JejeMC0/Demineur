#ifndef PROJET_IF2_SAUVEGARDE_H
#define PROJET_IF2_SAUVEGARDE_H




/**
  * @brief Sauvegarde l'état d'une partie dans un fichier.
  *
  * Cette fonction enregistre les informations nécessaires à la reconstitution d'une partie,
  * incluant la taille de la grille, le nombre de mines, la configuration des mines et
  * de la grille utilisateur, le mode de jeu, le nombre de vies restantes, le nombre de tours
  * de brouillage effectués, la couche d'objets et le temps écoulé.  Elle utilise un format texte
  * simple pour stocker ces données dans un fichier.
  *
  * @param nom_fichier Le nom du fichier dans lequel sauvegarder la partie.
  * @param taille_grille La dimension de la grille (nombre de lignes et de colonnes).
  * @param nb_mine Le nombre de mines présentes sur la grille.
  * @param mines Un tableau 2D représentant la configuration des mines.
  *               `mines[i][j]` indique le nombre de mines à l'intersection de la ligne `i` et de la colonne `j`.
  * @param grille_utilisateur Un tableau 2D représentant la grille visible par le joueur.
  *                             `grille_utilisateur[i][j]` représente un chiffre (0, 1, ou 2) indiquant
  *                             le nombre de mines adjacentes à l'intersection de la ligne `i` et de la colonne `j`.
  * @param mode L'indicateur du mode de jeu (par exemple, "classique", "expert").
  * @param vies Le nombre de vies restantes du joueur.
  * @param tours_brouillage Le nombre de tours de brouillage effectués par le joueur.
  * @param objets Un tableau 2D représentant les bonus et malus appliqués au joueur.
  *               `objets[i][j]` indique le bonus ou malus appliqué à l'intersection de la ligne `i` et de la colonne `j`.
  * @param temps_ecoule Le temps écoulé pendant la partie.
  */

void sauvegardePartie(const char *nom_fichier, int taille_grille, int nb_mine, int mines[taille_grille][taille_grille], char grille_utilisateur[taille_grille][taille_grille], int mode, int vies, int tours_brouillage, int objets[taille_grille][taille_grille], int temps_ecoule);


/**
 * @brief Charge l'état d'une partie à partir d'un fichier.
 *
 * Cette fonction lit les données d'une sauvegarde dans un fichier et les met à jour dans les variables
 * correspondantes. Elle permet de reprendre une partie précédemment sauvegardée.
 *
 * @param nom_fichier Le nom du fichier contenant la sauvegarde à charger.
 * @param taille_grille Un pointeur vers l'entier qui contiendra la dimension de la grille.
 * @param nb_mines Un pointeur vers l'entier qui contiendra le nombre de mines présentes sur la grille.
 * @param mines Un double pointeur 2D représentant le tableau des mines.
 *               `mines[i][j]` sera modifié pour contenir le nombre de mines à l'intersection de la ligne `i` et de la colonne `j`.
 * @param grille_utilisateur Un double pointeur 2D représentant la grille visible par le joueur.
 *                             `grille_utilisateur[i][j]` sera modifié pour contenir la valeur de la cellule à l'intersection de la ligne `i` et de la colonne `j`.
 * @param mode Un pointeur vers l'entier qui contiendra le mode de jeu (par exemple, "classique", "expert").
 * @param vies Un pointeur vers l'entier qui contiendra le nombre de vies restantes du joueur.
 * @param tours_brouillage Un pointeur vers l'entier qui contiendra le nombre de tours de brouillage effectués par le joueur.
 * @param objets Un double pointeur 2D représentant les bonus et malus appliqués au joueur.
 *               `objets[i][j]` sera modifié pour contenir la valeur du bonus/malus à l'intersection de la ligne `i` et de la colonne `j`.
 * @param temps_ecoule Un pointeur vers l'entier qui contiendra le temps écoulé pendant la partie.
 */

void chargerPartie(const char *nom_fichier, int *taille_grille, int *nb_mines, int mines[*taille_grille][*taille_grille], char grille_utilisateur[*taille_grille][*taille_grille], int *mode, int *vies, int *tours_brouillage, int objets[*taille_grille][*taille_grille], int *temps_ecoule);
#endif //PROJET_IF2_SAUVEGARDE_H
