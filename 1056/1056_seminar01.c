#include<stdio.h>
#include<malloc.h>

void interschimbare(int* nr1, int* nr2) {
	//dereferentiere
	int aux = *nr1;
	*nr1 = *nr2;
	*nr2 = aux;
}

void main() {
	int numarExamene = 5;
	float medieFinala = 9.5;
	char caracter = 'A';

	printf("\nNumar examene: %d, media finala este %.2f, caracterul este %c, codul Ascii pentru litera A este %d.", numarExamene, medieFinala, caracter, caracter);

	char nume[7];
	nume[0] = 65;
	nume[1] = 110;
	nume[2] = 100;
	nume[3] = 114;
	nume[4] = 101;
	nume[5] = 105;
	nume[6] = '\0';

	printf("\nNumele este %s.", nume);

	char* locatie = (char*)malloc(sizeof(char) * 5);
	strcpy(locatie, "Cluj");

	printf("\nLocatia este: %s.", locatie);

	int nr1 = 12, nr2 = 9;
	interschimbare(&nr1, &nr2);

	printf("\nNr1 = %d, nr2 = %d.", nr1, nr2);

	//dezalocare
	free(locatie);
}