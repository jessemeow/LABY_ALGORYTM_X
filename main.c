#include <stdio.h>
#include <stdbool.h>

// usun komentarze "KOM"
// co jesli puste wejscie?

#define MARGINES_BLEDU 100 // KOM zmien te nazwe...
#define MAX_LICZBA_KOLUMN (300 + MARGINES_BLEDU)
#define MAX_LICZBA_WIERSZY (200 + MARGINES_BLEDU)
// KOM [MAX_DLUGOSC_WIERSZY, MAX_DLUGOSC_KOLUMN]
#define PODLOGA '_'
#define PLUS '+'
#define MINUS '-'
#define SPACJA ' '
#define ZNAK_NOWEJ_LINII '\n'
#define INDEKS_NIEUSTALONY (-1)

struct tablica2D {
    int tablica[MAX_LICZBA_WIERSZY][MAX_LICZBA_KOLUMN];
    int liczbaWierszy;
    int liczbaKolumn;
};


bool czyDrukowacZnak (const int znakZFiltru) {
    return znakZFiltru == PLUS;
}


void drukujFiltrowanyWiersz (const int wiersz[MAX_LICZBA_KOLUMN], const int filtr[], const int dlugosc) {
    for (int i = 0; i < dlugosc; i++) {
        if (czyDrukowacZnak(filtr[i])) {
            putchar(wiersz[i]);
        }
    }

    putchar(ZNAK_NOWEJ_LINII);
    // zakladamy, ze wypisujemy pusty wiersz //np sgdy sa ssame minusy w filtrzze lub dl = 0
}


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

// zwraca ilosc dodanych znakow
// KOM ale to jest brzydkie xddd
int sklejWiersze (int zmienianyWiersz[], const int wiersz[], const int dlugosc) {
    const bool czyPasuja = czyWierszePasuja(zmienianyWiersz, wiersz, dlugosc);
    int iloscDodanychZnakow = 0;

    if (czyPasuja) {
        int indeks = 0;
        while (indeks < dlugosc) {
            if (zmienianyWiersz[indeks] == PODLOGA && wiersz[indeks] != PODLOGA) {
                zmienianyWiersz[indeks] = wiersz[indeks];
                iloscDodanychZnakow++;
            }
            indeks++;
        }
    }
    return iloscDodanychZnakow;
}

// zal ze wczesniej wiersze pasowaly i byly sklejone
void cofnijSklejenie (int zmienianyWiersz[], const int wiersz[], const int dlugosc) {
    for (int i = 0; i < dlugosc; i++) {
        if (wiersz[i] != PODLOGA) {
            zmienianyWiersz[i] = PODLOGA;
        }
    }
}


// zal. ze dlugosc > 0
void znajdzDokladnePokrycie (int wyraz[], struct tablica2D *wejscie,
                             const int indeksOstatniego, const int ileZnakow, const int filtr[]) {

    const int liczbaKolumn = wejscie->liczbaKolumn;
    const int liczbaWierszy = wejscie->liczbaWierszy;

    if (ileZnakow >= liczbaKolumn){
        drukujFiltrowanyWiersz(wyraz, filtr, liczbaKolumn);
    }
    else {
        for (int i = indeksOstatniego; i < liczbaWierszy; i++) {
            if (czyWierszePasuja(wyraz, wejscie->tablica[i], liczbaKolumn)) {
                const int iloscDodanychZnakow = sklejWiersze(wyraz, wejscie->tablica[i], liczbaKolumn);
                znajdzDokladnePokrycie(wyraz, wejscie, i+1, ileZnakow + iloscDodanychZnakow,  filtr);
                cofnijSklejenie(wyraz, wejscie->tablica[i], liczbaKolumn);
            }
        }
    }
}


bool koniecWierszaWejscia (const int *znak) {
    return (*znak == ZNAK_NOWEJ_LINII || *znak == EOF);
}


/** Parsuje wiersz ze standardowego wiersza i zwraca jego dlugosc.
 *  Zmienia wartosc parametru wiersz[] na sparsowane wejscie
 *  i ustawia jego ostatni znak (po wierszu wejscia) na znak nowej
 */
int parsujWiersz (int wiersz[]) {
    int znak = getchar();

    int licznik = 0;
    while (!koniecWierszaWejscia(&znak) && licznik < MAX_LICZBA_KOLUMN) {
        wiersz[licznik] = znak;
        licznik++;
        znak = getchar();
    }

    return licznik;
}


//  instancje - instancje problemu dokładnego pokrycia
//zwraca dl
// zmienia param
void parsujWejscie (int filtr[], struct tablica2D *wejscie) {
    const int dlugoscWiersza = parsujWiersz(filtr);  // Wczytujemy filtr oraz jego dlugosc
    wejscie->liczbaKolumn = dlugoscWiersza;

    if (dlugoscWiersza > 0) {
        int indeksWiersza = 0;
        int tempDlugosc = dlugoscWiersza;

        while (indeksWiersza < MAX_LICZBA_WIERSZY && tempDlugosc == dlugoscWiersza) {
            tempDlugosc = parsujWiersz(wejscie->tablica[indeksWiersza]); // KOM co jak puste wejscie?

            if (tempDlugosc != 0) {
                indeksWiersza++;
            }
        }
        wejscie->liczbaWierszy = indeksWiersza;
    }
    else {
        wejscie->liczbaWierszy = 0;
    }
}


void zmienTabliceNaPusta (int tablica[]) {
    for (int i = 0; i < MAX_LICZBA_KOLUMN; i++) {
        tablica[i] = PODLOGA;
    }
}


void zmienTablice2DNaPusta (struct tablica2D *tablica2D) {
    for (int i = 0; i < MAX_LICZBA_WIERSZY; i++) {
        for (int j = 0; j < MAX_LICZBA_KOLUMN; j++) {
            tablica2D->tablica[i][j] = PODLOGA;
        }
    }
}

/** Glowna funkcja sterujaca programu.
 *
 */
void dokladnePokrycie () {
    int filtr[MAX_LICZBA_KOLUMN] = {0};
    zmienTabliceNaPusta(filtr);

    struct tablica2D wejscie;
    zmienTablice2DNaPusta(&wejscie); // KOM moze byc problem

    parsujWejscie(filtr, &wejscie);

    if (wejscie.liczbaKolumn > 0 && wejscie.liczbaKolumn < MAX_LICZBA_KOLUMN && wejscie.liczbaWierszy < MAX_LICZBA_WIERSZY) {
        // warunek zmien na funkcje
        int wyraz[MAX_LICZBA_KOLUMN];
        zmienTabliceNaPusta(wyraz);

        znajdzDokladnePokrycie(wyraz, &wejscie, 0, 0,  filtr);
    }
}


int main(void) {
    dokladnePokrycie();
    return 0;
}
