#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "demineur.h"
#include "initialisation.h"
#include "sauvegarde.h"

int main(void)
{
    srand(time(NULL)); // Initialise le générateur de nombres aléatoires. Important pour la pseudo-aléatoire !
    int lancement = selectionnerOptionMenu();  // Obtient le choix du menu utilisateur (nouvelle partie, chargement, quitter)

    int taille_grille = 0 , nb_mine = 0, mode_jeu = 1;  // Valeurs par défaut
    int vies = 1; // Nombre de vies dont dispose le joueur.
    int tours_brouillage = 0; // Compteur pour les tours avec des effets bonus/malus (si applicable)
    int temps_deja_ecoule = 0; // Temps déjà écoulé dans une partie sauvegardée

    regle Configuration_temps;  // Structure pour stocker les données de configuration

    if (lancement == 1) { // Nouvelle Partie
        Configuration_temps = configurationPartie();  // Obtient la taille de la grille, le nombre de mines et le mode de difficulté auprès de l'utilisateur.
        taille_grille = Configuration_temps.dimension;
        nb_mine = mineDifficulte(Configuration_temps);  // Détermine le nombre de mines en fonction du niveau de difficulté
        mode_jeu = Configuration_temps.mode; // Définit le mode de jeu (facile/difficile, peut-être)

        printf("Nombre de mines : %d \n", nb_mine); // Affiche le nombre de mines à l'utilisateur.
    }

    if (lancement == 2) { // Charger la Partie
        FILE *f = fopen("sauvegarde.csv", "r");  // Ouvre le fichier de sauvegarde en mode lecture.
        if (f != NULL) {
            fscanf(f, "%d;%d;%d;%d;%d;%d\n", &taille_grille, &nb_mine, &mode_jeu, &vies, &tours_brouillage, &temps_deja_ecoule);  // Lit les données sauvegardées
            fclose(f); // Ferme le fichier. TRÈS IMPORTANT !
        } else {
            printf("Erreur: Impossible de lire le fichier de sauvegarde. Fermeture.\n");
            return 1;  // Indique qu'une erreur s'est produite (code de retour non nul).
        }
    }

    if (lancement == 3) { // Quitter le Jeu
        printf("\nAu revoir !\n");
        return 0;  // Termine le programme avec succès.
    }

    // --- Initialisation du plateau de jeu ---

    // Déclaration des matrices de jeu : mines, objets, grille utilisateur
    int mines[taille_grille][taille_grille];
    int objets[taille_grille][taille_grille]; // Stocke les objets bonus/malus. Séparé de la disposition des mines.
    char grille_utilisateur[taille_grille][taille_grille]; // La grille que l'utilisateur voit. Initialement cachée.

    // Initialise toutes les cellules à vide (important !)
    for (int i = 0; i < taille_grille; i++) {
        for (int j = 0; j < taille_grille; j++) {
            grille_utilisateur[i][j] = ' ';  // Cellule vide.
            mines[i][j] = 0; // Aucune mine initialement.
            objets[i][j] = 0; // Aucun bonus/malus initialement.
        }
    }

    if (lancement == 2) {
        chargerPartie("sauvegarde.csv", &taille_grille, &nb_mine, mines, grille_utilisateur, &mode_jeu, &vies, &tours_brouillage, objets, &temps_deja_ecoule); // Charge l'état de la partie à partir du fichier.
    }

    if (lancement == 1) {  // Si une nouvelle partie est créée :
        int valeur_mines[nb_mine];  // Tableau pour stocker les positions des mines.
        generePositionMines(nb_mine, valeur_mines, taille_grille); // Génère des emplacements de mine aléatoires

        for (int i = 0; i < nb_mine; ++i) {
            position mine_temp = position_x_y(valeur_mines[i], taille_grille);  // Convertit l'indice linéaire en coordonnées x/y.
            mines[mine_temp.y][mine_temp.x] = 9; // Marque la cellule comme une mine (la valeur '9' semble arbitraire).
        }

        valeurCaseAutourMine(taille_grille, mines);  // Calcule les nombres autour de chaque mine (combien de mines adjacentes)

        if (mode_jeu == 2) { // Si en mode "difficile" :
            int nb_bonus_malus = roundf(0.5 * taille_grille); // Détermine le nombre d'objets bonus/malus. La formule est importante à comprendre.
            if (nb_bonus_malus < 1) nb_bonus_malus = 1;
            generePositionBrouillage(nb_bonus_malus, taille_grille, mines, objets); // Place les objets bonus/malus aléatoirement sur la grille.
            generePosition1UP(nb_bonus_malus, taille_grille, mines, objets); // Génère la position de l'objet 1 UP (peut-être une amélioration de vie ?)
        }
    }

    // --- Boucle Principale du Jeu ---
    position clic_temp;  // Variable pour stocker les coordonnées du clic utilisateur et l'action.
    int statut_partie = 0;  // Indicateur de l'état du jeu (0=en cours, 1=victoire, -1=défaite, 2=quitter)
    time_t debut = time(NULL); // Enregistre l'heure de début pour le chronométrage

    while (statut_partie == 0)
    {
        // Boucle principale du jeu : continue jusqu'à la victoire ou à la défaite.

        afficherGrille(taille_grille, grille_utilisateur, mines, tours_brouillage);  // Affiche l'état actuel du jeu à l'utilisateur
        clic_temp = entree_utilisateur(taille_grille); // Obtient l'entrée de l'utilisateur (emplacement du clic et action : révéler, drapeau)

        if (clic_temp.action == 3)
        {
            // Option Sauvegarde
            int temps_total = (int)(time(NULL) - debut) + temps_deja_ecoule;
            sauvegardePartie("sauvegarde.csv", taille_grille, nb_mine, mines, grille_utilisateur, mode_jeu, vies, tours_brouillage, objets, temps_total); // Sauvegarde l'état actuel du jeu.
            int choix_post_sauvegarde;
            do {
                printf("\nPartie sauvegardée. Que voulez-vous faire :\n1) Continuer à jouer\n2) Quitter le jeu\nVotre choix : ");
                scanf("%d", &choix_post_sauvegarde);
            } while (choix_post_sauvegarde != 1 && choix_post_sauvegarde != 2);

            if (choix_post_sauvegarde == 2) {
                printf("Merci d'avoir joué. Au revoir\n");
                statut_partie = 2;
            }

        }
        if (clic_temp.action == 1) { // Action Révéler Cellule
            if (grille_utilisateur[clic_temp.y][clic_temp.x] != ' ' && grille_utilisateur[clic_temp.y][clic_temp.x] != 'D') {
                printf("\nErreur : Cette case a déjà été activée.\n");

            }

            // ÉTAPE 1 : Déclencher l'objet s'il y en a un sur la case
            int objet_cache = objets[clic_temp.y][clic_temp.x];
            if (objet_cache == 10 || objet_cache == 11) {
                appliquerBonusMalus(objet_cache, &vies, &tours_brouillage, &grille_utilisateur[clic_temp.y][clic_temp.x]);
                objets[clic_temp.y][clic_temp.x] = 0; // L'objet est maintenant ramassé
            }

            // ÉTAPE 2 : Traitement classique du terrain sous l'objet (Chiffre ou mine)
            int cible = mines[clic_temp.y][clic_temp.x];

            if (cible == 9) {  // Mine !
                statut_partie = gererExplosionMine(&vies, &grille_utilisateur[clic_temp.y][clic_temp.x]); // Gère l'explosion de la mine : réduit les vies, révèle éventuellement d'autres cellules.
                if (statut_partie == -1) {  // Jeu terminé !
                    tours_brouillage = 0;
                    for (int i = 0; i < taille_grille; i++) {
                        for (int j = 0; j < taille_grille; j++) {
                            if (mines[i][j] == 9) grille_utilisateur[i][j] = '*'; // Révèle toutes les mines.
                        }
                    }
                    afficherGrille(taille_grille, grille_utilisateur, mines, tours_brouillage);
                }
            } else {
                if (cible == 0) {
                    revelerCase(clic_temp.x, clic_temp.y, taille_grille, mines, grille_utilisateur); // Révèle la cellule récursivement si elle est vide.
                } else {
                    grille_utilisateur[clic_temp.y][clic_temp.x] = '0' + cible;  // Affiche le nombre de mines adjacentes.
                }
            }

            // Gestion de fin de tour
            if (statut_partie == 0) { // Si le jeu est toujours en cours :
                if (tours_brouillage > 0) {
                    tours_brouillage--;
                }

                // VÉRIFICATION DE LA VICTOIRE
                int cases_restantes = 0;
                for (int i = 0; i < taille_grille; i++) {
                    for (int j = 0; j < taille_grille; j++) {
                        if ((grille_utilisateur[i][j] == ' ' || grille_utilisateur[i][j] == 'D') && mines[i][j] != 9) {
                            cases_restantes++;
                        }
                    }
                }

                if (cases_restantes == 0) {
                    tours_brouillage = 0;
                    afficherGrille(taille_grille, grille_utilisateur, mines, tours_brouillage);
                    printf("\nFélicitations ! Vous avez révélé toutes les cases sûres. VICTOIRE !\n");
                    statut_partie = 1; // Jeu gagné !
                }

                int temps_total = (int)(time(NULL) - debut) + temps_deja_ecoule;
                printf("Temps écoulé : %d:%.02d\n", temps_total / 60, temps_total % 60); // Affiche le temps écoulé.
            }

        }
        else if (clic_temp.action == 2) {  // Action Drapéau Cellule

            if (grille_utilisateur[clic_temp.y][clic_temp.x] == 'D') {
                grille_utilisateur[clic_temp.y][clic_temp.x] = ' '; // Retire le drapeau
                printf("Drapeau retiré en (%d, %d)\n", clic_temp.x + 1, clic_temp.y + 1);
            } else if (grille_utilisateur[clic_temp.y][clic_temp.x] == ' ') {
                grille_utilisateur[clic_temp.y][clic_temp.x] = 'D'; // Place le drapeau
                printf("Drapeau placé en (%d, %d)\n", clic_temp.x + 1, clic_temp.y + 1);
            } else {
                printf("\nImpossible de mettre un drapeau sur une case déjà révélée !\n");
            }
        }

    } // Fin de la boucle principale du jeu
    return 0;  // Termine le programme avec succès.
}