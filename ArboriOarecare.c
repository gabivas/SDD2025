#include <stdio.h>
#include <malloc.h>

typedef struct Nod Nod;

struct Nod {
    int info;
    struct Nod* primulCopil;
    struct Nod* urmatorulFrate;
};

struct Nod* creareNod(int info) {
    struct Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = info;
    nou->primulCopil = NULL;
    nou->urmatorulFrate = NULL;
    return nou;
}

void adaugaCopil(Nod* parinte, int info) {
    struct Nod* nou = creareNod(info);
    if (parinte->primulCopil == NULL) {
        parinte->primulCopil = nou;
    }
    else {
        struct Nod* copilCurent = parinte->primulCopil;
        while (copilCurent->urmatorulFrate != NULL) {
            copilCurent = copilCurent->urmatorulFrate;
        }
        copilCurent->urmatorulFrate = nou;
    }
}

void afisareArbore(Nod* radacina, int depth) {
    if (radacina == NULL) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%d\n", radacina->info);
    afisareArbore(radacina->primulCopil, depth + 1);
    afisareArbore(radacina->urmatorulFrate, depth);
}

void dezalocare(Nod* radacina) {
    if (radacina == NULL) {
        return;
    }
    dezalocare(radacina->primulCopil);
    dezalocare(radacina->urmatorulFrate);
    free(radacina);
    radacina = NULL;
}

int main() {
    Nod* radacina = creareNod(1);

    adaugaCopil(radacina, 2);
    adaugaCopil(radacina, 3);
    adaugaCopil(radacina, 4);

    adaugaCopil(radacina->primulCopil, 5);
    adaugaCopil(radacina->primulCopil, 6);

    adaugaCopil(radacina->primulCopil->urmatorulFrate, 7);

    adaugaCopil(radacina->primulCopil->urmatorulFrate->urmatorulFrate, 8);

    printf("Arbore oarecare:\n");
    afisareArbore(radacina, 0);

    dezalocare(radacina);

    return 0;
}
