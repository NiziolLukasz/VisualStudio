// Szablony.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
struct LosowanieD
{
	short nrLosowania;
	short rok;
	char miesiac;
	char dzien;
	char Wyniki[6];
};
struct LosowanieM
{
	short nrLosowania;
	short rok;
	char miesiac;
	char dzien;
	char Wyniki[5];
};
/*==============================================================================  KLASA LOTEK  =========================================================================================*/
template<class TypStruktury>
class LotekS
{
private:
	short zilu; //pole ca�kowite dwubajtwe okreslaj�ce z ilu liczb jest losowanie np. z 49;
	short ile; //pole ca�kowite dwubajtowe okraslaj�ce ile liczb jest losowanych w jednym losowaniu np. 6 lub 5;
	bool ok; //pole o warto�ci logicznej; je�li ma warto�� true to mo�na wykonywa� operacje na obiekcie tej klasy;
	fstream bin; //zmienna strumieniowa reprezentuj�ca plik binarny wszystkich wynik�w losowa�;
	short Krotnosc[51]; //Je�li pierwszy element tej tablicy ( o indeksie 0) ma warto�� zero to tablica jeszcze nie jest wype�niona. Pozosta�e elementy(o indeksach od 1 do 49) okre�laj� cz�stotliwo�� wyst�powania liczb w losowaniach(tzn.warto�� elementu o indeksie i m�wi ile razy liczba i by�a wylosowana);
	int zapisBinarny(fstream  &a); //zapisuj�ca dane z pliku tekstowego (o danych zapisanych jak opisano wy�ej) do pliku binarnego w postaci struktur Losowanie; wynikiem funkcji jest liczba rekord�w zapisanych do pliku;
	void TablicaKrotnosc(); // metoda wype�niaj�ca tablic� Krotno��;
public:
	LotekS(short, short, string nazwaW = ""); //konstruktor z jednym parametrem tekstowym o warto�ci domy�lnej pusty �a�cuch. Parametrem metody jest �a�cuch okre�laj�cy plik tekstowy z wynikami losowa�.Je�li �a�cuch nie jest pusty konstruktor zapisuje dane tekstowe w pliku binarnym o rozszerzeniu dat i co najwy�ej o�miu znakach zadanej w parametrze nazwy pliku tekstowego(np. 2015_lot.dat) a p�niej otwiera go do czytania.Je�li �a�cuch jest pusty konstruktor otwiera plik binarny Duzy_lot.dat do odczytu(plik binarny wcze�niej utworzony).W zale�no�ci od powodzenia operacji na plikach ustawia odpowiednio warto�� pola ok.Zeruje tablic� Krotnosc;
	bool Niepusty(); //metoda daj�ca w wyniku warto�� pola ok;
	void Czestotliwosci(); //metoda wy�wietlaj�ca cz�stotliwo�� wyst�powania w losowaniach poszczeg�lnych liczb;
	void NajrzadziejLosowane(); //metoda wy�wietlaj�ca najrzadziej wylosowane liczby;
	void NajczesciejLosowane(); //metoda wy�wietlaj�ca najcz�ciej losowane liczby;
	void LosowanieNr(int nrLosowania); // metoda wy�wietlaj�ca zadane parametrem (numer losowania) losowanie;
	int  IleTakich(short tab[]); //metoda z parametrem b�d�cym tablic� sze�ciu liczb ca�kowitych dwubajtowych; wynikiem funkcji jest liczba m�wi�ca ile by�o losowa� z wynikami jak parametr metody, ponadto metoda wy�wietla te losowania;
	void WybierzDoPliku(short rok, short miesiac = 0); //metoda tworzy plik tekstowy o nazwie LTrrrrmm.txt i zapisuje do niego wyniki losowa� z zadanego roku i miesi�ca; je�li miesi�c jest zerowy to z ca�ego roku;
};

ostream & operator << (ostream & wyjscie, LosowanieD &l);



/*==============================================================================  MAIN  ================================================================================================*/



int main()
{
	LotekS <LosowanieD> lotek(6, 49, "Duzy_lotek.txt");
	lotek.Czestotliwosci();
	cout << endl;
	lotek.LosowanieNr(1);
	lotek.LosowanieNr(5907);
	lotek.LosowanieNr(1);
	cout << endl;
	LotekS <LosowanieM> lotekm(5, 42, "maly_lotek.txt");
	lotekm.Czestotliwosci();
	cout << endl;
	lotekm.LosowanieNr(2);
	lotekm.LosowanieNr(3007);
	lotekm.LosowanieNr(1);


	system("pause");
	return 0;
}



/*============================================================================  KONSTRUKTOR LOTEK  ======================================================================================*/
template<class TypStruktury>
LotekS<TypStruktury>::LotekS(short ile, short zilu, string nazwaW) //konstruktor z jednym parametrem tekstowym o warto�ci domy�lnej pusty �a�cuch. Parametrem metody jest �a�cuch okre�laj�cy plik tekstowy z wynikami losowa�.Je�li �a�cuch nie jest pusty konstruktor zapisuje dane tekstowe w pliku binarnym o rozszerzeniu dat i co najwy�ej o�miu znakach zadanej w parametrze nazwy pliku tekstowego(np. 2015_lot.dat) a p�niej otwiera go do czytania.Je�li �a�cuch jest pusty konstruktor otwiera plik binarny Duzy_lot.dat do odczytu(plik binarny wcze�niej utworzony).W zale�no�ci od powodzenia operacji na plikach ustawia odpowiednio warto�� pola ok.Zeruje tablic� Krotnosc;
{
	this->ile = ile;
	this->zilu = zilu;
	if (!nazwaW.empty()) //Sprawdzam czy �a�cuch "nazwaW" nie jest pusty 
	{
		string nazwaBin;
		if (nazwaW.length() >= 12) //Zapobieganie stworzenia nazwy typu "Lotek.tx.dat" z nazwy "Lotek.txt"
			nazwaBin = nazwaW.substr(0, 8) + ".dat";
		else
			nazwaBin = nazwaW.substr(0, nazwaW.length() - 4) + ".dat";
		fstream plikW(nazwaW.c_str(), ios::in); //Otwieram plik z wynikami by zapisa� go w formie binarnej pod nazw� "nazwaBin"
		if (!plikW)
			cout << "Blad otwarcia pliku: " << nazwaW << endl;
		else
		{
			bin.open(nazwaBin.c_str(), ios::out | ios::binary); //Otworzenie pliku binarnego do zapisu
			if (!bin)
				cout << "Blad otwarcia pliku do zapisu: " << nazwaBin << ". \n";
			else
				cout << "Zapisano " << zapisBinarny(plikW) << " rekordow do pliku o nazwie: " << nazwaBin << endl; //Zapis pliku tekstowego o nazwie "nazwaW", w  pliku binarnym o nazwie "nazwaBin"	
			bin.close(); //Zamkni�cie pliku binarnego o nazwie "nazwaBin"
			bin.open(nazwaBin.c_str(), ios::in | ios::binary); //Otworzenie pliku binarnego, o nazwie "nazwaBin", tylko do odczytu
			if (!bin)
				cout << "Blad otwarcia pliku do odczytu: " << nazwaBin << ". \n";
		}
		plikW.close(); //Zamkni�cie pliku tekstowego o nazwie "nazwaW"
	}
	else
	{
		bin.open("Duzy_lot.dat", ios::in | ios::binary); //Otwieranie pliku binarnego, o nazwie "Duzy_lot.dat", tylko do odczytu
		if (!bin)
			cout << "Blad otwarcia pliku: \"Duzy_lot.dat\" " << endl;
	}
	ok = bin.is_open(); //ustawianie pola "ok" w zale�no�ci czy plik jest otwarty, czy nie
	for (int i = 0; i < 51; i++)
		Krotnosc[i] = 0; //Zerowanie tablicy krotno��
}
/*==========================================================================  OPERATOR << LosowanieD ====================================================================================*/

ostream & operator << (ostream & wyjscie, LosowanieD &l)
{
	wyjscie << setw(4) << l.nrLosowania << ". " << setw(2) << setfill('0') << (short)l.dzien << "." << setw(2) << (short)l.miesiac << "." << l.rok << " ";
	for (int i = 0; i < 6; i++)
		wyjscie << (short)l.Wyniki[i] << " ";
	wyjscie << endl;
	wyjscie << setfill(' '); // Gdy tego nie ma to nast�pne wywo�anie z tego samego wyjscia "<<" (np. cout, plik, itp.), b�dzie skutkowa�o dodaniem '0' w puste miejsce w "nrLosowania" np. przy numerze "49" wyswietli "0049"
	return wyjscie;
}
/*==========================================================================  OPERATOR << LosowanieM ====================================================================================*/
ostream & operator << (ostream & wyjscie, LosowanieM &l)
{
	wyjscie << setw(4) << l.nrLosowania << ". " << setw(2) << setfill('0') << (short)l.dzien << "." << setw(2) << (short)l.miesiac << "." << l.rok << " ";
	for (int i = 0; i < 5; i++)
		wyjscie << (short)l.Wyniki[i] << " ";
	wyjscie << endl;
	wyjscie << setfill(' '); // Gdy tego nie ma to nast�pne wywo�anie z tego samego wyjscia "<<" (np. cout, plik, itp.), b�dzie skutkowa�o dodaniem '0' w puste miejsce w "nrLosowania" np. przy numerze "49" wyswietli "0049"
	return wyjscie;
}
/*==============================================================================  ZAPIS BINARNY  ========================================================================================*/
template<class TypStruktury>
int LotekS<TypStruktury>::zapisBinarny(fstream &plik) //zapisuj�ca dane z pliku tekstowego (o danych zapisanych jak opisano wy�ej) do pliku binarnego w postaci struktur Losowanie; wynikiem funkcji jest liczba rekord�w zapisanych do pliku;
{
	short temp;
	TypStruktury l;
	if (!bin) cout << "Problemy z plikiem binarnym w funkcji \"zapisBinarny\"" << endl;
	else
	{
		while (plik >> temp)
		{
			l.nrLosowania = temp;
			plik.ignore(); // Pomini�cie kropki
			plik >> temp;
			l.dzien = temp;
			plik.ignore();
			plik >> temp;
			plik.ignore();
			l.miesiac = temp;
			plik >> l.rok;
			for (int i = 0; i<ile; i++)
			{
				plik >> temp;
				l.Wyniki[i] = temp;
				if (i == ile - 1)
					break;
				plik.ignore();
			}
			bin.write(reinterpret_cast<char*>(&l), sizeof(l));
		}
	}
	bin.clear();
	return l.nrLosowania;
}
/*============================================================================  TABLICA KROTNOSC  =======================================================================================*/
template<class TypStruktury>
void LotekS<TypStruktury>::TablicaKrotnosc() // metoda wype�niaj�ca tablic� Krotno��; Je�li pierwszy element tej tablicy ( o indeksie 0) ma warto�� zero to tablica jeszcze nie jest wype�niona. Pozosta�e elementy(o indeksach od 1 do 49) okre�laj� cz�stotliwo�� wyst�powania liczb w losowaniach(tzn.warto�� elementu o indeksie i m�wi ile razy liczba i by�a wylosowana);
{
	if (ok)
	{
		TypStruktury L;
		bin.seekg(0);
		while (bin.read(reinterpret_cast <char*> (&L), sizeof(L)))  //Sczytanie z pliku bin struktury L o d�ugo�ci L
		{
			for (char i = 0; i < ile; i++)
				Krotnosc[L.Wyniki[i]]++;
		}
		Krotnosc[0] = 1;
		bin.clear(); //Cofniecie na pocz�tek pliku
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
}
/*=================================================================================  NIEPUSTY  ==========================================================================================*/
template<class TypStruktury>
bool LotekS<TypStruktury>::Niepusty() //metoda daj�ca w wyniku warto�� pola ok;
{
	return ok;
}
/*===============================================================================  NAJRZADZIEJ LOSOWANE  ================================================================================*/
template<class TypStruktury>
void LotekS<TypStruktury>::NajrzadziejLosowane() //metoda wy�wietlaj�ca najrzadziej wylosowane liczby;
{
	if (ok)
	{
		if (Krotnosc[0] == 0)
			TablicaKrotnosc();
		int najm = 1;
		for (int i = 2; i <= ile; i++)
			if (Krotnosc[i] <= Krotnosc[najm])
				najm = i;
		cout << "Najrzadziej losowane liczby: \n";
		for (int i = 1; i <= najm; i++)
			if (Krotnosc[i] == Krotnosc[najm])
				cout << i << " - " << Krotnosc[i] << " razy\n";
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
}
/*===============================================================================  NAJCZESCIEJ LOSOWANE  ================================================================================*/
template<class TypStruktury>
void LotekS<TypStruktury>::NajczesciejLosowane()//metoda wy�wietlaj�ca najcz�ciej losowane liczby;
{
	if (ok)
	{
		if (Krotnosc[0] == 0)
			TablicaKrotnosc();
		int najw = 1;
		for (int i = 2; i <= ile; i++)
			if (Krotnosc[i] >= Krotnosc[najw])
				najw = i;
		cout << "Najczesciej losowane liczby: \n";
		for (int i = 0; i <= najw; i++)
			if (Krotnosc[i] == Krotnosc[najw])
				cout << i << " - " << Krotnosc[i] << " razy\n";
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
}
/*===============================================================================  CZESTOTNIWOSC  =======================================================================================*/
template<class TypStruktury>
void LotekS<TypStruktury>::Czestotliwosci()  //metoda wy�wietlaj�ca cz�stotliwo�� wyst�powania w losowaniach poszczeg�lnych liczb;
{
	if (ok)
	{
		if (Krotnosc[0] == 0)
			TablicaKrotnosc();
		for (int i = 1; i <= zilu; i++)
		{
			cout << setw(2) << i << setw(4) << Krotnosc[i] << "| ";

			if (i % 10 == 0) cout << endl;
		}
		cout << endl;
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
}
/*==================================================================================  LOSOWANIE NR  =====================================================================================*/
template<class TypStruktury>
void LotekS<TypStruktury>::LosowanieNr(int nrLosowania) // metoda wy�wietlaj�ca zadane parametrem (numer losowania) losowanie;
{
	if (ok)
	{
		TypStruktury L;
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
template<class TypStruktury>
int LotekS<TypStruktury>::IleTakich(short tab[]) //metoda z parametrem b�d�cym tablic� sze�ciu liczb ca�kowitych dwubajtowych; wynikiem funkcji jest liczba m�wi�ca ile by�o losowa� z wynikami jak parametr metody, ponadto metoda wy�wietla te losowania;
{
	int licznik = 0;
	if (ok)
	{
		TypStruktury L;
		bin.seekg(0);
		while (bin.read(reinterpret_cast<char *>(&L), sizeof(L)))
		{
			if (tab[0] == L.Wyniki[0] && tab[1] == L.Wyniki[1] && tab[2] == L.Wyniki[2] && tab[3] == L.Wyniki[3] && tab[4] == L.Wyniki[4] && tab[5] == L.Wyniki[5])
			{
				licznik++;
				cout << L;
			}
		}
		bin.clear();
	}
	else
	{
		cout << "Nie mozna wykonywac operacji na pliku binarnym!" << endl;
	}
	return licznik;
}
/*==================================================================================  WYBIERZ DO PLIKU  =================================================================================*/
template<class TypStruktury>
void LotekS<TypStruktury>::WybierzDoPliku(short rok, short miesiac) //metoda tworzy plik tekstowy o nazwie LTrrrrmm.txt i zapisuje do niego wyniki losowa� z zadanego roku i miesi�ca; je�li miesi�c jest zerowy to z ca�ego roku;
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
		TypStruktury L;
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