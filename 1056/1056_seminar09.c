#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Casa Casa;
typedef struct MaxHeap MaxHeap;

struct Casa {
	int prioritate;
	char* numeCasa;
	float facturaGaze;
};

struct MaxHeap {
	Casa* vector;
	int dimensiune;
};

//fct de init 
Casa initCasa(int prioritate, const char* numeCasa, float facturaGaze) {
	Casa casa;
	casa.prioritate = prioritate;
	casa.facturaGaze = facturaGaze;
	casa.numeCasa = (char*)malloc(sizeof(char) * (strlen(numeCasa) + 1));
	strcpy(casa.numeCasa, numeCasa);

	return casa;
}

//de afisare Casa
void afisareCasa(Casa casa) {
	printf("\nprioriotatea: %d,nume Casa: %s, factura de gaze: %.2f ", casa.prioritate, casa.numeCasa, casa.facturaGaze);
}

//traversare Max Heap
void traversareMaxHeap(MaxHeap maxheap) {
	for (int i = 0; i < maxheap.dimensiune; i++)
	{
		afisareCasa(maxheap.vector[i]);
	}
}

void filtrareMaxHeap(MaxHeap mHeap, int index) {
	if (mHeap.dimensiune > 0) {
		int pozMax = index;
		int pozSt = 2 * index + 1;
		int pozDr = 2 * index + 2;

		if (pozSt < mHeap.dimensiune && mHeap.vector[pozMax].prioritate < mHeap.vector[pozSt].prioritate) {
			pozMax = pozSt;
		}

		if (pozDr < mHeap.dimensiune && mHeap.vector[pozMax].prioritate < mHeap.vector[pozDr].prioritate) {
			pozMax = pozDr;
		}

		if (pozMax != index) {
			Casa aux = mHeap.vector[index];
			mHeap.vector[index] = mHeap.vector[pozMax];
			mHeap.vector[pozMax] = aux;

			if (pozMax <= mHeap.dimensiune / 2 - 1) {
				filtrareMaxHeap(mHeap, pozMax);
			}
		}
	}
}

void extragereDinMaxHeap(MaxHeap* mHeap, Casa* c) {
	*c = initCasa(mHeap->vector[0].prioritate, mHeap->vector[0].numeCasa, mHeap->vector[0].facturaGaze);
	Casa aux = mHeap->vector[0];
	mHeap->vector[0] = mHeap->vector[mHeap->dimensiune - 1];
	mHeap->vector[mHeap->dimensiune - 1] = aux;
	mHeap->dimensiune--;
	filtrareMaxHeap(*mHeap, 0);
}

int main() {
	MaxHeap mh;
	mh.dimensiune = 6;
	mh.vector = (Casa*)malloc(sizeof(Casa) * mh.dimensiune);

	mh.vector[0] = initCasa(1, "Coman", 6.3);
	mh.vector[1] = initCasa(2, "Datcu", 6.7);
	mh.vector[2] = initCasa(3, "Ana", 8.3);
	mh.vector[3] = initCasa(4, "Maria", 4.1);
	mh.vector[4] = initCasa(5, "Flavia", 5.3);
	mh.vector[5] = initCasa(6, "Andreea", 3.3);

	traversareMaxHeap(mh);

	for (int i = mh.dimensiune / 2 - 1; i >= 0; i--) {
		filtrareMaxHeap(mh, i);
	}

	printf("\n MaxHeap valid: ");
	traversareMaxHeap(mh);

	Casa casa;
	printf("\nExtragere din heap:");
	while (mh.dimensiune != 0) {
		extragereDinMaxHeap(&mh, &casa);
		afisareCasa(casa);
		free(casa.numeCasa);
	}
	printf("\nPrioritati ordonate crescator:");

	for (int i = 0; i < 6; i++)
	{
		afisareCasa(mh.vector[i]);
		free(mh.vector[i].numeCasa);
	}
	free(mh.vector);
}