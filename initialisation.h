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
 * @brief Permet à l'utilisateur de choisir une option dans un menu principal.
 *
 * Cette fonction affiche un menu avec les options démarrer une partie, reprendre une partie
 * ou quitter le jeu. Elle valide ensuite l'entrée de l'utilisateur pour s'assurer qu'il choisit
 * une option valide (1, 2 ou 3).
 *
 * @return L'entier représentant le choix de l'utilisateur (1, 2 ou 3).
 */

int selectionnerOptionMenu();






/**
 * @brief Permet à l'utilisateur de configurer les paramètres d'une partie (mode, dimension, difficulté).
 *
 * Cette fonction guide l'utilisateur dans le choix des options pour configurer une nouvelle partie.
 * Elle utilise des boucles `do-while` pour valider les entrées de l'utilisateur et s'assurer qu'elles
 * sont dans les plages autorisées.  Elle retourne un objet 'regle' contenant ces paramètres configurés.
 *
 * @return Un objet 'regle' contenant les paramètres de configuration de la partie (mode, dimension, difficulté).
 */


regle configurationPartie();




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

int mineDifficulte(regle Configuration);




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

void generePositionMines(int nb_mine, int valeur_mines[nb_mine], int taille_grille);





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

void valeurCaseAutourMine(int taille_grille, int mines[taille_grille][taille_grille]);





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

void generePositionBrouillage(int nb_caseBrouillard, int taille_grille, int mines[taille_grille][taille_grille], int objets[taille_grille][taille_grille]);




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

void generePosition1UP(int nb_caseUP, int taille_grille, int mines[taille_grille][taille_grille], int objets[taille_grille][taille_grille]);

#endif //PROJET_IF2_INITIALISATION_H
