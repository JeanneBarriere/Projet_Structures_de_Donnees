/* biblio_hachage.h */

#ifndef biblio_hachage_h
#define biblio_hachage_h

typedef struct CellMorceau {
	struct CellMorceau *suiv ;
	int num;
	char *titre;
	char *artiste;
} CellMorceau ;

typedef struct Biblio {
	CellMorceau *L; /* Liste chainee des morceaux */
	int nE ; /* Nombre de morceau dans la hachage */
}Biblio;

Biblio *charge_n_entrees(const char *nomfichier, int n);

Biblio *nouvelle_biblio(void); 

void libere_biblio(Biblio *B);

static unsigned int fonction_cle(const char *artiste);

static unsigned int fonction_hachage(unsigned int k, int m);

void insere(Biblio *B, int num, char *titre, char *artiste);

void afficheMorceau(CellMorceau *cell);

void affiche(Biblio *B);

Biblio *uniques (Biblio *B);
   
CellMorceau * rechercheParNum(Biblio *B, int num);

CellMorceau *rechercheParTitre(Biblio *B, char * titre);

Biblio *rechercheParArtiste(Biblio *B, char * artiste);

int supprimeMorceau(Biblio *B, int num);



#endif/* biblio_hachage_h */
