// QUEUE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

template<class T>
class QUEUE
{
	struct node // blok/cegie�ka, kt�ra b�dzie nam przechowywa�a dan�, oraz wska�nik do nast�pnego elementu w kolejce;
	{
		T data; // warto�� ;
		node *next; // wska�nik do nast�pnego elementu w kolejce;
		node(T x) // konstruktor struktury, kt�ry przypisuje warto�� "x" oraz ustawia koniec olejki na NULL;
		{
			data = x;
			next = NULL;
		}
	};
	typedef node *pnode;
	pnode head, tail;
public:
	QUEUE(); //Konstruktor ustawiaj�cy head na NULL;
	bool empty() const; //Metoda sprawdzaj�ca czy kolejka jest pusta;
	void put(T); //Metoda dodaj�ca nam element typu T na koniec kolejki(tail);
	T get(); //Metoda, kt�ra usuwa nam pierwszy element kolejki(head) i zwracaj�ca jej warto��;
	int wieksze_od(T x); //Metoda kt�ra usuwa elementy wi�ksze ni� zmienna x; Metoda zwraca ilo�� usuni�tych element�w;
	~QUEUE(); //Destruktor
};


int main()
{
	QUEUE<int> k;
	k.put(3);
	k.put(6);
	k.put(1);
	k.put(8);
	k.put(4);
	k.put(3);
	k.put(7);
	k.put(6);
	k.put(9);
	

	system("pause");
    return 0;
}


//====================================================  KONSTRUKTOR QUEUE  ===========================================
template<class T>
QUEUE<T>::QUEUE()
{
	head = NULL;
}
//====================================================  METODA EMPTY  ================================================
template<class T>
bool QUEUE<T>::empty()const
{
	return head == NULL;
}
//====================================================  METODA PUT  ==================================================
template<class T>
void QUEUE<T>::put(T d)
{
	pnode temp = tail;
	tail = new node(d);
	if (head == NULL)// je�li kolejka jest pusta, to
		head = tail; // pocz�tek i koniec jest w stm samym miejscu
	else
		temp->next = tail; // w przeciwnym wypadku do obecnego ogona(temp = tail), przypisz stary ogon(tail)
}
//====================================================  METODA GET  ==================================================
template<class T>
T QUEUE<T>::get()
{
	if (head == NULL) //Sprawdzamy czy kolejka jest pusta
		throw out_of_range("Kolejka jest pusta");
	// je�li nie jest pusta, to przyjmijmy, �e przynajmniej jeden element w kolejce jest
	T temp = head->data;
	pnode p = head->next;
	delete head;
	head = p; //p mo�e by� NULL, bo nie pytam o warto��
	return temp;
}
//====================================================  METODA DEL  ==================================================
template<class T>
int QUEUE<T>::wieksze_od(T x)
{
	QUEUE<T> pom; //Kolejka pomocznicza do przechowywania nie usuni�tych liczb
	T temp; //zmienna pomocznicza do przetrzymywania liczb
	int licznik = 0;
	while (head != NULL) //dop�ki kolejka nie jest pusta
	{
		if (head->data > x)
		{
			temp = get();
			licznik++;
		}
		else
		{
			pom.put(get());
		}
	}
	while (pom.head != NULL)
	{
		put(pom.get());
	}
	return licznik;
}
//====================================================  DESTRUKTOR ~QUEUE  ===========================================
template<class T>
QUEUE<T>::~QUEUE()
{
	T temp;
	while (head != NULL)
		cout<< get();
}



