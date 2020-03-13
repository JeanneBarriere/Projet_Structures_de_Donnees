#include "biblio_hachage.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>



Biblio *charge_n_entrees(const char *nomfichier, int n){
	FILE * f = fopen(nomfichier, "r");
	Biblio * biblio = nouvelle_biblio();
	int l;//nombre de ligne a lire
	for (l=0; l<n; l++){
		if (end_of_file(f)==0){
			int num;
			char* titre = (char *) malloc(sizeof(char *));
			char* artiste = (char *) malloc(sizeof(char *));
			int a = 256;
			char* tab="\t";
			char* retour="\n";

			parse_int(f, &num);
			parse_char(f, *tab);

			parse_string(f, &titre, &a, *tab );
			parse_char(f, *tab);

			parse_string(f, &artiste, &a, *retour );
			parse_char(f, *retour);

			insere_lex(biblio, num, titre, artiste);
		}
	}
	fclose(f);
	return biblio;
}

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

void affiche_morceau(CellMorceau * L){
	if(L==NULL){
		printf("Le morceau est vide !\n");
		return;
	}
	printf("%d\t%s\t%s\n", L->num, L->titre, L->artiste);
}

void affiche_morceau_avec_num(CellMorceau * L, int n){
	if(L==NULL){
		printf("Le morceau est vide !\n");
		return;
	}
	printf("%d\t%s\t%s\n", n, L->titre, L->artiste);
}
