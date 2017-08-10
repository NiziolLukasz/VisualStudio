// Stos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

template <class T>
class STOS
{
	struct wezel // blok/cegie�ka, kt�ra b�dzie nam przechowywa�a na stosie dan� oraz wska�nik do nast�pnego elementu;
	{
		T dana; //warto�� przechowywana w w�le;
		wezel *nast; //wska�nik do nastepnego elementu;
		wezel(T x, wezel *pointer) //two�enie elementu o warto�ci "z" i po��czenie wska�nikiem poprzedniego elementu z obecnym ;
		{
			dana = x;
			nast = pointer;
		}
	};
	wezel *head; //wska�nik na wierzcho�ek/szczyt stosu;
public:
	STOS() {	head = NULL;	} //Utworzenie pustego stosu ;
	bool Pusty()const {		return head == NULL;	} //sprawdzenie czy stos jest pusty;
	void DoStosu(T d) { 	head = new wezel(d, head);	} // Dodanie elementu do stosu;
	T ZeStosu(); // Zrzucenie elementu ze stosu i zwr�cenie jej warto�ci o typie T;
	~STOS(); // Usuni�cie stosu z zawarto�ci�;
};

int main()
{
	STOS<int> slc; //Stos liczb ca�kowitych;
	for (int i = 10; i < 177; i += 10)
	{
		slc.DoStosu(i++);
	}

	while (!slc.Pusty())
		cout << slc.ZeStosu() << " ";
/*
	STOS<char> zu;
	while (!slc.Pusty())
		zu.DoStosu((char) slc.ZeStosu());
*/
	system("pause");
    return 0;
}

//====================================================  DESTRUKTOR ~STOS  ============================================
template<class T>
STOS<T>::~STOS()
{
	while (!Pusty()) //Je�li stos nie jest pusty
		ZeStosu(); //, to zdejmij element ze stosu
}
//====================================================  METODA ZESTOSU  ==============================================
template<class T>
T STOS<T>::ZeStosu()
{
	if (head == NULL)
		throw out_of_range("Stos pusty");
	T wynik = head->dana; //przypisanie warto�ci do wyniku;
	wezel *pom = head; //stwo�enie zmiennej pomoczniczej z warto�ci� pocz�tkow� head;
	head = head->nast; //przypisanie do nast�pnego (tego poni�ej od obecnego) g�owy/wierzcho�ka (nadanie mu warto�ci pierwszego elementu na stosie);
	delete pom; //Usuni�cie elementu kt�ry by� wierzcho�kiem stosu;
	return wynik; //Zwr�cenie warto�ci usunientego ju� elementu
}


