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

/*
 Cette bibliothèque contient quelques fonctions qui permettent
 de lire un fichier puis de le convertir en une liste chainee et qui permettent
 ensuite de manipuler cette chaine.
 */

/*
Cette fonction renvoie un pointeur une nouvelle Biblio
 */
Biblio *nouvelle_biblio(void);

/*
Cette fonction lit un fichier et créer une nouvelle biblio
en y inserant les morceaux lus dans le fichier. Elle renvoie
la biblio ainsi cree
*/
Biblio *charge_n_entrees(const char*nom_fichier , int n);

/*
Cette fonciton insere dans une biblio de nouveau morceaux
L'insertion se fait en tete de liste.
 */
void insere(Biblio *B, int num , char* titre , char* artiste);

/* Cette fonction affiche tout les morceaux contenu dans
une biblio */
void affiche(Biblio *B);

/* Cette fonction affiche tout les morceaux contenu dans
une biblio avec pour numero le numero passe en argument */
void recherche_numero(Biblio * B, int n);

/* Cette fonction affiche tout les morceaux contenu dans
une biblio avec pour titre le titre passe en argument */
void recherche_titre(Biblio * B, char * t);

/* Cette fonction affiche tout les morceaux contenu dans
une biblio avec pour artiste le artiste passe en argument */
void recherche_artiste(Biblio * B, char * a);

/* Cette fonction insere un nouveau morceau
dans la biblio. On suppose comme argument morceau une chaine de
caractere avec le numero, le titre et l'artiste separer
 par des tabulation */
void insertion_morceau(char * morceau, Biblio * b);

/* Cette fonction supprime un nouveau morceau
dans la biblio. On suppose comme argument morceau une chaine de caractere
avec le numero, le titre et l'artiste separer par des tabulation */
void suppression_morceau(Biblio * B, char * morceau);

/* Cette fonction affiche une liste comprenant les morceaux
qui n’apparaissent qu’une fois dans la biblioth`eque. */
void recherche_doublons(Biblio * B);

/* Cette fonction libere la bibliothèque */
void libere_biblio(Biblio *B);

#endif/* biblio_liste_h */
