#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct NodPrincipal NodPrincipal;
typedef struct Camion Camion;
typedef struct NodSecundar NodSecundar;
struct Camion
{
	int serie;
	char* marca;
	float greutate;
};

struct NodSecundar
{
	NodPrincipal* nod;
	NodSecundar* next;
};

struct NodPrincipal
{
	Camion info;
	NodSecundar* vecini;
	NodSecundar* next;
};

//inserare in lista principala la inceput
NodPrincipal* inserarePrincipala(NodPrincipal* graf, Camion c)
{
	NodPrincipal* nou = malloc(sizeof(NodPrincipal));
	nou->info = c;
	nou->next = graf;
	nou->vecini = NULL;
	return nou;
}

//functie de cautare NodPrincipal dupa serie camion
NodPrincipal* cautaNodDupaSerie(NodPrincipal* graf, int serie)
{
	while (graf && graf->info.serie != serie)
	{
		graf = graf->next;
	}
	return graf;
}

//inserare la sfarsit pt lista secundara
void inserareSecundara(NodSecundar** cap, NodPrincipal* nod)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->nod = nod;
	nou->next = NULL;
	if (*cap)
	{
		NodSecundar* p = *cap;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
	}
	else
	{
		*cap = nou;
	}
}

//inserare muchie in lista
void inserareMuchie(NodPrincipal* graf, int serieStart, int serieStop)
{
	NodPrincipal* nodStart = cautaNodDupaSerie(graf, serieStart);
	NodPrincipal* nodStop = cautaNodDupaSerie(graf, serieStop);
	if (nodStart && nodStop)
	{
		inserareSecundara(&(nodStart->vecini), nodStop);
		inserareSecundara(&(nodStop->vecini), nodStart);
	}
}

Camion creareCamion(int serie, const char* marca, float greutate)
{
	Camion c;
	c.serie = serie;
	c.greutate = greutate;
	c.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy(c.marca, marca);
	return c;
}

#pragma region coada

typedef struct NodCoada NodCoada;
struct NodCoada
{
	int info;
	NodCoada* next;
};

void inserareCoada(NodCoada** coada, int seria)
{
	NodCoada* nod = (NodCoada*)malloc(sizeof(NodCoada));
	nod->info = seria;
	nod->next = NULL;
	if (*coada)
	{
		NodCoada* aux = *coada;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nod;
	}
	else
	{
		*coada = nod;
	}
}

void pushStiva(NodCoada** stiva, int seria)
{
	NodCoada* nod = (NodCoada*)malloc(sizeof(NodCoada));
	nod->info = seria;
	nod->next = *stiva;
	*stiva = nod;
}

int popStiva(NodCoada** stiva)
{
	if (*stiva)
	{
		NodCoada* aux = *stiva;
		int rez = aux->info;
		*stiva = aux->next;
		free(aux);
		return rez;
	}
	return -1;
}

int popCoada(NodCoada** coada)
{
	if (*coada)
	{
		int rez = (*coada)->info;
		NodCoada* aux = *coada;
		*coada = (*coada)->next;
		free(aux);
		return rez;
	}
	return -1;
}

#pragma endregion

int calculNrNoduriGraf(NodPrincipal* graf)
{
	int nrNoduri = 0;
	while (graf)
	{
		nrNoduri++;
		graf = graf->next;
	}
	return nrNoduri;
}

void afisareCamion(Camion c)
{
	printf("%d. Camion %s are greutatea %6.2f\n", c.serie, c.marca, c.greutate);
}

void afisareParcurgereLatime(NodPrincipal* graf, int serieStart)
{
	if (graf)
	{
		NodCoada* coada = NULL;
		int nrNoduri = calculNrNoduriGraf(graf);
		char* vizitat = (char*)malloc(sizeof(char) * nrNoduri);
		for (int i = 0; i < nrNoduri; i++)
		{
			vizitat[i] = 0;
		}
		NodPrincipal* nodStart = cautaNodDupaSerie(graf, serieStart);
		if (nodStart)
		{
			vizitat[nodStart->info.serie] = 1;
			inserareCoada(&coada, nodStart->info.serie);
			while (coada)
			{
				int serieCurenta = popCoada(&coada);
				NodPrincipal* nodCurent = cautaNodDupaSerie(graf, serieCurenta);
				afisareCamion(nodCurent->info);
				NodSecundar* vecini = nodCurent->vecini;
				while (vecini)
				{
					if (vizitat[vecini->nod->info.serie] == 0)
					{
						inserareCoada(&coada, vecini->nod->info.serie);
						vizitat[vecini->nod->info.serie] = 1;
					}
					vecini = vecini->next;
				}
			}
		}
		if (vizitat)
		{
			free(vizitat);
		}
	}
}

void afisareParcurgereAdancime(NodPrincipal* graf, int serieStart)
{
	if (graf)
	{
		NodCoada* stiva = NULL;
		int nrNoduri = calculNrNoduriGraf(graf);
		char* vizitat = (char*)malloc(sizeof(char) * nrNoduri);
		for (int i = 0; i < nrNoduri; i++)
		{
			vizitat[i] = 0;
		}
		NodPrincipal* nodStart = cautaNodDupaSerie(graf, serieStart);
		if (nodStart)
		{
			vizitat[nodStart->info.serie] = 1;
			pushStiva(&stiva, nodStart->info.serie);
			while (stiva)
			{
				int serieCurenta = popStiva(&stiva);
				NodPrincipal* nodCurent = cautaNodDupaSerie(graf, serieCurenta);
				afisareCamion(nodCurent->info);
				NodSecundar* vecini = nodCurent->vecini;
				while (vecini)
				{
					if (vizitat[vecini->nod->info.serie] == 0)
					{
						pushStiva(&stiva, vecini->nod->info.serie);
						vizitat[vecini->nod->info.serie] = 1;
					}
					vecini = vecini->next;
				}
			}
		}
		if (vizitat)
		{
			free(vizitat);
		}
	}
}

void stergereListaVecini(NodSecundar** vecini)
{
	while (*vecini)
	{
		NodSecundar* aux = *vecini;
		(*vecini) = (*vecini)->next;
		free(aux);
	}
}

void stergereGraf(NodPrincipal** graf)
{
	while (*graf)
	{
		NodPrincipal* p = *graf;
		free(p->info.marca);
		stergereListaVecini(&(p->vecini));
		(*graf) = p->next;
		free(p);
	}
}

void main()
{
	NodPrincipal* graf = NULL;
	//inseram 5 noduri cu id urile 0 1 2 3 4
	graf = inserarePrincipala(graf, creareCamion(4, "Mercedes", 20));
	graf = inserarePrincipala(graf, creareCamion(3, "Scania", 20));
	graf = inserarePrincipala(graf, creareCamion(2, "Volvo", 30));
	graf = inserarePrincipala(graf, creareCamion(1, "Renault", 25));
	graf = inserarePrincipala(graf, creareCamion(0, "Man", 15));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 0, 3);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);
	inserareMuchie(graf, 1, 3);

	afisareParcurgereLatime(graf, 4);
	printf("\n\n");
	afisareParcurgereAdancime(graf, 4);

	stergereGraf(&graf);
}
