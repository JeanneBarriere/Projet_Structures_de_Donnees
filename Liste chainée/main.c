#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "biblio_liste.h"

void menu() {

	printf("Menu :\n");
	printf("\t0−Sortie\n");
	printf("\t1−Affichage\n");
	printf("\t2−Affiche morceaux par numéro \n");
	printf("\t3−Affiche morceau par titre \n");
	printf("\t4−Affiche morceaux par artiste \n");

	printf("Votre choix:");
}

int main(int argc , const char * argv []) {
	if(argc != 3){
		printf(" Erreur format : %s <NomFichierBiblio.txt> <NbLigneALire> ",argv[0]);
		return 1;
	}

	const char *nomfic = argv [1];
	int nlignes = atoi(argv [2]);

	printf("Lecture:\n");
	Biblio *biblio = charge_n_entrees(nomfic , nlignes);
	affiche(biblio);


	int ch;
	int n;
	char * t;
	do{
		menu();
		int lus = scanf("%d", &ch);
		if(lus == 0) {
			ch = 0;
		}
		switch(ch) {
			case 1:
			{
				printf("Affichage\n");
				affiche(biblio);
				break;
			}
			case 2:
			{
				printf("Quel numero ?\n");
				scanf("%d", &n);
				recherche_numero(biblio, n);
				break;
			}
			case 3:
			{
				printf("Quel titre ?\n");
				char s[20] = "";
				scanf("%19s", s);
				recherche_titre(biblio, s);
				break;
			}
	// // 		case 4:
	// // 		{
	// // 			printf("Quel artiste?\n");
	// // 			char a[50] = "";
	// // 			scanf("%49s", a);
	// // 			printf("%s\n", a);
	// // 			affiche_artiste(biblio, a);
	// // 			break;
	// // 		}
			default:
				ch = 0;
				break;
		}
	} while(ch != 0);

	libere_biblio(biblio);
	printf("Au revoir\n ");

	return 0;
}
