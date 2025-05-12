#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>

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

int inaltimeArbore(Nod* radacina) {
	if (radacina != NULL) {
		int inaltimeSt = inaltimeArbore(radacina->stanga);
		int inaltimeDr = inaltimeArbore(radacina->dreapta);
		if (inaltimeSt > inaltimeDr) {
			return 1 + inaltimeSt;
		}
		else {
			return 1 + inaltimeDr;
		}
	}
	else {
		return 0;
	}
}

int diferentaInaltimiSubarbori(Nod* radacina) {
	if (radacina != NULL) {
		return inaltimeArbore(radacina->stanga) - inaltimeArbore(radacina->dreapta);
	}
	else {
		return 0;
	}
}

void rotireLaDreapta(Nod** radacina) {
	Nod* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux->dreapta;
	aux->dreapta = *radacina;
	*radacina = aux;
}

void rotireLaStanga(Nod** radacina) {
	Nod* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = *radacina;
	*radacina = aux;
}

void inserareAVL(Nod** radacina, Examen examen) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = examen;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		*radacina = nou;
	}
	else if (examen.id < (*radacina)->info.id) {
		inserareAVL(&(*radacina)->stanga, examen);
	}
	else {
		inserareAVL(&(*radacina)->dreapta, examen);
	}

	//diferente inaltimi subarbori
	//s - d = 2 => dezechilibru pe partea stanga
	//s - d = -2 => dezechilibru pe partea dreapta

	int diferentaInaltimi = diferentaInaltimiSubarbori(*radacina);
	if (diferentaInaltimi == 2) {
		if (diferentaInaltimiSubarbori((*radacina)->stanga) == -1) {
			rotireLaStanga(&(*radacina)->stanga);
		}
		rotireLaDreapta(radacina);
	}
	if (diferentaInaltimi == -2) {
		if (diferentaInaltimiSubarbori((*radacina)->dreapta) == 1) {
			rotireLaDreapta(&(*radacina)->dreapta);
		}
		rotireLaStanga(radacina);
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

bool esteFrunza(Nod* radacina, int id) {
	if (radacina == NULL)
		return false;
	if (radacina->info.id == id && radacina->dreapta == NULL
		&& radacina->stanga == NULL) {
		return true;

	}
	return esteFrunza(radacina->stanga, id) || esteFrunza(radacina->dreapta, id);
}

void main()
{
	Nod* radacina = NULL;

	inserareAVL(&radacina, initExamen(7, "SDD", 5));
	inserareAVL(&radacina, initExamen(4, "PAW", 5));
	inserareAVL(&radacina, initExamen(9, "PEAG", 5));
	inserareAVL(&radacina, initExamen(3, "JAVA", 5));
	inserareAVL(&radacina, initExamen(5, "MACRO", 5));
	inserareAVL(&radacina, initExamen(8, "POO", 5));
	inserareAVL(&radacina, initExamen(2, "ATP", 5));
	inserareAVL(&radacina, initExamen(1, "SGBD", 5));

	printf("\nParcurgere inordine arbore: ");
	parcurgereInordineArbore(radacina);

	printf("\nParcurgere postordine arbore: ");
	parcurgerePostordineArbore(radacina);

	Examen examenCautat = cautareById(radacina, 5);
	printf("\nExamenul cautat: ");
	afisareExamen(examenCautat);
	free(examenCautat.materie);

	printf("\nDiferenta inaltimi subarbori: %d", diferentaInaltimiSubarbori(radacina));
	if (esteFrunza(radacina,2))
	{
		printf("\nNodul este frunza!");
	}
	else
	{
		printf("\nNodul Nu este frunza!");
	}

	dezalocare(&radacina);
}