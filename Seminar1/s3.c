#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Locuinta {
	int id;
	char* strada;
	int numar;
};

void afisareLocuinta(struct Locuinta l) {
	printf("ID-ul: %d\nStrada: %s Numarul: %d\n", l.id, l.strada, l.numar);
}

void afisareVectorLocuinta(struct Locuinta* vector, int dim)
{
	for (int i = 0; i < dim; i++) {
		afisareLocuinta(vector[i]);
	}
}

void inserareLocuinta(struct Locuinta** vector, int* dim, struct Locuinta l) {
	struct Locuinta* copie;
	copie = malloc(sizeof(struct Locuinta) * (++(*dim)));
	for (int i = 0; i < (*dim) - 1; i++) {
		copie[i] = (*vector)[i];
	}
	copie[(*dim) - 1] = l;
	if ((*vector) != NULL) {
		free((*vector));
	}
	(*vector) = copie;
}

void stergeLocuinta(struct Locuinta** vector, int* dim, int id) {
	int pozitie = -1; // Initialize with an invalid position
	for (int i = 0; i < *dim; i++) {
		if ((*vector)[i].id == id) {
			pozitie = i; // Store the position of the item to be deleted
			break;
		}
	}

	if (pozitie != -1) { // Check if the item was found
		struct Locuinta* copie = malloc(sizeof(struct Locuinta) * (*dim - 1));
		if (copie == NULL) {
			// Handle memory allocation failure
			printf("Memory allocation failed\n");
			return;
		}

		int j = 0;
		for (int i = 0; i < *dim; i++) {
			if (i != pozitie) {
				copie[j++] = (*vector)[i];
			}
		}
		(*dim)--;
		free(*vector);
		*vector = copie;
	}
}

void citesteFisier(const char* nume_fisier, struct Locuinta** vector, int* dim) {
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) 
	{
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL) {
			(*dim) = 0;
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL)
			{
				char* token;
				token = strtok(buffer, delimitator); //strtok lasa un flag in buffer pe care il cauta la urmatorul apel
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delimitator); // folosim NULL pt a continua de unde a ramas apelul precedent
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitator);
				locuinta.numar = atoi(token);
				inserareLocuinta(vector, dim, locuinta);
			}
		}
		fclose(f);
	}
}

void main()
{
	struct Locuinta* locuinte = NULL;
	int dim = 3;
	citesteFisier("fisier.txt", &locuinte, &dim);
	afisareVectorLocuinta(locuinte, dim);
	printf("Initial: \n\n");

	stergeLocuinta(&locuinte, &dim, 20);
	printf("Ulterior: \n\n");
	afisareVectorLocuinta(locuinte, dim);
}