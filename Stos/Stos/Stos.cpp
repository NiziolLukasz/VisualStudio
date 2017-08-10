// Stos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

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
	STOS() {	head = NULL;	} //Utworzenie pustego stosu ;
	bool Pusty()const {		return head == NULL;	} //sprawdzenie czy stos jest pusty;
	void DoStosu(T d) { 	head = new wezel(d, head);	} // Dodanie elementu do stosu;
	T ZeStosu(); // Zrzucenie elementu ze stosu i zwrócenie jej wartoœci o typie T;
	~STOS(); // Usuniêcie stosu z zawartoœci¹;
};

int main()
{
	STOS<int> slc; //Stos liczb ca³kowitych;
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


