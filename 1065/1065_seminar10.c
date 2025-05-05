#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct Examen Examen;

struct Examen {
	int id;
	char* materie;
	float nota;
};
typedef struct Nod Nod;

struct Nod {
	Examen info;
	Nod* stanga;
	Nod* dreapta;
};

Examen initExamen(int id, char* materie, float nota) {
	Examen nou;
	nou.id = id;
	nou.nota = nota;
	nou.materie = (char*)malloc(sizeof(char) * (strlen(materie) + 1));
	strcpy(nou.materie, materie);

	return nou;
}

void afisareExamen(Examen e) {
	printf("\nExamenul la mataria %s, are id-ul %d, si nota minima promovare %f", e.materie, e.id, e.nota);
};

void inserareBST(Nod** radacina, Examen examen) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = examen;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*radacina = nou;
	}
	else if (examen.id < (*radacina)->info.id) {
		inserareBST(&(*radacina)->stanga, examen);
	}
	else {
		inserareBST(&(*radacina)->dreapta, examen);
	}
}

void parcurgereInordineArbore(Nod* radacina) {
	if (radacina) {
		parcurgereInordineArbore(radacina->stanga);
		afisareExamen(radacina->info);
		parcurgereInordineArbore(radacina->dreapta);
	}
}

void parcurgerePostordineArbore(Nod* radacina) {
	if (radacina) {
		parcurgerePostordineArbore(radacina->stanga);
		parcurgerePostordineArbore(radacina->dreapta);
		afisareExamen(radacina->info);
	}
}

Examen cautareById(Nod* radacina, int id) {
	if (radacina == NULL) {
		return initExamen(-1, "", 0.0);
	}
	else if (id == radacina->info.id) {
		return initExamen(radacina->info.id, radacina->info.materie, radacina->info.nota);
	}
	else if (id < radacina->info.id) {
		return cautareById(radacina->stanga, id);
	}
	else {
		return cautareById(radacina->dreapta, id);
	}
}

void dezalocare(Nod** radacina) {
	if (*radacina) {
		dezalocare(&(*radacina)->stanga);
		dezalocare(&(*radacina)->dreapta);
		free((*radacina)->info.materie);
		free(*radacina);
	}
}

void main()
{
	Nod* radacina = NULL;

	inserareBST(&radacina, initExamen(7, "SDD", 5));
	inserareBST(&radacina, initExamen(4, "PAW", 5));
	inserareBST(&radacina, initExamen(9, "PEAG", 5));
	inserareBST(&radacina, initExamen(3, "JAVA", 5));
	inserareBST(&radacina, initExamen(5, "MACRO", 5));
	inserareBST(&radacina, initExamen(8, "POO", 5));
	inserareBST(&radacina, initExamen(2, "ATP", 5));
	inserareBST(&radacina, initExamen(1, "SGBD", 5));

	printf("\nParcurgere inordine arbore: ");
	parcurgereInordineArbore(radacina);

	printf("\nParcurgere postordine arbore: ");
	parcurgerePostordineArbore(radacina);

	Examen examenCautat = cautareById(radacina, 5);
	printf("\nExamenul cautat: ");
	afisareExamen(examenCautat);
	free(examenCautat.materie);

	dezalocare(&radacina);
}
