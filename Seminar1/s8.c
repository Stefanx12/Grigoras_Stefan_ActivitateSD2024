#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Quiz Quiz;
typedef struct Heap Heap;

struct Quiz {
    char* materie;
    int grileGresite;
};

struct Heap {
    Quiz* vector;
    int dimensiune;
    int dimensiuneTotala;
};

Heap initializareHeap(int nr) {
    Heap heap;
    heap.vector = (Quiz*)malloc(nr * sizeof(Quiz));
    heap.dimensiuneTotala = nr;
    heap.dimensiune = 0;
    return heap;
}

Heap adaugareQuizHeap(Quiz quiz, Heap heap) {
    if (heap.dimensiune < heap.dimensiuneTotala) {
        heap.vector[heap.dimensiune] = quiz;
        heap.dimensiune++;
        //To do filtrare
    }
    return heap;
}

Quiz initializareQuiz(char* materie, int grileGresite) {
    Quiz q;
    q.materie = (char*)malloc(strlen(materie) + 1);
    strcpy(q.materie, materie);
    q.grileGresite = grileGresite;
    return q;
}

void afisareQuiz(Quiz q) {
    printf("Materie: %s NrGrileGresite: %d\n", q.materie, q.grileGresite);
}

void afisareHeap(Heap h) {
    for (int i = 0; i < h.dimensiune; i++) {
        afisareQuiz(h.vector[i]);
    }
}

Heap filtrareHeap(Heap heap, int pozRadacina) {
    int nodSt = pozRadacina * 2 + 1;
    int nodDr = pozRadacina * 2 + 2;
    int idxMin = pozRadacina;
    if (nodSt < heap.dimensiune && heap.vector[nodSt].grileGresite < heap.vector[idxMin].grileGresite) {
        idxMin = nodSt;
    }

    if (nodDr < heap.dimensiune && heap.vector[nodDr].grileGresite < heap.vector[idxMin].grileGresite) {
        idxMin = nodDr;
    }

    if (idxMin != pozRadacina) {
        Quiz aux;
        aux = heap.vector[pozRadacina];
        heap.vector[pozRadacina] = heap.vector[idxMin];
        heap.vector[idxMin] = aux;
        filtrareHeap(heap, idxMin);
    }
    return heap;
}

Quiz extragereMinim(Heap* heap) {
    if (heap->dimensiune > 0) {
        Quiz aux;
        aux = heap->vector[0];
        heap->vector[0] = heap->vector[heap->dimensiune - 1];
        heap->vector[heap->dimensiune - 1] = aux;

        heap->dimensiune--;

        for (int i = (heap->dimensiune) / 2 - 2; i >= 0; i--)
            filtrareHeap(*heap, i);

        return aux;
    }
    else {
        return initializareQuiz("N/A", -1);
    }
}

int main() {
    Heap heap;
    heap = initializareHeap(6);
    heap.vector[0] = initializareQuiz("SDD", 10);
    heap.vector[1] = initializareQuiz("Java", 20);
    heap.vector[2] = initializareQuiz("PEAG", 1);
    heap.vector[3] = initializareQuiz("Analiza", 0);
    heap.vector[4] = initializareQuiz("ATP", 4);
    heap.vector[5] = initializareQuiz("POO", 9);

    heap.dimensiune = 6;
    afisareHeap(heap);

    for (int i = (heap.dimensiune) / 2 - 2; i >= 0; i--)
        filtrareHeap(heap, i);

    printf("\n\n");
    afisareHeap(heap);

    printf("\n\n");

    afisareQuiz(extragereMinim(&heap));
    afisareQuiz(extragereMinim(&heap));

    free(heap.vector);

    return 0;
}
