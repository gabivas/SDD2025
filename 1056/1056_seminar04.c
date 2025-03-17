#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Shaorma Shaorma;
typedef struct Nod Nod;

struct Shaorma
{
	char* tip;
	float pret;
	int nrIngrediente;
};

struct Nod {
	Shaorma info;
	Nod* next;
	Nod* prev;
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

void afisareListaShaormaDreaptaStanga(Nod* coada) {
	while (coada != NULL) {
		afisareShaorma(coada->info);
		coada = coada->prev;
	}
}

void afisareListaShaormaCirculara(Nod* cap) {
	if (!cap) {
		return;
	}

	Nod* copie = cap;
	do {
		afisareShaorma(cap->info);
		cap = cap->next;

	} while (cap != copie);
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

void inserareLaInceput(Nod** cap, Nod** coada, Shaorma shaorma) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = shaorma;
	nou->next = *cap;
	nou->prev = NULL;

	if ((*cap) == NULL) {
		*cap = *coada =  nou;
	}
	else {
		(*cap)->prev = nou;
		*cap = nou;
	}
}

void inserareLaSfarsit(Nod** cap, Nod** coada, Shaorma shaorma) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = shaorma;
	nou->next = NULL;
	nou->prev = *coada;

	if ((*cap) == NULL) {
		*cap = *coada = nou;
	}
	else {
		(*coada)->next = nou;
		*coada = nou;
	}
}

void dezalocare(Nod** cap, Nod** coada) {
	while ((*cap) != NULL) {
		free((*cap)->info.tip);
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie);
	}
	*coada = NULL;
}

float calculPretMediuShaorma(Nod* cap) {
	float suma = 0;
	int contor = 0;
	while (cap != NULL) {
		suma += cap->info.pret;
		contor++;
		cap = cap->next;
	}
	return suma / contor;
}

float getShaormaPretMaximListaCirculara(Nod* cap) {
	float max = 0;
	if (cap == NULL)
	{
		return 0;
	}
	Nod* copie = cap;
	do {
		if ((cap)->info.pret > max)
		{
			max = cap->info.pret;
		}

		cap = cap->next;

	} while (cap != copie);
	return max;
}

void main() {
	FILE* file = fopen("VectorShaorma.txt", "r");
	Shaorma* vectorShaorma = NULL;
	int nrShaorma = 0;
	citireVectorShaorma(file, &vectorShaorma, &nrShaorma);
	Nod* cap = NULL;
	Nod* coada = NULL;
	for (int i = 0; i < nrShaorma; i++) {
		inserareLaSfarsit(&cap, &coada, vectorShaorma[i]);
	}

	cap->prev = coada;
	coada->next = cap;

	//LDI circulara

	afisareListaShaormaCirculara(cap);
	printf("\nShaorma cea mai scumpa costa %.2f lei!", getShaormaPretMaximListaCirculara(cap));
	//afisareListaShaorma(cap);
	//afisareListaShaormaDreaptaStanga(coada);
	//printf("\nPretul mediu pentru o shaorma este %.2f lei.", calculPretMediuShaorma(cap));
	
	//dezalocare(&cap, &coada);
	free(vectorShaorma);
	fclose(file);
}