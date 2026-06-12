#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
#include <time.h>
#include "demineur.h"
#include "initialisation.h"
#include "sauvegarde.h"

int main(void) {
    srand(time(NULL));
    int lancement = selectionnerOptionMenu();

    int taille_grille = 0 , nb_mine = 0, mode_jeu = 1;
    int vies = 1;
    int tours_brouillage = 0;
    int temps_deja_ecoule = 0;

    regle Configuration_temps;

    if (lancement == 1) {
        Configuration_temps = configurationPartie();
        taille_grille = Configuration_temps.dimension;
        nb_mine = mineDifficulte(Configuration_temps);
        mode_jeu = Configuration_temps.mode;
        printf("Nombre de mines : %d \n", nb_mine);
    }

    if (lancement == 2) {
        FILE *f = fopen("sauvegarde.csv", "r");
        if (f != NULL) {
            fscanf(f, "%d;%d;%d;%d;%d;%d\n", &taille_grille, &nb_mine, &mode_jeu, &vies, &tours_brouillage, &temps_deja_ecoule);
            fclose(f);
        } else {
            printf("Erreur: Impossible de lire le fichier de sauvegarde. Fermeture.\n");
            return 1;
        }
    }

    if (lancement == 3) {
        printf("\nAu revoir !\n");
        return 0;
    }

    // Déclarations des matrices de jeu
    int mines[taille_grille][taille_grille];
    int objets[taille_grille][taille_grille]; // <-- Nouvelle couche d'objets autonome
    char grille_utilisateur[taille_grille][taille_grille];

    // Initialisation par défaut à vide
    for (int i = 0; i < taille_grille; i++) {
        for (int j = 0; j < taille_grille; j++) {
            grille_utilisateur[i][j] = ' ';
            mines[i][j] = 0;
            objets[i][j] = 0;
        }
    }

    if (lancement == 2) {
        chargerPartie("sauvegarde.csv", &taille_grille, &nb_mine, mines, grille_utilisateur, &mode_jeu, &vies, &tours_brouillage, objets, &temps_deja_ecoule);
    }

    if (lancement == 1) {
        int valeur_mines[nb_mine];
        generePositionMines(nb_mine, valeur_mines, taille_grille);

        for (int i = 0; i < nb_mine; ++i) {
            position mine_temp = position_x_y(valeur_mines[i], taille_grille);
            mines[mine_temp.y][mine_temp.x] = 9;
        }

        valeurCaseAutourMine(taille_grille, mines);

        if (mode_jeu == 2) {
            int nb_bonus_malus = roundf(0.5 * taille_grille);
            if (nb_bonus_malus < 1) nb_bonus_malus = 1;
            generePositionBrouillage(nb_bonus_malus, taille_grille, mines, objets);
            generePosition1UP(nb_bonus_malus, taille_grille, mines, objets);
        }
    }

    // --- BOUCLE PRINCIPALE DE JEU ---
    position clic_temp;
    int statut_partie = 0;
    time_t debut = time(NULL);

    while (statut_partie == 0) {

        afficherGrille(taille_grille, grille_utilisateur, mines, tours_brouillage);
        clic_temp = entree_utilisateur(taille_grille);

        if (clic_temp.action == 3) {
            int temps_total = (int)(time(NULL) - debut) + temps_deja_ecoule;
            sauvegardePartie("sauvegarde.csv", taille_grille, nb_mine, mines, grille_utilisateur, mode_jeu, vies, tours_brouillage, objets, temps_total);
            int choix_post_sauvegarde;
            do {
                printf("\nPartie sauvegardee. Que voulez-vous faire :\n1) Continuer a jouer\n2) Quitter le jeu\nVotre choix : ");
                scanf("%d", &choix_post_sauvegarde);
            } while (choix_post_sauvegarde != 1 && choix_post_sauvegarde != 2);

            if (choix_post_sauvegarde == 2) {
                printf("Merci d'avoir joue. Au revoir\n");
                statut_partie = 2;
                break;
            } else {
                continue;
            }
        }

        if (clic_temp.x < 0 || clic_temp.x >= taille_grille || clic_temp.y < 0 || clic_temp.y >= taille_grille) {
            printf("\nErreur : Coordonnees invalides.\n");
            continue;
        }

        if (clic_temp.action == 1) {
            if (grille_utilisateur[clic_temp.y][clic_temp.x] != ' ' && grille_utilisateur[clic_temp.y][clic_temp.x] != 'D') {
                printf("\nErreur : Cette case a deja ete activee.\n");
                continue;
            }

            // ÉTAPE 1 : Déclencher l'objet s'il y en a un sur la case
            int objet_cache = objets[clic_temp.y][clic_temp.x];
            if (objet_cache == 10 || objet_cache == 11) {
                appliquerBonusMalus(objet_cache, &vies, &tours_brouillage, &grille_utilisateur[clic_temp.y][clic_temp.x]);
                objets[clic_temp.y][clic_temp.x] = 0; // L'objet est maintenant ramassé
            }

            // ÉTAPE 2 : Traitement classique du terrain sous l'objet (Chiffre ou mine)
            int cible = mines[clic_temp.y][clic_temp.x];

            if (cible == 9) {
                statut_partie = gererExplosionMine(&vies, &grille_utilisateur[clic_temp.y][clic_temp.x]);
                if (statut_partie == -1) {
                    tours_brouillage = 0;
                    for (int i = 0; i < taille_grille; i++) {
                        for (int j = 0; j < taille_grille; j++) {
                            if (mines[i][j] == 9) grille_utilisateur[i][j] = '*';
                        }
                    }
                    afficherGrille(taille_grille, grille_utilisateur, mines, tours_brouillage);
                }
            }
                else {
                if (cible == 0) {
                    revelerCase(clic_temp.x, clic_temp.y, taille_grille, mines, grille_utilisateur);
                } else {
                    grille_utilisateur[clic_temp.y][clic_temp.x] = '0' + cible;
                }
            }

            // Gestion de fin de tour
            if (statut_partie == 0) {
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
                    printf("\nFelicitations ! Vous avez revele toutes les cases sûres. VICTOIRE ! ✨\n");
                    statut_partie = 1;
                }

                int temps_total = (int)(time(NULL) - debut) + temps_deja_ecoule;
                printf("Temps ecoule : %d:%.02d\n", temps_total / 60, temps_total % 60);
            }
        }
        else if (clic_temp.action == 2) {
            if (grille_utilisateur[clic_temp.y][clic_temp.x] == 'D') {
                grille_utilisateur[clic_temp.y][clic_temp.x] = ' ';
                printf("Drapeau retire en (%d, %d)\n", clic_temp.x + 1, clic_temp.y + 1);
            } else if (grille_utilisateur[clic_temp.y][clic_temp.x] == ' ') {
                grille_utilisateur[clic_temp.y][clic_temp.x] = 'D';
                printf("Drapeau place en (%d, %d)\n", clic_temp.x + 1, clic_temp.y + 1);
            } else {
                printf("\nImpossible de mettre un drapeau sur une case deja revelee !\n");
            }
        }
    }

    return 0;
}