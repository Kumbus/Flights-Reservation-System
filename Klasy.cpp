#include"Klasy.h"
#include"Funkcje.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

//LOTPDST
Lotpdst::Lotpdst() :wylot(""), przylot(""), data(""), liczba_miejsc(0), linia("") {};
Lotpdst::Lotpdst(string wylot, string przylot, string data, int liczba_miejsc) : wylot(wylot), przylot(przylot), data(data), liczba_miejsc(liczba_miejsc) {};
Lotpdst::Lotpdst(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot)
    : wylot(wylot), przylot(przylot), data(data), liczba_miejsc(liczba_miejsc), linia(linia), cena(cena), godzinawylotu(godzinawylotu), godzinaprzylotu(godzinaprzylotu), nrlini(nrlini), samolot(samolot) {};

Lotpdst::Lotpdst(const Lotpdst& lp) : wylot(lp.wylot), przylot(lp.przylot), data(lp.data), liczba_miejsc(lp.liczba_miejsc), linia(lp.linia), cena(lp.cena), godzinawylotu(lp.godzinawylotu), godzinaprzylotu(lp.godzinaprzylotu), nrlini(lp.nrlini), samolot(lp.samolot) {};


void Lotpdst::Wypisz() {}

bool Lotpdst::operator==(Lotpdst& zmienna)
{
    if ((wylot == zmienna.wylot) && (przylot == zmienna.przylot) && (data == zmienna.data) && (zmienna.liczba_miejsc - liczba_miejsc >= 0))
        return true;
    else
        return false;
}

vector < shared_ptr<Lotpdst>> Lotpdst::Szukaj(vector < shared_ptr<Lotpdst>>& dane,vector<int> &miejsca)
{
    vector < shared_ptr<Lotpdst>> dobreloty;

    for (int i = 0; i < dane.size(); i++)
    {
        if (*this == *dane[i])
        {

            if ((*dane[i]).linia == "Lot")
            {
                dobreloty.push_back( unique_ptr<Lotpdst> { new Lot(*dane[i]) });
                miejsca.push_back(i);
            }

            if ((*dane[i]).linia == "Emirates")
            {
                dobreloty.push_back(unique_ptr<Lotpdst> { new Emirates(*dane[i]) });
                miejsca.push_back(i);
            }
            if ((*dane[i]).linia == "Lufthansa")
            {
                dobreloty.push_back(unique_ptr<Lotpdst> { new Lufthansa(*dane[i]) });
                miejsca.push_back(i);
            }
            if ((*dane[i]).linia == "RyanAir")
            {
                dobreloty.push_back(unique_ptr<Lotpdst> { new RyanAir(*dane[i]) });
                miejsca.push_back(i);
            }
        }
    }


    return dobreloty;
}

void Lotpdst::getDane()
{
    cout << "Prosze podac miejsce wylotu:  ";
    cin >> wylot;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << endl << "Prosze podac cel podrozy:  ";
    cin >> przylot;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << endl << "Prosze podac date (dd-mm-rrrr):  ";
    cin >> data;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << endl << "Prosze podac liczbe biletow:  ";
    cin >> liczba_miejsc;
    cin.clear();
    cin.ignore(1000, '\n');
}

vector<int> Lotpdst::WczytywanieWieku()
{
    int wiek;
    vector<int> t;
    for (int i = 0; i < 4; i++)
        t.push_back(0);
    bool ok = false;

    for (int i = 1; i <= liczba_miejsc; i++)
    {
        do
        {
            cout << "Pasazer " << i << " : ";
            cin >> wiek;
            if (!WpisywanieNumeru(wiek, 1, 4))
                continue;
            else
            {
                t[wiek - 1]++;
                break;
            }
        } while (1);
    }
    return t;
}

bool Lotpdst::Walidator()
{
    for (int i = 0; i < wylot.length(); i++)
        if ((wylot[i] < 65 || wylot[i]>90) && (wylot[i] < 97 || wylot[i]>122))
            return false;

    for (int i = 0; i < przylot.length(); i++)
        if ((przylot[i] < 65 || przylot[i]>90) && (przylot[i] < 97 || przylot[i]>122))
            return false;

    if (data.length() != 10)
        return false;
    else
    {
        if (data[0] < 48 || data[0]>51)//pierwsza cyfra dnia
            return false;
        if (data[3] < 48 || data[3]>49)//pierwsaz cyfra miesiaca
            return false;
        if (data[1] < 48 || data[1]>57)//druga cyfra dnia
            return false;
        if (data[4] < 48 || data[4]>57)//druga cyfra miesiaca
            return false;
        if (data[3] == '0' && data[4] == '0')//00 w miesiacu
            return false;
        if (data[0] == '0' && data[1] == '0')//00 w dniu
            return false;
        if (data[0] == '3' && (data[1] < 48 || data[1]>49))//na przyklad 35 dzien miesiaca
            return false;
        if (data[0] == '3' && data[3] == '0' && data[4] == '2')//na przyklad 30 lutego
            return false;
        if (data[0] == '3' && data[1] == '1' && ((data[3] == '0' && (data[4] == '4' || data[4] == '6' || data[4] == '9')) || (data[3] == '1' && data[4] == '1')))//na przyklad 31 kwietnia
            return false;
        if (data[6] != '2' || data[7] != '0' || data[8] != '2')//cos innego niz 202x w roku
            return false;
        if (data[9] < 49 || data[9]>57)//ostatnia cyfra roku
            return false;
        if (data[2] != '-' || data[5] != '-')//myslniki
            return false;
    }

    string s = to_string(liczba_miejsc);
    for (int i = 0; i < s.length(); i++)
        if (s[i] < 48 || s[i]>57)
            return false;

    return true;
}


bool Lotpdst::WyborKlasy(vector<int> &t, int numerklasy)
{
    return 0;
}

int Lotpdst::IleKlas() { return 0; }

string Lotpdst::getKLase() { return(" "); }

void Lotpdst::ZaktualizowaneDoPliku(int miejsce, int liczbapasazerow,ofstream &plz,int licznik)
{
    if (miejsce == licznik)
    {
        plz << wylot << " " << przylot << " " << data << " " << liczba_miejsc - liczbapasazerow << " " << linia << " " << cena << " " << godzinawylotu << " " << godzinaprzylotu << " " << nrlini << " " << samolot << endl;
    }
    else
        plz << wylot << " " << przylot << " " << data << " " << liczba_miejsc << " " << linia << " " << cena << " " << godzinawylotu << " " << godzinaprzylotu << " " << nrlini << " " << samolot << endl;
}


//------------------------------------LOT--------------------------------------------
Lot::Lot(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot)
    : Lotpdst(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), klasa("ekonomiczna") {};

Lot::Lot(const Lotpdst& l) :Lotpdst(l), klasa("ekonomiczna") {};

void Lot::Wypisz()
{
    cout << wylot << "-------->" << przylot << "     " << linia << "  " << cena << " zl" << endl << endl;
    cout << "Wylot: " << godzinawylotu << "  Przylot: " << godzinaprzylotu << endl;
    cout << "Numer lotu  " << nrlini << "  Model samolotu  " << samolot << endl << endl;

    cout << "Dostepne klasy podrozy: " << endl << "1.Ekonomiczna" << endl << "2.Premium" << endl << "3.Biznesowa" << endl << endl;
}

bool Lot::WyborKlasy(vector<int> &t,int numerklasy)
{
    int ok2;
    vector<unique_ptr<Lot>> klasa;

        if (numerklasy == 1)
            klasa.push_back(unique_ptr<Lot> { new Ekonomiczna(*this, t) });
        else if (numerklasy == 2)
            klasa.push_back(unique_ptr<Lot> { new Premium(*this, t) });
        else  if (numerklasy == 3)
            klasa.push_back(unique_ptr<Lot> { new Biznesowa(*this, t) });

        klasa[0]->Wypisz();
        t.push_back(klasa[0]->WyliczCene());
        do
        {
            cin >> ok2;
        } while (!WpisywanieNumeru(ok2, 1, 2));


        if (ok2 == 1)
            return true;
        else
            return false;
}

int Lot::IleKlas() { return ileklas; }

int Lot::WyliczCene() { return 0; }

string Lot::getKLase() { return klasa; }

//EKONOMICZNA
Ekonomiczna::Ekonomiczna(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t)
    : Lot(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), t(t) {};

Ekonomiczna::Ekonomiczna(const Lot& e, vector<int> &t) : Lot(e), t(t) {};

void Ekonomiczna::Wypisz()
{
    cout << "                                       KLASA EKONOMICZNA       " << endl << endl;
    cout << "Wygodne fotele, dostep do cyfrowej prasy oraz wliczone w cene biletu przekaski i napoje." << endl;
    cout << "Lot Economy Class to komfortowa podroz dostepna dla kazdego." << endl << endl;
    cout << "Dostepne udogodnienia:" << endl << "- Przekaski i napoje" << endl << "- E-prasa (1 darmowe pobranie)" << endl << "- Bagaz podreczny (1 x 8 kg)" << endl;
    cout << "- Bagaz rejestrowany (1 x 23 kg)" << endl << "- Bagaz rejestrowany dla niemowlecia (1 x 23 kg)" << endl << endl;
    cout << "Koszt za wszystkich podrozujacych to: " << WyliczCene() << " zl" << endl << endl;
    cout << "Jesli chcesz wybrac ta opcje podrozy nacisnij 1, jesli nie nacisnij 2" << endl;

}

int Ekonomiczna::WyliczCene()
{
    return(1.25 * cena * (t[0] + 0.75 * t[1] + 0.75 * t[2] + 0.1 * t[3]));
}

//PREMIUM
Premium::Premium(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t)
    : Lot(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), t(t) {};

Premium::Premium(const Lot& p, vector<int>& t) : Lot(p), t(t) {};

void Premium::Wypisz()
{
    cout << "                  KLASA PREMIUM        " << endl << endl;
    cout << "Omin kolejki na lotnisku i ciesz sie wyzszym standardem podrozy." << endl;
    cout << "Na pokladzie czeka na Ciebie specjalne menu Premium z bogata oferta napojow alkoholowych oraz komfortowe fotele w kameralnej kabinie." << endl;
    cout << "LOT Premium to wyjatkowy standard podrozy, na ktory mozesz sobie pozwolic!" << endl << endl;
    cout << "Dostepne udogodnienia:" << endl << "- Posilek premium" << endl << "- Priorytetowe wejscie na poklad" << endl << "- E-prasa (2 darmowe pobrania)" << endl;
    cout << "- Bagaz podreczny (1 x 8 kg)" << endl << "- Bagaz rejestrowany (2 x 23 kg)" << endl << "- Bagaz rejestrowany dla niemowlecia (1 x 23 kg)" << endl << endl;
    cout << "Koszt za wszystkich podrozujacych to: " << WyliczCene() << " zl" << endl << endl;
    cout << "Jesli chcesz wybrac ta opcje podrozy nacisnij 1, jesli nie nacisnij 2" << endl;
}
int Premium::WyliczCene()
{
    return(3.88 * cena * (t[0] + 0.75 * t[1] + 0.75 * t[2] + 0.1 * t[3]));
}

//BIZNESOWA
Biznesowa::Biznesowa(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t)
    : Lot(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), t(t) {};

Biznesowa::Biznesowa(const Lot& b, vector<int>& t) : Lot(b), t(t) {};

void Biznesowa::Wypisz()
{
    cout << "                       KLASA BIZNESOWA           " << endl << endl;
    cout << "Maksimum komfortu i goscinnosci – taka jest nasza LOT Business Class." << endl;
    cout << "Wyjatkowe menu, fotele w kameralnej kabinie, wolne miejsce obok oraz wyjatkowy serwis pokladowy zapewnia maksymalna przestrzen i komfort podczas podrozy." << endl << endl;
    cout << "Dostepne udogodnienia:" << endl << "- Posilek z menu Business" << endl << "- Wolny fotel obok" << endl << "- Wstep do saloniku biznesowego" << endl << "Priorytetowe wejscie na poklad" << endl;
    cout << "- E-prasa(3 darmowe pobrania)" << endl << "- Bagaz podreczny (2 x 9 kg)" << endl << "- Bagaz rejestrowany (2 x 32 kg)" << endl << "- Bagaz rejestrowany dla niemowlecia (1 x 23 kg)" << endl << endl;
    cout << "Koszt za wszystkich podrozujacych to: " << WyliczCene() << " zl" << endl << endl;
    cout << "Jesli chcesz wybrac ta opcje podrozy nacisnij 1, jesli nie nacisnij 2" << endl;
}
int Biznesowa::WyliczCene()
{
    return(4.9 * cena * (t[0] + 0.75 * t[1] + 0.75 * t[2] + 0.1 * t[3]));
}

//--------------------------------------------LUFTHANSA------------------------------------------------------------------

Lufthansa::Lufthansa(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot)
    : Lotpdst(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), klasa("ekonomic") {};

Lufthansa::Lufthansa(const Lotpdst& l) :Lotpdst(l), klasa("ekonomic") {};

void Lufthansa::Wypisz()
{
    cout << wylot << "-------->" << przylot << "     " << linia << "  " << cena << " zl" << endl << endl;
    cout << "Wylot: " << godzinawylotu << "  Przylot: " << godzinaprzylotu << endl;
    cout << "Numer lotu  " << nrlini << "  Model samolotu  " << samolot << endl << endl;

    cout << "Dostepne klasy podrozy: " << endl << "1.Ekonomiczna" << endl << "2.Biznesowa" << endl << endl;
}

bool Lufthansa::WyborKlasy(vector<int>& t, int numerklasy)
{
    int ok2;
    vector<unique_ptr<Lufthansa>> klasa;

    if (numerklasy == 1)
        klasa.push_back(unique_ptr<Lufthansa> { new Ekonomic(*this, t) });
    else if (numerklasy == 2)
        klasa.push_back(unique_ptr<Lufthansa> { new Biznes(*this, t) });

    klasa[0]->Wypisz();
    t.push_back(klasa[0]->WyliczCene());
    do
    {
        cin >> ok2;
    } while (!WpisywanieNumeru(ok2, 1, 2));

    if (ok2 == 1)
        return true;
    else
        return false;
}

string Lufthansa::getKLase() { return klasa; }

int Lufthansa::IleKlas() { return ileklas; }

int Lufthansa::WyliczCene() { return 0; }

//EKONOMICZNA Lufthansa
Ekonomic::Ekonomic(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t)
    : Lufthansa(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), t(t) {};

Ekonomic::Ekonomic(const Lufthansa& e, vector<int>& t) : Lufthansa(e), t(t) {};

void Ekonomic::Wypisz()
{
    cout << "                 KLASA EKONOMICZNA       " << endl << endl;
    cout << "Klasa Ekonomiczna zapewnia wysoki komfort. Dzieki temu mozesz cieszyc sie wygodna podroza w wybranym kierunku," << endl;
    cout << "a zaraz po przyjezdzie mozesz rozpoczac zwiedzanie lub udac sie na spotkanie biznesowe." << endl << endl;
    cout << "Dostepne udogodnienia: " << endl << "- Przekaski i napoje za oplata" << endl << "- Priorytetowy boarding" << "- 1 bagaz do 23 kg" << endl << "- 1 bagaz podreczny do 8 kg"  << endl << endl;
    cout << "Koszt za wszystkich podrozujacych to: " << WyliczCene() << " zl" << endl << endl;
    cout << "Jesli chcesz wybrac ta opcje podrozy nacisnij 1, jesli nie nacisnij 2" << endl;

}

int Ekonomic::WyliczCene()
{
    return(1.16 * cena * (t[0] + 0.75 * t[1] + 0.75 * t[2] + 0 * t[3]));
}

//BIZNESOWA Lufthansa
Biznes::Biznes(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t)
    : Lufthansa(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), t(t) {};

Biznes::Biznes(const Lufthansa& b, vector<int>& t) : Lufthansa(b), t(t) {};

void Biznes::Wypisz()
{
    cout << "                       KLASA BIZNESOWA           " << endl << endl;
    cout << "Rozkoszuj sie komfortem i prywatnoscia w Klasie Biznes Lufthansy, a na miejsce dotrzesz wypoczety i zrelaksowany. Gdziekolwiek podrozujesz, podrozuj w komfortowych warunkach Klasa Biznes Lufthansy." << endl;
    cout << "Mozliwosc korzystania z salonikow na lotnisku, priorytetowy boarding, wiekszy limit bezplatnego bagazu i wyjatkowe dania – to wszystko oferujemy naszym pasazerom Klasy Biznes." << endl << endl;
    cout << "Dostepne udogodnienia:" << endl << "- Priorytetowy boarding" << endl << "- Magazyny cyfrowe" << endl << "- Mozliwosc korzystania z poczekalni" << endl << "- Przejscie priorytetowe" << endl;
    cout << "- Wolne miejsce w srodku" << endl << "- 2 bagaze, kazdy do 23 kg" << endl << "- 2 bagaze podreczne do 8 kg" << endl << "- Pelny posilek" << endl << endl;
    cout << "Koszt za wszystkich podrozujacych to: " << WyliczCene() << " zl" << endl << endl;
    cout << "Jesli chcesz wybrac ta opcje podrozy nacisnij 1, jesli nie nacisnij 2" << endl;
}
int Biznes::WyliczCene()
{
    return(2.04 * cena * (t[0] + 0.75 * t[1] + 0.75 * t[2] + 0 * t[3]));
}

//--------------------------------EMIRATES---------------------------------------

Emirates::Emirates(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot)
    : Lotpdst(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), klasa("ekonomiczna") {};

Emirates::Emirates(const Lotpdst& l) :Lotpdst(l), klasa("ekonomiczna") {};

void Emirates::Wypisz()
{
    cout << wylot << "-------->" << przylot << "     " << linia << "  " << cena << " zl" << endl << endl;
    cout << "Wylot: " << godzinawylotu << "  Przylot: " << godzinaprzylotu << endl;
    cout << "Numer lotu  " << nrlini << "  Model samolotu  " << samolot << endl << endl;

    cout << "Dostepne klasy podrozy: " << endl << "1.Ekonomiczna" << endl << "2.Biznesowa" << endl << "3.Pierwsza" << endl << endl;
}

bool Emirates::WyborKlasy(vector<int>& t, int numerklasy)
{
    int ok2;
    vector<unique_ptr<Emirates>> klasa;

    if (numerklasy == 1)
        klasa.push_back(unique_ptr<Emirates> { new Economy(*this, t) });
    else if (numerklasy == 2)
        klasa.push_back(unique_ptr<Emirates> { new Business(*this, t) });
    else  if (numerklasy == 3)
        klasa.push_back(unique_ptr<Emirates> { new First(*this, t) });

    klasa[0]->Wypisz();
    t.push_back(klasa[0]->WyliczCene());
    do
    {
        cin >> ok2;
    } while (!WpisywanieNumeru(ok2, 1, 2));

    if (ok2 == 1)
        return true;
    else
        return false;
}

string Emirates::getKLase() { return klasa; }

int Emirates::IleKlas() { return ileklas; }

int Emirates::WyliczCene() { return 0; }

//EKONOMICZNA emirates
Economy::Economy(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t)
    : Emirates(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), t(t) {};

Economy::Economy(const Emirates& e, vector<int>& t) : Emirates(e), t(t) {};

void Economy::Wypisz()
{
    cout << "                 KLASA EKONOMICZNA       " << endl << endl;
    cout << "Klasa ekonomiczna, ktora sprawia wrazenie wyzszej klasy lotu" << endl;
    cout << "W klasie ekonomicznej Emirates mozesz oczekiwac wiecej dzieki tysiacom kanalow, polaczeniu Wi-Fi na pokladzie i daniom kuchni regionalnej." << endl;
    cout << "Wybierz regionalne dania z pokladowego menu i delektuj sie potrawami, ktore zabiora Cie w podroz po swiecie. Ogladaj komedie, thrillery i romanse na pokladzie." << endl;
    cout << "Wybieraj sposrod najnowszych filmow i seriali. Dobierz do posilku ktorys z darmowych napojow. Odkryj ponad 4 500 kanalow." << endl;
    cout << "Pozwol, aby nasz system rozrywki pokladowej zabral Cie w nowe miejsca." << endl << endl;
    cout << "Dostepne udogodnienia:" << endl << "- Bagaz 1 x 35 kg" << endl << "- Bagaz podreczny 1 x 7 kg" << endl << endl;
    cout << "Koszt za wszystkich podrozujacych to: " << WyliczCene() << " zl" << endl << endl;
    cout << "Jesli chcesz wybrac ta opcje podrozy nacisnij 1, jesli nie nacisnij 2" << endl;

}

int Economy::WyliczCene()
{

    return(1.44 * cena * (t[0] + 0.9 * t[1] + 0.75 * t[2] + 0.1 * t[3]));
}

//Biznesowa Emirates
Business::Business(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t)
    : Emirates(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), t(t) {};

Business::Business(const Emirates& b, vector<int>& t) : Emirates(b), t(t) {};

void Business::Wypisz()
{
    cout << "                  KLASA BIZNESOWA        " << endl << endl;
    cout << "Witamy w swiecie klasy biznes" << endl;
    cout << "Fotel, ktory plynnie rozklada sie w plaskie ³ozko z miekkim, wygodnym materacem i przytulnym kocem. Slodkich snow! Po³acz interesy i przyjemnosci w naszej klasie biznes." << endl;
    cout << "Wlacz sie do rozmowy w naszym nowym saloniku pokladowym. Poznawaj ciekawych ludzi, delektujac siê przekaskami." << endl;
    cout << "Wybieraj z karty wykwintnych regionalnych dan i delektuj sie potrawami, ktore zabiora Cie w podroz po swiecie." << endl << endl;
    cout << "Dostepne udogodnienia:" << endl << "- Bagaz 1 x 40 kg" << endl << "- Bagaz podreczny 2 x 7 kg" << endl << "- Prywatny kierowca" << endl << "- Poczekalnia" << endl << endl;
    cout << "Koszt za wszystkich podrozujacych to: " << WyliczCene() << " zl" << endl << endl;
    cout << "Jesli chcesz wybrac ta opcje podrozy nacisnij 1, jesli nie nacisnij 2" << endl;
}
int Business::WyliczCene()
{
    return(3.36 * cena * (t[0] + 0.9 * t[1] + 0.75 * t[2] + 0.1 * t[3]));
}

//Pierwsza emirates
First::First(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t)
    : Emirates(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), t(t) {};

First::First(const Emirates& f, vector<int>& t) : Emirates(f), t(t) {};

void First::Wypisz()
{
    cout << "                       PIERWSZA KLASA           " << endl << endl;
    cout << "Lataj we wlasnym stylu w pierwszej klasie" << endl; 
    cout << "Zasun drzwi, przygas swiatlo i zrelaksuj sie w prywatnym kinie. Przeksztalc swoj fotel w calkowicie plaskie lozko i popros personel o przygotowanie poscieli, aby moc sie wygodnie wyspac." << endl;
    cout << "Od wykwintnych dan a la carte po smaczne przekaski... Odkryj nasza spersonalizowana oferte gastronomiczna. Odzyskaj energie w spa z prysznicem na pokladzie." << endl;
    cout << "Skorzystaj z naszych ekskluzywnych zestawow kosmetykow Emirates Private Collection Bvlgari." << endl << endl;
    cout << "Dosepne udogodnienia:" << endl << "- Bagaz 1 x 50 kg" << endl << "- Bagaz podreczny 2 x 7 kg" << endl << "- Prywatny kierowca" << endl << "- Poczekalnia" << endl << endl;
    cout << "Koszt za wszystkich podrozujacych to: " << WyliczCene() << " zl" << endl << endl;
    cout << "Jesli chcesz wybrac ta opcje podrozy nacisnij 1, jesli nie nacisnij 2" << endl;
}
int First::WyliczCene()
{
    return(4.99 * cena * (t[0] + 0.9 * t[1] + 0.75 * t[2] + 0.1 * t[3]));
    
}

//---------------------------------RyanAir-----------------------------------
RyanAir::RyanAir(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot)
    : Lotpdst(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), klasa("ekonomic") {};

RyanAir::RyanAir(const Lotpdst& l) :Lotpdst(l), klasa("ekonomic") {};

void RyanAir::Wypisz()
{
    cout << wylot << "-------->" << przylot << "     " << linia << "  " << cena << " zl" << endl << endl;
    cout << "Wylot: " << godzinawylotu << "  Przylot: " << godzinaprzylotu << endl;
    cout << "Numer lotu  " << nrlini << "  Model samolotu  " << samolot << endl << endl;

    cout << "Dostepne klasy podrozy: " << endl << "1.Regular" << endl << "2.Plus" << endl << endl;
}

bool RyanAir::WyborKlasy(vector<int>& t, int numerklasy)
{
    int ok2;
    vector<unique_ptr<RyanAir>> klasa;

    if (numerklasy == 1)
        klasa.push_back(unique_ptr<RyanAir> { new Regular(*this, t) });
    else if (numerklasy == 2)
        klasa.push_back(unique_ptr<RyanAir> { new Plus(*this, t) });

    klasa[0]->Wypisz();
    t.push_back(klasa[0]->WyliczCene());
    do
    {
        cin >> ok2;
    } while (!WpisywanieNumeru(ok2, 1, 2));

    if (ok2 == 1)
        return true;
    else
        return false;
}
string RyanAir::getKLase() { return klasa; }

int RyanAir::IleKlas() { return ileklas; }

int RyanAir::WyliczCene() { return 0; }

//Regular RyanAir
Regular::Regular(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t)
    : RyanAir(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), t(t) {};

Regular::Regular(const RyanAir& r, vector<int>& t) : RyanAir(r), t(t) {};

void Regular::Wypisz()
{
    cout << "                 KLASA REGULAR       " << endl << endl;
    cout << "Taryfa Regular to idealne rozwiazanie dla wszystkich podrozujacych z punktu A do punktu B na jednej z 1800 tras pomiedzy 33 krajami." << endl;
    cout << "Ryanair gwarantuje najwieksza siatke polaczen. Dodawaj dodatkowe uslugi do standardowej ceny." << endl << endl;
    cout << "Dostepne udogodnienia:" << endl << "- Pierwszenstwo wejscia" << endl << "- Bagaz kabinowy 10 kg" << endl << "- 1 mala torba podreczna" << endl << endl;
    cout << "Koszt za wszystkich podrozujacych to: " << WyliczCene() << " zl" << endl << endl;
    cout << "Jesli chcesz wybrac ta opcje podrozy nacisnij 1, jesli nie nacisnij 2" << endl;

}

int Regular::WyliczCene()
{
   return(1.34 * cena * (t[0] + t[1] + 0.75 * t[2]) + t[3] * 84);
}

//Plus Lufthansa
Plus::Plus(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t)
    : RyanAir(wylot, przylot, data, liczba_miejsc, linia, cena, godzinawylotu, godzinaprzylotu, nrlini, samolot), t(t) {};

Plus::Plus(const RyanAir& p, vector<int>& t) : RyanAir(p), t(t) {};

void Plus::Wypisz()
{
    cout << "                       KLASA PLUS           " << endl << endl;
    cout << "Plus to idealne rozwiazanie dla pasazerow podrozujacych sluzbowo." << endl;
    cout << "Taryfa obejmuje elastycznosc przy zmianie daty podrozy, pierwszenstwo wejscia na poklad, przydzielone miejsce, fast track oraz mozliwosc odprawy na lotnisku bezplatnie." << endl << endl;
    cout << "Dostepne udogodnienia:" << endl << "- Pierwszenstwo wejscia" << endl << "- Bagaz kabinowy 10 kg" << endl << "- 1 mala torba podreczna" << endl;
    cout << "- Ekspresowa kontrola bezpieczenstwa dzieki opcji Fast Track" << endl << "- Bezplatna odprawa na lotnisku" << endl << endl;
    cout << "Koszt za wszystkich podrozujacych to: " << WyliczCene() << " zl" << endl << endl;
    cout << "Jesli chcesz wybrac ta opcje podrozy nacisnij 1, jesli nie nacisnij 2" << endl;
}
int Plus::WyliczCene()
{
    return(2.16 * cena * (t[0] + t[1] + 0.75 * t[2]) + t[3] * 84);
}



Pasazer::Pasazer() {};
Pasazer::Pasazer(const Pasazer& p) :imie(p.imie), nazwisko(p.nazwisko), pesel(p.pesel), rodzaj(p.rodzaj){};

void Pasazer::GetDane()
{
    cout << "Imie: ";
    cin >> imie;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << endl << "Nazwisko: ";
    cin >> nazwisko;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << endl << "Pesel: ";
    cin >> pesel;
    cin.clear();
    cin.ignore(1000, '\n');

}

bool Pasazer::walidator()
{
    for (int i = 0; i < imie.length(); i++)
        if ((imie[i] < 65 || imie[i]>90) && (imie[i] < 97 || imie[i]>122))
        {
            cout << "Imie jest nieprawodlowe" << endl;
            return false;
        }
    for (int i = 0; i < nazwisko.length(); i++)
        if ((nazwisko[i] < 65 || nazwisko[i]>90) && (nazwisko[i] < 97 || nazwisko[i]>122))
        {
            cout << "Nazwisko jest nieprawidlowe" << endl;
            return false;
        }
    int t[10] = { 1,3,7,9,1,3,7,9,1,3 };
    if (pesel.length() != 11)
    {
        cout << "Pesel ma nieprawidlowa dlugosc" << endl;
        return false;
    }
    for (int i = 0; i < 11; i++)
        if (pesel[i] > 57 || pesel[i] < 48)
        {
            cout << "Pesel nie sklada sie z samych cyfr" << endl;
            return false;
        }
    int suma = 0;
    for (int i = 0; i < 10; i++)
        suma = ((int)pesel[i] - 48) * t[i] + suma;

    if ((10 - (suma % 10) != (int)pesel[10] - 48) && (10 - (suma % 10) != 10 && pesel[10] != 0))
    {
        cout << "Pesel jest nieprawidlowy" << endl;
        return false;
    }
    return true;
}

int Pasazer::wieki[4] = { 0,0,0,0 };

void Pasazer::SprawdzanieWieku()
{
    
    if (pesel[0] == '2' && (pesel[2] == '2' || pesel[2] == '3'))
    {
        wieki[3]++;
        rodzaj = "Niemowle";
    }

    else if (pesel[0] == '1' && (pesel[2] == '2' || pesel[2] == '3'))
    {
        wieki[2]++;
        rodzaj = "Dziecko";
    }

    else if (pesel[0] == '0' && pesel[1] > 51 && (pesel[2] == '2' || pesel[2] == '3'))
    {
        wieki[1]++;
        rodzaj = "Mlodziez";
    }
    else
    {
        wieki[0]++;
        rodzaj = "Dorosly";
    }

}

void Pasazer::Zeruj()
{
    for (int i = 0; i < 4; i++)
        wieki[i] = 0;
}

bool Pasazer::PorownanieWieku(vector<int> vectorwieku)
{
    for (int i = 0; i < 4; i++)
    {
        if (vectorwieku[i] != wieki[i])
        {
            cout << "Typ pasazerow podany na poczatku nie zgadza sie z datami ich urodzin" << endl;
            return false;
        }
    }
    return true;
}

void Pasazer::DoPliku(string mail,string telefon,shared_ptr<Lotpdst> lot)
{
    ofstream plz;
    plz.open("Ludzie.txt", ios::app);


    plz << imie << " " << nazwisko << " " << pesel << " " << rodzaj << " " << mail << " " << telefon << " " << lot->wylot << " " << lot->przylot << " " << lot->data << " " << lot->nrlini << " " << lot->getKLase() << endl;

    plz.close();

}

Glowny::Glowny(const Pasazer& p) :Pasazer(p) {};

void Glowny::GetDane()
{
    cout << "E-mail: ";
    cin >> mail;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << endl << "Telefon: ";
    cin >> telefon;
    cin.clear();
    cin.ignore(1000, '\n');
}

bool Glowny::walidator()
{
    bool malpa = false;
    if (mail.length() < 3)
    {
        cout << "E-mail jest za krotki" << endl << endl;
    }
    for (int i = 0; i < mail.length(); i++)
    {
        if (mail[i] == ' ')
        {
            cout << "E-mail jest nieprawidlowy" << endl << endl;
            return false;
        }
        if ((mail[i] == '@') && i != 0 && i != mail.length() - 1)
            malpa = true;
    }

    if (!malpa)
    {
        cout << "E-mail jest nieprawidlowy" << endl << endl;
        return false;
    }


    if (telefon.length() != 9 && telefon.length() != 12)
    {
        cout << "Numer telefonu ma nieprawidlowa dlugosc" << endl << endl;
        return false;
    }
    if (telefon.length() == 12 && telefon[0] != '+')
    {
        cout << "Telefon w formie 12-znakowej powinien zaczynac sie od '+'" << endl << endl;
        return false;
    }
    else if (telefon.length() == 12)
        for (int i = 1; i < 12; i++)
            if (telefon[i] < 48 || telefon[i]>57)
            {
                cout << "Na pozycji " << i + 1 << " w numerze nie ma cyfry" << endl << endl;
                return false;
            }
    for (int i = 0; i < 9; i++)
        if (telefon[i] < 48 || telefon[i]>57)
        {
            cout << "Na pozycji " << i + 1 << " w numerze nie ma cyfry" << endl << endl;
            return false;
        }

    return true;
}


void Glowny::Blik()
{
    int cyfra;
    for (int i = 1; i <= 6; i++)
    {
        do
        {
            cout << "Podaj " << i << " cyfre kodu BLIK: ";
            cin >> cyfra;
        } while (!WpisywanieNumeru(cyfra, 0, 9));
        cout << cyfra << endl;
    }
}

void Glowny::Przelew()
{
    string login, haslo;
    cout << "Podaj login: ";
    cin >> login;
    cin.clear();
    cin.ignore(1000, '\n');
    cout << endl << "Podaj haslo: ";
    cin >> haslo;
    cin.clear();
    cin.ignore(1000, '\n');
}

string Glowny::DajMail()
{
    return mail;
}

string Glowny::DajTelefon()
{
    return telefon;
}