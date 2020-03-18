#include "biblio_liste.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Cette bibliothèque contient quelques fonctions qui permettent
 de lire un fichier puis de le convertir en une liste chainee et qui permettent
 ensuite de manipuler cette chaine.
 */

/*
Cette fonction renvoie un pointeur une nouvelle Biblio
 */
Biblio * nouvelle_biblio(void){
	Biblio *biblio = (Biblio *) malloc(sizeof(Biblio));
	biblio -> L = NULL;
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
	CellMorceau * nouv = (CellMorceau *) malloc(sizeof(CellMorceau));
	nouv -> num = num;
	nouv -> titre = titre;
	nouv -> artiste = artiste ;
	nouv -> suiv = NULL;

	if (B->L== NULL){
		B -> L = nouv;
		B -> nE = 1;
		nouv -> suiv = NULL;
	 }else{
	 	nouv->suiv =  B->L;
		B->L = nouv;
	 	B -> nE = (B -> nE) + 1;
	 }
}

/* Cette fonction affiche tout les morceaux contenu dans
une biblio */
void affiche(Biblio *B){
	if(B->L==NULL){
		printf("La liste est vide !\n");
		return;
	}
	int i=0;
	CellMorceau * l2 = B->L;
	for (i;i<(B->nE);i++){
		printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
		l2 = l2->suiv;
	}
}

/* Cette fonction affiche tout les morceaux contenu dans
une biblio avec pour numero le numero passe en argument */
void recherche_numero(Biblio * B, int n){
	CellMorceau * l2 = B->L;
	while (l2){
		if(l2->num==n){
			printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
		}
		l2=l2->suiv;
	}
}

/* Cette fonction affiche tout les morceaux contenu dans
une biblio avec pour titre le titre passe en argument */
void recherche_titre(Biblio * B, char * t){
	CellMorceau * l2 = B->L;
	while (l2){
		if((strcmp(l2->titre, t)==0)){
			printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
		}
		l2=l2->suiv;
	}
}

/* Cette fonction affiche tout les morceaux contenu dans
une biblio avec pour artiste le artiste passe en argument */
void recherche_artiste(Biblio * B, char * a){
	CellMorceau * l2 = B->L;
	while (l2){
		if((strcmp(l2->artiste, a))==0){
		printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
		}
		l2=l2->suiv;
	}
}

/* Cette fonction insere un nouveau morceau
dans la biblio. On suppose comme argument morceau
une chaine de caractere avec le numero, le titre
et l'artiste separer par des tabulation */
void insertion_morceau(char * morceau, Biblio * b){
	int num;
	char* titre = (char *) malloc(sizeof(char *));
	char* artiste = (char *) malloc(sizeof(char *));
	char * tab = "\t";

	num = atoi(strtok(morceau, tab));
	titre = strtok(NULL, tab);
	artiste = strtok(NULL, tab);

	insere(b, num, titre, artiste);
}


/* Cette fonction supprime un nouveau morceau
dans la biblio. On suppose comme argument morceau
une chaine de caractere avec le numero, le titre
et l'artiste separer par des tabulation */
void suppression_morceau(Biblio * B, char * morceau){
	CellMorceau * tmpL = B->L;
	CellMorceau * l2 = B->L;
	int suppr = 0;
	char* tab="\t";

	int num = atoi(strtok(morceau, tab));
	char * titre = strtok(NULL, tab);
	char * artiste = strtok(NULL, tab);

	if (l2->num == num && (strcmp(l2->titre, titre)==0) && (strcmp(l2->artiste, artiste)==0) ){
				B->L=l2->suiv;
				free(tmpL);
				l2 = B->L;
				B->nE=(B->nE)-1;
			};

	while (l2->suiv){
			CellMorceau * l3 = l2->suiv;
			if (l3->num == num && (strcmp(l3->titre, titre)==0) && (strcmp(l3->artiste, artiste)==0) ){
				l2->suiv = l3->suiv;
				free(l3);
				B->nE=(B->nE)-1;
		}
		l2=l2->suiv;
	}
}

/* Cette fonction affiche une liste comprenant les morceaux
qui n’apparaissent qu’une fois dans la biblioth`eque. */
void recherche_doublons(Biblio * B){
	CellMorceau * l2 = B->L;
	while (l2){
		int vis =0;
		CellMorceau * l3=B->L;
		while(l3){
			if (((strcmp(l2->artiste, l3->artiste))==0)&&((strcmp(l2->titre, l3->titre))==0)&&l2->num == l3->num){
				vis=vis+1;
			}
			l3=l3->suiv;
		}
		if(vis <= 2){
				printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
		}
		vis=0;
		l2=l2->suiv;
	}
}

/* Cette fonction libere la bibliothèque */
void libere_biblio(Biblio * b){
	CellMorceau * l2 = b->L;
	while (l2) {
		CellMorceau * tmp = l2->suiv;
		free(l2->artiste);
		free(l2->titre);
		free(l2);
		l2 = tmp;
	}
	free(b);
}
