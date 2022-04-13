#include<iostream>
#include<vector>
#include<fstream>
#include<Windows.h>
#include"Funkcje.h"
#include"Klasy.h"
using namespace std;




void PobierzDane(vector < shared_ptr<Lotpdst>>& dane)
{
    ifstream plo;
    string s, s1, s2, s3, s4, s5, s6, s7;
    int l, l1;
    plo.open("Loty.txt");


    while (!plo.eof())
    {

        plo >> s >> s1 >> s2 >> l >> s3 >> l1 >> s4 >> s5 >> s6 >> s7;
        if (plo.fail())
            break;
        dane.push_back(shared_ptr<Lotpdst>(new Lotpdst(s, s1, s2, l, s3, l1, s4, s5, s6, s7)));

    }
    plo.close();
}

bool WpisywanieNumeru(int numer, int poczatek, int koniec) 
{
    cin.clear();
    cin.ignore(1000, '\n');
    if (numer<poczatek || numer >koniec)
    {
        cout << "Nie ma takiego numeru" << endl << endl;
        cout << "Mozesz wpisac numery: ";
        for (int i = poczatek; i <= koniec; i++)
            cout << i << " ";

        cout << endl;
        Sleep(750);
        return false;
    }
    return true;
}

