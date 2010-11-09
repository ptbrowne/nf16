#include "arbre.h"

//fonctions deja developpees
pPileN creerPileN() {
    pPileN p = (pPileN)malloc(sizeof(PileN));

    if(p==NULL)
    {
        perror("erreur: pile.c : fonction creerPileN: manque de memoire");
        return NULL;
    }

	p->iSommet = -1;

	return p;
}

int	pileVideN ( pPileN p) {
    if(p == NULL)
    {
        perror("erreur: pile.c : fonction pileVideN: pointeur NULL");
        return ERROR;
    }

	if (p->iSommet == -1)
		return 1;
	else
		return 0;
}

int	pilePleineN( pPileN p) {
    if(p == NULL)
    {
        perror("erreur: pile.c : fonction pilePleineN: pointeur NULL");
        return ERROR;
    }

	if (p->iSommet == (MAX_SIZE_PILE -1) )
		return 1;
	else
		return 0;
}

void empilerN( pPileN p, pNoeud pN) {
    if(p == NULL || pN == NULL)
    {
        perror("erreur: pile.c : fonction empilerN: pointeur NULL");
        return;
    }

	if (pilePleineN(p)) {
		printf("erreur: pile.c : fonction empilerN: la Pile est pleine\n");
		return;
	}

	p->iSommet = p->iSommet + 1;
	p->tabNoeud[ p->iSommet] = pN;
}

pNoeud depilerN( pPileN p) {
	pNoeud pN;
    if(p == NULL)
    {
        perror("erreur: pile.c : fonction depilerN: pointeur NULL");
        return NULL;
    }

	if (pileVideN(p)) {
		printf("erreur: pile.c : fonction depilerN: la Pile est vide\n");
		return NULL;
	}

	pN = p->tabNoeud[ p->iSommet];
	p->iSommet = p->iSommet-1;
	return pN;
}

pNoeud SommetNoeud( pPileN p ){
     if(p == NULL)
    {
        perror("erreur: pile.c : fonction SommetNoeud: pointeur NULL");
        return NULL;
    }

	if (pileVideN(p)) {
		printf("erreur: pile.c : fonction SommetNoeud: la Pile est vide\n");
		return NULL;
	}

	return p->tabNoeud[ p->iSommet];
}


void supprimerPileN(pPileN p){
    pNoeud pN;

    if(p == NULL)
    {
        perror("erreur: pile.c : fonction supprimerPileN: pointeur NULL");
        return;
    }

    while(!pileVideN(p))
    {
      pN = depilerN(p);
      free(pN);
    }

	free(p);
}


pNoeud minimumABR(pNoeud arbre) {
    pNoeud pN;
    pN = arbre;

    if(arbre==NULL)
    {
         perror("erreur: arbre.c : fonction minimumABR: pointeur NULL");
         return NULL;
    }

    while(pN->gch!=NULL)
        pN = pN->gch;

    return pN;
}

pNoeud succeseurABR(pNoeud noeud) {
      pNoeud pNX,pNY;

      if(noeud->drt != NULL)
            return minimumABR(noeud->drt);

      pNY = noeud->pere;
      pNX = noeud;

      while(pNY!=NULL && pNX == pNY->drt)
      {
        pNX = pNY;
        pNY = pNY->pere;
      }
      return pNY;
}

void copyEmployer(pEmploye pe1, pEmploye pe2)
{
    pe1->num = pe2->num;
    strcpy(pe1->nom,pe2->nom);
    strcpy(pe1->fct,pe2->fct);
    pe1->age = pe2->age;
    pe1->salaire = pe2->salaire;
}


//fonctions a developper. libre a vous de rajouter des autres fonctions si necessaire
// la fonction supprimerNoeud vous est fournie

pNoeud supprimerNoeud(pNoeud arbre, pNoeud noeud)
{
       pNoeud pn, pnS;

       if(arbre==NULL || noeud==NULL)
       {
         perror("erreur: arbre.c : fonction supprimerNoeud: pointeur NULL");
         return arbre;
       }

       if(noeud->gch==NULL && noeud->drt==NULL) // si c'est une feuille
       {
         pn = noeud->pere;
         if(pn == NULL)
               arbre = NULL;
         else if(noeud == pn->gch)
               pn->gch = NULL;
         else
               pn->drt = NULL;
       }
       else if(noeud->drt==NULL)  // fils gauche n'est pas nul
       {
            pn = noeud->pere;

            if(pn == NULL)
              arbre =  noeud->gch;
            else if(noeud == pn->gch)
              pn->gch = noeud->gch;
            else
              pn->drt = noeud->gch;

            noeud->gch->pere = pn;
       }
       else if(noeud->gch==NULL) // fils droit n'est pas nul
       {
            pn = noeud->pere;

            if(pn == NULL)
              arbre =  noeud->drt;
            else if(noeud == pn->gch)
              pn->gch = noeud->drt;
            else
              pn->drt = noeud->drt;

            noeud->drt->pere = pn;
       }
       else  //tous les deux fils ne sont pas nul
       {
           pnS = succeseurABR(noeud);

           if(pnS == pnS->pere->gch)
             pnS->pere->gch = NULL;
           else
             pnS->pere->drt = NULL;

           pnS->pere = noeud->pere;
           pnS->gch = noeud->gch;
           pnS->drt = noeud->drt;

           if(pnS->pere==NULL)
             arbre = pnS;
           else if(pnS == pnS->pere->gch)
             pnS->pere->gch = pnS;
           else
             pnS->pere->drt = pnS;

           if(pnS->gch != NULL)
             pnS->gch->pere = pnS;
           if(pnS->drt != NULL)
             pnS->drt->pere = pnS;
       }
         supprimerPile(noeud->pileEmploye);
         free(noeud);

         return arbre;
}
