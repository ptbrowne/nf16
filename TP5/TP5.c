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
        if (arbre->gch || arbre->drt) { // si c est des noeuds internes
            if (newEmploye->salaire<arbre->salaire)
                insererEmploye(arbre->gch,newEmploye);
            else
                insererEmploye(arbre->drt,newEmploye);
        }
        else { // on est arrive aux feuilles
            pNoeud newNoeud=Nouveaunoeud(newEmploye->salaire);
            empiler(newNoeud->pileEmploye,newEmploye);
            if (arbre->salaire==NULL) {

                return (pNoeud)newEmploye;
            }
            else {
                if (newEmploye->salaire<arbre->salaire)
                    arbre->gch=newNoeud;
                else
                    arbre->drt=newNoeud;
            }
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
        printf("gch");
        afficheArbreTest(arbre->gch);
    }
    if (arbre->drt)
        afficheArbreTest(arbre->drt);
}


int main() {
pNoeud a=Nouveaunoeud(1);
//pEmploye b=nouveauEmploye(14, "bob", "directeur",20,5000);
//printf("salaire : %d\n",a->salaire);
//afficherEmploye(b);

    int i,salaire;
    for (i=0;i<5;i++) {
        scanf("%d",&salaire);
        pEmploye b=nouveauEmploye(14, "bob", "directeur",20,salaire);
        insererEmploye(a,b);
    }
    afficheArbreTest(a);
}
