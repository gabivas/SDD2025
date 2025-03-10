#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Carte Carte;
typedef struct Nod Nod;

struct Carte
{
	char* autor;
	int nrPagini;
	float pret;
};

struct Nod
{
	Carte info;
	Nod* next;
};

void afisareCarte(Carte carte) {
	printf("\nCartea scrisa de %s are %d pagini si costa %.2f lei.", carte.autor, carte.nrPagini, carte.pret);
}

void citire_vector_fisier(char* file_name, int* length, int** vector) {
	FILE* fisier;
	fisier = fopen(file_name, "r");

	if (fisier == NULL) {
		return;
	}

	fscanf(fisier, "%d", length);

	*vector = (int*)malloc(sizeof(int) * (*length));

	for (int i = 0; i < (*length); i++) {
		fscanf(fisier, "%d", &(*vector)[i]);
	}
}

void afisare_vector_fisier(int length, int* vector) {
	for (int i = 0; i < (length); i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");
}

Carte citireCarte(FILE* fileStream) {
	Carte carte;
	char buffer[30];
	fgets(buffer, 30, fileStream);

	char* autor = strtok(buffer, "\n");

	carte.autor = (char*)malloc(sizeof(char) * (strlen(autor) + 1));
	strcpy(carte.autor, autor);

	fgets(buffer, 5, fileStream);
	carte.nrPagini = atoi(buffer);

	fgets(buffer, 5, fileStream);
	carte.pret = atof(buffer);
	return carte;
}

void citireVectorCarti(FILE* file, Carte** vectorCarti, int* nrCarti) {
	if (file == NULL) {
		return;
	}
	while (!feof(file)) {
		*vectorCarti = (Carte*)realloc(*vectorCarti, ((*nrCarti) + 1) * sizeof(Carte));
		(*vectorCarti)[*nrCarti] = citireCarte(file);
		(*nrCarti)++;
	}
}

void inserareLaInceput(Nod** cap, Carte carte) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carte;
	nou->next = *cap;
	*cap = nou;
}

void traversareLista(Nod* cap) {
	while (cap) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void inserareLaSfarsit(Nod** cap, Carte carte) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carte;
	nou->next = NULL;

	if ((*cap) == NULL) {
		*cap = nou;
	}
	else {
		Nod* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void dezalocare(Nod** cap) {
	while ((*cap)) {
		free((*cap)->info.autor);
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
}
}

int nrCartiByAutor(Nod* cap, char* autor){
	int cont = 0;
	while (cap) {

		if (strcmp(cap->info.autor, autor) == 0) {
			cont++;
		}

		cap = cap->next;
	}
	return cont;
}

void main() {
	FILE* fileStream = fopen("Carte.txt", "r");
	Carte carte = citireCarte(fileStream);

	fclose(fileStream);

	printf("\n Autorul este: %s.", carte.autor);

	free(carte.autor);

	FILE* file = fopen("Carti.txt", "r");
	Carte* vectorCarti = NULL;
	int nrCarti = 0;
	citireVectorCarti(fileStream, &vectorCarti, &nrCarti);
	//printf("\nAfisare vector:");

	Nod* cap = NULL;
	for (int i = 0; i < nrCarti; i++) {
		//printf("\nAutorul este: %s.", vectorCarti[i].autor);
		//afisareCarte(vectorCarti[i]);
		//free(vectorCarti[i].autor);
		//inserareLaInceput(&cap, vectorCarti[i]);
		inserareLaSfarsit(&cap, vectorCarti[i]);
	}
	traversareLista(cap);
	printf("\nNumarul de carti scrise de Nichita Stanescu este: %d", nrCartiByAutor(cap, "Nichita Stanescu"));

	dezalocare(&cap);
	
	free(vectorCarti);
	fclose(file);
}