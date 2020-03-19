#include "biblio_dynamique.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

/*
 Cette bibliothèque contient quelques fonctions qui permettent
 de lire un fichier puis de le convertir en une liste chainee et qui permettent
 ensuite de manipuler cette chaine.
 */

/*
Cette fonction renvoie un pointeur une nouvelle Biblio
 */
Biblio * nouvelle_biblio(void){
	Morceau * T = malloc(25 * sizeof(Morceau));
	Biblio * biblio = (Biblio *) malloc(sizeof(Biblio));
	biblio -> capacite = 25;
	biblio -> T = T;
	biblio -> nE = 0;
	return biblio;
}

/*
Cette fonction lit un fichier et créer une nouvelle biblio
en y inserant les morceaux lus dans le fichier. Elle renvoie
la biblio ainsi cree
*/
Biblio *charge_n_entrees(const char *nomfichier, int n){
	FILE * f = fopen(nomfichier, "r");
	Biblio * biblio = nouvelle_biblio();
	int l;//nombre de ligne a lire
	for (l=0; l<n; l++){
		if (end_of_file(f)==0){
			int num;
			char* titre = (char *) malloc(sizeof(char *));
			char* artiste = (char *) malloc(sizeof(char *));
			char * retour = "\n";
			char * tab = "\t";
			int taille = 256;

			parse_int(f, &num);
			parse_char(f, *tab);
			parse_string(f, &titre, &taille, *tab );
			parse_char(f, *tab);

			parse_string(f, &artiste, &taille, *retour );
			parse_char(f, *retour);

			insere(biblio, num, titre, artiste);
		}
	}
	fclose(f);
	return biblio;
}

/*
Cette fonciton insere dans une biblio de nouveau morceaux
L'insertion se fait en tete de liste.
 */
void insere(Biblio *B, int num, char *titre, char *artiste){

	if (B->nE == B->capacite){
		realloc( B->T , 2*(B->capacite));
		B->capacite = 2*(B->capacite);
	 }
	 B->T[(B->nE)].titre = titre;
	 B->T[(B->nE)].artiste = artiste;
	 B->T[(B->nE)].num = num;
	 B->nE = B->nE+1;
}

/* Cette fonction affiche tout les morceaux contenu dans
une biblio */
void affiche(Biblio *B){
	if(B->nE==0){
		printf("La liste est vide !\n");
		return;
	}else{
		int i=0;
		Morceau * T = B->T;
		while (i<(B->capacite)){
			i++;
			if (T[i].artiste!=NULL){
				printf("%d\t%s\t%s\n", T[i].num, T[i].titre, T[i].artiste);
			}
		}
	}
}

/* Cette fonction affiche tout les morceaux contenu dans
une biblio avec pour numero le numero passe en argument */
void recherche_numero(Biblio * B, int n){
	if(B->nE==0){
		printf("La liste est vide !\n");
		return;
	}else{
		int i=0;
		Morceau * T = B->T;
		while (i<(B->capacite)){
			if (T[i].artiste!=NULL){
				if(B->T[i].num==n){
					printf("%d\t%s\t%s\n", T[i].num, T[i].titre, T[i].artiste);
				}
				i++;
			}
		}
	}
}

/* Cette fonction affiche tout les morceaux contenu dans
une biblio avec pour titre le titre passe en argument */
void recherche_titre(Biblio * B, char * t){
	if(B->nE==0){
		printf("La liste est vide !\n");
		return;
	}else{
		int i=0;
		Morceau * T = B->T;
		while (i<(B->capacite)){
			if (T[i].artiste!=NULL){
				if((strcmp(B->T[i].titre, t)==0)){
					printf("%d\t%s\t%s\n", T[i].num, T[i].titre, T[i].artiste);
				}
				i++;
			}
		}
	}
}

/* Cette fonction affiche tout les morceaux contenu dans
une biblio avec pour artiste le artiste passe en argument */
void recherche_artiste(Biblio * B, char * a){
	if(B->nE==0){
		printf("La liste est vide !\n");
		return;
	}else{
		int i=0;
		Morceau * T = B->T;
		while (i<(B->capacite)){
			if (T[i].artiste!=NULL){
				if((strcmp(B->T[i].artiste, a)==0)){
					printf("%d\t%s\t%s\n", T[i].num, T[i].titre, T[i].artiste);
				}
				i++;
			}
		}
	}
}

/* Cette fonction insere un nouveau morceau
dans la biblio. On suppose comme argument morceau
une chaine de caractere avec le numero, le titre
et l'artiste separer par des tabulation */
void insertion_morceau(char * morceau, Biblio * B){
	int num;
	char* titre = (char *) malloc(sizeof(char *));
	char* artiste = (char *) malloc(sizeof(char *));
	char * tab = "\t";

	num = atoi(strtok(morceau, tab));
	titre = strtok(NULL, tab);
	artiste = strtok(NULL, tab);

	if (B->nE == B->capacite){
		realloc( B->T , 2*(B->capacite));
		B->capacite = 2*(B->capacite);
	 }
	 int i = 0;
	while(B->T[i].artiste!=NULL){
		i++;
	}
	 B->T[i].titre = titre;
	 B->T[i].artiste = artiste;
	 B->T[i].num = num;
	 B->nE = B->nE+1;
}

/* Cette fonction supprime un nouveau morceau
dans la biblio. On suppose comme argument morceau
une chaine de caractere avec le numero, le titre
et l'artiste separer par des tabulation */
void suppression_morceau(Biblio * B, char * morceau){
	char* tab="\t";

	int num = atoi(strtok(morceau, tab));
	char * titre = strtok(NULL, tab);
	char * artiste = strtok(NULL, tab);

	int i=0;
	for (i;i<(B->capacite);i++){
		if (B->T[i].num == num && (strcmp(B->T[i].titre, titre)==0) && (strcmp(B->T[i].artiste, artiste)==0) ){
				free(B->T[i].titre);
				free(B->T[i].artiste);
				B->T[i].titre = NULL;
				B->T[i].artiste = NULL;
				B->T[i].num = 0;
				B->nE=(B->nE)-1;
		}
	}
}

/* Cette fonction affiche une liste comprenant les morceaux
qui n’apparaissent qu’une fois dans la biblioth`eque. */
void recherche_doublons(Biblio * B){
		int i=0;
		for (i;i<(B->capacite);i++){
			int vis =0;
			int j=0;
			for (j;j<(B->capacite);j++){
				if( B->T[i].artiste!=NULL && B->T[j].artiste!=NULL ){
					if (B->T[i].num == B->T[j].num  && (strcmp(B->T[i].titre, B->T[j].titre)==0) && (strcmp(B->T[i].artiste, B->T[j].artiste)==0) ){
					vis=vis+1;
					}
				}
			}
			if(vis <= 2 && B->T[i].artiste!=NULL ){
				printf("%d\t%s\t%s\n", B->T[i].num, B->T[i].titre, B->T[i].artiste);
		}
		vis=0;
	}
}

/* Cette fonction libere la bibliothèque */
void libere_biblio(Biblio * B){
	int i=0;
	for (i;i<(B->capacite);i++){
		if( B->T[i].artiste!=NULL){
			free( B->T[i].artiste);
			free( B->T[i].titre);
		}
	}
	free(B->T);
	free(B);
}
