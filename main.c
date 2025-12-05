#include <stdio.h>
#include <stdbool.h>

// usun komentarze "KOM"
// co jesli puste wejscie?

#define BLAD 5 // KOM zmien te nazwe...
#define MAX_DLUGOSC_WIERSZY (300 + BLAD)
#define MAX_DLUGOSC_KOLUMN (200 + BLAD)
// KOM [MAX_DLUGOSC_WIERSZY, MAX_DLUGOSC_KOLUMN]
#define PODLOGA '_'
#define PLUS '+'
#define MINUS '-'
#define SPACJA ' '
#define ZNAK_NOWEJ_LINII '\n'


void znajdzDokladnePokrycie (int wyraz[], int tablica[MAX_DLUGOSC_KOLUMN][MAX_DLUGOSC_WIERSZY],
                             int ostatnioSprawdzanyWiersz, const int dlugoscWejscia) {

    while (ostatnioSprawdzanyWiersz < dlugoscWejscia) {

    }
}

bool koniecWierszaWejscia (const int *znak) {
    return (*znak == ZNAK_NOWEJ_LINII || *znak == EOF);
}

bool czyDrukowacZnak (const int znakZFiltru) {
    return znakZFiltru == PLUS;
}

void drukujFiltrowanaTablice (const int tablica[MAX_DLUGOSC_KOLUMN][MAX_DLUGOSC_KOLUMN], const int filtr[], const int dlugosc) {
    for (int i = 0; i < MAX_DLUGOSC_KOLUMN; i++) {
        for (int j = 0; j < dlugosc; j++) {
            const int znakFiltru = filtr[j];

            if (czyDrukowacZnak(znakFiltru)) {
                putchar(tablica[i][j]);

                if (j == dlugosc - 1) {
                    putchar(SPACJA); // KOM     co
                }
            }
        }
    }
}

/** Parsuje wiersz ze standardowego wiersza i zwraca jego dlugosc.
 *  Zmienia wartosc parametru wiersz[] na sparsowane wejscie
 *  i ustawia jego ostatni znak (po wierszu wejscia) na znak nowej
 */
int parsujWiersz (int wiersz[]) {
    int znak = getchar();

    int licznik = 0;
    while (!koniecWierszaWejscia(&znak) && licznik < MAX_DLUGOSC_KOLUMN) {
        wiersz[licznik] = znak;
        licznik++;
        znak = getchar();
    }
    wiersz[licznik] = ZNAK_NOWEJ_LINII;

    return licznik;
}


//  instancje - instancje problemu dokładnego pokrycia
void parsujWejscie (int filtr[], int instancje[MAX_DLUGOSC_KOLUMN][MAX_DLUGOSC_WIERSZY]) {
    const int dlugoscWiersza = parsujWiersz(filtr);  // Wczytujemy filtr oraz jego dlugosc

    if (dlugoscWiersza > 0) {
        int indeksWiersza = 0;

    }
}

/** Glowna funkcja sterujaca programu.
 *
 */
void dokladnePokrycie () {
    //int filtr[MAX_DLUGOSC_WIERSZY];
    //int wejscie[MAX_DLUGOSC_KOLUMN][MAX_DLUGOSC_WIERSZY];


}

int main(void) {
    printf("Hello, World!\n");
    return 0;
}
