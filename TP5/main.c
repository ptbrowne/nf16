#include "arbre.c"
#include "pile.c"
#include <stdbool.h>

pNoeud Nouveaunoeud(int salaire);
pEmploye nouveauEmploye(int num, char * nom, char * fonction, int age, int salaire);


pNoeud Nouveaunoeud(int salaire) {
    pNoeud newNoeud=(pNoeud)malloc(sizeof(Noeud));
    newNoeud->pileEmploye=creerPile();
    newNoeud->salaire=salaire;
    newNoeud->pere=NULL;
    newNoeud->gch=NULL;
    newNoeud->drt=NULL;

    return newNoeud;
}

pEmploye nouveauEmploye(int num, char * nom, char * fonction, int age, int salaire) {
    pEmploye newEmploye=(pEmploye)malloc(sizeof(Employe));

    newEmploye->num=num;
    strcpy(newEmploye->nom,nom);
    strcpy(newEmploye->fct,fonction);
    newEmploye->age=age;
    newEmploye->salaire=salaire;

    return newEmploye;
}

void afficherEmploye(pEmploye E) {
    printf("%d\t | ",E->num);
    printf("%s\t | ",E->nom);
    printf("%s\t | ",E->fct);
    printf("%d\t | ",E->age);
    printf("%d\t | ",E->salaire);
}


pNoeud chercherEmploye(pNoeud arbre, int numero) {
    if (arbre==NULL || numero==NULL)
        printf("erreur chercheEmploye : pointeur null ou numero null");
    else {
        if (chercherEmployePile(arbre->pileEmploye,numero)) {
            return arbre;
        }
        else {
            if (arbre->gch)
                chercherEmploye(arbre->gch,numero);
            if (arbre->drt)
                chercherEmploye(arbre->drt,numero);
        }
    }
    return NULL;
}

pNoeud insererEmploye(pNoeud arbre, pEmploye newEmploye) {
    if (newEmploye->salaire==arbre->salaire)
        empiler(arbre->pileEmploye,newEmploye);
    else {
        pNoeud arbre_ajout;
        if (newEmploye->salaire<arbre->salaire)
            arbre_ajout=arbre->gch;
        else
            arbre_ajout=arbre->drt;
        if (arbre_ajout!=NULL)
                insererEmploye(arbre_ajout,newEmploye);
        else {
            pNoeud newNoeud=Nouveaunoeud(newEmploye->salaire);
            empiler(newNoeud->pileEmploye,newEmploye);
            if (newEmploye->salaire<arbre->salaire)
                arbre->gch=newNoeud;
            else
                arbre->drt=newNoeud;
        }
    }
    while (arbre->pere!=NULL)
        arbre=arbre->pere; // on remonte
    return arbre; // on renvoie la racine
}

afficheArbreTest (pNoeud arbre) {
    int a=0,b=0;
    if (arbre->gch)
        a=arbre->gch->salaire;
    if (arbre->drt)
        b=arbre->drt->salaire;
    printf("%d : %d | %d\n",arbre->salaire,a,b);
    if (arbre->gch) {
        afficheArbreTest(arbre->gch);
    }
    if (arbre->drt)
        afficheArbreTest(arbre->drt);
}

pNoeud supprimerEmploye(pNoeud arbre, int numero) {
    pNoeud endroit=chercherEmploye(arbre,numero); // on cherche dans quel noeud est l'employe
    supprimerEmployePile(endroit->pileEmploye,numero); // on le supprime de la pile employe du noeud
    if (pileVide(endroit)) { // on supprime le noeud
        if (endroit->gch && endroit->drt) { // le noeud a 2 enfants
            // voir sur wikipedia : http://fr.wikipedia.org/wiki/Arbre_binaire_de_recherche#Suppression
        }
        else if (endroit->gch && endroit->drt==NULL)// le noeud a 1 enfant a gauche
            endroit->pere->gch=endroit->gch;
        else if (endroit->gch==NULL && endroit->drt)
            endroit->pere->drt=endroit->drt;
        else { // le noeud est une feuille
            if (endroit->pere->salaire>endroit->salaire) // endroit est a gauche
                endroit->pere->gch=NULL;
            else // endroit est a droite
                endroit->pere->drt=NULL;
        }
        free(endroit);
    }
}

int main() {
pNoeud a=Nouveaunoeud(5);
//pEmploye b=nouveauEmploye(14, "bob", "directeur",20,5000);
//printf("salaire : %d\n",a->salaire);
//afficherEmploye(b);
    int i,salaire;
    for (i=0;i<5;i++) {
        salaire=0;
        scanf("%d",&salaire);
        pEmploye b=nouveauEmploye(i, "", "",0,salaire);
        insererEmploye(a,b);
    }
    afficheArbreTest(a);

}
