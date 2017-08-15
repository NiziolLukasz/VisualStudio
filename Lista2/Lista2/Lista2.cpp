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
		T dane; //Wartoœæ elementu Listy dwukierunkowej
		WezelListy2 *poprz, *nast;  //wskaŸnik na lewy oraz prawy element Listy dwukierunkowej
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
	void Wstaw(T); //Wstawia do Listy dwukierunkowej element podany w parametrze i wstawia go zale¿nie od wartoœci (najwiêksze elementy z ty³u)
	bool Usun(T); //Usuwa z Listy dwukierunkowej element podany w parametrze
	bool Pusta()const; //Sprawdza czy Lista dwukierunkowa jest pusta, wtedy zwraca TRUE
	void Pisz()const; //Wyœwietla wszystkie elementy Listy dwukierunkowej
protected:
	WskListy2 Pierwszy; //WskaŸnik na pierwszy element Listy dwukierunkowej
	WskListy2 Znajdz(const T &); //Szuka w Liscie dwukierunkowej elementu podanego jako parametr i zwraca jego wartoœæ
	WskListy2 NowyWezel(const T d, WskListy2 p = NULL, WskListy2 n = NULL); //Tworzy nowy element Listy dwukierunkowej z elementami podanymi w parametrach, tj.  d-wartoœæ, p-wskaŸnik na poprzedni element listy, n-wskaŸnik na nastêpny element listy
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
	if (!Pusta()) //Sprawdza czy jest w ogóle sens usuwaæ(po co usuwaæ coœ z pustej listy)
	{
		WskListy2 rob = Pierwszy; //element pomoczniczy do usuwania
		while (Pierwszy != NULL) //dopóki pierwszy element nie bêdzie pusty, to...
		{
			Pierwszy = Pierwszy->nast; //przechodzi na nastêpny element listy
			delete rob; //usuwa element pomoczniczy, który jest pierwszym elementem w liœcie
			rob = Pierwszy; //ustawia element pomoczniczy na pierwszy element w liœcie
		}
	}
}
//==============================================================================================================================================  Wstaw  ==================================================================
template<class T>
void Lista2<T>::Wstaw(T d)
{
	if (Pusta()) //jeœli lista jest pusta, to...
		Pierwszy = NowyWezel(d); //tworzy element jako pierwszy na liœcie
	else
		if (Pierwszy->dane > d) //je¿eli wstawiany element jest mniejszy ni¿ pierwszy element w liœcie, to wstaw go na pocz¹tek
		{
			Pierwszy = NowyWezel(d, NULL, Pierwszy); //przypisz do pierwszego elementu w liœcie, element, który bêdzie mia³ wartoœæ zmiennej d, jego poprzedni element bêdzie pusy, a nastêpnym elementem bêdzie pierwszy element w liœcie(czyli ju¿ drugi)
			Pierwszy->nast->poprz = Pierwszy; //powedz elementowi, który przed chwil¹ by³ pierwszym elementem w liœcie, ¿e jego poprzednik jest pierwszym elementem w liœcie
		}
		else //je¿eli wstawiany element jest wiêkszy ni¿ pierwszy, to...
		{
			WskListy2 rob = Pierwszy; //ustaw pomocznicz¹ zmienna na pierwszy element z listy
			while (rob->nast != NULL && rob->nast->dane < d) //szukaj elementu dopóki nastêpny element od obecnego bêdzie pusty(koñiec listy) lub nastêpny element bêdzie mniejszy od wstawianego
				rob = rob->nast; //przejdŸ do nastêpnego elementu w liœcie(w prawo)
			//wyszliœmy z pêtli czyli mamy ju¿ miejsce dla naszego elementu
			WskListy2 nowy = NowyWezel(d, rob, rob->nast); //utwórz nowy element, który bêdzie mia³ wartoœæ d, jego poprzednim elementem bêdzie rob, a nastêpnym element po prawej rob (czyli wciœnij siê pomiêczy roba a jego nastêpny element)
			if (rob->nast != NULL) //jeœli element po prawej rob'a, i teraz po prawej naszego nowego elementu, nie jest pusty, to...
				rob->nast->poprz = nowy; //... powedz temu elementowi ¿e jego poprzednikiem bêdzie nowo utworzony element
			rob->nast = nowy; // a je¿eli jest pusty to poprostu wstaw tam nowo utworzony element
		}
}
//==============================================================================================================================================  Usun  ===================================================================
template<class T>
bool Lista2<T>::Usun(T d)
{
	WskListy2 usuwany; //stwórz pomocznicz¹ zmienna o nazwie "usuwany" i ...
	usuwany = Znajdz(d); //... znajdŸ wartoœæ w liœcie, któr¹ chcemy usun¹æ, a nastêpnie podpisz ca³y element zawieraj¹cy t¹ wartoœæ pod zmienn¹

	if (usuwany == NULL) //je¿eli taki element nie istnieje w liœcie
		return false; //to zwróæ falsz
	WskListy2 p, l; //utwórz dwie zmienne pomocznicze "p" i "l", dalej bêd¹ zwane jako "prawy" i "lewy"
	l = usuwany->poprz; //podpisz pod lewy, element po lewej od usuwanego  } Operacja jest potrzebna po to by "zasklepiæ dziurê" po usuniêciu elementu
	p = usuwany->nast; //podpisz pod prawy, element po prawej od usuwanego }
	delete usuwany; //usuñ element
	if (l != NULL) //sprawdzamy czy po lewej elementu usuniêtego ktoœ jest
		l->nast = p; //jeœli jest to nastepnym elementem bêdzie "p", czyli prawy element od usuniêtego
	else
		Pierwszy = p; //jeœli element po lewej usuniêtego jest pusty(przypadek gdy usuwany jest pierwszym elementem listy), to teraz "p", czyli prawy element od usuniêtego, bêdzie pierwszym elementem w liœcie
	if (p != NULL) //Sprawdzamy czy po prawej elementu usuniêtego ktoœ jest
		p->poprz = l; //jeœli jest, to jego poprzednikiem bêdzie "l", czyli lewy element od usuniêtego
	return true; //je¿eli element po prawej od uwusniêtego jest pusty(przypadek gdy usuwany element jest ostatnim elementem w liœcie), to zwróæ TRUE, czyli usuwanie siê powiod³o
}
//==============================================================================================================================================  Znajdz  =================================================================
template<class T>
Lista2<T>::WskListy2 Lista2<T>::Znajdz(const T &d)
{
	if (Pierwsza == NULL) //je¿eli Pierwszy element w liœcie jest pusty, to...
		return NULL; // nie ma czego szukaæ, wiêc zwróc NULL
	WskListy2 rob = Pierwszy; //stwórz zmienn¹ pomocnicz¹ zawieraj¹c¹ pierwszy element listy
	while (rob != NULL & rob->dane < d) //szukaj elementu dopóki dojdziesz do pustego (koñca listy) lub element szukany jest wiêkszy od obecnego
		rob = rob->nast; //przejdŸ do nastêpnego elementu w liœcie(w prawo)
	//wyszliœmy z pêtli czyli znaleŸliœmy nasz element lub doszliœmy do koñca listy
	if (rob == NULL || rob->dane < d) //je¿eli doszliœmy do koñca listy lub obecny element jest mniejszy od szukanego
		return NULL; //to zwróæ NULL, czyli brak elementu
	return rob; //jeœli nei to zwróæ szukany element
}
//==============================================================================================================================================  NowyWezel  ==============================================================;
template<class T>
Lista2<T>::WskListy2 Lista2<T>::NowyWezel(T d, WskListy2 p, WskListy2 n)
{
	return new WezelListy2(d, p, n);
}