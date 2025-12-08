/**
 * Program "dokladne pokrycie":
 *
 * - czyta ze standardowego wejscia filtr (pierwszy wiersz)
 *  oraz zestaw kolejnych wierszy danych,
 *
 *  - znajduje taki podzbior wczytanych wierszy, ktory
 *  po nalozeniu na siebie tworzy pelny ciag znakow
 *  (poprawne pokrycie), i drukuje je,
 *  z wylaczeniem miejsc, gdzie filtr ma znak '-'.
 *
 *  Rozwiazanie jest oparte na algorytmie z nawrotami (backtracking).
 *
 *  autor: Julia Dębicka
 */

#include <stdio.h>
#include <stdbool.h>

#define MARGINES_BLEDU 100
#define MAX_LICZBA_KOLUMN (300 + MARGINES_BLEDU)
#define MAX_LICZBA_WIERSZY (200 + MARGINES_BLEDU)

#define PODLOGA '_'
#define PLUS '+'
#define MINUS '-'
#define SPACJA ' '
#define ZNAK_NOWEJ_LINII '\n'
#define INDEKS_NIEUSTALONY (-1)

/**
 * Tablica dwuwymiarowa
 * i jej rzeczywiste wymiary.
 */
typedef struct {
    int tablica[MAX_LICZBA_WIERSZY][MAX_LICZBA_KOLUMN];
    int liczbaWierszy;
    int liczbaKolumn;
} tablica2D;


/** @brief Sprawdza, czy dany znak z filtru oznacza miejsce,
 * ktore nalezy drukowac.
 * @param znakZFiltru Obecnie sprawdzany znak filtru (PLUS lub MINUS).
 * @return Prawda, jezeli obecnym znakiem jest PLUS.
 */
bool czyDrukowacZnak(const int znakZFiltru) {
    return znakZFiltru == PLUS;
}


/**@brief Drukuje wyrazenie, uwzgledniajac filtr.
 * przy zalozeniu, ze wyrazenie jest poprawne
 * i, ze wypisujemy pusty wiersz, jezeli w filtrze sa same znaki MINUS.
 */
void drukujFiltrowanyWiersz(const int wiersz[MAX_LICZBA_KOLUMN], const int filtr[], const int dlugosc) {
    for (int i = 0; i < dlugosc; i++) {
        if (czyDrukowacZnak(filtr[i])) {
            putchar(wiersz[i]);
        }
    }
    putchar(ZNAK_NOWEJ_LINII);
}


/**@brief Sprawdza, czy dwa wyrazenia moga byc sklejone,
 * tj. czy nie pokrywaja sie dwa znaki niebedace znakiem PODLOGA.
 * @param dlugosc Rzeczywista dlugosc wiersza wejscia.
 * @return Czy wierszA i wierszB moga byc sklejone?
 */
bool czyWierszePasuja(const int wierszA[], const int wierszB[], const int dlugosc) {
    bool czyPasuja = true;
    int indeks = 0;

    while (indeks < dlugosc && czyPasuja) {
        if (wierszA[indeks] != PODLOGA && wierszB[indeks] != PODLOGA) {
            czyPasuja = false;
        }
        indeks++;
    }
    return czyPasuja;
}


/**@brief Skleja dwa wyrazenia,
 *  przy zalozeniu, ze oba wyrazenia do siebie pasuja (tj. moga byc sklejone).
 * @param zmienianyWiersz Wyrazenie, ktore modyfikujemy.
 * @param wiersz Wyrazenie, ktore doklejamy do zmienianyWiersz.
 * @param dlugosc Rzeczywista dlugosc wiersza wejscia.
 * @return Ilosc dodanych znakow to wyrazenia.
 */
int sklejWiersze(int zmienianyWiersz[], const int wiersz[], const int dlugosc) {
    int iloscDodanychZnakow = 0;
    int indeks = 0;

    while (indeks < dlugosc) {
        if (zmienianyWiersz[indeks] == PODLOGA && wiersz[indeks] != PODLOGA) {
            // Znalezlismy znak, ktorego mozna dokleic.
            zmienianyWiersz[indeks] = wiersz[indeks];
            iloscDodanychZnakow++;
        }
        indeks++;
    }
    return iloscDodanychZnakow;
}


/**@brief Cofa sklejenie dwoch wyrazen
 * przy zalozeniu, ze byly one wczesniej sklejone.
 * @param zmienianyWiersz Wyrazenie, ktore modyfikujemy.
 * @param wiersz Wyrazenie, z ktorym zmienianyWiersz byl wczesniej sklejony.
 * @param dlugosc Rzeczywista dlugosc wiersza wejscia.
 */
void cofnijSklejenie(int zmienianyWiersz[], const int wiersz[], const int dlugosc) {
    for (int i = 0; i < dlugosc; i++) {
        if (wiersz[i] != PODLOGA) {
            // Znalezlismy doklejony znak, pozbywamy sie go.
            zmienianyWiersz[i] = PODLOGA;
        }
    }
}


/**@brief Wyznacza wyrazenia dokladnego pokrycia na podstawie parametru wejscia
 * i drukuje wszystkie takie poprawne wyrazenia.
 * @param wyraz Obecny stan wyrazenia.
 * @param wejscie Sparsowane wejscie i jego rzeczywiste wymiary.
 * @param indeksOstatniego Indeks ostatniego sprawdzanego wiersza wejscia.
 * @param ileZnakow Ilosc znakow niebedacych znakiem PODLOGA w obecnym stanie wyrazenia,
 * potrzebne, aby wiedziec, kiedy mozna wydrukowac wyrazenie.
 * @param filtr Sparsowany filtr potrzebny do poprawnego drukowania poprawnego wyrazenia.
 */
void znajdzDokladnePokrycie(int wyraz[], tablica2D *wejscie,
                             const int indeksOstatniego, const int ileZnakow, const int filtr[]) {

    const int liczbaKolumn = wejscie->liczbaKolumn;
    const int liczbaWierszy = wejscie->liczbaWierszy;

    // Czy mamy poprawne (pelne, bez znaku PODLOGA) wyrazenie?
    if (ileZnakow >= liczbaKolumn){
        drukujFiltrowanyWiersz(wyraz, filtr, liczbaKolumn);
    }
    else {
        for (int i = indeksOstatniego + 1; i < liczbaWierszy; i++) {
            if (czyWierszePasuja(wyraz, wejscie->tablica[i], liczbaKolumn)) {
                // Dwa wyrazenia do siebie pasuja, wiec je sklejamy.
                const int iloscDodanychZnakow = sklejWiersze(wyraz, wejscie->tablica[i], liczbaKolumn);

                // Idziemy dalej rekurencyjnie.
                znajdzDokladnePokrycie(wyraz, wejscie, i, ileZnakow + iloscDodanychZnakow,  filtr);

                // Cofamy zmiane i idziemy dalej iteracyjnie.
                cofnijSklejenie(wyraz, wejscie->tablica[i], liczbaKolumn);
            }
        }
    }
}


/**
 * @param znak Obecnie sprawdzany znak wejscia.
 * @return Czy koniec standardowego wejscia?
 */
bool koniecWierszaWejscia(const int znak) {
    return (znak == ZNAK_NOWEJ_LINII || znak == EOF);
}


/**@brief Parsuje wiersz ze standardowego wiersza i zwraca jego dlugosc.
 * @param wiersz Funkcja zmienia jego wartosc na pierwszy sparsowany wiersz.
 * @return Dlugosc wczytanego wiersza.
 */
int parsujWiersz(int wiersz[]) {
    int znak = getchar();

    int licznik = 0;
    while (!koniecWierszaWejscia(znak) && licznik < MAX_LICZBA_KOLUMN) {
        wiersz[licznik] = znak;
        licznik++;
        znak = getchar();
    }
    return licznik;
}


/**@brief Wczytuje cale wejscie: najpierw filtr,
 * a nastepnie pozostale wiersze.
 * Ignoruje wiersze o dlugosci innej, niz dlugosc filtra,
 * (konczy wczytywanie po napotkaniu takiego wiersza).
 * @param filtr Funkcja zmienia jego wartosc na pierwszy sparsowany wiersz
 * @param wejscie Funkcja zmienia jej wartosc tablica na reszte sparsowanych wierszy
 * i zmienia jej wartosci liczbaWierszy i liczbaKolumn na odpowiednie liczby
 * wierszy i kolumn w parsowanym wejsciu.
 */
void parsujWejscie(int filtr[], tablica2D *wejscie) {
    const int dlugoscWiersza = parsujWiersz(filtr);  // Wczytujemy filtr oraz jego dlugosc.
    wejscie->liczbaKolumn = dlugoscWiersza; // Zapisujemy rzeczywista dlugosc wiersza wejscia.

    if (dlugoscWiersza > 0) {
        int indeksWiersza = 0;
        int tempDlugosc = dlugoscWiersza;

        while (indeksWiersza < MAX_LICZBA_WIERSZY && tempDlugosc == dlugoscWiersza) {
            tempDlugosc = parsujWiersz(wejscie->tablica[indeksWiersza]);

            // Jezeli dlugosc wczytanego wiersza jest rozny od
            // rzeczywistej dlugosci wiersza konczymy wczytywanie.
            if (tempDlugosc != 0) {
                indeksWiersza++;
            }
        }
        wejscie->liczbaWierszy = indeksWiersza; // Zapisujemy rzeczywista dlugosc kolumn wejscia.
    }
    else {
        wejscie->liczbaWierszy = 0; // Zapisujemy rzeczywista dlugosc kolumn wejscia.
    }
}


/**@brief Zmienia cala zawartosc tablicy jednowymiarowej na znak PODLOGA
 * @param tablica wszystkie wartosci zmienione na znak PODLOGA
 */
void zmienTabliceNaPusta(int tablica[]) {
    for (int i = 0; i < MAX_LICZBA_KOLUMN; i++) {
        tablica[i] = PODLOGA;
    }
}


/**@brief Zmienia cala zawartosc tablicy 2D na znak PODLOGA
 * @param tablica wszystkie wartosci zmienione na znak PODLOGA
 */
void zmienTablice2DNaPusta(tablica2D *tablica) {
    for (int i = 0; i < MAX_LICZBA_WIERSZY; i++) {
        for (int j = 0; j < MAX_LICZBA_KOLUMN; j++) {
            tablica->tablica[i][j] = PODLOGA;
        }
    }
}


/**@brief Glowna funkcja sterujaca programu.
 *  @details Deklaruje i inicjalizuje tablice filtr i wejscie
 *  i wywoluje na nich parsujWejscie,
 *  po czym wywoluje funkcje pomocnicza znajdzDokladnePokrycie.
 */
void dokladnePokrycie() {
    int filtr[MAX_LICZBA_KOLUMN] = {0};
    zmienTabliceNaPusta(filtr);

    static tablica2D wejscie;
    zmienTablice2DNaPusta(&wejscie);

    parsujWejscie(filtr, &wejscie);

    // Czy mozemy szukac dokladnego pokrycia?
    if (wejscie.liczbaKolumn > 0 && wejscie.liczbaKolumn < MAX_LICZBA_KOLUMN
        && wejscie.liczbaWierszy < MAX_LICZBA_WIERSZY) {

        int wyraz[MAX_LICZBA_KOLUMN];
        zmienTabliceNaPusta(wyraz);
        znajdzDokladnePokrycie(wyraz, &wejscie, INDEKS_NIEUSTALONY, 0,  filtr);
    }
}


int main(void) {
    dokladnePokrycie();
    return 0;
}