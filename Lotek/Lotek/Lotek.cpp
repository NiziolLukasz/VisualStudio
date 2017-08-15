#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
struct Losowanie
{
	short nrLosowania;
	short rok;
	char miesiac;
	char dzien;
	char Wyniki[6];
};
/*==============================================================================  KLASA LOTEK  =========================================================================================*/
class Lotek
{
private:
	bool ok; //pole o wartoœci logicznej; jeœli ma wartoœæ true to mo¿na wykonywaæ operacje na obiekcie tej klasy;
	fstream bin; //zmienna strumieniowa reprezentuj¹ca plik binarny wszystkich wyników losowañ;
	short Krotnosc[50]; //Jeœli pierwszy element tej tablicy ( o indeksie 0) ma wartoœæ zero to tablica jeszcze nie jest wype³niona. Pozosta³e elementy(o indeksach od 1 do 49) okreœlaj¹ czêstotliwoœæ wystêpowania liczb w losowaniach(tzn.wartoœæ elementu o indeksie i mówi ile razy liczba i by³a wylosowana);
	int zapisBinarny(fstream  &a); //zapisuj¹ca dane z pliku tekstowego (o danych zapisanych jak opisano wy¿ej) do pliku binarnego w postaci struktur Losowanie; wynikiem funkcji jest liczba rekordów zapisanych do pliku;
	void TablicaKrotnosc(); // metoda wype³niaj¹ca tablicê Krotnoœæ;
public:
	Lotek(string nazwaW = ""); //konstruktor z jednym parametrem tekstowym o wartoœci domyœlnej pusty ³añcuch. Parametrem metody jest ³añcuch okreœlaj¹cy plik tekstowy z wynikami losowañ.Jeœli ³añcuch nie jest pusty konstruktor zapisuje dane tekstowe w pliku binarnym o rozszerzeniu dat i co najwy¿ej oœmiu znakach zadanej w parametrze nazwy pliku tekstowego(np. 2015_lot.dat) a póŸniej otwiera go do czytania.Jeœli ³añcuch jest pusty konstruktor otwiera plik binarny Duzy_lot.dat do odczytu(plik binarny wczeœniej utworzony).W zale¿noœci od powodzenia operacji na plikach ustawia odpowiednio wartoœæ pola ok.Zeruje tablicê Krotnosc;
	bool Niepusty(); //metoda daj¹ca w wyniku wartoœæ pola ok;
	void Czestotliwosci(); //metoda wyœwietlaj¹ca czêstotliwoœæ wystêpowania w losowaniach poszczególnych liczb;
	void NajrzadziejLosowane(); //metoda wyœwietlaj¹ca najrzadziej wylosowane liczby;
	void NajczesciejLosowane(); //metoda wyœwietlaj¹ca najczêœciej losowane liczby;
	void LosowanieNr(int nrLosowania); // metoda wyœwietlaj¹ca zadane parametrem (numer losowania) losowanie;
	int  IleTakich(short T[]); //metoda z parametrem bêd¹cym tablic¹ szeœciu liczb ca³kowitych dwubajtowych; wynikiem funkcji jest liczba mówi¹ca ile by³o losowañ z wynikami jak parametr metody, ponadto metoda wyœwietla te losowania;
	void WybierzDoPliku(short rok, short miesiac = 0); //metoda tworzy plik tekstowy o nazwie LTrrrrmm.txt i zapisuje do niego wyniki losowañ z zadanego roku i miesi¹ca; jeœli miesi¹c jest zerowy to z ca³ego roku;
};
ostream & operator << (ostream & wyjscie, Losowanie &l);



/*==============================================================================  MAIN  ================================================================================================*/



int main()
{
	Lotek l("Duzy_lotek.txt");
	int n;
	l.Czestotliwosci();
	cout << endl;
	l.NajrzadziejLosowane();
	cout << endl;
	l.NajczesciejLosowane();
	cout << endl;
	short T[6] = { 2,4,31,38,39,46 };
	cout << "Znalazlo: " << l.IleTakich(T) << " podobienstw.\n";
	cout << endl;
	l.WybierzDoPliku(1978, 05);

	cout << "Podaj numer losowania: ";
	cin >> n;
	l.LosowanieNr(n);
	system("pause");
	return 0;
}



/*============================================================================  KONSTRUKTOR LOTEK  ======================================================================================*/
Lotek::Lotek(string nazwaW) //konstruktor z jednym parametrem tekstowym o wartoœci domyœlnej pusty ³añcuch. Parametrem metody jest ³añcuch okreœlaj¹cy plik tekstowy z wynikami losowañ.Jeœli ³añcuch nie jest pusty konstruktor zapisuje dane tekstowe w pliku binarnym o rozszerzeniu dat i co najwy¿ej oœmiu znakach zadanej w parametrze nazwy pliku tekstowego(np. 2015_lot.dat) a póŸniej otwiera go do czytania.Jeœli ³añcuch jest pusty konstruktor otwiera plik binarny Duzy_lot.dat do odczytu(plik binarny wczeœniej utworzony).W zale¿noœci od powodzenia operacji na plikach ustawia odpowiednio wartoœæ pola ok.Zeruje tablicê Krotnosc;
{
	if (!nazwaW.empty()) //Sprawdzam czy ³añcuch "nazwaW" nie jest pusty 
	{
		string nazwaBin;
		if (nazwaW.length() >= 12) //Zapobieganie stworzenia nazwy typu "Lotek.tx.dat" z nazwy "Lotek.txt"
			nazwaBin = nazwaW.substr(0, 8) + ".dat";
		else
			nazwaBin = nazwaW.substr(0, nazwaW.length() - 4) + ".dat";
		fstream plikW(nazwaW.c_str(), ios::in); //Otwieram plik z wynikami by zapisaæ go w formie binarnej pod nazw¹ "nazwaBin"
		if (!plikW)
			cout << "Blad otwarcia pliku: " << nazwaW << endl;
		else
		{
			bin.open(nazwaBin.c_str(), ios::out | ios::binary); //Otworzenie pliku binarnego do zapisu
			if (!bin)
				cout << "Blad otwarcia pliku do zapisu: " << nazwaBin << ". \n";
			else
				cout << "Zapisano " << zapisBinarny(plikW) << " rekordow do pliku o nazwie: " << nazwaBin << endl; //Zapis pliku tekstowego o nazwie "nazwaW", w  pliku binarnym o nazwie "nazwaBin"	
			bin.close(); //Zamkniêcie pliku binarnego o nazwie "nazwaBin"
			bin.open(nazwaBin.c_str(), ios::in | ios::binary); //Otworzenie pliku binarnego, o nazwie "nazwaBin", tylko do odczytu
			if (!bin)
				cout << "Blad otwarcia pliku do odczytu: " << nazwaBin << ". \n";
		}
		plikW.close(); //Zamkniêcie pliku tekstowego o nazwie "nazwaW"
	}
	else
	{
		bin.open("Duzy_lot.dat", ios::in | ios::binary); //Otwieranie pliku binarnego, o nazwie "Duzy_lot.dat", tylko do odczytu
		if (!bin)
			cout << "Blad otwarcia pliku: \"Duzy_lot.dat\" " << endl;
	}
	ok = bin.is_open(); //ustawianie pola "ok" w zale¿noœci czy plik jest otwarty, czy nie
	for (int i = 0; i < 50; i++)
		Krotnosc[i] = 0; //Zerowanie tablicy krotnoœæ
}
/*==========================================================================  OPERATOR <<  ==============================================================================================*/
ostream & operator << (ostream & wyjscie, Losowanie &l)
{
	wyjscie << setw(4) << l.nrLosowania << ". " << setw(2) << setfill('0') << (short)l.dzien << "." << setw(2) << (short)l.miesiac << "." << l.rok << " ";
	for (int i = 0;i < 5;i++)
		wyjscie << (short)l.Wyniki[i] << ",";
	wyjscie << (short)l.Wyniki[5] << endl;
	wyjscie << setfill(' '); // Gdy tego nie ma to nastêpne wywo³anie tego samego wyjscia "<<", bêdzie skutkowa³o dodaniem '0' w puste miejsce w "nrLosowania" np. przy numerze "49" wyswietli "0049"
	return wyjscie;
}
/*==============================================================================  ZAPIS BINARNY  ========================================================================================*/
int Lotek::zapisBinarny(fstream &plik) //zapisuj¹ca dane z pliku tekstowego (o danych zapisanych jak opisano wy¿ej) do pliku binarnego w postaci struktur Losowanie; wynikiem funkcji jest liczba rekordów zapisanych do pliku;
{
	short temp;
	Losowanie l;
	if (!bin) cout << "Problemy z plikiem binarnym w funkcji \"zapisBinarny\"" << endl;
	else
	{
		while (plik >> temp)
		{
			l.nrLosowania = temp;
			plik.ignore();
			plik >> temp;
			l.dzien = temp;
			plik.ignore();
			plik >> temp;
			plik.ignore();
			l.miesiac = temp;
			plik >> l.rok;
			for (int i = 0; i<5; i++)
			{
				plik >> temp;
				plik.ignore();
				l.Wyniki[i] = temp;
			}
			plik >> temp;
			l.Wyniki[5] = temp;
			bin.write(reinterpret_cast<char*>(&l), sizeof(l));
		}
	}
	bin.clear();
	return l.nrLosowania;
}
/*============================================================================  TABLICA KROTNOSC  =======================================================================================*/
void Lotek::TablicaKrotnosc() // metoda wype³niaj¹ca tablicê Krotnoœæ; Jeœli pierwszy element tej tablicy ( o indeksie 0) ma wartoœæ zero to tablica jeszcze nie jest wype³niona. Pozosta³e elementy(o indeksach od 1 do 49) okreœlaj¹ czêstotliwoœæ wystêpowania liczb w losowaniach(tzn.wartoœæ elementu o indeksie i mówi ile razy liczba i by³a wylosowana);
{
	if (ok)
	{
		Losowanie L;
		bin.seekg(0);
		while (bin.read(reinterpret_cast <char*> (&L), sizeof(L)))  //Sczytanie z pliku bin struktury L o d³ugoœci L
		{
			for (char i = 0; i < 6; i++)
				Krotnosc[L.Wyniki[i]]++;
		}
		Krotnosc[0] = 1;
		bin.clear(); //Cofniecie na pocz¹tek pliku
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
}
/*=================================================================================  NIEPUSTY  ==========================================================================================*/
bool Lotek::Niepusty() //metoda daj¹ca w wyniku wartoœæ pola ok;
{
	return ok;
}
/*===============================================================================  NAJRZADZIEJ LOSOWANE  ================================================================================*/
void Lotek::NajrzadziejLosowane() //metoda wyœwietlaj¹ca najrzadziej wylosowane liczby;
{
	if (ok)
	{
		if (Krotnosc[0] == 0)
			TablicaKrotnosc();
		int najm = 1;
		for (int i = 2;i < 50;i++)
			if (Krotnosc[i] <= Krotnosc[najm])
				najm = i;
		cout << "Najrzadziej losowane liczby: \n";
		for (int i = 1;i <= najm;i++)
			if (Krotnosc[i] == Krotnosc[najm])
				cout << i << " - " << Krotnosc[i] << " razy\n";
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
}
/*===============================================================================  NAJCZESCIEJ LOSOWANE  ================================================================================*/
void Lotek::NajczesciejLosowane()//metoda wyœwietlaj¹ca najczêœciej losowane liczby;
{
	if (ok)
	{
		if (Krotnosc[0] == 0)
			TablicaKrotnosc();
		int najw = 1;
		for (int i = 2;i < 50;i++)
			if (Krotnosc[i] >= Krotnosc[najw])
				najw = i;
		cout << "Najczesciej losowane liczby: \n";
		for (int i = 0;i <= najw;i++)
			if (Krotnosc[i] == Krotnosc[najw])
				cout << i << " - " << Krotnosc[i] << " razy\n";
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
}
/*===============================================================================  CZESTOTNIWOSC  =======================================================================================*/
void Lotek::Czestotliwosci()  //metoda wyœwietlaj¹ca czêstotliwoœæ wystêpowania w losowaniach poszczególnych liczb;
{
	if (ok)
	{
		if (Krotnosc[0] == 0)
			TablicaKrotnosc();
		for (int i = 1; i < 50; i++)
			cout << setw(2) << i << "| " << setw(5) << Krotnosc[i] << endl;
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
}
/*==================================================================================  LOSOWANIE NR  =====================================================================================*/
void Lotek::LosowanieNr(int nrLosowania) // metoda wyœwietlaj¹ca zadane parametrem (numer losowania) losowanie;
{
	if (ok)
	{
		Losowanie L;
		//bin.clear();
		bin.seekg(0);
		while (bin.read(reinterpret_cast <char *> (&L), sizeof(L)))
			if (L.nrLosowania == nrLosowania)
			{
				cout << L;
				bin.clear();
				return;
			}
		bin.clear();
		cout << "Nie ma Losowania o takim numerze." << endl;
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
}
/*==================================================================================  ILE TAKICH  =======================================================================================*/
int Lotek::IleTakich(short T[]) //metoda z parametrem bêd¹cym tablic¹ szeœciu liczb ca³kowitych dwubajtowych; wynikiem funkcji jest liczba mówi¹ca ile by³o losowañ z wynikami jak parametr metody, ponadto metoda wyœwietla te losowania;
{
	int licznik = 0;
	if (ok)
	{
		Losowanie L;
		bin.seekg(0);
		while (bin.read(reinterpret_cast<char *>(&L), sizeof(L)))
		{
			if (T[0] == L.Wyniki[0] && T[1] == L.Wyniki[1] && T[2] == L.Wyniki[2] && T[3] == L.Wyniki[3] && T[4] == L.Wyniki[4] && T[5] == L.Wyniki[5])
			{
				licznik++;
				cout << L;
			}
		}
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
	bin.clear();
	return licznik;
}
/*==================================================================================  WYBIERZ DO PLIKU  =================================================================================*/
void Lotek::WybierzDoPliku(short rok, short miesiac) //metoda tworzy plik tekstowy o nazwie LTrrrrmm.txt i zapisuje do niego wyniki losowañ z zadanego roku i miesi¹ca; jeœli miesi¹c jest zerowy to z ca³ego roku;
{
	if (ok)
	{
		bin.seekg(0);
		ostringstream ss;
		ss << rok;
		if (miesiac != 0)
		{
			if (miesiac < 10)
				ss << 0;
			ss << miesiac;
		}
		string nazwa = "LT" + ss.str() + ".txt";
		fstream plik(nazwa.c_str(), ios::out);
		Losowanie L;
		int licznik = 0;
		while (bin.read(reinterpret_cast<char *>(&L), sizeof(L)))
		{
			if (miesiac != 0)
			{
				if (rok == L.rok && miesiac == L.miesiac)
				{
					plik << L;
				}
			}
			else
				if (rok == L.rok)
				{
					plik << L;
				}
		}
		bin.clear();
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
}