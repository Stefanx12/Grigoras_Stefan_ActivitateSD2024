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
        printf("Denumire: %s\n", p.denumire);
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

void dezalocare(struct Patiserie* p) {
    free(p->denumire);
    p->denumire = NULL;
    free(p->glazura);
    p->glazura = NULL;
}

int main() {
    struct Patiserie GogoasaCiocolata;
    GogoasaCiocolata.denumire = (char*)malloc(sizeof(char) * (strlen("Gogoasa") + 1));
    strcpy(GogoasaCiocolata.denumire, "Gogoasa");
    GogoasaCiocolata.glazura = (char*)malloc(sizeof(char) * (strlen("Ciocolata") + 1));
    strcpy(GogoasaCiocolata.glazura, "Ciocolata");
    GogoasaCiocolata.pret = 12;
    GogoasaCiocolata.cantitate = 1;

    afisareComanda(GogoasaCiocolata);
    dezalocare(&GogoasaCiocolata);

    struct Patiserie GogoasaDulceata = initializareAliment("Gogoasa", "Dulceata", 14, 1);
    afisareComanda(GogoasaDulceata);
    dezalocare(&GogoasaDulceata);

    return 0;
}
