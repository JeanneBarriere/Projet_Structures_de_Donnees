#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio_liste.h"
#include "parser.h"

void menu() {

	printf("Menu :\n");
	printf("\t0−Sortie\n");
	printf("\t1−Affichage\n");
	printf("\t2−Affiche morceaux par numéro \n");
	printf("\t3−Affiche morceau par titre \n");
	printf("\t4−Affiche morceaux par artiste \n");

	printf("Votre choix:");
}

void viderBuffer()
{
    int c = 0;
    while (c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
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
	int a = 256;
	char* retour="\n";
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
				char s[50];
				void viderBuffer();
				parse_string(stdin, &s, &a, *retour );
				recherche_titre(biblio, s);
				break;
			}
			case 4:
			{
				printf("Quel artiste?\n");
				char art[50];
				parse_string(stdin, &art, &a, *retour );
				printf("%s\n", art);
				recherche_artiste(biblio, art);
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
