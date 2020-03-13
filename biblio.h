/* biblio.h */
#include "biblio_liste.h"
#include "biblio_arbrelex.h"
#ifndef biblio_h
#define biblio_h


Biblio *nouvelle_biblio(void);
Biblio *charge_n_entrees(const char*nom_fichier , int n);
void libere_biblio(Biblio *B);

void affiche(Biblio *B);
void affiche_morceau(CellMorceau * L);
void affiche_morceau_avec_num(CellMorceau * L, int n);

Biblio *uniques(Biblio *B);

/* Ajoutez toutes les fonctions communes ‘a toutes les structures de donn’ees. */

#endif/* biblio_h */