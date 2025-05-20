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

void main() {
	NodPrincipal* graf = NULL;
	inserareListaPrincipala(&graf, initExamen(1, "SDD", 5));
	inserareListaPrincipala(&graf, initExamen(2, "PAW", 5));
	inserareListaPrincipala(&graf, initExamen(3, "PEAG", 5));
	inserareListaPrincipala(&graf, initExamen(4, "JAVA", 5));
	inserareListaPrincipala(&graf, initExamen(5, "MACRO", 5));
	inserareListaPrincipala(&graf, initExamen(6, "SGBD", 5));
	
}