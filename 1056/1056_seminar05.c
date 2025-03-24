#include<stdio.h>
#include<malloc.h>

typedef struct Restaurant Restaurant;
typedef struct Nod Nod;

struct Restaurant
{
	char* nume;
	int capacitate;
	char* domeniu; //specific
};

struct Nod
{
	Restaurant info;
	Nod* next;
};

Restaurant initRestaurant(const char* nume, int capacitate, const char* domeniu) {
	Restaurant r;
	if (nume != NULL && domeniu != NULL) {
		r.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(r.nume, nume);
		r.domeniu = (char*)malloc(sizeof(char) * (strlen(domeniu) + 1));
		strcpy(r.domeniu, domeniu);
		r.capacitate = capacitate;
	}
	return r;
}

void afisareRestaurant(Restaurant r) {
	printf("Nume: %s, Capacitate: %d, Domeniu: %s\n", r.nume, r.capacitate, r.domeniu);
}

void push(Nod** varf, Restaurant r) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = r;
	nou->next = *varf;
	*varf = nou;
}

Restaurant pop(Nod** varf)
{
	if(*varf == NULL)
		return initRestaurant(NULL, 0, NULL);

	Restaurant r;
	r = (*varf)->info;
	Nod* temp = *varf;
	*varf = (*varf)->next;
	free(temp);

	return r;
}

void put(Nod** coada, Restaurant restaurant) {
	//coada reprezinta adresa primului nod din structura COADA
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = restaurant;
	nou->next = NULL;

	if (*coada == NULL) {
		*coada = nou;
	}
	else {
		Nod* copie = *coada;
		while (copie->next != NULL) {
			copie = copie->next;
		}
		copie->next = nou;
	}
}

void main() {
	Nod* stiva = NULL;
	Restaurant r1 = initRestaurant("Mitza Biciclista", 54, "romanesc");
	Restaurant r2 = initRestaurant("Socului", 34, "shaormerie");
	Restaurant r3 = initRestaurant("MC Romana", 82, "fast-food");

	push(&stiva, r1);
	push(&stiva, r2);
	push(&stiva, r3);

	Restaurant r4;
	printf("Traversare stiva:\n");
	while (stiva != NULL)
	{
		r4 = pop(&stiva);
		afisareRestaurant(r4);
		free(r4.nume);
		free(r4.domeniu);
	}

	Nod* coada = NULL;

	put(&coada, initRestaurant("Mitza Biciclista", 54, "romanesc"));
	put(&coada, initRestaurant("Socului", 34, "shaormerie"));
	put(&coada, initRestaurant("MC Romana", 82, "fast-food"));
	printf("Traversare coada:\n");
	while (coada != NULL)
	{
		r4 = pop(&coada);
		afisareRestaurant(r4);
		free(r4.nume);
		free(r4.domeniu);
	}
}
