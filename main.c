#include <stdio.h>
#include <stdbool.h>

// usun komentarze "KOM"
// co jesli puste wejscie?

#define BLAD 5 // KOM zmien te nazwe...
#define MAX_LICZBA_KOLUMN (300 + BLAD)
#define MAX_LICZBA_WIERSZY (200 + BLAD)
// KOM [MAX_DLUGOSC_WIERSZY, MAX_DLUGOSC_KOLUMN]
#define PODLOGA '_'
#define PLUS '+'
#define MINUS '-'
#define SPACJA ' '
#define ZNAK_NOWEJ_LINII '\n'
#define INDEKS_NIEUSTALONY (-1)


// KOM usun
void drukujWiersz (int w[], int n) {
    for (int i = 0; i < n; i++) {
        putchar(w[i]);
    }
    printf("\n");
}

bool czyDrukowacZnak (const int znakZFiltru) {
    return znakZFiltru == PLUS;
}


bool czyPelnyWyraz (const int wyraz[MAX_LICZBA_KOLUMN], const int dlugosc) {
    bool czyPelny = true;
    int indeks = 0;

    while (indeks < dlugosc && czyPelny) {
        if (wyraz[indeks] == PODLOGA) {
            czyPelny = false;
        }
        indeks++;
    }
    return czyPelny;
}


void drukujFiltrowanyWiersz (const int wiersz[MAX_LICZBA_KOLUMN], const int filtr[], const int dlugosc) {
    for (int i = 0; i < dlugosc; i++) {

        if (czyDrukowacZnak(filtr[i])) {
            putchar(wiersz[i]);

            if (i == dlugosc - 1) {
                putchar(SPACJA); // KOM     co
            }
        }
    }
}

//OK
bool czyWierszePasuja (const int A[], const int B[], const int dlugosc) {
    bool czyPasuja = true;
    int indeks = 0;

    while (indeks < dlugosc && czyPasuja) {
        if (A[indeks] != PODLOGA && B[indeks] != PODLOGA) {
            czyPasuja = false;
        }
        indeks++;
    }
    return czyPasuja;
}

// zwraca falsz jezeli wiersze do siebie pasuja
// KOM ale to jest brzydkie xddd
// OK
void sklejWiersze (int zmienianyWiersz[], const int wiersz[], const int dlugosc) {
    const bool czyPasuja = czyWierszePasuja(zmienianyWiersz, wiersz, dlugosc);

    printf("%d\n", czyPasuja);
    if (czyPasuja) {
        int indeks = 0;
        while (indeks < dlugosc) {
            if (zmienianyWiersz[indeks] == PODLOGA && wiersz[indeks] != PODLOGA) {
                zmienianyWiersz[indeks] = wiersz[indeks];
            }
            indeks++;
        }
    }
}

// zal ze wczesniej wiersze pasowaly i byly sklejone
// OK
void cofnijSklejenie (int zmienianyWiersz[], const int wiersz[], const int dlugosc) {
    for (int i = 0; i < dlugosc; i++) {
        if (wiersz[i] != PODLOGA) {
            zmienianyWiersz[i] = PODLOGA;
        }
    }
}


// zal. ze dlugosc > 0
void znajdzDokladnePokrycie (int wyraz[], int tablica[MAX_LICZBA_WIERSZY][MAX_LICZBA_KOLUMN],
                             int indeksOstatnioWpisanego, const int dlugosc, const int filtr[]) {

    if (indeksOstatnioWpisanego >= dlugosc && czyPelnyWyraz(wyraz, dlugosc)){
        drukujFiltrowanyWiersz(wyraz, filtr, dlugosc);
    }
    else {
        for (int i = indeksOstatnioWpisanego; i < dlugosc; i++) {
            if (czyWierszePasuja(wyraz, tablica[i], dlugosc)) {
                sklejWiersze(wyraz, tablica[i], dlugosc);
                znajdzDokladnePokrycie(wyraz, tablica, indeksOstatnioWpisanego+1, dlugosc, filtr);
                cofnijSklejenie(wyraz, tablica[i], dlugosc);
            }
        }
    }
}

// OK
bool koniecWierszaWejscia (const int *znak) {
    return (*znak == ZNAK_NOWEJ_LINII || *znak == EOF);
}


/** Parsuje wiersz ze standardowego wiersza i zwraca jego dlugosc.
 *  Zmienia wartosc parametru wiersz[] na sparsowane wejscie
 *  i ustawia jego ostatni znak (po wierszu wejscia) na znak nowej
 */
// OK
int parsujWiersz (int wiersz[]) {
    int znak = getchar();

    int licznik = 0;
    while (!koniecWierszaWejscia(&znak) && licznik < MAX_LICZBA_WIERSZY) {
        wiersz[licznik] = znak;
        licznik++;
        znak = getchar();
    }
    wiersz[licznik] = ZNAK_NOWEJ_LINII;

    return licznik;
}


//  instancje - instancje problemu dokładnego pokrycia
//zwraca dl
// zmienia param
// OK
int parsujWejscie (int filtr[], int instancje[MAX_LICZBA_WIERSZY][MAX_LICZBA_KOLUMN]) {
    const int dlugoscWiersza = parsujWiersz(filtr);  // Wczytujemy filtr oraz jego dlugosc

    if (dlugoscWiersza > 0) {
        int indeksWiersza = 0;
        int tempDlugoscWejscia = dlugoscWiersza;

        while (indeksWiersza < MAX_LICZBA_WIERSZY && tempDlugoscWejscia == dlugoscWiersza) {
            tempDlugoscWejscia = parsujWiersz(instancje[indeksWiersza]); // KOM co jak puste wejscie?
            indeksWiersza++;
        }
    }
    return dlugoscWiersza;
}

void zmienTabliceNaPusta (int tablica[]) {
    for (int i = 0; i < MAX_LICZBA_KOLUMN; i++) {
        tablica[i] = PODLOGA;
    }
}

/** Glowna funkcja sterujaca programu.
 *
 */
void dokladnePokrycie () {
    int filtr[MAX_LICZBA_KOLUMN];
    int wejscie[MAX_LICZBA_WIERSZY][MAX_LICZBA_KOLUMN];

    int dlugosc = parsujWejscie(filtr, wejscie);

    if (dlugosc > 0) {
        printf("dlugosc: %d\n", dlugosc);
        int wyraz[MAX_LICZBA_KOLUMN];
        zmienTabliceNaPusta(wyraz);

        znajdzDokladnePokrycie(wyraz, wejscie, 0, dlugosc, filtr);
    }

}


int main(void) {

    int dlugosc = 5;
    int filtr[5] = {'+', '-', '+', '+', '+'};
    int wejscie[2][5] = {{'a', 'b', 'c', 'a', 'd'}, {'_', '_', '_', 'a', '_'}};
    sklejWiersze(wejscie[0], wejscie[1], dlugosc);
    drukujWiersz(wejscie[0], dlugosc);
    cofnijSklejenie(wejscie[0], wejscie[1], dlugosc);
    drukujWiersz(wejscie[0], dlugosc);


    dokladnePokrycie();
    return 0;
}
