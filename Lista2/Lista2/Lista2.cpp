#include "stdafx.h"
#include <iostream>
using namespace std;

//============================================================================================================================================== Class Lista2  ============================================================;
template<class T>
class Lista2 //Lista dwukierunkowa
{
protected:
	//================================================  WezelListy2  ============================================================
	struct WezelListy2
	{
		T dane; //Warto�� elementu Listy dwukierunkowej
		WezelListy2 *poprz, *nast;  //wska�nik na lewy oraz prawy element Listy dwukierunkowej
		WezelListy2(const T d, WezelListy2 *p = NULL, WezelListy2 *n = NULL)
		{
			dana = d;
			poprz = p;
			nast = n;
		}
	};
	//===========================================================================================================================
public:
	typedef WezelListy2 * WskListy2;
	Lista2(); //Kostruktor Listy dwukierunkowej
	~Lista2(); //Destruktor Listy dwukierunkowej
	void Wstaw(T); //Wstawia do Listy dwukierunkowej element podany w parametrze i wstawia go zale�nie od warto�ci (najwi�ksze elementy z ty�u)
	bool Usun(T); //Usuwa z Listy dwukierunkowej element podany w parametrze
	bool Pusta()const; //Sprawdza czy Lista dwukierunkowa jest pusta, wtedy zwraca TRUE
	void Pisz()const; //Wy�wietla wszystkie elementy Listy dwukierunkowej
protected:
	WskListy2 Pierwszy; //Wska�nik na pierwszy element Listy dwukierunkowej
	WskListy2 Znajdz(const T &); //Szuka w Liscie dwukierunkowej elementu podanego jako parametr i zwraca jego warto��
	WskListy2 NowyWezel(const T d, WskListy2 p = NULL, WskListy2 n = NULL); //Tworzy nowy element Listy dwukierunkowej z elementami podanymi w parametrach, tj.  d-warto��, p-wska�nik na poprzedni element listy, n-wska�nik na nast�pny element listy
};
//==============================================================================================================================================  MAIN  ===================================================================
int main()
{
    return 0;
}

//==============================================================================================================================================  Konstruktor Lista2  =====================================================
template<class T>
Lista2<T>::Lista2()
{
	Pierwszy = NULL; //Ustawia pierwszy element Listy dwukierunkowej na pusty (NULL)
}
//==============================================================================================================================================  Destruktor Lista2  ======================================================
template<class T>
Lista2<T>::~Lista2()
{
	if (!Pusta()) //Sprawdza czy jest w og�le sens usuwa�(po co usuwa� co� z pustej listy)
	{
		WskListy2 rob = Pierwszy; //element pomoczniczy do usuwania
		while (Pierwszy != NULL) //dop�ki pierwszy element nie b�dzie pusty, to...
		{
			Pierwszy = Pierwszy->nast; //przechodzi na nast�pny element listy
			delete rob; //usuwa element pomoczniczy, kt�ry jest pierwszym elementem w li�cie
			rob = Pierwszy; //ustawia element pomoczniczy na pierwszy element w li�cie
		}
	}
}
//==============================================================================================================================================  Wstaw  ==================================================================
template<class T>
void Lista2<T>::Wstaw(T d)
{
	if (Pusta()) //je�li lista jest pusta, to...
		Pierwszy = NowyWezel(d); //tworzy element jako pierwszy na li�cie
	else
		if (Pierwszy->dane > d) //je�eli wstawiany element jest mniejszy ni� pierwszy element w li�cie, to wstaw go na pocz�tek
		{
			Pierwszy = NowyWezel(d, NULL, Pierwszy); //przypisz do pierwszego elementu w li�cie, element, kt�ry b�dzie mia� warto�� zmiennej d, jego poprzedni element b�dzie pusy, a nast�pnym elementem b�dzie pierwszy element w li�cie(czyli ju� drugi)
			Pierwszy->nast->poprz = Pierwszy; //powedz elementowi, kt�ry przed chwil� by� pierwszym elementem w li�cie, �e jego poprzednik jest pierwszym elementem w li�cie
		}
		else //je�eli wstawiany element jest wi�kszy ni� pierwszy, to...
		{
			WskListy2 rob = Pierwszy; //ustaw pomocznicz� zmienna na pierwszy element z listy
			while (rob->nast != NULL && rob->nast->dane < d) //szukaj elementu dop�ki nast�pny element od obecnego b�dzie pusty(ko�iec listy) lub nast�pny element b�dzie mniejszy od wstawianego
				rob = rob->nast; //przejd� do nast�pnego elementu w li�cie(w prawo)
			//wyszli�my z p�tli czyli mamy ju� miejsce dla naszego elementu
			WskListy2 nowy = NowyWezel(d, rob, rob->nast); //utw�rz nowy element, kt�ry b�dzie mia� warto�� d, jego poprzednim elementem b�dzie rob, a nast�pnym element po prawej rob (czyli wci�nij si� pomi�czy roba a jego nast�pny element)
			if (rob->nast != NULL) //je�li element po prawej rob'a, i teraz po prawej naszego nowego elementu, nie jest pusty, to...
				rob->nast->poprz = nowy; //... powedz temu elementowi �e jego poprzednikiem b�dzie nowo utworzony element
			rob->nast = nowy; // a je�eli jest pusty to poprostu wstaw tam nowo utworzony element
		}
}
//==============================================================================================================================================  Usun  ===================================================================
template<class T>
bool Lista2<T>::Usun(T d)
{
	WskListy2 usuwany; //stw�rz pomocznicz� zmienna o nazwie "usuwany" i ...
	usuwany = Znajdz(d); //... znajd� warto�� w li�cie, kt�r� chcemy usun��, a nast�pnie podpisz ca�y element zawieraj�cy t� warto�� pod zmienn�

	if (usuwany == NULL) //je�eli taki element nie istnieje w li�cie
		return false; //to zwr�� falsz
	WskListy2 p, l; //utw�rz dwie zmienne pomocznicze "p" i "l", dalej b�d� zwane jako "prawy" i "lewy"
	l = usuwany->poprz; //podpisz pod lewy, element po lewej od usuwanego  } Operacja jest potrzebna po to by "zasklepi� dziur�" po usuni�ciu elementu
	p = usuwany->nast; //podpisz pod prawy, element po prawej od usuwanego }
	delete usuwany; //usu� element
	if (l != NULL) //sprawdzamy czy po lewej elementu usuni�tego kto� jest
		l->nast = p; //je�li jest to nastepnym elementem b�dzie "p", czyli prawy element od usuni�tego
	else
		Pierwszy = p; //je�li element po lewej usuni�tego jest pusty(przypadek gdy usuwany jest pierwszym elementem listy), to teraz "p", czyli prawy element od usuni�tego, b�dzie pierwszym elementem w li�cie
	if (p != NULL) //Sprawdzamy czy po prawej elementu usuni�tego kto� jest
		p->poprz = l; //je�li jest, to jego poprzednikiem b�dzie "l", czyli lewy element od usuni�tego
	return true; //je�eli element po prawej od uwusni�tego jest pusty(przypadek gdy usuwany element jest ostatnim elementem w li�cie), to zwr�� TRUE, czyli usuwanie si� powiod�o
}
//==============================================================================================================================================  Znajdz  =================================================================
template<class T>
Lista2<T>::WskListy2 Lista2<T>::Znajdz(const T &d)
{
	if (Pierwsza == NULL) //je�eli Pierwszy element w li�cie jest pusty, to...
		return NULL; // nie ma czego szuka�, wi�c zwr�c NULL
	WskListy2 rob = Pierwszy; //stw�rz zmienn� pomocnicz� zawieraj�c� pierwszy element listy
	while (rob != NULL & rob->dane < d) //szukaj elementu dop�ki dojdziesz do pustego (ko�ca listy) lub element szukany jest wi�kszy od obecnego
		rob = rob->nast; //przejd� do nast�pnego elementu w li�cie(w prawo)
	//wyszli�my z p�tli czyli znale�li�my nasz element lub doszli�my do ko�ca listy
	if (rob == NULL || rob->dane < d) //je�eli doszli�my do ko�ca listy lub obecny element jest mniejszy od szukanego
		return NULL; //to zwr�� NULL, czyli brak elementu
	return rob; //je�li nei to zwr�� szukany element
}
//==============================================================================================================================================  NowyWezel  ==============================================================;
template<class T>
Lista2<T>::WskListy2 Lista2<T>::NowyWezel(T d, WskListy2 p, WskListy2 n)
{
	return new WezelListy2(d, p, n);
}