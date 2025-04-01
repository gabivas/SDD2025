#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Shaorma Shaorma;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

struct Shaorma
{
	char* tip;
	float pret;
	int nrIngrediente;
};

struct Nod {
	Shaorma info;
	Nod* next;
};

struct HashTable
{
	int dimensiune;
	Nod** vector;
};

void afisareShaorma(Shaorma shaorma) {
	printf("\nShaorma de tipul %s costa %.2f lei si contine %d ingrediente", shaorma.tip, shaorma.pret, shaorma.nrIngrediente);
}

void afisareListaShaorma(Nod* cap) {
	while (cap != NULL) {
		afisareShaorma(cap->info);
		cap = cap->next;
	}
}

Shaorma citireShaorma(FILE* fileStream) {
	char buffer[10];
	Shaorma shaorma;
	fgets(buffer, 10, fileStream);

	char* tip = strtok(buffer, "\n");
	shaorma.tip = (char*)malloc(sizeof(char) * (strlen(tip) + 1));
	strcpy(shaorma.tip, tip);

	fgets(buffer, 4, fileStream);
	shaorma.pret = atof(buffer);

	fgets(buffer, 4, fileStream);
	shaorma.nrIngrediente = atoi(buffer);

	return shaorma;
}

void citireVectorShaorma(FILE* file, Shaorma** vectorShaorma, int* nrShaorma) {
	if (file == NULL) {
		return;
	}
	while (!feof(file)) {
		*vectorShaorma = (Shaorma*)realloc(*vectorShaorma, ((*nrShaorma) + 1) * sizeof(Shaorma));
		(*vectorShaorma)[*nrShaorma] = citireShaorma(file);
		(*nrShaorma)++;
	}
}

void inserareLaSfarsit(Nod** cap, Shaorma shaorma) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = shaorma;
	nou->next = NULL;

	if ((*cap) == NULL) {
		*cap = nou;
	}
	else {
		Nod* aux = *cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

void dezalocare(Nod** cap) {
	while ((*cap) != NULL) {
		free((*cap)->info.tip);
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie);
	}
}

float calculPretMediuShaorma(HashTable tabela, int nrIngrediente) {
	float suma = 0;
	int contor = 0;
	int pozitie = hash(tabela.dimensiune, nrIngrediente);
	Nod* cap = tabela.vector[pozitie];
	while (cap != NULL) {
		suma += cap->info.pret;
		contor++;
		cap = cap->next;
	}
	return suma / contor;
}

HashTable initHashTable(int dimensiune) {
	HashTable tabela;
	tabela.dimensiune = dimensiune;
	tabela.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		tabela.vector[i] = NULL;
	}
	return tabela;
}

int hash(int dimensiune, int nrIngrediente) {
	return nrIngrediente % dimensiune;
}

void inserareHashTable(HashTable tabela, Shaorma shaorma) {
	if (tabela.dimensiune > 0) {
		int pozitie = hash(tabela.dimensiune, shaorma.nrIngrediente);
		if (pozitie >= 0 && pozitie < tabela.dimensiune) {
			inserareLaSfarsit(&(tabela.vector[pozitie]), shaorma);
		}
	}
}

void afisareHashTable(HashTable tabela){
	for (int i = 0; i < tabela.dimensiune; i++) {
		printf("\nPozitie: %d", i);
		afisareListaShaorma(tabela.vector[i]);
	}
}

void dezalocareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimensiune;i++) {
		dezalocare(&(tabela.vector[i]));
	}
	free(tabela.vector);
}

void main() {
	FILE* file = fopen("VectorShaorma.txt", "r");
	Shaorma* vectorShaorma = NULL;
	int nrShaorma = 0;
	citireVectorShaorma(file, &vectorShaorma, &nrShaorma);
	int dimensiune = 7;
	HashTable tabela = initHashTable(dimensiune);

	for (int i = 0; i < nrShaorma; i++) {
		inserareHashTable(tabela, vectorShaorma[i]);
	}

	afisareHashTable(tabela);
	printf("\nPretul mediu pentru o shaorma este %.2f lei.", calculPretMediuShaorma(tabela, 6));
	dezalocareHashTable(tabela);
	free(vectorShaorma);
	fclose(file);
}