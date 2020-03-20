#include "biblio_arbrelex.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

			insere(biblio, num, titre, artiste);
		}
	}
	fclose(f);
	return biblio;
}

//Creation d'une nouvelle biblioth'eque
Biblio * nouvelle_biblio(void){
	Biblio *biblio = (Biblio *) malloc(sizeof(Biblio));
	biblio -> A = NULL;
	biblio -> nE = 0;
	return biblio;
}

//Insertion d'un nouveau morceau dans une biblioth'eque
void insere(Biblio *B, int num, char *titre, char *artiste){
	CellMorceau * nouv = (CellMorceau *) malloc(sizeof(CellMorceau));
	nouv -> num = num;
	nouv -> titre = titre;
	nouv -> artiste = artiste ;
	nouv -> suiv = NULL;

	Noeud * cour = B->A;
	Noeud * prec = cour;

	int i = 0;
	while (artiste[i]!='\0'){
		if(cour==NULL){
			Noeud * n = (Noeud *) malloc(sizeof(Noeud *));
			n->car_suiv=NULL;
			n->liste_car=NULL;
			n->liste_morceaux=NULL;
			n->car = artiste[i];
			if(B->A==NULL){
				B->A=n;
			}
			if(prec!=NULL){
				prec->liste_car=n;
			}
			cour=n;
		}
		else if(cour->car == artiste[i]){
			prec=cour;
			cour=cour->car_suiv;
			i++;
		}else if (cour->car != artiste[i]){
			prec=cour;
			cour=cour->liste_car;
		}
	}


	if (prec->liste_morceaux== NULL){
		prec->liste_morceaux = nouv;
		nouv -> suiv = NULL;
	 }else{
	 	nouv->suiv=prec->liste_morceaux;
	 	prec->liste_morceaux=nouv;
	 }
	 B->nE=(B->nE)+1;
}

//Affiche la biblioth'eque
void affiche(Biblio *B){
	if(B->A==NULL){
		printf("La liste est vide\n");;
	} else {
		affiche_noeud(B->A);
	}
}

//Affiche le noeud et tous ceux qui font partie de la double liste chain'ee
void affiche_noeud(Noeud * n){
	Noeud * cour = n;

	if(cour->liste_morceaux != NULL){
		CellMorceau * l2 = cour->liste_morceaux;
		while(l2){
			printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
			l2 = l2->suiv;
		}
	}

	if(cour->liste_car!=NULL){
		affiche_noeud(cour->liste_car);
	}
	if(cour->car_suiv!=NULL){
		affiche_noeud(cour->car_suiv);
	}
}

//Affiche les morceaux avec le numero indiqu'e
void recherche_numero(Biblio * B, int n){
	if(B->A==NULL){
		printf("La liste est vide\n");;
	} else {
		affiche_noeud_num(B->A, n);
	}
}

void affiche_noeud_num(Noeud * n, int num){
	Noeud * cour = n;

	if(cour->liste_morceaux != NULL){
		CellMorceau * l2 = cour->liste_morceaux;
		while(l2){
			if(l2->num==num){
				printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
			}
			l2 = l2->suiv;
		}
	}

	if(cour->liste_car!=NULL){
		affiche_noeud_num(cour->liste_car, num);
	}
	if(cour->car_suiv!=NULL){
		affiche_noeud_num(cour->car_suiv, num);
	}
}


//Affiche les morceaux avec le titre indiqu'e
void recherche_titre(Biblio * B, char * titre){
	if(B->A==NULL){
		printf("La liste est vide\n");;
	} else {
		affiche_noeud_titre(B->A, titre);
	}
}

void affiche_noeud_titre(Noeud * n, char * titre){
	Noeud * cour = n;

	if(cour->liste_morceaux != NULL){
		CellMorceau * l2 = cour->liste_morceaux;
		while(l2){
			if((strcmp(l2->titre, titre)==0)){
				printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
			}
			l2 = l2->suiv;
		}
	}

	if(cour->liste_car!=NULL){
		affiche_noeud_titre(cour->liste_car, titre);
	}
	if(cour->car_suiv!=NULL){
		affiche_noeud_titre(cour->car_suiv, titre);
	}
}


//rechercher les morceaux par le nom d'artiste
void recherche_artiste(Biblio * B, char * artiste){
 	if(B->A==NULL){
 		printf("La liste est vide\n");;
 	} else {
 		affiche_noeud_artiste(B->A, artiste);
 	}
 }

 void affiche_noeud_artiste(Noeud * n, char * artiste){
 	Noeud * cour = n; int i=0;

 	if(cour->liste_morceaux != NULL){
 		CellMorceau * l2 = cour->liste_morceaux;
 		while(l2){
 			if((strcmp(l2->artiste, artiste)==0)){
 				printf("%d\t%s\t%s\n", l2->num, l2->titre, l2->artiste);
 			}
			l2 = l2->suiv;
 		}
 	}

 	if(cour->liste_car!=NULL){
 		affiche_noeud_artiste(cour->liste_car, artiste);
 	}
 	if(cour->car == artiste[i]){
			cour=cour->car_suiv;
			i++;
			if(cour->car_suiv!=NULL){
 				affiche_noeud_artiste(cour->car_suiv, artiste);
 			}
 	}
 }

//Supprimer un morceau
void suppression_morceau(Biblio *B, char *artiste, int num, char * t){
	Noeud * cour = B->A;
	Noeud * prec = cour;
 	int i = 0;
 	while ((cour!=NULL)&&(artiste[i]!='\0')){
 		prec=cour;
 		if(cour->car == artiste[i]){
 			cour=cour->car_suiv;
 			i++;
 		}else{
 			cour = cour ->liste_car;
 		}
 	}

 	if(artiste[i]=!'\0'){
 		printf("Artiste est pr'esent");
 		CellMorceau * l2 = cour->liste_morceaux;
 		CellMorceau * tmpL = cour->liste_morceaux;
 		if((strcmp(l2->titre, t)==0) && (strcmp(l2->artiste, artiste)==0) ){
 			cour->liste_morceaux=cour->liste_morceaux->suiv;
 			free(tmpL);
 			l2 = cour->liste_morceaux;
 		};

 		while (l2->suiv){
 			if((strcmp(l2->suiv->titre, t)==0) && (strcmp(l2->artiste, artiste)==0)){
 				CellMorceau * l3 = l2->suiv;
 				l2->suiv = l3->suiv;
 				free(l3);
 			}
 			l2=l2->suiv;
 		}
 		B->nE=(B->nE)-1;


 	}else{
 		printf("Artiste absent");
 	}
}

static Noeud * rechercheNoeudDe(Noeud *racine, int num)
{
	if (racine == NULL) return NULL;
	CellMorceau *tmp = racine->liste_morceaux;
	while (tmp != NULL && tmp->num != num)
		tmp = tmp->suiv;
	
	if (tmp != NULL) return racine;
	
	Noeud *tmpN = rechercheNoeudDe(racine->liste_car, num); 
	if (tmpN != NULL) return tmpN;
	return rechercheNoeudDe(racine->car_suiv, num);
}



//afficher les morceaux sans doublons
static long long int noeuds_uniques(Biblio *B, Noeud *A){
    if (A == NULL) return 0;
    long long int cpt = 0;
    CellMorceau *cour = A->liste_morceaux;
    while (cour != NULL) {
        CellMorceau *cour2 = A->liste_morceaux;
        while (cour2 != NULL) {
            cpt++;
            if (strcmp(cour->titre, cour2->titre) == 0 && cour != cour2)
                break;
            cour2 = cour2->suiv;
        }
        if (cour2 == NULL)
            insere(B, cour->num, strdup(cour->titre), strdup(cour->artiste));
        cour = cour->suiv;
    }
    cpt +=  noeuds_uniques(B, A->car_suiv);
    cpt += noeuds_uniques(B, A->liste_car);
    printf("test\n");
    return cpt;
}



Biblio *uniques (Biblio *B){
    Biblio *nouv = nouvelle_biblio();
    long long int cpt = noeuds_uniques(nouv, B->A);
    printf("NB tour: %lld\n", cpt);
    return nouv;
}

//supprimer un morceau du biblio
int supprimer_morceau(Biblio *B, int num)
{
	Noeud *nodeOfNum = rechercheNoeudDe(B->A, num);
	
	if (nodeOfNum == NULL) return 0;
	CellMorceau *tmp = nodeOfNum->liste_morceaux;
	if (tmp->num == num) {
		CellMorceau *suppr = tmp;
		nodeOfNum->liste_morceaux = suppr->suiv;
		B->nE--;
   
        free(suppr->titre);
        free(suppr->artiste);
        free(suppr);
        return 1;
	}
	
	CellMorceau *c = nodeOfNum->liste_morceaux;
	while (c->suiv->num != num)
		c = c->suiv;
	
	
	CellMorceau *suppr = c->suiv;
	c->suiv = suppr->suiv;
	
	free(suppr->titre);
    free(suppr->artiste);
    free(suppr);
    B->nE--;
    return 1;
}
//
// void affiche_doublon(Biblio *B){
// 	if(B->A==NULL){
// 		printf("La liste est vide\n");;
// 	} else {
// 		affiche_noeud_doublon(B->A);
// 	}
// }
//
// void affiche_noeud_doublon(Noeud * n){
// 	Noeud * cour = n;
//
// 	if(cour->liste_morceaux != NULL){
// 		CellMorceau * l2 = cour->liste_morceaux;
// 		while(l2){
// 			affiche_liste_doublon(cour->liste_morceaux);
// 		}
// 	}
//
// 	if(cour->liste_car!=NULL){
// 		affiche_noeud_doublon(cour->liste_car);
// 	}
// 	if(cour->car_suiv!=NULL){
// 		affiche_noeud_doublon(cour->car_suiv);
// 	}
// }
//
// void affiche_liste_doublon(CellMorceau * l){
// 	CellMorceau * l2 = l;
//
// 	while (l2){
// 		int vis =0;
// 		CellMorceau * l3=l;
// 		while(l3){
// 			if (((strcmp(l2->artiste, l3->artiste))==0)&&((strcmp(l2->titre, l3->titre))==0)&&l2->num != l3->num){
// 				vis=1;
// 			}
// 			l3=l3->suiv;
// 		}
// 		if(vis != 1){
// 			affiche_morceau(l2);
// 		}
// 		vis=0;
// 		l2=l2->suiv;
// 	}
// }

//liberer une bibliotheque
static void libere_noeud(Noeud *A){
    if (A == NULL) return;
    CellMorceau *it = A->liste_morceaux;
    while (it != NULL) {
    	CellMorceau *suppr = it;
    	it = it->suiv;
        free(suppr->titre);
        free(suppr->artiste);
        free(suppr);
    }
    
    
    libere_noeud(A->liste_car);
    libere_noeud(A->car_suiv);
    free(A);
}

void libere_biblio(Biblio *B){
    libere_noeud(B->A);
    free(B);
}
