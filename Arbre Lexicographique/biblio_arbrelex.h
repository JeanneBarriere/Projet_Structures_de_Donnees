#ifndef biblio_arbrelex_h
#define biblio_arbrelex_h

typedef struct CellMorceau {
struct CellMorceau *suiv;
int num;
char* titre;
char* artiste;
} CellMorceau;

/* Cellule de l’arbre lexicographique */
typedef struct Noeud {
struct Noeud *liste_car;/* liste des choix possibles de caract‘eres */
struct Noeud *car_suiv;/* caract‘ere suivant dans la cha^ine */
CellMorceau *liste_morceaux;/* liste des morceaux ayant le m^eme interpr‘ete */
char car;
} Noeud;

typedef struct Biblio {
int nE;/* nombre d’’elements contenus dans l’arbre */
Noeud *A;/* arbre lexicographique */
} Biblio;

Biblio *nouvelle_biblio(void);

Biblio *charge_n_entrees(const char*nom_fichier , int n);

void affiche(Biblio *B);

void affiche_noeud(Noeud * n);
//
// void affiche_morceau(CellMorceau * L);

void insere(Biblio *B, int num , char* titre , char* artiste);

// void recherche_artiste_prof(Biblio *B, char *artiste);

// void recherche_artiste(Biblio *B, char *artiste);
//
// void affiche_noeud_artiste(Noeud * n, char * artiste);

// void recherche_numero(Biblio * B, int n);
//
// void affiche_noeud_num(Noeud * n, int num);
//
// void recherche_titre(Biblio * B, char * titre);
//
// void affiche_noeud_titre(Noeud * n, char * titre);

// void affiche_artiste(Biblio *B, char *artiste);

// void suppression_morceau(Biblio *B, char *a, int num, char * t);
//
// void affiche_doublon(Biblio *B);
//
// void affiche_noeud_doublon(Noeud * n);
//
// void affiche_liste_doublon(CellMorceau * l);


#endif/* biblio_arbrelex_h */
