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
	Nod* prev;
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

void inserareLaInceput(Nod** cap, Nod** coada, Carte carte) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carte;
	nou->next = *cap;
	nou->prev = NULL;

	if ((*cap) != NULL) {
		(*cap)->prev = nou;
		*cap = nou;
	}
	else {
		*cap = *coada = nou;
	}	
}

void traversareLista(Nod* cap) {
	while (cap) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void traversareListaDreaptaStanga(Nod* coada) {
	while (coada) {
		afisareCarte(coada->info);
		coada = coada->prev;
	}
}

void inserareLaSfarsit(Nod** cap, Nod** coada, Carte carte) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carte;
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
	while ((*cap)) {
		free((*cap)->info.autor);
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp);
	}
	*coada = NULL;
}

int nrCartiByAutor(Nod* cap, char* autor) {
	int cont = 0;
	while (cap) {

		if (strcmp(cap->info.autor, autor) == 0) {
			cont++;
		}

		cap = cap->next;
	}
	return cont;
}

void traversareListaCirculara(Nod* cap) {
	if (!cap) {
		return;
	}
	Nod* copie = cap;
	do {
		afisareCarte(cap->info);
		cap = cap->next;

	} while (cap != copie);

}

int nrCartiByAutorListaCirculara(Nod* cap, const char* autor) {
	int contor = 0;
	if (cap == NULL) {
		return contor;
	}

	Nod* copie = cap;
	do {
		if (strcmp(cap->info.autor, autor) == 0) {
			contor++;
		}
		cap = cap->next;

	} while (cap != copie);
	return contor;
}

void main() {
	FILE* file = fopen("Carti.txt", "r");
	Carte* vectorCarti = NULL;
	int nrCarti = 0;
	citireVectorCarti(file, &vectorCarti, &nrCarti);

	Nod* cap = NULL;
	Nod* coada = NULL;
	for (int i = 0; i < nrCarti; i++) {
		//inserareLaInceput(&cap, &coada, vectorCarti[i]);
		inserareLaSfarsit(&cap, &coada, vectorCarti[i]);
	}
	//traversareLista(cap);
	//traversareListaDreaptaStanga(coada);
	//printf("\nNumarul de carti scrise de Nichita Stanescu este: %d", nrCartiByAutor(cap, "Nichita Stanescu"));

	//dezalocare(&cap, &coada);

	//LDI circulara
	coada->next = cap;
	cap->prev = coada;

	traversareListaCirculara(cap);

	printf("\nNumarul de carti scrise de Nichita Stanescu este: %d", nrCartiByAutorListaCirculara(cap, "Nichita Stanescu"));

	free(vectorCarti);
	fclose(file);
}