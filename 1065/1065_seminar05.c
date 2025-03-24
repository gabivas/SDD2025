#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <string.h>

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina
{
	char* marca;
	int putere;
	int anFabricatie;
};

struct Nod
{
	Masina info;
	Nod* next;
};

Masina creareMasina(const char* marca,
	int putere, int anFabricatie) {
	Masina m;
	if (marca != NULL){
		m.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
		strcpy(m.marca, marca);
	}
	m.putere = putere;
	m.anFabricatie = anFabricatie;
	return m;
}

void afisareMasina(Masina m) {
	printf("\nMarca:%s, Putere:%d, AnFabricatie:%d", m.marca, m.putere, m.anFabricatie);
}

void push(Nod** top, Masina m) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = *top;
	nou->info = m;
	*top = nou;
}

Masina pop(Nod** top)
{
	if (*top == NULL) 
		return creareMasina(NULL, 0, 0);
	Masina m = (*top)->info;
	Nod* temp = *top;
	*top = (*top)->next;
	free(temp);
	temp = NULL;
	return m;
}

void put(Nod** coada,Masina m) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->next = NULL;
	if (*coada == NULL) {
		*coada = nou;
	}
	else
	{
		Nod* temp = *coada;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void main() {
	Masina m1 = creareMasina("Audi", 130, 2017);
	Masina m2 = creareMasina("Bmw", 150, 2020);
	Masina m3 = creareMasina("Porsche", 230, 2019);
	/*afisareMasina(m1);
	afisareMasina(m2);
	afisareMasina(m3);*/
	Nod* top = NULL;
	push(&top, m1);
	push(&top, m2);
	push(&top, m3);

	Masina m4;
	printf("Parcurgere stiva:");
	while (top != NULL)
	{
		m4 = pop(&top);
		afisareMasina(m4);
		free(m4.marca);
	}
	
	Nod* coada = NULL;
	put(&coada, creareMasina("Audi", 130, 2017));
	put(&coada, creareMasina("Bmw", 150, 2020));
	put(&coada, creareMasina("Porsche", 230, 2019));
	printf("\n\nParcurgere coada:");
	while (coada != NULL)
	{
		m4 = pop(&coada);
		afisareMasina(m4);
		free(m4.marca);
	}
}