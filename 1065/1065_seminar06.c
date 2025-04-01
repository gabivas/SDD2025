#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Carte Carte;
typedef struct Nod Nod;
typedef struct HashTable HashTable;

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

//mecanismul chaining
struct HashTable
{
	int dimensiune;
	Nod** vector;
};

void afisareCarte(Carte carte) {
	printf("\nCartea scrisa de %s are %d pagini si costa %.2f lei.", carte.autor, carte.nrPagini, carte.pret);
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

int nrCartiByAutor(HashTable tabela, char* autor) {
	int cont = 0;
	int pozitie = hash(autor[0], tabela.dimensiune);
	Nod* cap = tabela.vector[pozitie];
	while (cap) {

		if (strcmp(cap->info.autor, autor) == 0) {
			cont++;
		}

		cap = cap->next;
	}
	return cont;
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

int hash(char primaLiteraAutor, int dimensiune) {
	return primaLiteraAutor % dimensiune;
}

void inserareInHashTable(HashTable tabela, Carte carte) {
	if (tabela.dimensiune > 0) {
		int pozitie = hash(carte.autor[0], tabela.dimensiune);
		if (pozitie >= 0 && pozitie < tabela.dimensiune) {
			inserareLaSfarsit(&(tabela.vector[pozitie]), carte);
		}
	}
}

void traversareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimensiune; i++) {
		printf("\nPozitia: %d", i);
		traversareLista(tabela.vector[i]);
	}
}

void dezalocareHashTable(HashTable tabela) {
	for (int i = 0; i < tabela.dimensiune; i++) {
		dezalocare(&(tabela.vector[i]));
	}
	free(tabela.vector);
}

void main() {
	FILE* file = fopen("Carti.txt", "r");
	Carte* vectorCarti = NULL;
	int nrCarti = 0;
	citireVectorCarti(file, &vectorCarti, &nrCarti);

	HashTable tabela = initHashTable(6);
	for (int i = 0; i < nrCarti; i++) {
		inserareInHashTable(tabela, vectorCarti[i]);
	}
	traversareHashTable(tabela);
	printf("\nNumarul de carti scrise de Nichita Stanescu este: %d", nrCartiByAutor(tabela, "Nichita Stanescu"));

	dezalocareHashTable(tabela);

	free(vectorCarti);
	fclose(file);
}