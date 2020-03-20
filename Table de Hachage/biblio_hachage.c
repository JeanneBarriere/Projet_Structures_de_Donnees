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

//creer une nouvelle bibliotheque
Biblio *nouvelle_biblio(void) 
{
    Biblio *B = malloc(sizeof(Biblio));
    B->m = TAILLE_TABLE;
    B->nE = 0;
    B->T = malloc(sizeof(CellMorceau)*B->m);
  	int i;
  	for (i = 0; i < B->m; i++)
  		B->T[i] = NULL;
    return B;
}

//liberer une bibliotheque
void libere_biblio(Biblio *B)
{
    int i;
    for (i = 0; i < B->m; i++) {
        CellMorceau *cell = B->T[i];
        while (cell != NULL) {
            CellMorceau *suppr = cell;
            cell = cell->suiv;
            free(suppr->titre);
            free(suppr->artiste);
            free(suppr);
        }
    }
    free(B->T);
    free(B);
}

//fonction pour avoir les cles de la table d'hachage
static unsigned int fonction_cle(const char *artiste){
    unsigned int cle = 0;
    while (*artiste != '\0') {
        cle = cle * 129 + (unsigned char)(*artiste);
        artiste++;
    }
    return cle;
}

//foction de hachage
static unsigned int fonction_hachage(unsigned int k, int m){
    double ka = k*A;
    return (unsigned int)(m * (ka - floor(ka)));
}
//fonction qui insere un morceau dans la biblio
void insere(Biblio *B, int num, char *titre, char *artiste){
    CellMorceau *nouv = malloc(sizeof(CellMorceau));
    unsigned int cle = fonction_cle(artiste);
    nouv->cle = cle;
    nouv->num = num;
    nouv->titre = titre;
    nouv->artiste = artiste;
    
    unsigned int hash = fonction_hachage(cle, B->m);
    nouv->suiv = B->T[hash];
    B->T[hash] = nouv;
    B->nE++;
}

//Afficher un seul morceau
void afficheMorceau(CellMorceau *cell)
{
	printf("| %8d | %-32.32s | %-32.32s |\n", cell->num, cell->titre, cell->artiste);
}

//Afficher une biblio 
void affiche(Biblio *B){
    int i;
    for (i = 0; i < B->m; i++) {
        CellMorceau *cell = B->T[i];
        while (cell != NULL) {
            afficheMorceau(cell);
            cell = cell->suiv;
        }
    }
    printf("La bibliotheque contient %d morceaux\n", B->nE);
}

//Fonction qui retourne les morceaux uniques 
Biblio *uniques (Biblio *B){
    Biblio *nouvB = nouvelle_biblio();
    long long int cpt = 0;
    int i;
    for (i = 0; i < B->m; i++) {
        CellMorceau *cour = B->T[i];
        while (cour != NULL) {
            CellMorceau *cour2 = B->T[i];
            while (cour2 != NULL) {
                cpt++;
                if (cour->cle == cour2->cle
                    && strcmp(cour->titre, cour2->titre) == 0
                    && strcmp(cour->artiste, cour2->artiste) == 0
                    && cour != cour2) 
                    break;
                cour2 = cour2->suiv;
            }
            if (cour2 == NULL)
                insere(nouvB, cour->num, strdup(cour->titre), strdup(cour->artiste));
            cour = cour->suiv;
        }
    }
    
    printf("Nombre de tours : %lld\n", cpt);
    return nouvB;
}

//Recherche d'un morceau par son num
CellMorceau * rechercheParNum(Biblio *B, int num)
{
	int i;
    for (i = 0; i < B->m; i++) {
    	CellMorceau *cour = B->T[i];
    	while (cour != NULL && cour->num != num)
    		cour = cour->suiv;
    	if (cour != NULL)
    		return cour;
    }
    return NULL;
}

//Recherche d'un morceau par son titre
CellMorceau *rechercheParTitre(Biblio *B, char * titre){
	int i;
    for (i = 0; i < B->m; i++) {
    	CellMorceau *cour = B->T[i];
    	while (cour != NULL && strcmp(cour->titre, titre) != 0)
    		cour = cour->suiv;
    	if (cour != NULL)
    		return cour;
    }
    return NULL;
}

//afficher les morceaux d'un artiste passe en parametre
Biblio *rechercheParArtiste(Biblio *B, char * artiste){
	unsigned int cle = fonction_cle(artiste);
	unsigned int hash = fonction_hachage(cle, B->m);
	CellMorceau * m = B->T[hash];
	if (m == NULL) return NULL;
	Biblio * b_art = nouvelle_biblio();
	while (m != NULL) {
		insere(b_art, m->num, strdup(m->titre), strdup(m->artiste));
		m = m->suiv;
	}
	return b_art;
}

//Suprrimer un morceau par le numero
int supprimeMorceau(Biblio *B, int num){
	if (B->nE == 0) 
		return 0;
	
	int i;
    for (i = 0; i < B->m; i++) {
    	CellMorceau *cour = B->T[i];
    	if (cour != NULL) {
    		if (cour->num == num) {
    			CellMorceau * suppr = cour;
    			B->T[i] = suppr->suiv;
    			free(suppr->titre);
		        free(suppr->artiste);
		        free(suppr);
		        B->nE--;
		        return 1;
    		}
    		
			while (cour->suiv != NULL && cour->suiv->num != num)
				cour = cour->suiv;
			if (cour->suiv != NULL) {
				CellMorceau * suppr = cour;
				cour->suiv = suppr->suiv;
				free(suppr->titre);
		        free(suppr->artiste);
		        free(suppr);
		        B->nE--;
		        return 1;
			}	
		}
    }
    return 0;
}














