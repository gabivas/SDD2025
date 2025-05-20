#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
typedef struct Examen Examen;

typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct Nod {
	int ID;
	Nod* next;
	Nod* prev;
};

struct ListaDubla {
	Nod* first;
	Nod* last;
};

struct Examen {
	int id;
	char* materie;
	float nota;
};

struct NodPrincipal {
	Examen info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* info;
	NodSecundar* next;
};

void push(ListaDubla* ld, int ID) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = ld->first;
	nou->prev = NULL;
	nou->ID = ID;

	if (ld->first == NULL) {
		ld->first = ld->last = nou;
	}
	else {
		ld->first->prev = nou;
		ld->first = nou;
	}
}

void put(ListaDubla* ld, int ID) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL;
	nou->prev = ld->last;
	nou->ID = ID;

	if (ld->last == NULL) {
		ld->first = ld->last = nou;
	}
	else {
		ld->last->next = nou;
		ld->last = nou;
	}
}

int pop(ListaDubla* ld) {
	int ID = -1;
	if (ld->first) {
		ID = ld->first->ID;
		Nod* aux = ld->first;
		ld->first = ld->first->next;
		if (ld->first == NULL) {
			ld->last = NULL;
		}
		free(aux);
	}
	return ID;
}

Examen initExamen(int id, const char* materie, float nota)
{
	Examen examen;
	examen.id = id;
	examen.materie = (char*)malloc(strlen(materie) + 1);
	strcpy(examen.materie, materie);
	examen.nota = nota;

	return examen;
}

void inserareListaPrincipala(NodPrincipal** cap, Examen examen) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = examen;
	nou->next = NULL;
	nou->vecini = NULL;
	NodPrincipal* aux = *cap;
	if (*cap) {
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

void inserareListaSecundara(NodSecundar** cap, NodPrincipal* info)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->info = info;
	nou->next = NULL;
	if (*cap)
	{
		NodSecundar* aux = *cap;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		*cap = nou;
	}
}

void afisareExamen(Examen e) {
	printf("\n%d. Nota minima de promovare a examenului la materia %s: %.2f", e.id, e.materie, e.nota);
}

NodPrincipal* cautareNodDupaId(NodPrincipal* graf, int id) {
	while (graf != NULL && id != graf->info.id) {
		graf = graf->next;
	}
	return graf;
}

void adaugaMuchie(NodPrincipal* graf, int id1, int id2) {
	NodPrincipal* nod1 = cautareNodDupaId(graf, id1);
	NodPrincipal* nod2 = cautareNodDupaId(graf, id2);
	if (nod1 != NULL && nod2 != NULL) {
		inserareListaSecundara(&nod1->vecini, nod2);
		inserareListaSecundara(&nod2->vecini, nod1);
	}
}

void afisareGraf(NodPrincipal* graf) {
	while (graf != NULL) {
		afisareExamen(graf->info);
		NodSecundar* vecini = graf->vecini;
		printf("\n Vecini:");
		while (vecini) {
			afisareExamen(vecini->info->info);
			vecini = vecini->next;
		}
		printf("\n");
		graf = graf->next;
	}
}

void parcurgereInAdancime(NodPrincipal* graf, int idStart) {
	int dimensiune = 6;
	int* vectorVizitate = (int*)malloc(dimensiune * sizeof(int));
	for (int i = 0; i < dimensiune; i++) {
		vectorVizitate[i] = 0;
	}

	ListaDubla stiva;
	stiva.first = stiva.last = NULL;
	push(&stiva, idStart);
	vectorVizitate[idStart-1] = 1;
	while (stiva.first) {
		int idExtras = pop(&stiva);
		NodPrincipal* nodExtras = cautareNodDupaId(graf, idExtras);
		afisareExamen(nodExtras->info);
		NodSecundar* vecini = nodExtras->vecini;
		while (vecini) {
			if (vectorVizitate[vecini->info->info.id - 1] == 0) {
				push(&stiva, vecini->info->info.id);
				vectorVizitate[vecini->info->info.id - 1] = 1;
			}
			vecini = vecini->next;
		}
	}

	free(vectorVizitate);
}

void main() {
	NodPrincipal* graf = NULL;
	inserareListaPrincipala(&graf, initExamen(1, "SDD", 5));
	inserareListaPrincipala(&graf, initExamen(2, "PAW", 5));
	inserareListaPrincipala(&graf, initExamen(3, "PEAG", 5));
	inserareListaPrincipala(&graf, initExamen(4, "JAVA", 5));
	inserareListaPrincipala(&graf, initExamen(5, "MACRO", 5));
	inserareListaPrincipala(&graf, initExamen(6, "SGBD", 5));

	adaugaMuchie(graf, 1, 2);
	adaugaMuchie(graf, 1, 3);
	adaugaMuchie(graf, 2, 4);
	adaugaMuchie(graf, 3, 5);
	adaugaMuchie(graf, 4, 6);
	adaugaMuchie(graf, 5, 6);

	afisareGraf(graf);

	printf("\n Parcurgere in adancime:");
	parcurgereInAdancime(graf, 1);
}