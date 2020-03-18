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
		for (i;i<(B->nE);i++){
			printf("%d\t%s\t%s\n", T[i].num, T[i].titre, T[i].artiste);
		}
	}
}
