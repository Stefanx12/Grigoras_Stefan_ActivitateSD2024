#include<stdio.h>
#include<malloc.h>

struct Haina {
	int marime;
	char* marca;
	float pret;
	char gender;
};

void afisareHaina(struct Haina h) {
	if (h.marca != NULL) {
		printf("Marca: %s\n", h.marca);
	}
	printf("Marime: %d\n", h.marime);
	printf("Pret: %5.2f\n", h.pret);
	printf("Genul: %c\n", h.gender);
}

struct Haina initializareHaina(int marime, const char* marca, float pret, char gender) {
	struct Haina h;
	h.marime = marime;
	if (h.marca != NULL && strlen(marca) > 0) {
		h.marca = malloc(strlen(marca) + 1);
		strcpy(h.marca, marca);
	}
	else {
		h.marca = NULL;
	}
	h.pret = pret;
	h.gender = gender;
	return h;
}

void dezalocare(struct Haina* h) {
	free(h->marca);
	h->marca = NULL;
}

void main() {
	struct Haina haina1;
	haina1.marime = 33;
	haina1.marca = (char*)malloc(sizeof(char) * (strlen("Nike") + 1));
	strcpy(haina1.marca, "Nike");
	haina1.pret = 45;
	haina1.gender = 'M';

	afisareHaina(haina1);
	dezalocare(&haina1);

	struct Haina haina2 = initializareHaina(27, "Addidas", 23.6, 'F');
	afisareHaina(haina2);
	dezalocare(&haina2);

}