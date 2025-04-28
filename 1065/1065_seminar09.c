#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Examen Examen;

struct Examen {
	int nrCredite; //prioritate
	char* materie;
	float nota;
};
typedef struct MaxHeap MaxHeap;

struct MaxHeap {
	Examen* vector;
	int dim;
};

Examen initExamen(int nrCredite, char* materie,float nota) {
	Examen nou;
	nou.nrCredite = nrCredite;
	nou.nota = nota;
	nou.materie = (char*)malloc(sizeof(char) * (strlen(materie) + 1));
	strcpy(nou.materie, materie);

	return nou;
}

void afisareExamen(Examen e) {
	printf("\nExamenul la mataria %s, are un numar de credite de %d, si nota minima promovare %f", e.materie, e.nrCredite, e.nota);
};

void traversareMaxHeap(MaxHeap m) {
	for (int i = 0; i < m.dim; i++)
	{
		afisareExamen(m.vector[i]);
	}
};

void filtrareMaxHeap(MaxHeap mHeap, int index) {
	if (mHeap.dim > 0) {
		int pozMax = index;
		int pozSt = 2 * index + 1;
		int pozDr = 2 * index + 2;

		if (pozSt < mHeap.dim && mHeap.vector[pozMax].nrCredite < mHeap.vector[pozSt].nrCredite) {
			pozMax = pozSt;
		}
		if (pozDr < mHeap.dim && mHeap.vector[pozMax].nrCredite < mHeap.vector[pozDr].nrCredite) {
			pozMax = pozDr;
		}

		if (pozMax != index) {
			Examen aux = mHeap.vector[index];
			mHeap.vector[index] = mHeap.vector[pozMax];
			mHeap.vector[pozMax] = aux;

			if (pozMax <= mHeap.dim / 2 - 1) {
				filtrareMaxHeap(mHeap, pozMax);
			}
		}
	}
}

void extragereDinMaxHeap(MaxHeap* mHeap, Examen* e) {
	*e = initExamen(mHeap->vector[0].nrCredite, mHeap->vector[0].materie, mHeap->vector[0].nota);
	Examen aux = mHeap->vector[0];
	mHeap->vector[0] = mHeap->vector[mHeap->dim - 1];
	mHeap->vector[mHeap->dim - 1] = aux;
	mHeap->dim--;
	filtrareMaxHeap(*mHeap, 0);
}

void main()
{
	MaxHeap m;
	m.dim = 6;

	m.vector = (Examen*)malloc(sizeof(Examen) * m.dim);

	m.vector[0] = initExamen(1, "POO", 5.3);
	m.vector[1]= initExamen(2, "ATP", 6.5);
	m.vector[2]= initExamen(3, "SDD", 4);
	m.vector[3]= initExamen(4, "Micro", 8.2);
	m.vector[4]= initExamen(5, "SGBD", 3.7);
	m.vector[5]= initExamen(6, "PAW", 2.3);

	traversareMaxHeap(m);

	for (int i = m.dim / 2 - 1; i >= 0; i--) {
		filtrareMaxHeap(m, i);
	}
	printf("\n MaxHeap valid:");
	traversareMaxHeap(m);

	Examen examen;
	printf("\n Extragere din heap:");
	while (m.dim != 0) {
		extragereDinMaxHeap(&m, &examen);
		afisareExamen(examen);
		free(examen.materie);
	}
	printf("\n MaxHeap valid:");

	for (int i = 0; i < 6; i++)
	{
		afisareExamen(m.vector[i]);
		free(m.vector[i].materie);
	}
	free(m.vector);
}

