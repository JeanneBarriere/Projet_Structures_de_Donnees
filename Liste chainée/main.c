
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "biblio.h"
#include "biblio_liste.h"
#include "biblio_arbrelex.h"

void menu() {

	printf("Menu :\n");
	printf("\t0−Sortie\n");
	printf("\t1−Affichage\n");
	printf("\t2−Recherche morceaux uniques \n");

	printf("Votre choix:");
}

int main(int argc , const char * argv []) {
	if(argc != 3){
		printf(" Erreur format : %s <NomFichierBiblio.txt> <NbLigneALire> ",argv[0]);
		return 1;
	}

	const char *nomfic = argv [1];
	int nlignes = atoi(argv [2]);
	char * titre = "Bright";
	char * artiste = "Hey";

	printf("Lecture:\n");
	Biblio *biblio = charge_n_entrees(nomfic , nlignes);
	// CellMorceau *c1 = recherche_numero(biblio , 3);
	// affiche_morceau(c1);
	// CellMorceau *c2 = recherche_titre(biblio , titre);
	// 	affiche_morceau(c2);
	// Biblio * b2 = liste_artiste(biblio , artiste);
	// 	affiche(b2);
	
	// suppression_morceau_num(biblio , 0);
	// affiche(biblio);

	// suppression_morceau_titre(biblio , titre);
	// affiche(biblio);
	
	recherche_doublons(biblio);

	printf("r'eaffiche biblio\n");
	affiche(biblio);


	int ch;
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
				//Biblio *Bunique = uniques(biblio);
				//affiche(Bunique);
				//libere_biblio(Bunique);
				break;
			}
			default:
				ch = 0;
				break;
		}
	} while(ch != 0);

	//libere_biblio(biblio);
	printf("Au revoir\n ");

	return 0;
}