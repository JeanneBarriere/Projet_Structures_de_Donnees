/* biblio_hachage.h */

#ifndef biblio_hachage_h
#define biblio_hachage_h

#include <math.h>
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_TABLE 60000
#define A 0.6180339887498949


typedef struct CellMorceau {
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
    unsigned int cle;
} CellMorceau;


typedef struct Biblio {
    int nE;
    int m;
    CellMorceau **T;    
} Biblio;


Biblio *charge_n_entrees(const char *nomfichier, int n);

Biblio *nouvelle_biblio(void); 

Biblio *nouvelle_biblio1();

void libere_biblio(Biblio *B);

static unsigned int fonction_cle(const char *artiste);

static unsigned int fonction_hachage(unsigned int k, int m);

void insere(Biblio *B, int num, char *titre, char *artiste);

void afficheMorceau(CellMorceau *cell);

void affiche(Biblio *B);

Biblio *uniques (Biblio *B);

//void recherche_doublons(Biblio * B);
   
CellMorceau * rechercheParNum(Biblio *B, int num);

CellMorceau *rechercheParTitre(Biblio *B, char * titre);

Biblio *rechercheParArtiste(Biblio *B, char * artiste);

void insereSansNum(Biblio *B, char *titre, char *artiste);

int supprimeMorceau(Biblio *B, int num);



#endif/* biblio_hachage_h */
