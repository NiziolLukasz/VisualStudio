#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class Tadres
{
protected:
	string miasto;
	string ulica;
	int numer;
public:
	Tadres(string miasto, string ulica, int numer); // Konstruktor ustawiaj¹cy wszystkie pola na podstawie swoich parametrów
	void Wyswietl(); // wyœwietlenie adresu
	~Tadres(); // Destruktor
};
class TOsoba
{
protected:
	string imie;
	string nazwisko;
	int wiek;
	Tadres adres;
public:
	TOsoba(string imie, string nazwisko, int wiek, Tadres adres); //Konstruktor ustawiaj¹cy wszystkie pola na podstawie swoich parametrów
	virtual void Wyswietl() = 0; //Wyœwietla informacje o osobie
	string PodajImie(); // zwraca imiê
	string PodajNazwisko(); //zwraca nazwisko
	virtual ~TOsoba(); //Destruktor
};
class TStudent
	:public TOsoba
{
protected:
	string kierunek;
	int rok;
public:
	TStudent(string imie, string nazwisko, int wiek, Tadres adres, string kierunek, int rok); //Konstruktor ustawiaj¹cy wszystkie pola na podstawie swoich parametrów
	virtual void Wyswietl(); //Wyœwietla informacje o studencie
	string PodajKierunek(); //Zwraca kierunek
	virtual ~TStudent(); //Destruktor
};
void Testuj();

int main()
{
	Testuj();
	system("pause");
	return 0;
}
//============================== Metody TOsoba =========================================
TOsoba::TOsoba(string imie, string nazwisko, int wiek, Tadres adres) : adres(adres)
{
	cout << "Konstruktor TOsoba";
	this->imie = imie;
	this->nazwisko = nazwisko;
	this->wiek = wiek < 0 ? 0 : wiek > 130 ? 0 : wiek;
}
string TOsoba::PodajImie()
{
	return imie;
}
string TOsoba::PodajNazwisko()
{
	return nazwisko;
}
TOsoba::~TOsoba()
{
	cout << "Destruktor TOsoba";
}
//============================== Metody TStudent =======================================
TStudent::TStudent(string imie, string nazwisko, int wiek, Tadres adres, string kierunek, int rok) :TOsoba(imie, nazwisko, wiek, adres)
{
	cout << "Konstruktor TStudent";
	this->kierunek = kierunek;
	this->rok = rok;
}
void TStudent::Wyswietl()
{
	cout << "Imie: " << imie << endl;
	cout << "Nazwisko: " << nazwisko << endl;
	cout << "Wiek: " << wiek << endl;
	adres.Wyswietl();
	cout << "Kierunek: " << kierunek << endl;
	cout << "Rok: " << rok << endl;
}
string TStudent::PodajKierunek()
{
	return kierunek;
}
TStudent::~TStudent()
{
	cout << "Destruktor TStudent";
}
//============================== Metody Tadres =========================================
Tadres::Tadres(string m, string ul, int nr)
{
	cout << "Konstruktor Tadres";
	miasto = m;
	ulica = ul;
	numer = nr <= 0 ? 0 : nr;
}
void Tadres::Wyswietl()
{
	cout << "Miasto: " << miasto << endl;
	cout << "Ulica: " << ulica << endl;
	cout << "Numer domu: " << numer << endl;
}
Tadres::~Tadres()
{
	cout << "Destruktor Tadres";
}
//============================== Metody ================================================
void Testuj()
{
	Tadres *adres1 = new Tadres("krasnystaw", "Stryjow", 90);
	Tadres *adres2 = new Tadres("Chrz¹szczy¿ewoszyce", "£êko³ody", 19);

	TStudent st1("Lukasz", "Niziol", 20, *adres1, "Informatyka", 2);
	cout << endl;
	st1.Wyswietl();
	cout << endl;

	TOsoba *st2 = new TStudent("Grzegorz", "Brzêczyszczykiewicz", 25, *adres2, "Architektura Krajobrazu", 3);
	cout << endl;
	st2->Wyswietl();
	cout << endl;

	TOsoba &os = st1;
	cout << endl;
	os.Wyswietl();
	cout << endl;

	cout << st1.PodajNazwisko() << " " << st1.PodajKierunek() << endl;
	cout << st2->PodajNazwisko() << endl;
	cout << ((TStudent*)st2)->PodajKierunek() << endl;
	delete st2;
}
