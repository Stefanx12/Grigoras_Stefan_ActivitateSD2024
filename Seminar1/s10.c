#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct Cinema Cinema;
struct Cinema
{
	int id;
	int nrFilme;
	char** listaFilme;
};

typedef struct Nod Nod;
struct Nod
{
	Cinema info;
	Nod* st;
	Nod* dr;
};

void inserareInArbore(Nod** radacina, Cinema c)
{
	if (*radacina)
	{
		if ((*radacina)->info.id > c.id)
		{
			inserareInArbore(&((*radacina))->st, c);
		}
		else
		{
			inserareInArbore(&((*radacina)->dr), c);
		}
	}
	else
	{
		Nod* nod = malloc(sizeof(Nod));
		nod->dr = NULL;
		nod->st = NULL;
		nod->info = c;
		*radacina = nod;
	}
}

Cinema citireCinema(FILE* f)
{
	Cinema c;
	fscanf(f, "%d", &c.id);
	if (c.nrFilme != 0)
	{
		fscanf(f, "%d", &c.nrFilme);
		c.listaFilme = malloc(sizeof(char*) * c.nrFilme);
		for (int i = 0; i < c.nrFilme; i++)
		{
			char buffer[100];
			fscanf(f, "%s", buffer);
			c.listaFilme[i] = malloc(sizeof(char) * strlen((buffer)+1));
			strcpy(c.listaFilme[i], buffer);
		}
	}
	else
	{
		c.listaFilme = NULL;
	}
	return c;
}

Nod* citireFisier(const char* numeFisier)
{
	Nod* radacina = NULL;
	if (numeFisier != NULL && strlen(numeFisier) > 0)
	{
		FILE* f = fopen(numeFisier, "r");
		if (f != NULL)
		{
			int dim = 0;
			fscanf(f, "%d", &dim);
			for (int i = 0; i < dim; i++)
			{
				Cinema cinema = citireCinema(f);
				inserareInArbore(&radacina, cinema);
			}
		}
	}
	return radacina;
}

void afisareCinema(Cinema c)
{
	printf("Cinematograful cu id-ul %d are in derulare %d filme: ", c.id, c.nrFilme);
	for (int i = 0; i < c.nrFilme; i++)
	{
		printf("%s, ", c.listaFilme[i]);
	}
	printf("\n");
}

void afisareArboreInOrdine(Nod* rad)
{
	if (rad)
	{
		afisareArboreInOrdine(rad->st);
		afisareCinema(rad->info);
		afisareArboreInOrdine(rad->dr);
	}
}

void afisareArborePreordine(Nod* radacina)
{
	if (radacina)
	{
		afisareCinema(radacina->info);
		afisareArborePreordine(radacina->st);
		afisareArborePreordine(radacina->dr);
	}
}

int CalculnrFilmeRedate(Nod* radacina)
{
	if (radacina)
	{
		int sum = radacina->info.nrFilme;
		sum += CalculnrFilmeRedate(radacina->st);
		sum += CalculnrFilmeRedate(radacina->dr);
		return sum;
	}
	else
	{
		return 0;
	}
}

void main()
{
	Nod* arbore = NULL;
	arbore = citireFisier("filme.txt");
	afisareArboreInOrdine(arbore);

	printf("\n NrFilme derulate: %d", CalculnrFilmeRedate(arbore));
}