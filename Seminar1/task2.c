#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Patiserie {
    char* denumire;
    char* glazura;
    float pret;
    int cantitate;
};

void afisareComanda(struct Patiserie p) {
    if (p.denumire != NULL) {
        printf("\nDenumire: %s\n", p.denumire);
    }
    printf("Glazura: %s\n", p.glazura);
    printf("Pret: %.2f\n", p.pret);
    printf("Cantitate: %d\n", p.cantitate);
}

struct Patiserie initializareAliment(const char* denumire, const char* glazura, float pret, int cantitate) {
    struct Patiserie p;
    p.denumire = malloc(strlen(denumire) + 1);
    strcpy(p.denumire, denumire);
    p.glazura = malloc(strlen(glazura) + 1);
    strcpy(p.glazura, glazura);
    p.pret = pret;
    p.cantitate = cantitate;
    return p;
}

struct Patiserie* copiazaPrimeleNAricole(struct Patiserie* p, int nrArticole, int nrArticoleCopiate) {
    if (nrArticoleCopiate < nrArticole && nrArticole > 0) {
        struct Patiserie* copie = (struct Patiserie*)malloc(sizeof(struct Patiserie) * nrArticoleCopiate);
        for (int i = 0; i < nrArticoleCopiate; i++) {
            copie[i] = initializareAliment(p[i].denumire, p[i].glazura, p[i].pret, p[i].cantitate);
        }
        return copie;
    }
    else
    {
        return NULL;
    }
}

void dezalocare(struct Patiserie* p) {
    free(p->denumire);
    p->denumire = NULL;
    free(p->glazura);
    p->glazura = NULL;
}

float calculeazaPret(struct Patiserie p) {
    return p.pret * p.cantitate;
}

struct Patiserie* copieAlimentePret(struct Patiserie* p, int nrArticole, int* nrArticoleMutate) {
    struct Patiserie* noileAlimente = (struct Patiserie*)malloc(sizeof(struct Patiserie) * nrArticole);
    *nrArticoleMutate = 0;

    for (int i = 0; i < nrArticole; i++) {
        if (p[i].pret > 20) {
            noileAlimente[*nrArticoleMutate] = p[i];
            (*nrArticoleMutate)++;
        }
    }

    return noileAlimente;
}

void main() {
    struct Patiserie p1 = initializareAliment("Cozoonac", "Nuca", 60, 1);
    struct Patiserie p2 = initializareAliment("Croissant", "Fructe", 5, 1);
    struct Patiserie p3 = initializareAliment("Muffins", "Ciocolata", 21, 1);
    struct Patiserie p4 = initializareAliment("Chec", "Fructe", 40, 1);
    struct Patiserie p5 = initializareAliment("Ecler", "Ciocolata", 15, 1);

    int nrAlimente = 5;
    struct Patiserie* produse = (struct Patiserie*)malloc(sizeof(struct Patiserie) * nrAlimente);
    produse[0] = p1;
    produse[1] = p2;
    produse[2] = p3;
    produse[3] = p4;
    produse[4] = p5;

    int nrAlimenteCopiate = 3;
    struct Patiserie* copie = copiazaPrimeleNAricole(produse, nrAlimente, nrAlimenteCopiate);
    if (copie != NULL) {
        printf("\nPrimele %d alimente copiate:\n", nrAlimenteCopiate);
        for (int i = 0; i < nrAlimenteCopiate; i++) {
            afisareComanda(copie[i]);
        }
        for (int i = 0; i < nrAlimenteCopiate; i++) {
            dezalocare(&copie[i]);
        }
        free(copie);
    }
    else {
        printf("\nNumarul de obiecte de copiat este mai mare sau egal cu numarul total de obiecte sau sunt mai putin de 1 obiecte.\n");
    }

    int nrArticolePret;
    printf("\nAlimente copiate cu pret mai mare de 20:\n");
    struct Patiserie* ArticoleCopiatePret = copieAlimentePret(produse, nrAlimente, &nrArticolePret);
    for (int i = 0; i < nrArticolePret; i++) {
        afisareComanda(ArticoleCopiatePret[i]);
    }
    free(ArticoleCopiatePret);
    free(produse);
}