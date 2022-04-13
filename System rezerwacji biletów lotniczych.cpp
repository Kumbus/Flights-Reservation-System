#include <iostream>
#include <fstream>
#include <vector>
#include<cstdlib>
#include<windows.h>
#include"Klasy.h"
#include"Funkcje.h"
using namespace std;

int main()
{
    vector<int>t;
    int cena = 0;

    vector<shared_ptr<Lotpdst>> dane;
    vector<shared_ptr<Lotpdst>> dobre;
    vector<int> miejsca;

    
    PobierzDane(dane);

    do
    {
        cout << "Witamy w systemie rezerewacji biletow lotniczych J&W" << endl << endl;
        Lotpdst lot;
        lot.getDane();

        if (!lot.Walidator())
        {
            system("cls");
            cout << "Podales nieprawidlowe dane - podaj jeszcze raz" << endl << endl;
            Sleep(1500);
            continue;
        }
        cout << endl << "Prosze podac typ pasazera(dorosly [1], mlodziez(12-17 lat) [2], dziecko(2-11 lat) [3], niemowle(0-1 lat) [4]" << endl;

        t=lot.WczytywanieWieku();

        cout << endl;

        dobre = lot.Szukaj(dane,miejsca);
        if (dobre.size() == 0)
        {
            cout << "Niestety lot ktorego szukasz nie istnieje lub nie ma w nim wystraczjaco duzo wolnych miejsc" << endl;
            Sleep(1543);
            continue;
        }
        int numer;
        bool ok = 0;

        bool powrot1 = false;
        do
        {
            int k = 0;
            do
            {
                Sleep(k);
                system("cls");
                cout << "Wybierz interesujacy cie lot poprzez wcisniecie numeru obok niego " << endl << endl;

                for (int i = 0; i < dobre.size(); i++)
                {
                    cout << i + 1 << ".";
                    dobre[i]->Wypisz();
                }
                cout << dobre.size() + 1 << ".Powrot do wpisywania danych lotu" << endl;

                cin >> numer;
                k = 1000;
            } while (!WpisywanieNumeru(numer, 1, dobre.size() + 1));
            if (numer == dobre.size() + 1)
            {
                powrot1 = true;
                break;
            }

            int numerklasy;
            bool powrot = false;
            do
            {
                do
                {
                    system("cls");
                    dobre[numer - 1]->Wypisz();
                    cout << endl << "Wybierz klase w jakiej chcesz podrozowac poprzez wcisniecie odpowiedniego numeru, " << dobre[numer - 1]->IleKlas() + 1<<" - powrot do wyboru lotu" << endl;
                    cin >> numerklasy;
                } while (!WpisywanieNumeru(numerklasy, 1, dobre[numer-1]->IleKlas()+1));
                if (numerklasy == dobre[numer - 1]->IleKlas() + 1)
                {
                    powrot = true;
                    break;
                }
                system("cls");
                dobre[numer - 1]->Wypisz();
            } while (!(dobre[numer-1]->WyborKlasy(t, numerklasy)));
            

                if (powrot)
                    continue;

                break;
            
        } while (1);
        if (powrot1)
            continue;

        vector<shared_ptr<Pasazer>> ludzie;
        system("cls");
        do
        {
            ludzie.clear();
            Pasazer::Zeruj();
            for (int i = 1; i <= lot.liczba_miejsc; i++)
            {
                shared_ptr<Pasazer> pasazer{ new Pasazer };
                do
                {
                    cout << "Podaj imie, nazwisko i pesel " << i << " pasazera" << endl;
                    pasazer->GetDane();

                } while (!pasazer->walidator());
                pasazer->SprawdzanieWieku();
                ludzie.push_back(pasazer);
            }

            system("cls");
        } while (!Pasazer::PorownanieWieku(t));

        Pasazer::Zeruj();
        shared_ptr<Glowny> pasazerprime{ new Glowny(*ludzie[0]) };

        do
        {
            cout << "Podaj e-mail i telefon " << endl;
            pasazerprime->GetDane();

        } while (!pasazerprime->walidator());

        int metoda;
        do
        {
            cout << endl << "Wybierz metode platnosci:" << endl << "1.Przelew" << endl << "2.BLIK" << endl << "3.Jesli nagle zorientowles sie ze nie jestes w stanie zapalcic " << t[t.size()-1] << " zl i chcesz wszystko anulowac" << endl;
            cin >> metoda;
        } while (!WpisywanieNumeru(metoda, 1, 3));

        if ((metoda == 2) && t[t.size()-1] <= 500)
        {
            pasazerprime->Blik();
        }
        else if (t[4] > 500 && metoda == 2)
        {
            cout << endl << "Blikiem mozna placic tylko do 500 zl wiec trzeba zaplacic tradycyjnie" << endl;
            pasazerprime->Przelew();
        }
        else if (metoda == 1)
            pasazerprime->Przelew();
        else
            continue;

        int decyzja;

        do
        {
            system("cls");
            cout << "Dziekujemy za skorzystanie z systemu rezerwacji biletow lotniczych J&W i zapraszamy ponownie" << endl << endl;
            cout << "Co chcesz zrobic teraz?" << endl << endl << "1.Zamawiam kolejne bilety" << endl << "2.Koncze rezerwacje" << endl;
            cin >> decyzja;
        } while (!WpisywanieNumeru(decyzja, 1, 2));

        for (int i = 0; i < ludzie.size(); i++)
        {
            ludzie[i]->DoPliku(pasazerprime->DajMail(),pasazerprime->DajTelefon(),dobre[numer-1]);
        }

        ofstream plz;
        plz.open("Loty.txt");
        for (int i = 0; i < dane.size(); i++)
        {
            dane[i]->ZaktualizowaneDoPliku(miejsca[numer-1],lot.liczba_miejsc,plz,i);
        }
        plz.close();
        if (decyzja == 1)
            continue;
        break;

        
    } while (1);
}

