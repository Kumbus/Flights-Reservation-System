#ifndef KLASY_H
#define KLASY_H
#include<iostream>
#include<vector>
using namespace std;

/** \class Lotpdst Odpowiada za przechowywanie i dzialanie na podstawowych danych o locie, klasa bazowa dla pozostalych klas zwiazanych z liniami lotniczymi */
class Lotpdst
{
public:
    /**\var miejsce wylotu */
    string wylot;
    /**\var miejsce przylotu */
    string przylot;
    string data;
    int liczba_miejsc;
    string linia;
    int cena;
    string godzinawylotu;
    string godzinaprzylotu;
    string nrlini;
    string samolot;

    /** Konstruktor bezargumentowy*/
    Lotpdst();
    /** Konstruktor wieloargumentowy potrzebny do tworzenia lotu na podstawie danych od uzytkownika*/
    Lotpdst(string wylot, string przylot, string data, int liczba_miejsc);
    /** Konstruktor wieloargumentowy inicjalizujacy wszystkie pola*/
    Lotpdst(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot);
    /** Konstruktor kopiujacy*/
    Lotpdst(const Lotpdst& lp);

    /** Metoda wirtualna odpowidajaca za wypisanie danych o locie w klasach pochodnych */
    void virtual Wypisz();

    /** Operator porownujacy do siebie dwa loty na podsawie mejsca wylotu i przylotu, daty i wolnych miejsc
    @param zmienna lot ktory bedziemy porownywac z tym na rzecz ktorego wywolujemy metode
    @return true, jesli loty sobie odpowidaja
            false, jesli loty sobie nie odpowiadaja */
    bool operator==(Lotpdst& zmienna);

    /** Metoda wyszukujaca we wszystkich lotach lotow, ktore odpowidaja parametrom podanym przez uzytkownika
    @param dane vector z wszystkimi lotami
    @param miejsca vector do ktorego sa zapisywane pozycje lotow z vetora z wszystkimi lotami, ktore odpowiadaja uzytkownikowi
    @return vector lotow ktore zgadzaja sie z tym co podal uzytkownik */
    vector < shared_ptr<Lotpdst>> Szukaj(vector < shared_ptr<Lotpdst>>& dane, vector<int> &miejsca);

    /** Metoda sprawdzajaca czy dane podane przez uzytkownika sa poprawne
    @return true, jesli dane sa poprawne
            false, jesli dane sa niepoprawne*/
    bool Walidator();

    /** Metoda przyjmujaca dane od uzytkownika potrzebne do wyszukania lotu*/
    void getDane();

    /** Metoda przyjmujaca od uzytkownika dane dotyczace wieku pasazerow i zapisujaca je do vectora
    @return vector liczb calkowitych gdzie kazde pole odpowiada liczbie paszerow z danego przedzialu wiekowego */
    vector<int> WczytywanieWieku();

    /** Metoda wirtualna odpowiadajaca za wybor klasy podrozy w klasach pochodnych*/
    bool virtual WyborKlasy(vector<int> &t, int numerklasy);

    /** Metoda wirtualna zwracajaca ilosc klas podrozy w klasach pochodnych*/
    int virtual IleKlas();

    /** Metoda wirtualna zwracajaca klase podrozy w klasach pochodnych*/
    string virtual getKLase();

    /** Metoda zapisujaca do pliku tekstowego z danymi zaktualizowane dane po dokonaniu rezerwacji
    @param miejsce miejsce lotu, ktory zostal zarezerwowany w pliku tekstowym
    @param liczbapasazeerow liczba pasazerow, ktora wlasnie zarezerwowala lot
    @param plz plik z danymi, ktory bedzie aktualizowany
    @param licznik numer odpowiadajacy aktualnie zapisywanemu lotowi*/
    void ZaktualizowaneDoPliku(int miejsce, int liczbapasazerow,ofstream &plz,int licznik);
};

//LOT

/** \class Lot Odpowiada za loty lini lotniczej LOT, klasa pochodna klasy Lotpdst, klasa bazowa klas odpowiadajacych za klasy podrozy*/
class Lot : public Lotpdst
{
    string klasa;
    const int ileklas = 3;
public:
    /** Konstruktor wieloargumentowy*/
    Lot(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot);
    /** Konstruktor kopiujacy*/
    Lot(const Lotpdst& l);

    /** Metoda wypisujaca dane o locie*/
    void Wypisz();

    /** Metoda tworzaca obiekt klasy pochodnej i wywolujaca metody z nim zwiazane
    @param t vector z danymi odosnie wieku pasazerow
    @param numerklasy wpisany przez uzytkownika numer odpowiadajcy klasie podrozy jaka wybral
    @return true, jesli uzytkownik zdecydowal sie na dana klase podrozy
            false, jesli uzytkownik zrezygnowal z danej klasy podrozy */
    bool WyborKlasy(vector<int> &t,int numerklasy);

    /** Metoda zwracajaca liczbe klas podrozy ktorymi dysponuje linia lotnicza
    @return liczba klas podrozy lini lotniczej LOT*/
    int IleKlas();

    /** Metoda wirtualna wyliczajaca cene za lot w klasach pochodnych*/
    int virtual WyliczCene();

    /** Metoda zwracajaca klase podrozy
    @return klasa podrozy w jakiej bedzie lot*/
    string getKLase();
};

class Ekonomiczna : public Lot
{
    vector<int> t;

public:
    /** Konstruktor wieloargumentowy*/
    Ekonomiczna(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t);
    /** Konstruktor kopiujacy*/
    Ekonomiczna(const Lot& e, vector<int>& t);
    
    /** Metoda wypisujaca informacje o klasie podrozy*/
    void Wypisz();

    /** Metoda obliczajaca cene za bilety dla wszystkich podrozujacych
    @return cena za bilety*/
    int WyliczCene();

};

class Premium : public Lot
{
    vector<int> t;

public:
    /** Konstruktor wieloargumentowy*/
    Premium(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t);
    /** Konstruktor kopiujacy*/
    Premium(const Lot& p, vector<int>& t);
    /** Metoda wypisujaca informacje o klasie podrozy*/
    void Wypisz();
    /** Metoda obliczajaca cene za bilety dla wszystkich podrozujacych
    @return cena za bilety*/
    int WyliczCene();

};
class Biznesowa : public Lot
{
    vector<int> t;

public:
    /** Konstruktor wieloargumentowy*/
    Biznesowa(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t);
    /** Konstruktor kopiujacy*/
    Biznesowa(const Lot& b, vector<int>& t);
    /** Metoda wypisujaca informacje o klasie podrozy*/
    void Wypisz();
    /** Metoda obliczajaca cene za bilety dla wszystkich podrozujacych
    @return cena za bilety*/
    int WyliczCene();

};



//lufthansa
/** \class Lufthansa Odpowiada za loty lini lotniczej Lufthansa, klasa pochodna klasy Lotpdst, klasa bazowa klas odpowiadajacych za klasy podrozy*/
class Lufthansa : public Lotpdst
{
    string klasa;
    const int ileklas = 2;
public:
    /** Konstruktor wieloargumentowy*/
    Lufthansa(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot);
    /** Konstruktor kopiujacy*/
    Lufthansa(const Lotpdst& l);
    /** Metoda wypisujaca dane o locie*/
    void Wypisz();
    /** Metoda tworzaca obiekt klasy pochodnej i wywolujaca metody z nim zwiazane
    @param t vector z danymi odosnie wieku pasazerow
    @param numerklasy wpisany przez uzytkownika numer odpowiadajcy klasie podrozy jaka wybral
    @return true, jesli uzytkownik zdecydowal sie na dana klase podrozy
            false, jesli uzytkownik zrezygnowal z danej klasy podrozy */
    bool WyborKlasy(vector<int>& t, int numerklasy);
    /** Metoda zwracajaca liczbe klas podrozy ktorymi dysponuje linia lotnicza
    @return liczba klas podrozy lini lotniczej Lufthansa*/
    int IleKlas();
    /** Metoda wirtualna wyliczajaca cene za lot w klasach pochodnych*/
    int virtual WyliczCene();
    /** Metoda zwracajaca klase podrozy
    @return klasa podrozy w jakiej bedzie lot*/
    string getKLase();
};

class Ekonomic : public Lufthansa
{
    vector<int> t;

public:
    /** Konstruktor wieloargumentowy*/
    Ekonomic(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t);
    /** Konstruktor kopiujacy*/
    Ekonomic(const Lufthansa& e, vector<int>& t);
    /** Metoda wypisujaca informacje o klasie podrozy*/
    void Wypisz();
    /** Metoda obliczajaca cene za bilety dla wszystkich podrozujacych
    @return cena za bilety*/
    int WyliczCene();

};

class Biznes : public Lufthansa
{
    vector<int> t;

public:
    /** Konstruktor wieloargumentowy*/
    Biznes(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t);
    /** Konstruktor kopiujacy*/
    Biznes(const Lufthansa& b, vector<int>& t);
    /** Metoda wypisujaca informacje o klasie podrozy*/
    void Wypisz();
    /** Metoda obliczajaca cene za bilety dla wszystkich podrozujacych
    @return cena za bilety*/
    int WyliczCene();

};

//Emirates
/** \class Emirates Odpowiada za loty lini lotniczej Emirates, klasa pochodna klasy Lotpdst, klasa bazowa klas odpowiadajacych za klasy podrozy*/
class Emirates : public Lotpdst
{
    string klasa;
    const int ileklas = 3;

public:
    /** Konstruktor wieloargumentowy*/
    Emirates(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot);
    /** Konstruktor kopiujacy*/
    Emirates(const Lotpdst& l);
    /** Metoda wypisujaca dane o locie*/
    void Wypisz();
    /** Metoda tworzaca obiekt klasy pochodnej i wywolujaca metody z nim zwiazane
    @param t vector z danymi odosnie wieku pasazerow
    @param numerklasy wpisany przez uzytkownika numer odpowiadajcy klasie podrozy jaka wybral
    @return true, jesli uzytkownik zdecydowal sie na dana klase podrozy
            false, jesli uzytkownik zrezygnowal z danej klasy podrozy */
    bool WyborKlasy(vector<int>& t, int numerklasy);
    /** Metoda zwracajaca liczbe klas podrozy ktorymi dysponuje linia lotnicza
    @return liczba klas podrozy lini lotniczej Emirates*/
    int IleKlas();
    /** Metoda wirtualna wyliczajaca cene za lot w klasach pochodnych*/
    int virtual WyliczCene();
    /** Metoda zwracajaca klase podrozy
    @return klasa podrozy w jakiej bedzie lot*/
    string getKLase();
};

class Economy : public Emirates
{
    vector<int> t;

public:
    /** Konstruktor wieloargumentowy*/
    Economy(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t);
    /** Konstruktor kopiujacy*/
    Economy(const Emirates& e, vector<int>& t);
    /** Metoda wypisujaca informacje o klasie podrozy*/
    void Wypisz();
    /** Metoda obliczajaca cene za bilety dla wszystkich podrozujacych
    @return cena za bilety*/
    int WyliczCene();

};

class Business : public Emirates
{
    vector<int> t;

public:
    /** Konstruktor wieloargumentowy*/
    Business(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t);
    /** Konstruktor kopiujacy*/
    Business(const Emirates& b, vector<int>& t);
    /** Metoda wypisujaca informacje o klasie podrozy*/
    void Wypisz();
    /** Metoda obliczajaca cene za bilety dla wszystkich podrozujacych
    @return cena za bilety*/
    int WyliczCene();

};

class First : public Emirates
{
    vector<int> t;

public:
    /** Konstruktor wieloargumentowy*/
    First(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t);
    /** Konstruktor kopiujacy*/
    First(const Emirates& f, vector<int>& t);
    /** Metoda wypisujaca informacje o klasie podrozy*/
    void Wypisz();
    /** Metoda obliczajaca cene za bilety dla wszystkich podrozujacych
    @return cena za bilety*/
    int WyliczCene();

};


//ryanair
/** \class RyanAir Odpowiada za loty lini lotniczej RyanAir, klasa pochodna klasy Lotpdst, klasa bazowa klas odpowiadajacych za klasy podrozy*/
class RyanAir : public Lotpdst
{
    string klasa;
    const int ileklas = 2;
public:
    /** Konstruktor wieloargumentowy*/
    RyanAir(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot);
    /** Konstruktor kopiujacy*/
    RyanAir(const Lotpdst& l);
    /** Metoda wypisujaca dane o locie*/
    void Wypisz();
    /** Metoda tworzaca obiekt klasy pochodnej i wywolujaca metody z nim zwiazane
    @param t vector z danymi odosnie wieku pasazerow
    @param numerklasy wpisany przez uzytkownika numer odpowiadajcy klasie podrozy jaka wybral
    @return true, jesli uzytkownik zdecydowal sie na dana klase podrozy
            false, jesli uzytkownik zrezygnowal z danej klasy podrozy */
    bool WyborKlasy(vector<int>& t, int numerklasy);
    /** Metoda zwracajaca liczbe klas podrozy ktorymi dysponuje linia lotnicza
        @return liczba klas podrozy lini lotniczej RyanAir*/
    int IleKlas();
    /** Metoda wirtualna wyliczajaca cene za lot w klasach pochodnych*/
    int virtual WyliczCene();
    /** Metoda zwracajaca klase podrozy
    @return klasa podrozy w jakiej bedzie lot*/
    string getKLase();
};

class Regular : public RyanAir
{
    vector<int> t;

public:
    /** Konstruktor wieloargumentowy*/
    Regular(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t);
    /** Konstruktor kopiujacy*/
    Regular(const RyanAir& r, vector<int>& t);
    /** Metoda wypisujaca informacje o klasie podrozy*/
    void Wypisz();
    /** Metoda obliczajaca cene za bilety dla wszystkich podrozujacych
    @return cena za bilety*/
    int WyliczCene();

};

class Plus : public RyanAir
{
    vector<int> t;

public:
    /** Konstruktor wieloargumentowy*/
    Plus(string wylot, string przylot, string data, int liczba_miejsc, string linia, int cena, string godzinawylotu, string godzinaprzylotu, string nrlini, string samolot, vector<int> t);
    /** Konstruktor kopiujacy*/
    Plus(const RyanAir& p, vector<int>& t);
    /** Metoda wypisujaca informacje o klasie podrozy*/
    void Wypisz();
    /** Metoda obliczajaca cene za bilety dla wszystkich podrozujacych
    @return cena za bilety*/
    int WyliczCene();

};

class Pasazer
{
    string imie;
    string nazwisko;
    string pesel;
    static int wieki[4];
    string rodzaj;

public:
    /** Konstruktor bezargumentowy*/
    Pasazer();
    /** Konstruktor kopiujacy*/
    Pasazer(const Pasazer& p);

    /** Metoda pobierajaca dane od uzytkownika*/
    void GetDane();

    /** Metoda sprawdzajaca poprawnosc danych wprowadzonych przez uzytkownika
    @return true, jesli dane sa popranwe
            false, jesli dane sa niepoprawne*/
    bool walidator();

    /** Metoda okreslajaca wiek pasazerow na podstawie ich peselu*/
    void SprawdzanieWieku();

    /** Metoda statyczna sprawdzajaca czy wiek pasazerow podany przez uzytkownika zgadza sie z ich peselami
    @param vectorwieku vector, w ktorym sa zapisane dane odnosnie wieku pasazerow
    @return true, jesli wiek dane sie zgadzaja
            false, jesli dane sie nie zgadzaja*/
    bool static PorownanieWieku(vector<int> vectorwieku);

    /** Metoda zapisujaca dane osobowe i dane lotu do pliku tekstowego
    @param mail mail placacego
    @param telefon numer telefonu placacego
    @param lot wskaznik na lot, na ktory bilet zostal zarezerwowany*/
    void DoPliku(string mail,string telefon,shared_ptr<Lotpdst> lot);

    /** Metoda statyczna zerujaca dane zmieniane w SprawdzanieWieku*/
    void static Zeruj();

};

class Glowny : public Pasazer
{
    string mail;
    string telefon;

public:
    /** Konstruktor kopiujacy*/
    Glowny(const Pasazer &p);

    /** Metoda pobierajaca dane od uzytkownika*/
    void GetDane();

    /** Metoda sprawdzajaca poprawnosc danych wprowadzonych przez uzytkownika
    @return true, jesli dane sa popranwe
            false, jesli dane sa niepoprawne*/
    bool walidator();

    /** Metoda przeprowadzajaca placenie Blikiem*/
    void Blik();

    /** Metoda przeprowadzajaca placenie przelewem*/
    void Przelew();

    /** Metoda zwracajaca maila
    @return mail uzytkownika*/
    string DajMail();

    /** Metoda zwracajaca telefon
    @return numer telefonu uzytkownika*/
    string DajTelefon();
};

#endif
