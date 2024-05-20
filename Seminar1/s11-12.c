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

Nod* rotireDreapta(Nod* rad)
{
	if (rad)
	{
		Nod* aux = rad->st;
		rad->st = aux->dr;
		aux->dr = rad;
		return aux;
	}
	else
	{
		return rad;
	}
}

Nod* rotireStanga(Nod* rad)
{
	if (rad)
	{
		Nod* aux = rad->dr;
		rad->dr = aux->st;
		aux->st = rad;
		return aux;
	}
	else
	{
		return rad;
	}
}

int calculInaltime(Nod* rad)
{
	if (rad != NULL)
	{
		int inaltimeSt = calculInaltime(rad->st);
		int inaltimeDr = calculInaltime(rad->dr);
		if (inaltimeSt > inaltimeDr)
			return 1 + inaltimeSt;
		else return 1 + inaltimeDr;
	}
	else return 0;

}

int calculGradEchilibru(Nod* rad)
{
	int inaltimeSubarboreSt = calculInaltime(rad->st);
	int inaltimeSubarboreDr = calculInaltime(rad->dr);
	return inaltimeSubarboreSt - inaltimeSubarboreDr;
}

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
		int grad = calculGradEchilibru(*(radacina));
		if (grad == 2)
		{
			//dezechibilru in partea stanga
			int gradCopil = calculGradEchilibru((*radacina)->st);
			if (gradCopil == -1)
			{
				(*radacina)->st = rotireStanga((*radacina)->st);
			}
			*radacina = rotireDreapta((*radacina));
		}
		else if (grad == -2)
		{
			int gradCopil = calculGradEchilibru((*radacina)->dr);
			if (gradCopil == 1)
			{
				(*radacina)->dr = rotireDreapta((*radacina)->dr);
			}
			*radacina = rotireStanga((*radacina));
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

void stergereArbore(Nod** rad)
{
	if (rad)
	{
		stergereArbore(&((*rad))->st);
		stergereArbore(&((*rad))->dr);
		if ((*rad)->info.listaFilme != NULL)
		{
			for (int i = 0; i < (*rad)->info.nrFilme; i++)
			{
				free((*rad)->info.listaFilme[i]);
			}
			free((*rad)->info.listaFilme);
		}
		free(*rad);
		*rad = NULL;
	}
}

Cinema calculCinemaCuNrMax(Nod* rad)
{
	if (rad)
	{
		Cinema cinemaSt = calculCinemaCuNrMax(rad->st);
		Cinema cinemaDr = calculCinemaCuNrMax(rad->dr);
		Cinema cinemaMaxim;
		if (rad->info.nrFilme > cinemaSt.nrFilme && rad->info.nrFilme > cinemaDr.nrFilme)
		{
			cinemaMaxim = rad->info;
		}
		else if (cinemaSt.nrFilme > cinemaDr.nrFilme)
		{
			cinemaMaxim = cinemaSt;
		}
		else
		{
			cinemaMaxim = cinemaDr;
		}
		return cinemaMaxim;
	}
	else
	{
		Cinema c;
		c.id = -1;
		c.listaFilme = NULL;
		c.nrFilme = 0;
		return c;
	}
}

void main()
{
	Nod* arbore = NULL;
	arbore = citireFisier("filme.txt");
	afisareArborePreordine(arbore);

	printf("\n NrFilme derulate: %d", CalculnrFilmeRedate(arbore));

	printf("\nCinema cu nr filme max: /n");
	Cinema cinema = calculCinemaCuNrMax(arbore);
	afisareCinema(cinema);

	stergereArbore(&arbore);
	afisareArborePreordine(arbore);


}