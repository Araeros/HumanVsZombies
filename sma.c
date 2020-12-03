#include <stdio.h>
#include <stdlib.h>
#include"matsumoto.h"
#include <time.h>
#include <math.h>

#define TAILLE 50								// Taille de la matrice affichée
#define TRANSFORMATION 100						// 1/TRANSFORMATION : Pourcentage de chance qu'un humain tombe malade et devienne un zombie
#define NB_CENTRALE ((TAILLE*TAILLE)*2)/100		// Nombre de centrales sur la carte
#define EXPLOSION 50							// 1/EXPLOSION : Pourcentage de chance qu'une centrale explose
#define FRAPPE_MAX 5							// Nombre de frappes aériennes max par tour
#define LARGAGE_VACCIN_MAX 10					// Nombre de largage de vaccin max par tour
#define CHALEUR 100								// 1/CHALEUR : Pourcentage de chance de déclencher une vague de chaleur
#define DEATH_CHALEUR 2							// 1/DEATH_CHALEUR : Pourcentage de chance qu'un zombie meurt de la chaleur

char mat[TAILLE + 2][TAILLE + 2];
char mat_combat[TAILLE + 2][TAILLE + 2];

/*
	Initialisation de la matrice mat avec du vide ' '
*/
void init_mat() {
	for (int i = 0; i < TAILLE + 2; i ++) {
		for (int j = 0; j < TAILLE + 2; j ++) {
			mat[i][j] = ' ';
		}
	}
}

/*
	Initialisation de la matrice mat_combat par copie de mat
*/
void creation_mat_combat() {
	for (int i = 0; i < TAILLE + 2; i ++) {
		for (int j = 0; j < TAILLE + 2; j ++) {
			mat_combat[i][j] = mat[i][j];
		}
	}
}

/*
	Copie de la matrice de combat vers la matrice mat
*/
void copie_combat() {
	for (int i = 0; i < TAILLE + 2; i ++) {
		for (int j = 0; j < TAILLE + 2; j ++) {
			mat[i][j] = mat_combat[i][j];
		}
	}
}



/*
	Sauvegarde des bords de la matrice combat dans l'espace thaurique des différents côtés
	Première colonne cachée = Dernière colonne affichée
*/
void mat_combat_thaurique_droite() {
	for (int i = 0; i < TAILLE; i ++) {
		mat_combat[i+1][0] = mat_combat[i+1][TAILLE];
	} 
}

/*
	Dernière colonne cachée = Première colonne affichée
*/
void mat_combat_thaurique_gauche() {
	for (int i = 0; i < TAILLE; i ++) {
		mat_combat[i+1][TAILLE+1] = mat_combat[i+1][1];
	}
}

/*
	Première ligne cachée = Dernière ligne affichée
*/
void mat_combat_thaurique_bas() {
	for (int j = 0; j < TAILLE; j ++) {
		mat_combat[0][j+1] = mat_combat[TAILLE][j+1];
	}
}

/*
	Dernière ligne cachée = Première ligne affichée
*/
void mat_combat_thaurique_haut() {
	for (int j = 0; j < TAILLE; j ++) {
		mat_combat[TAILLE+1][j+1] = mat_combat[1][j+1];
	}
}

/*
	Sauvegarde des bords de la matrice combat dans l'espace thaurique
*/
void mat_combat_thaurique() {
	mat_combat_thaurique_haut();
	mat_combat_thaurique_bas();
	mat_combat_thaurique_gauche();
	mat_combat_thaurique_droite();
}

/* 
	Sauvegarde des bords de la matrice dans l'espace thaurique
*/
void mat_thaurique() {
	for (int i = 0; i < TAILLE; i ++) {
		mat[i+1][0] = mat[i+1][TAILLE];
	} 
	for (int i = 0; i < TAILLE; i ++) {
		mat[i+1][TAILLE+1] = mat[i+1][1];
	}
	for (int j = 0; j < TAILLE; j ++) {
		mat[0][j+1] = mat[TAILLE][j+1];
	}
	for (int j = 0; j < TAILLE; j ++) {
		mat[TAILLE+1][j+1] = mat[1][j+1];
	}
}

/*
	Application de l'espace thaurique de la matrice mat des différents cotés
	Dernière colonne affichée = Première colonne cachée
*/
void application_mat_combat_thaurique_gauche() {
	for (int i = 0; i < TAILLE; i ++) {
		mat[i+1][TAILLE] = mat[i+1][0];
	} 
}

/*
	Première colonne affichée = Dernière colonne cachée
*/
void application_mat_combat_thaurique_droite() {
	for (int i = 0; i < TAILLE; i ++) {
		mat[i+1][1] = mat[i+1][TAILLE+1];
	}
}

/*
	Dernière ligne affichée = Première ligne cachée
*/
void application_mat_combat_thaurique_haut() {
	for (int j = 0; j < TAILLE; j ++) {
		mat[TAILLE][j+1] = mat[0][j+1];
	}
}

/*
	Première ligne affichée = Dernière ligne cachée
*/
void application_mat_combat_thaurique_bas() {
	for (int j = 0; j < TAILLE; j ++) {
		mat[1][j+1] = mat[TAILLE+1][j+1];
	}
}

/*
	Application de l'epace thaurique de la matrice mat de tous les côtés
*/
void application_mat_combat_thaurique() {
	application_mat_combat_thaurique_gauche();
	application_mat_combat_thaurique_droite();
	application_mat_combat_thaurique_haut();
	application_mat_combat_thaurique_bas();	
}

void application_mat_thaurique() {
	for (int i = 0; i < TAILLE; i ++) {
		mat[i+1][TAILLE] = mat[i+1][0];
	} 
	for (int i = 0; i < TAILLE; i ++) {
		mat[i+1][1] = mat[i+1][TAILLE+1];
	}
	for (int j = 0; j < TAILLE; j ++) {
		mat[TAILLE][j+1] = mat[0][j+1];
	}
	for (int j = 0; j < TAILLE; j ++) {
		mat[1][j+1] = mat[TAILLE+1][j+1];
	}
}

/*
	Affichage de mat_combat
*/
void affiche_mat_combat() {
	printf("\n");
	for(int i = 0; i < TAILLE + 2; i ++) {
		for(int j = 0; j < TAILLE + 2; j ++) {
			printf("%c ",mat_combat[i][j]);
		}
		printf ("\n");
	}
}

/*
	Affichage de mat
*/
void affiche_mat() {
	printf("\n");
	for(int i = 1; i < TAILLE + 1; i ++) {
		for(int j = 1; j < TAILLE + 1; j ++) {
			printf("%c ",mat[i][j]);
		}
		printf ("\n");
	}
}

/*
	Fonction comptant les entités de la matrice :
		- Humains
		- Zombies
		- Cases vides
		- Centrales
		- Cases Irradiées
		- Cases Détruites 
*/
void count() {
	int nb_humains=0;
	int nb_zombies=0;
	int nb_cases_vides=0;
	int nb_centrales=0;
	int nb_cases_irradiees=0;
	int nb_cases_detruites=0;
	printf("\n");
	for(int i = 1; i < TAILLE + 1; i ++) {
		for(int j = 1; j < TAILLE + 1; j ++) {
			switch (mat[i][j]) {
				case 'H' :
					nb_humains ++;
					break;
				case 'Z' :
					nb_zombies ++;
					break;
				case ' ' :
					nb_cases_vides ++;
					break;
				case 'A' : 
					nb_centrales ++;
					break;
				case 'X' :
					nb_cases_irradiees ++;
					break;
				case 'D' : 
					nb_cases_detruites ++;
					break;
				default :
					printf("Cas anormal dans la fonction count, entité inconnue dans la matrice.\n");
			}
		}
	}
	printf("Nb d'humains : %d\n",nb_humains);
	printf("Nb de zombies : %d\n",nb_zombies);
	printf("Nb de cases vides : %d\n",nb_cases_vides);
	printf("Nb de centrales actives : %d\n",nb_centrales);
	printf("Nb de cases irradiées : %d\n",nb_cases_irradiees);
	printf("Nb de centrales détruites : %d\n",nb_cases_detruites);
}

/*
	Compte le nombre d'humains et de zombies pour déterminer si la partie est finie
*/
int est_finie(){
	int nb_humains = 0;
	int nb_zombies = 0;

	for(int i = 1; i < TAILLE + 1; i ++) {
		for(int j = 1; j < TAILLE + 1; j ++) {
			if(mat[i][j] == 'H') {
				nb_humains ++;
			}
			if(mat[i][j] == 'Z') {
				nb_zombies ++;
			}
		}
	}
	if(nb_zombies == 0) {
		return 1;
	}
	if(nb_humains == 0) {
		return 2;
	}
	return 0;
}

/*
	Place le nombre d'humains choisi sur la matrice
*/
void place_humains(int nb_humains) {
	int rand_ligne, rand_colonne;

	while(nb_humains != 0) {
		rand_ligne = genrand_int32() % TAILLE + 1;
		rand_colonne = genrand_int32() % TAILLE + 1;
		if(mat[rand_ligne][rand_colonne] == ' ') {
			mat[rand_ligne][rand_colonne] = 'H';
			nb_humains --;
		} 
	}
}

/*
	Place le nombre de zombies choisi sur la matrice
*/
void place_zombies(int nb_zombies){
	int rand_ligne, rand_colonne;

	while(nb_zombies != 0) {
		rand_ligne = genrand_int32() % TAILLE + 1;
		rand_colonne = genrand_int32() % TAILLE + 1;
		if(mat[rand_ligne][rand_colonne] == ' ') {
			mat[rand_ligne][rand_colonne] = 'Z';
			nb_zombies --;
		}
	}
}

/*
	Place le nombre de centrale (NB_CENTRALE) déterminé sur la matrice
*/
void place_centrale() {
	int centrales = NB_CENTRALE, index_ligne, index_col;
	while (centrales != 0) {
		index_ligne = genrand_int32() % TAILLE + 1;
		index_col = genrand_int32() % TAILLE + 1;
		if(mat[index_ligne][index_col] == ' ') {
			mat[index_ligne][index_col] = 'A';
			centrales --;
		}
	}
}

/*
	Initilisation du jeu, lancement des différentes fonctions de placement des entités ainsi que la sauvegarde dans l'espace thaurique
*/
void init_jeu(int nb_humains, int nb_zombies) {
	place_humains(nb_humains);
	place_zombies(nb_zombies);
	place_centrale();
	mat_thaurique();
}

/*
	Explosion d'une case, si centrale alors explosion en chaine
*/
void explosion_case(int vert, int hor, char etat) { //etat est 'D' pour détruit et 'X' Pour irradié
	mat[vert][hor] = etat;
	for (int abs = -1; abs <= 1; abs ++) {
		for (int ord = -1; ord <= 1; ord ++) {
			if (mat[vert+abs][hor+ord] == 'A') {
				explosion_case(vert+abs, hor+ord, 'D');
			}
			if(mat[vert+abs][hor+ord] != 'D') {
				mat[vert+abs][hor+ord] = 'X';
			}
		}
	}
	application_mat_thaurique();
}

/*
	Explosion d'une centrale

X X X
X D X	-> Marque d'explosion d'une centrale
X X X
*/
void explosion(){
	for(int i = 1; i < TAILLE + 1; i ++) {
		for(int j = 1; j < TAILLE + 1; j ++) {
			if(mat[i][j] == 'A') {
				if(genrand_int32() % EXPLOSION == 0) {
					explosion_case(i, j, 'D');
				}
			}
		}	
	}
}

/*
	Elimination des cases 'X', décontamination des zones irradiées
*/
void decontamination(){
	for(int i = 0; i < TAILLE + 2; i ++) {
		for(int j = 0; j < TAILLE + 2; j ++) {
			if(mat[i][j]=='X') {
				mat[i][j]=' ';
			}
		}
	}
}

/*
	Application de la vague de chaleur sur la partie de matrice déterminée
*/
void coup_de_chaud(int i, int max_i, int j, int max_j, int *compteur_chaleur) {
	for(int tmp_i = i; tmp_i < max_i; tmp_i ++) {
		for(int tmp_j = j; tmp_j < max_j; tmp_j ++) {
			if(mat[tmp_i][tmp_j] == 'Z') {
				if(genrand_int32() % DEATH_CHALEUR == 1) {
					mat[tmp_i][tmp_j] = ' ';
					*compteur_chaleur = *compteur_chaleur + 1;
				}
			}
		}	
	}
	mat_thaurique();
}

/*
	Déclenchement des vagues de chaleur
*/
void vague_chaleur(int *compteur) {
	int decoupage = genrand_int32() % 4; 
	//Choisit dans quelle zone la vague va frapper (0 = en haut à gauche, 1 = en bas à gauche, 2 = en haut à droite, 3 = en bas à droite)

	if (genrand_int32() % CHALEUR == 0) {
		switch (decoupage) {
			case 0 :
				coup_de_chaud(1, TAILLE/2 + 1, 1, TAILLE/2 + 1, compteur);
				break;

			case 1 :
				coup_de_chaud(1, TAILLE/2 + 1, TAILLE/2 + 1, TAILLE + 1, compteur);
				break;

			case 2 :
				coup_de_chaud(TAILLE/2 + 1, TAILLE + 1, 1, TAILLE/2 + 1, compteur);
				break;

			case 3 :
				coup_de_chaud(TAILLE/2 + 1, TAILLE + 1, TAILLE/2 + 1, TAILLE + 1, compteur);
				break;

			default : 
				printf("Erreur de modulo dans vague_chaleur\n");
		}
	}
}

/*
	Gestion des infections des humains
*/
void transformation_hz(int *nb_transformations){
	for(int i = 1; i < TAILLE + 1; i ++) {
		for(int j = 1; j < TAILLE + 1; j ++) {
			if (mat[i][j] == 'H') {	
				if (genrand_int32() % TRANSFORMATION == 0) {
					mat[i][j] = 'Z';
					*nb_transformations = *nb_transformations + 1;
				}
			}
		}
	}
	mat_thaurique();
}

/*
	Lancement des frappes aériennes sur la carte

X X X
X X X	-> Marque de Frappe
X X X
*/
void frappe_aerienne_v2(int *mort_par_frappe_humain, int *mort_par_frappe) {
	int nb_frappes = genrand_int32() % FRAPPE_MAX;
	for (nb_frappes; nb_frappes >= 0; nb_frappes--) { 
	//exemple nb_frappes compris entre 0 et 9 si 9 -> 10 frappes, on fait au minimum une frappe par tour
		int i = genrand_int32() % (TAILLE) + 1;
		int j = genrand_int32() % (TAILLE) + 1;
		mat[i][j] = 'X';
		for (int vert = -1; vert <= 1; vert ++) {
			for (int hor = -1; hor <= 1; hor ++) {
				//Si centrale -> Destruction centrale -> Radiation en chaine
				if (mat[i+vert][j+hor] == 'A') {
					explosion_case(i+vert, j+hor, 'X');
				}
				//Sinon Irradiation de la case
				if (mat[i+vert][j+hor] == 'H') {
					mat[i+vert][j+hor] = 'X';
					*mort_par_frappe_humain = *mort_par_frappe_humain + 1;
				}
				if (mat[i+vert][j+hor] == 'Z') {
					mat[i+vert][j+hor] = 'X';
					*mort_par_frappe = *mort_par_frappe + 1;
				}
				if (mat[i+vert][j+hor] != 'D') {
					mat[i+vert][j+hor] = 'X';
				}
			}
		}	
	}
}

/*
	Largage du vaccin sur la carte

Largage type:
X X X X X 
X X X X X 
X X T X X    T représente le point visé 
X X X X X 
X X X X X
*/
int largage_vaccin (int *soins_largage) {
	int nb_largage = genrand_int32() % LARGAGE_VACCIN_MAX;
	while (nb_largage >= 0) {
		int i = genrand_int32() % (TAILLE - 4) + 3;
		int j = genrand_int32() % (TAILLE - 4) + 3;
		for (int abs = -2; abs <= 2; abs ++) {
			for (int ord = -2; ord <= 2; ord ++) {
				if (mat[i+abs][j+ord] == 'Z') {
					mat[i+abs][j+ord] = 'H';
					*soins_largage = *soins_largage + 1;
				}
			}
		}
		nb_largage --;
	}
	mat_thaurique();
}

/*
	Combat des humains contre les zombies

	Si deux Humains se trouvent autour d'un zombie
	. . H
	H Z .    Le zombie sera tué, autrement dit, si 2 humains entourent le zombies (diagonales comprises) ils le tuent sans subir de morsure
	. . .
*/
void combat_humains(int *nb_meurtre, int mode){
	for(int i = 1; i < TAILLE + 1; i ++) {
		for(int j = 1; j < TAILLE + 1; j ++) {
			if(mat[i][j] == 'Z') {
				
				int compteur_h = 0;
				for (int vert = -mode; vert <= mode; vert ++) {
					for (int hor = -mode; hor <= mode; hor ++) {
						if (mat[i+hor][j+vert] == 'H') {
							compteur_h ++;
						}
					}
				}
				if (compteur_h >= 2) {
					mat[i][j] = ' ';
					*nb_meurtre = *nb_meurtre + 1;
				}
			}
		}
	}
	mat_thaurique();
}

/*
	Combat des zombies contre les humains
*/
void combat_zombies(int *nb_zombification){
	for(int i = 1; i < TAILLE + 1; i ++) {
		for(int j = 1; j < TAILLE + 1; j ++) {
			if(mat[i][j] == 'H') {
				if(mat[i][j+1] == 'Z' || mat[i][j-1] == 'Z' || mat[i-1][j] == 'Z'|| mat[i+1][j] == 'Z') {
					mat[i][j] = 'Z';
					*nb_zombification = *nb_zombification + 1;
				}
			}
		}
	}
	mat_thaurique();
}

/*
	Initialisation de la phase de combat lancement des méthodes de combat et de gestion de l'espace thaurique
*/
void combat(int *nb_meurtre, int *nb_zombification) {
	//On fait 2 parcours de matrice différents pour avantager les humains et leur donner l'initiative
	mat_thaurique();
	combat_humains(nb_meurtre, 1);
	combat_zombies(nb_zombification);
}

/*
	Fonction de combat de la phase intensive (tour > 50) pour accélerer le jeu
	Fonction combat_zombies() : Modifiée pour permettre une intensivité plus grande après le tour 50
*/
void faim_devorante(int *nb_zombification, int mode) {
	mode --;
	for(int i = 1; i < TAILLE + 1; i ++) {
		for(int j = 1; j < TAILLE + 1; j ++) {
			if(mat[i][j] == 'H') {
				int compteur_z = 0;
				for (int vert = -mode; vert <= mode; vert ++) {
					for (int hor = -mode; hor <= mode; hor ++) {
						if (mat[i+hor][j+vert] == 'H') {
							compteur_z ++;
						}
					}
				}
				if (compteur_z >= 2) {
					mat[i][j] = 'Z';
					*nb_zombification = *nb_zombification + 1;
				}
			}
		}
	}
	mat_thaurique();
}

/*
	Fonction transformation_hz() modifiée pour permettre une intensivité plus grande à divers paliers
*/
void surinfection(int *nb_transformations, int mode) {
	int tab_rand_val[TRANSFORMATION];
	mode --;
	int puissance = pow(2,mode);
	int limite = (2*TRANSFORMATION)/puissance;
	for (int i = 0; i < TRANSFORMATION; i ++) {
		if (i >= limite - 1){
			tab_rand_val[i] = 1;
		} else {
			tab_rand_val[i] = 0;
		}
	}
	for(int i = 1; i < TAILLE + 1; i ++) {
		for(int j = 1; j < TAILLE + 1; j ++) {
			if (mat[i][j] == 'H') {	
				if (tab_rand_val[genrand_int32() % TRANSFORMATION] == 1) {
					mat[i][j] = 'Z';
					*nb_transformations = *nb_transformations + 1;
				}
			}
		}
	}
	mat_thaurique();
}

/*
Initialisation de la phase de combat intensive
*/
void combat_intensif(int *nb_meurtre, int *nb_zombification, int *transformations, int mode) {
	mat_thaurique();
	combat_humains(nb_meurtre, mode);
	faim_devorante(nb_zombification, mode);
	surinfection(transformations, mode);
}

/*
	Déclenchement des morts par radiations
*/
void mort_radiation(char type, int i, int j, int *zombies_irradiees, int *humains_irradiees) {
	if (type == 'Z') {
		mat_combat[i][j] = ' ';
		*zombies_irradiees = *zombies_irradiees + 1;
	}
	if (type == 'H') {
		mat_combat[i][j] = ' ';
		*humains_irradiees = *humains_irradiees + 1;
	}
}

/*
	Déplacements dans chaques sens
*/
void deplacements_gauche(char type, int i, int j, int *zombies_irradiees, int *humains_irradiees) {
	if (mat_combat[i][j-1] == ' ') {
		mat_combat[i][j-1] = type;
		application_mat_combat_thaurique_gauche();
		mat_combat[i][j] = ' ';
		mat_combat_thaurique_gauche();
	}
	if (mat_combat[i][j-1] == 'X') {
		mat_combat[i][j] = ' ';
		mort_radiation(type, i, j, zombies_irradiees, humains_irradiees);
		mat_combat_thaurique_gauche();
	}
}

void deplacements_droite(char type, int i, int j, int *zombies_irradiees, int *humains_irradiees) {
	if (mat_combat[i][j+1] == ' ') {
		mat_combat[i][j+1] = type;
		application_mat_combat_thaurique_droite();
		mat_combat[i][j] = ' ';
		mat_combat_thaurique_droite();
	}
	if (mat_combat[i][j+1] == 'X') {
		mat_combat[i][j] = ' ';
		mort_radiation(type, i, j, zombies_irradiees, humains_irradiees);
		mat_combat_thaurique_droite();
	}
}

void deplacements_haut(char type, int i, int j, int *zombies_irradiees, int *humains_irradiees) {
	if (mat_combat[i-1][j] == ' ') {
		mat_combat[i-1][j] = type;
		application_mat_combat_thaurique_haut();
		mat_combat[i][j] = ' ';
		mat_combat_thaurique_haut();
	}
	if (mat_combat[i+1][j] == 'X') {
		mat_combat[i][j] = ' ';
		mort_radiation(type, i, j, zombies_irradiees, humains_irradiees);
		mat_combat_thaurique_haut();
	}
}

void deplacements_bas(char type, int i, int j, int *zombies_irradiees, int *humains_irradiees) {
	if (mat_combat[i+1][j] == ' ') {
		mat_combat[i+1][j] = type;
		application_mat_combat_thaurique_bas();
		mat_combat[i][j] = ' ';
		mat_combat_thaurique_bas();
	}
	if (mat_combat[i+1][j] == 'X') {
		mat_combat[i][j] = ' ';
		mort_radiation(type, i, j, zombies_irradiees, humains_irradiees);
		mat_combat_thaurique_bas();
	}
}

/*
	Gestion des déplacements des humains et des zombies
*/
void deplacements(int *zombies_irradiees, int *humains_irradiees) {
	for (int i = 1; i < TAILLE + 1; i ++) {
		for (int j = 1; j < TAILLE + 1; j ++) {
			char type = mat[i][j];
			if (type == 'Z' || type == 'H') {
				int direction = genrand_int32() % 4; //car 4 directions possibles
				switch (direction) {
					case 0:
						deplacements_droite(type, i, j, zombies_irradiees, humains_irradiees);
						break;
					case 1:
						deplacements_gauche(type, i, j, zombies_irradiees, humains_irradiees);
						break;
					case 2:
						deplacements_haut(type, i, j, zombies_irradiees, humains_irradiees);
						break;
					default :
						deplacements_bas(type, i, j, zombies_irradiees, humains_irradiees);
				}
			}
		}
	}
}

/*
	Initialisation de la phase de déplacement 
*/
void init_deplacements(int *zombies_irradiees, int *humains_irradiees) {
	creation_mat_combat();
	deplacements(zombies_irradiees, humains_irradiees);
	copie_combat();
	mat_thaurique();
}

/*
	Fonction d'attente
*/
void sleep(int seconde){
	time_t start_time=0;
	time_t current_time=0;

	start_time=time(NULL);
	while (current_time-start_time+1<=seconde)
	{
		current_time = time(NULL);
	}
}

/*
	Fonction de saisie et de vérification des données
*/
void entree_donnees(int *nb_zombies, int *nb_humains) {
	printf("ATTENTION ! le total des humains et des zombies doit etre inferieur ou egal a %d\nSi il est supérieur nous remplierons la matrice avec le même rapport Zombies/Humains que vous avez demandé\n", TAILLE*TAILLE-NB_CENTRALE);
	printf("Entrez le nombre de Zombies : ");
	scanf("%d",nb_zombies);
	printf("Entrez le nombre d'Humains : ");
	scanf("%d",nb_humains);
	if (*nb_humains == 0) {
		*nb_humains = 1;
	}
	if (*nb_zombies == 0) {
		*nb_zombies = 1;
	}
	/*
	1000 H et 9 000 Z -> 245 H et 2205 Z 
	2000 H et 8 000 Z -> 490 H et 1960 Z
	5000 H et 1 000 Z -> 2042 H et 408 Z
	*/
	if (*nb_zombies + *nb_humains > TAILLE * TAILLE - NB_CENTRALE) {
		float total = TAILLE * TAILLE - NB_CENTRALE, rapport;
		if (*nb_zombies == *nb_humains) {
			*nb_zombies = total / 2;
			*nb_humains = total / 2;
		}
		if (*nb_zombies > *nb_humains) {
			rapport = (float)*nb_zombies / (float)*nb_humains + (float)1;
			*nb_humains = total / rapport;
			*nb_zombies  = total - *nb_humains;
		}
		if (*nb_zombies < *nb_humains) {
			rapport = (float)*nb_humains / (float)*nb_zombies + (float)1;
			*nb_zombies = total / rapport;
			*nb_humains = total - *nb_zombies;
		}
	}
}

/*
	Déroulement du jeu :
		- Combats
		- Maladie
		- Vague de chaleur
		- Frappes aériennes
		- Largage du vaccin
		- Explosion des centrales
		- Décontamination : 1 tour sur 2
*/
void jeu(int *nb_meurtre, int *nb_zombification, int *transformations, int *mort_par_chaleur, int *mort_par_frappe_humain, int *mort_par_frappe, int *soins_largage, int nb_tours) {
	if (nb_tours >= 50) {
		int mode = nb_tours / 50 + 1;
		combat_intensif(nb_meurtre, nb_zombification, transformations, mode);
	} else {
		combat(nb_meurtre, nb_zombification);
		transformation_hz(transformations);
	}
	vague_chaleur(mort_par_chaleur);
	frappe_aerienne_v2(mort_par_frappe_humain, mort_par_frappe);
	largage_vaccin(soins_largage);
	explosion();
	//clean les cases irradiés un tour sur deux 
	if((nb_tours%2)==1)
	{
		decontamination();
	}
}

/*
	Fonction main
		Permet de lancer le programme
		Gère le menu
		La création des variables
		Les appels des méthodes
		La gestion de pointeurs
		L'affichage des résultats
*/
int main(int argc, char **argv){

    
	/*Gestion des erreurs au lancement du programme*/
	if(argc!=2)
	{
		printf("Vous devez choisir un jeu de la liste ci dessous !\n");
		printf("1 -> Humains VS Zombies\n");
		exit(0);
	}
	if(atoi(argv[1])>1)
	{
		printf("1 -> Humains VS Zombies\n");
		printf("Aucun autre jeu existant pour le moment\n");
	}
	if(atoi(argv[1])==1)
	{
		/*Gestion du jeu Zombies VS Humains*/

		printf("--------------------------------------------------------\n");
		printf("-------------------ZOMBIES VS HUMANS--------------------\n");
		printf("--------------------------------------------------------\n");
		printf("\n");

		int nb_zombies, nb_humains, total, i, j;
		int nb_tours=0;
		int nb_meurtre=0;					//compteur final de mort de Zombies
		int nb_zombification=0;				//compteur final de transformation Humains en Zombies
		int mort_par_chaleur=0;				//compteur vague_chaleur
		int mort_par_frappe=0;				//compteur pour zombies mort par frappe aerienne
		int transformations=0;				//compteur transformation aleatoire
		int mort_par_frappe_humain = 0;     //Compteur pour humains morts d'une frappe aérienne
		int soins_largage = 0;				//Compteur du nombre de zombies soignés par largage
		int zombies_irradiees = 0; 			//Zombies morts car ils se sont déplacés en zone irradiée
		int humains_irradiees = 0;			//Humains morts car ils se sont déplacés en zone irradiée

		//Initialisation matrice contenant humains et zombies
		init_mat();
		//Saisie et Vérification des données
		entree_donnees(&nb_zombies, &nb_humains);
		//Remplissage de la matrice mat avec les humains et les zombies 
		init_jeu(nb_humains,nb_zombies);
		printf("\n");
		
		/* Affichage et Deroulement */
		printf("--------------------Matrice de base--------------------- \n");
		affiche_mat();
		count();
		printf("\n");
		printf("----------------------Debut Du Jeu-----------------------\n");
		while(est_finie() == 0)
		{
			//Lancement des fonctions de jeu comme le combat, les largages, ...
			jeu(&nb_meurtre, &nb_zombification, &transformations, &mort_par_chaleur, &mort_par_frappe_humain, &mort_par_frappe, &soins_largage, nb_tours);

			//deplacement 
			init_deplacements(&zombies_irradiees, &humains_irradiees);

			//Affichage a chaque tour
			system("clear");
			affiche_mat();
			count();		
			nb_tours = nb_tours + 1;
			printf("\t\tTOUR %d\n", nb_tours);
			sleep(1);
		}
		

		printf("\n");
		printf("-------------------------------------------------\n");
		printf("|\t\t FIN DE PARTIE  \t\t|\n");
		printf("-------------------------------------------------\n");
		printf("%d : Humains transformés en zombies par maladie\n",transformations);
		printf("%d : Zombies tués par des humains\n",nb_meurtre);
		printf("%d : Humains transformés en zombies par morsure\n",nb_zombification);
		printf("%d : Zombies tués par vague de chaleur\n",mort_par_chaleur);
		printf("%d : Zombies tués par frappe aerienne\n",mort_par_frappe);
		printf("%d : Humains tués par frappe aerienne\n",mort_par_frappe_humain);
		printf("%d : Zombies soignés par largage de vaccins\n", soins_largage);
		printf("%d : Zombies tués par radiation\n", zombies_irradiees);
		printf("%d : Humains tués par radiation\n", humains_irradiees);
		/* Test qui est le vainqueur */
		if(est_finie()==1)
			{
				printf("\n");
				printf("---------------Humans win-----------------\n\n");
			}
			else
			{
				if(est_finie()==2)
				{
					printf("\n");
					printf("---------------Zombies win---------------\n\n");
				}
			}
		return 0;
	}
	return 0;
}	