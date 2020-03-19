#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio_dynamique.h"
#include "parser.h"

# include <time.h>

clock_t temps_initial ; /* Temps initial en micro-secondes */
clock_t temps_final ; /* Temps final en micro-secondes */
double temps_cpu ; /* Temps total en secondes */

int main(int argc , const char * argv []) {
	if(argc != 2){
		printf(" Erreur format : %s <NomFichierBiblio.txt>",argv[0]);
		return 1;
	}

	const char *nomfic = argv [1];

	int i = 1000;
	while (i<3000000){
		temps_final = clock () ;
		Biblio *biblio = charge_n_entrees(nomfic ,i);
		temps_cpu = (( double ) ( temps_final - temps_initial ) ) / CLOCKS_PER_SEC ;
		printf ("%d %f ",i , temps_cpu ) ;
		libere_biblio(biblio);
		i=i+10000;
	}

	printf("Au revoir\n ");

	return 0;
}
