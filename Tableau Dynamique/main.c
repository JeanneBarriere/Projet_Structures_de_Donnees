#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio_dynamique.h"
#include "parser.h"

void menu() {

	printf("Menu :\n");
	printf("\t0−Sortie\n");
	printf("\t1−Affichage\n");
	printf("\t2−Affiche morceau par numéro \n");
	printf("\t3−Affiche morceau par titre \n");
	printf("\t4−Affiche morceaux par artiste \n");
	printf("\t5−Ajout d'un morceau \n");
	printf("\t6−Suppression d'un morceau \n");
	printf("\t7−Affichage sans doublons \n");


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
	int taille = 256;
	char * tab = "\t";
	char * retour="\n";
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
				char * titre = (char *) malloc(sizeof(char *));
				parse_char(stdin, *retour);
				parse_string(stdin, &titre, &taille, *retour);
				recherche_titre(biblio, titre);
				free(titre);
				break;
			}
			case 4:
			{
				printf("Quel artiste?\n");
				char * artiste = (char *) malloc(sizeof(char *));
				parse_char(stdin, *retour);
				parse_string(stdin, &artiste, &taille, *retour );
				recherche_artiste(biblio, artiste);
				free(artiste);
				break;
			}
			case 5:
			{

				printf("Quel morceau ? Format : num|tab|titre|tab|artiste\n");
				char * morceau = (char *) malloc(sizeof(char *));
				parse_char(stdin, *retour);
				parse_string(stdin, &morceau, &taille, *retour );
				insertion_morceau(morceau, biblio);
				free(morceau);
				break;
			}
			case 6:
			{

				printf("Quel morceau ? Format : num|tab|titre|tab|artiste\n");
				char * morceau = (char *) malloc(sizeof(char *));
				parse_char(stdin, *retour);
				parse_string(stdin, &morceau, &taille, *retour );
				suppression_morceau(biblio, morceau);
				free(morceau);
				break;
			}
			case 7:
			{
				recherche_doublons(biblio);
				break;
			}
			default:
				ch = 0;
				break;
		}
	} while(ch != 0);

	libere_biblio(biblio);
	printf("Au revoir\n ");

	return 0;
}
