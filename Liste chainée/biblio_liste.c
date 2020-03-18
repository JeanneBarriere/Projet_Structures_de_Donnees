#include "biblio_liste.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Biblio * nouvelle_biblio(void){
	Biblio *biblio = (Biblio *) malloc(sizeof(Biblio));
	biblio -> L = NULL;
	biblio -> nE = 0;
	return biblio;
}

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
			printf("test\n" );
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

void recherche_numero(Biblio * B, int n){
	CellMorceau * l2 = B->L;
	while (l2){
		if(l2->num==n){
			printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
		}
		l2=l2->suiv;
	}
}

void recherche_titre(Biblio * B, char * t){
	CellMorceau * l2 = B->L;
	while (l2){
		if((strcmp(l2->titre, t)==0)){
			printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
		}
		l2=l2->suiv;
	}
}

void recherche_artiste(Biblio * B, char * a){
	CellMorceau * l2 = B->L;
	while (l2){
		if((strcmp(l2->artiste, a))==0){
		printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
		}
		l2=l2->suiv;
	}
}

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

void suppression_morceau(Biblio * B, char * morceau){
	CellMorceau * tmpL = B->L;
	CellMorceau * l2 = B->L;
	int suppr = 0;
	char* tab="\t";

	int num = atoi(strtok(morceau, tab));
	char * titre = strtok(NULL, tab);
	char * artiste = strtok(NULL, tab);

	if (l2->num == num && (strcmp(l2->titre, titre)==0) && (strcmp(l2->artiste, artiste)==0) ){
				B->L=B->L->suiv;
				free(tmpL);
				B->L->num=0;
				l2 = B->L;
			};

	while (l2->suiv){
		printf("test avant\n");
			if (l2->num == num && (strcmp(l2->titre, titre)==0) && (strcmp(l2->artiste, artiste)==0) ){
			CellMorceau * l3 = l2->suiv;
			l2->suiv = l3->suiv;
			free(l3);
			B->nE=(B->nE)-1;
		}
		l2=l2->suiv;
		printf("test fin\n" );
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

void suppression_morceau_num(Biblio * B, int n){
	CellMorceau * tmpL = B->L;
	CellMorceau * l2 = B->L;
	int suppr = 0;

	if (l2->num == n){
				B->L=B->L->suiv;
				free(tmpL);
				B->L->num=0;
				suppr=1;
				l2 = B->L;
			};

	while (l2->suiv){
		if(l2->suiv->num==n){
			CellMorceau * l3 = l2->suiv;
			l2->suiv = l3->suiv;
			free(l3);
			suppr = 1;
		}
		if (suppr ==1){
			l2->suiv->num=(l2->suiv->num)-1;
		}
		l2=l2->suiv;
	}
	B->nE=(B->nE)-1;
}

void suppression_morceau_num_ds_liste(CellMorceau * L, int n){
	CellMorceau * tmpL = L;
	CellMorceau * l2 = L;
	int suppr = 0;

	if (l2->num == n){
				L=L->suiv;
				free(tmpL);
				L->num=0;
				suppr=1;
				l2 = L;
			};

	while (l2->suiv){
		if(l2->suiv->num==n && l2->suiv->suiv!=NULL){
			CellMorceau * l3 = l2->suiv;
			l2->suiv = l3->suiv;
			if (l3->suiv !=NULL)
			{
				free(l3);
			}

			suppr = 1;
		}
		if (suppr==1 && (l2->suiv)!=NULL){

			l2->suiv->num=(l2->suiv->num)-1;
		}
		l2=l2->suiv;

	}
}

void suppression_morceau_titre(Biblio * B, char * t){
	CellMorceau * tmpL = B->L;
	CellMorceau * l2 = B->L;
	int suppr = 0;

	if((strcmp(l2->titre, t)==0)){
				B->L=B->L->suiv;
				free(tmpL);
				B->L->num=0;
				suppr=1;
				l2 = B->L;
			};

	while (l2->suiv){
		if((strcmp(l2->suiv->titre, t)==0)){
			CellMorceau * l3 = l2->suiv;
			l2->suiv = l3->suiv;
			free(l3);
			suppr = 1;
		}
		if (suppr ==1){
			l2->suiv->num=(l2->suiv->num)-1;
		}
		l2=l2->suiv;
	}
	B->nE=(B->nE)-1;
}

void recherche_doublons(Biblio * B){
	CellMorceau * l2 = B->L;
	int i=0;
	while (l2){
		int vis =0;
		CellMorceau * l3=B->L;
		while(l3){
			if (((strcmp(l2->artiste, l3->artiste))==0)&&((strcmp(l2->titre, l3->titre))==0)&&l2->num != l3->num){
				vis=1;
			}
			l3=l3->suiv;
		}
		if(vis != 1){
			affiche_morceau_avec_num(l2, i);
			i++;
		}
		vis=0;
		l2=l2->suiv;
	}
}

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
