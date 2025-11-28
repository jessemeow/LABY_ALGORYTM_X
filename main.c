#include <stdio.h>
#include <stdbool.h>

#define MAX_DLUGOSC_WIERSZY 300
#define MAX_DLUGOSC_KOLUMN 200
// [MAX_DLUGOSC_WIERSZY, MAX_DLUGOSC_KOLUMN]
#define PODLOGA '_'
#define PLUS '+'
#define MINUS '-'
#define SPACJA ' '
#define ZNAK_NOWEJ_LINII '\n'


bool koniecWierszaWejscia (const int *znak) {
    return (*znak == ZNAK_NOWEJ_LINII || *znak == EOF);
}

bool czyDrukowacZnak (const int *znakZFiltru) {
    return *znakZFiltru == PLUS;
}

void drukujFiltrowanaTablice (const int tablica[MAX_DLUGOSC_KOLUMN][MAX_DLUGOSC_KOLUMN], const int filtr[], const int *dlugosc) {
    for (int i = 0; i < MAX_DLUGOSC_KOLUMN; i++) {
        for (int j = 0; j < *dlugosc; j++) {
            int znakFiltru = filtr[j];

            if (czyDrukowacZnak(&znakFiltru)) {
                putchar(tablica[i][j]);

                if (j == *dlugosc - 1) {
                    putchar(SPACJA);
                }
            }
        }
    }
}

void dokladnePokrycie () {

}

/*
 * Zwroci falsz jezeli jest koniec wejscia,
 * zwroci prawde w przeciwnym wypadku.
 */
bool parsujWiersz (int wynik[]) {
    int znak = getchar();

    int i = 0;
    while (!koniecWierszaWejscia(&znak)) {
        wynik[i] = znak;
        znak = getchar();
    }

    if (znak == EOF) {
        return false;
    }

    return true;
}

/** Wczytuje filtr (pierwszy wiersz) ze standardowego wejscia i zwraca jego dlugosc
 *  Zmienia wartosc parametru filtr[] na sparsowany filtr.
 */
int parsujFiltr (int filtr[]) {
    int znak = getchar();

    int dlugosc = 0;
    while (!koniecWierszaWejscia(&znak)) {
        filtr[dlugosc] = znak;
        dlugosc++;
    }

    return dlugosc;
}

void parsujWejscie (int filtr[], int wejscie[MAX_DLUGOSC_KOLUMN][MAX_DLUGOSC_WIERSZY]) {
    const int dlugoscWiersza = parsujFiltr(filtr);  // Wczytujemy filtr

    if (dlugoscWiersza > 0) {
        int indeksWiersza = 0;
        int indeksKolumny = 0;

        wejscie[0][0] = indeksWiersza + indeksKolumny; // skasuj
    }
}

/** Glowna funkcja sterujaca programu.
 *
 */
void znajdzDokladnePokrycie () {
    //int filtr[MAX_DLUGOSC_WIERSZY];
    //int wejscie[MAX_DLUGOSC_KOLUMN][MAX_DLUGOSC_WIERSZY];


}

int main(void) {
    printf("Hello, World!\n");
    return 0;
}