// ONP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

//====================================================  KLASA STOS  ==================================================
template <class T>
class STOS
{
	struct wezel // blok/cegie³ka, która bêdzie nam przechowywa³a na stosie dan¹ oraz wskaŸnik do nastêpnego elementu;
	{
		T dana; //wartoœæ przechowywana w wêŸle;
		wezel *nast; //wskaŸnik do nastepnego elementu;
		wezel(T x, wezel *pointer) //two¿enie elementu o wartoœci "z" i po³¹czenie wskaŸnikiem poprzedniego elementu z obecnym ;
		{
			dana = x;
			nast = pointer;
		}
	};
	wezel *head; //wskaŸnik na wierzcho³ek/szczyt stosu;
public:
	STOS() { head = NULL; } //Utworzenie pustego stosu ;
	bool Pusty()const { return head == NULL; } //sprawdzenie czy stos jest pusty;
	void DoStosu(T d) { head = new wezel(d, head); } // Dodanie elementu do stosu;
	T ZeStosu(); // Zrzucenie elementu ze stosu i zwrócenie jej wartoœci o typie T;
	~STOS(); // Usuniêcie stosu z zawartoœci¹;
};
//====================================================  KLASA ONP  ===================================================
class ONP
{
	STOS <int> st;
	string linia; //zmoemma robocza;
	void UsunSpacje(); //Usiñ spacje wod¹ce;
	void WykonajDzialanie(char);
public:
	int WartoscONP(const string &);
};

int main()
{
	fstream dane("ONP.txt");
	if (dane)
	{
		ONP onp;
		string linia;
		getline(dane, linia);
		while (dane)
		{
			if (linia.length() > 0)
			{
				cout << linia + " : ";
				try
				{
					cout << onp.WartoscONP(linia);
				}
				catch(exception &e)
				{
					cout << e.what() << endl;
				}
			}
			getline(dane, linia);
		}
		dane.close();
	}


	system("pause");
	return 0;
}


//--------------------------------------------------------------------------------------------------------------------
//====================================================  METODY KLASY STOS  ===========================================
//--------------------------------------------------------------------------------------------------------------------

//====================================================  DESTRUKTOR ~STOS  ============================================
template<class T>
STOS<T>::~STOS()
{
	while (!Pusty()) //Jeœli stos nie jest pusty
		ZeStosu(); //, to zdejmij element ze stosu
}
//====================================================  METODA ZESTOSU  ==============================================
template<class T>
T STOS<T>::ZeStosu()
{
	if (head == NULL)
		throw out_of_range("Stos pusty");
	T wynik = head->dana; //przypisanie wartoœci do wyniku;
	wezel *pom = head; //stwo¿enie zmiennej pomoczniczej z wartoœci¹ pocz¹tkow¹ head;
	head = head->nast; //przypisanie do nastêpnego (tego poni¿ej od obecnego) g³owy/wierzcho³ka (nadanie mu wartoœci pierwszego elementu na stosie);
	delete pom; //Usuniêcie elementu który by³ wierzcho³kiem stosu;
	return wynik; //Zwrócenie wartoœci usunientego ju¿ elementu
}
//--------------------------------------------------------------------------------------------------------------------
//====================================================  METODY KLASY ONP  ============================================
//--------------------------------------------------------------------------------------------------------------------

//====================================================  METODA UsunSpacje  ===========================================
void ONP::UsunSpacje()
{
	while (linia.length() > 0 && linia[0] == ' ')
		linia.erase(0, 1);
}
//====================================================  METODA WykonajDzialanie  =====================================
void ONP::WykonajDzialanie(char dz)
{
	int arg1, arg2, wynik;
	if (st.Pusty())
		throw out_of_range("Zabraklo liczb na stosie");
	arg2 = st.ZeStosu();
	if (st.Pusty())
		throw out_of_range("Zabraklo liczb na stosie");
	arg1 = st.ZeStosu();
	switch (dz)
	{
	case '+': wynik = arg1 + arg2;
		break;
	case '-': wynik = arg1 - arg2;
		break;
	case '*': wynik = arg1 * arg2;
		break;
	default:
		if (arg2 == 0)
		{
			while (!st.Pusty())
				st.ZeStosu();
			throw invalid_argument("Zero dla / lub %");
		}
		if (dz == '/')
			wynik = arg1 / arg2;
		else
			wynik = arg1 % arg2;
	}
	st.DoStosu(wynik);
}
//====================================================  METODA WartoscONP  ===========================================
int ONP::WartoscONP(const string & wyrazenie)
{
	linia = wyrazenie;
	UsunSpacje();
	while (linia.length() > 0)
	{
		string elementONP;
		int n = linia.find(' ');
		if (n > 0)
			elementONP = linia.substr(0, n);
		else
			elementONP = linia;
		if (elementONP[0] >= '0' && elementONP[0] <= '9')
			st.DoStosu(atoi(elementONP.c_str()));
		else
			WykonajDzialanie(elementONP[0]);
		linia.erase(0, n);
		UsunSpacje();
	}
	if (st.Pusty())
		throw invalid_argument("Brak ONP");
	int rob = st.ZeStosu();
	if (!st.Pusty())
		throw invalid_argument("Niepoprawne ONP");
	return rob;
}
