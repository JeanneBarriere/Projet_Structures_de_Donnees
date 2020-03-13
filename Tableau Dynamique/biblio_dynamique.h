/* biblio_dynamique.h */

#ifndef biblio_dynamique_h
#define biblio_dynamique_h

typedef struct CellMorceau {
	struct CellMorceau *suiv ;
	int num;
	char *titre;
	char *artiste;
} CellMorceau ;

typedef struct Biblio {
	CellMorceau *L; /* Liste chainee des morceaux */
	int nE ; /* Nombre de morceau dans la dynamique */
}Biblio;

Biblio *charge_n_entrees(const char*nom_fichier , int n);

void affiche(Biblio *B);

void affiche_morceau(CellMorceau * L);

void affiche_morceau_avec_num(CellMorceau * L, int n);

Biblio *uniques(Biblio *B);

Biblio *nouvelle_biblio(void);

void libere_biblio(Biblio *B);

Biblio *nouvelle_biblio(void);

void insere(Biblio *B, int num , char* titre , char* artiste);

void suppression_morceau_num(Biblio * B, int n);

void suppression_morceau_titre(Biblio * B, char * t);

void recherche_doublons(Biblio * B);

CellMorceau * recherche_numero(Biblio * B, int n);

CellMorceau * recherche_titre(Biblio * B, char * t);

#endif/* biblio_dynamique_h */
