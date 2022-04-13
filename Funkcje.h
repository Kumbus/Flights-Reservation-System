#ifndef FUNKCJE_H
#define FUNKCJE_H
#include<iostream>
#include<vector>
#include"Klasy.h"
using namespace std;

/**Funkcja pobiera dane z pliku tekstowego i tworzy na ich podstawie wskazniki na obiekty klasy Lotpdst i umieszcza te wskazniki w vectorze ktory bedzie je przechowywal
@param dane vector wskaznikow na obiekty klasy Lotpdst */
void PobierzDane(vector < shared_ptr<Lotpdst>>& dane);

/**Funkcja sprawdza czy podany przez uzytkownika numer jest z zakresu jaki jest dla niego dostepny
@param numer liczba podana przez uzytkownika
@param poczatek najmniejsza dostepna liczba
@param koniec najwieksza dostepna liczba 
@return true, jesli zostala podana poprawna liczba
		false, jesli zostala podana niepoprawna liczba */
bool WpisywanieNumeru(int numer, int poczatek, int koniec);

#endif

