#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

void interschimbare(int* numar1, int* numar2) {
	//dereferentiere
	int copie = *numar1;
	*numar1 = *numar2;
	*numar2 = copie;
}

void main() {
	int numarTeme = 5;
	float medieFinala = 10.0f;
	char litera = 'a';

	printf("\nNumar teme: %d, media finala: %.2f, litera este: %c, litera ca numar intreg: %d.", numarTeme, medieFinala, litera, litera);

	char sirCaractere[5];
	sirCaractere[0] = 97;
	sirCaractere[1] = 98;
	sirCaractere[2] = 99;
	sirCaractere[3] = 100;
	sirCaractere[4] = '\0';

	printf("\nSir= %s", sirCaractere);

	char* nume = (char*)malloc(sizeof(char)* 6);
	strcpy(nume, "Mihai");

	printf("\nNumele este %s.", nume);

	int numar1 = 7, numar2 = 9;
	interschimbare(&numar1, &numar2);

	printf("\n Numar1= %d, numar2= %d.", numar1, numar2);

	//dezalocare
	free(nume);
}