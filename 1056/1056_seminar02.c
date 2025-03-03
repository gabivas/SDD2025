#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct Shaorma Shaorma;

struct Shaorma
{
	char* tip;
	float pret;
	int nrIngrediente;
};

int* citire_vector(int* dimensiune, FILE* fisier)
{
	fscanf(fisier, "%d", dimensiune);

	int* vector = (int*)malloc((*dimensiune) * sizeof(int));

	for (int i = 0; i < *dimensiune; i++)
	{
		fscanf(fisier, "%d", &vector[i]);
	}

	return vector;
}

void afisare_vector(int* vector, int dimensiune)
{
	printf("\n");
	for (int i = 0; i < dimensiune; i++)
	{
		printf("%d ", vector[i]);
	}
}

Shaorma citireShaorma(FILE* fileStream) {
	char buffer[10];
	Shaorma shaorma;
	fgets(buffer, 10, fileStream);

	char* tip = strtok(buffer, "\n");
	shaorma.tip = (char*)malloc(sizeof(char) * (strlen(tip) + 1));
	strcpy(shaorma.tip, tip);

	fgets(buffer, 4, fileStream);
	shaorma.pret = atof(buffer);

	fgets(buffer, 4, fileStream);
	shaorma.nrIngrediente = atoi(buffer);

	return shaorma;
}

void main() {
	FILE* fisier = fopen("fisier.txt", "r");
	int value1, value2;

	if (fisier != NULL) {
		fscanf(fisier, "%d", &value1);
		fscanf(fisier, "%d", &value2);
	}

	fclose(fisier);

	printf("\nValue1=%d, value2=%d", value1, value2);

	FILE* f = fopen("file.txt", "r");
	int dimensiune;
	int* vector=NULL;
	if (f != NULL)
	{
		vector = citire_vector(&dimensiune, f);
	}

	afisare_vector(vector, dimensiune);
	free(vector);
	fclose(f);

	FILE* fileStream = fopen("Shaorma.txt", "r");
	Shaorma shaorma = citireShaorma(fileStream);

	fclose(fileStream);

	printf("\nTipul ales este: %s", shaorma.tip);

	free(shaorma.tip);
}