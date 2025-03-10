#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Carte Carte;

struct Carte
{
	char* autor;
	int nrPagini;
	float pret;
};

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

void main() {
	/*FILE* fisier;
	int nrIntreg1, nrIntreg2;
	fisier = fopen("FisierNumereIntregi.txt", "r");
	if (fisier != NULL) {
		fscanf(fisier, "%d", &nrIntreg1);
		fscanf(fisier, "%d", &nrIntreg2);
	}

	fclose(fisier);

	printf("\nNr1=%d, nr2=%d", nrIntreg1, nrIntreg2);

	int* vector;
	int length;
	printf("\n");

	citire_vector_fisier("fisier_vector.txt", &length, &vector);
	afisare_vector_fisier(length, vector);*/

	FILE* fileStream = fopen("Carte.txt", "r");
	Carte carte = citireCarte(fileStream);

	fclose(fileStream);

	printf("\n Autorul este: %s.", carte.autor);

	free(carte.autor);

	FILE* file = fopen("Carti.txt", "r");
	Carte* vectorCarti = NULL;
	int nrCarti = 0;
	citireVectorCarti(fileStream, &vectorCarti, &nrCarti);
	printf("\nAfisare vector:");
	for (int i = 0; i < nrCarti; i++) {
		printf("\nAutorul este: %s.", vectorCarti[i].autor);
		free(vectorCarti[i].autor);
	}

	fclose(file);
}