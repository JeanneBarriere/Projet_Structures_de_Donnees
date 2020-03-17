/* biblio_liste.h */

#ifndef biblio_liste_h
#define biblio_liste_h

typedef struct CellMorceau {
	struct CellMorceau *suiv ;
	int num;
	char *titre;
	char *artiste;
} CellMorceau ;

typedef struct Biblio {
	CellMorceau *L; /* Liste chainee des morceaux */
	int nE ; /* Nombre de morceau dans la liste */
}Biblio;

Biblio *nouvelle_biblio(void);

Biblio *charge_n_entrees(const char*nom_fichier , int n);

void insere(Biblio *B, int num , char* titre , char* artiste);

void affiche(Biblio *B);

// void recherche_numero(Biblio * B, int n);
//
// void recherche_titre(Biblio * B, char * t);

// void recherche_artiste(Biblio * B, char * a);

// void affiche_morceau(CellMorceau * L);
//
// void affiche_morceau_avec_num(CellMorceau * L, int n);
//
// void libere_biblio(Biblio *B);
//
// void suppression_morceau_num(Biblio * B, int n);
//
// void suppression_morceau_titre(Biblio * B, char * t);
//
// void recherche_doublons(Biblio * B);

//
//
// Biblio * affiche_artiste(Biblio * B, char * a);

#endif/* biblio_liste_h */
