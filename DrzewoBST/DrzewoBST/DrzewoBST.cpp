// DrzewoBST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

/*=====================================================================================================================================================================  CLASS DrzewoBST  ====================================*/
template <class T>
class DrzewoBST
{/*======================================================================  CLASS Wierzcholek  ==================================*/
	class Wierzcholek
	{
	public:
		Wierzcholek(const T &d) : lewy(NULL), prawy(NULL), dane(d)
		{}
		T dane;
		Wierzcholek *lewy, *prawy;
	};/*========================================================================================================================*/
public:
	DrzewoBST(); //konstruktor drzewa pustego;
	DrzewoBST(const DrzewoBST &); /*konstruktor kopiuj¹cy bez implementacji po to, by nie da³o siê utworzeyæ kopii (taka blokada) |to mówi, ¿e nie chce konstruktora kopiuj¹cego bo bêde mia³ swój, a swój niec nie bedzie robi³|;*/
	bool Wstaw(const T &); //Wstawianie danej do Drzewa;
	void PreOrder()const; //Wyœwietlanie w kolejnoœci: 1. korzeñ; 2.PreOrder lewe poddrzewo; 3.PreOrder prawe poddrzewo;
	void InOrder()const; //Wyœwietlanie w kolejnoœci: 1.InOrder lewe poddrzewo; 2.korzeñ 3.InOrder prawe poddrzewo;
	void PostOrder()const; //Wyœwietlanie w kolejnoœci: 1.PostOrder lewe poddrzewo; 2.PostOrder prawe poddrzewo; 3.korzeñ;
	bool Usun(const T &); //Usuwa wybran¹ dan¹ z Drzewa;
	int ilWierzcholkow(); //Zwraca iloœæ wierzcho³ków;
	int ilLisci(); //Zwraca iloœæ Liœci;
	int WysDrzewa(); //Zwraca wysokoœæ Drzewa;
	int TakieSameWys(); //Zwraca iloœæ takich samych wysokoœci poddrzew;
	int ilWierzcholkowJedenPotomek(); //Wyznacza liczbê wierzcho³ków maj¹cych tylko jednego potomka
	void WyswietlLiscieRosnaco()const; //Wyœwietla liœcie w kolejnoœci rosn¹cej
	void OdwrocDrzewo(); //Odwraca drzewo tzn. dla ka¿dego wierzcho³ka zamieniæ miejscami jego poddrzewa
	~DrzewoBST(); //Destruktor;
protected:
	typedef Wierzcholek * wskw; //wskaŸnik wierzcho³ka;
	wskw korzen;
private:
	bool WstawPom(wskw &, const T &);
	void InOrderPom(wskw)const;
	void PreOrderPom(wskw)const;
	void PostOrderPom(wskw)const;
	void UsunDrzewo(wskw &);
	int ilWierzcholkowPom(wskw);
	int ilLisciPom(wskw);
	int WysDrzewaPom(wskw);
	int TakieSameWysPom(wskw);
	int ilWierzcholkowJedenPotomekPom(wskw);
	void WyswietlLiscieRosnacoPom(wskw)const;
	void OdwrocDrzewoPom(wskw);
};

/*=====================================================================================================================================================================  MAIN  =================================================*/
int main()
{
	DrzewoBST<int> d;

	d.Wstaw(44);
	d.Wstaw(33);
	d.Wstaw(77);
	d.Wstaw(88);
	d.Wstaw(66);
	d.Wstaw(40);
	d.Wstaw(50);
	d.Wstaw(70);
	d.Wstaw(20);
	d.Wstaw(30);
	d.Wstaw(10);
	d.Wstaw(100);
	
	cout << "PreOrder: ";
	d.PreOrder();
	cout << endl << "InOrder: ";
	d.InOrder();
	cout << endl << "PostOrder: ";
	d.PostOrder();

	/*d.PreOrder();
	d.OdwrocDrzewo();
	cout << endl;
	d.PreOrder();*/
	cout << endl;
	system("pause");
    return 0;
}

/*=====================================================================================================================================================================  Konstruktor  ========================================*/
template<class T>
DrzewoBST<T>::DrzewoBST()
{
	korzen = NULL; //Tworzy puste drzewo;
}
/*=====================================================================================================================================================================  Wstaw  ==============================================*/
template<class T>
bool DrzewoBST<T>::WstawPom(wskw &w, const T &d)
{
	if (w == NULL) //jeœli wierzcho³ek jest pusty to wstaw dan¹;
	{
		wskw pom;
		try
		{
			pom = new Wierzcholek(d);
			w = pom;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	else //jeœli wierzcho³ek nie jest pusty to ...;
	{
		if (d < w->dane) //sprawdŸ czy dana jest mniejsza od aktualnego wierzcho³ka;
			return WstawPom(w->lewy, d); //jeœli jest, to przejdŸ w lewo od wierzcho³ka;
		else
			if (w->dane < d) //sprawdŸ czy dana jest wiêksza od aktualnego wierzcho³ka;
				return WstawPom(w->prawy, d); //jeœli jest, to przejdŸ w prawo od wierzcho³ka;
			else
				return false; //jeœli dana jest równa wierzcho³kowi, to zakoñcz funkcje (Drzewo nie przyjmuje duplikatów)
	}
}
/////////////////////////////////////////////////////
template<class T>
bool DrzewoBST<T>::Wstaw(const T &d)
{
	return WstawPom(korzen, d);
}
/*=====================================================================================================================================================================  UsunDrzewo  =========================================*/
template<class T>
void DrzewoBST<T>::UsunDrzewo(wskw &w)
{
	if (w != NULL) //jeœli drzewo/wierzcho³ek istnieje to;
	{
		UsunDrzewo(w->lewy); //przejdŸ najbardziej na lewo;
		UsunDrzewo(w->prawy); //potem najbardziej na prawo;
		delete w; //usuñ dany wierzcho³ek;
		w = NULL; //nadaj mu wartoœæ NULL/pust¹;
	}
}
/*=====================================================================================================================================================================  Destruktor  =========================================*/
template<class T>
DrzewoBST<T>::~DrzewoBST()
{
	UsunDrzewo(korzen);
}
/*=====================================================================================================================================================================  PreOrder  =============================================*/
template<class T>
void DrzewoBST<T>::PreOrderPom(wskw w)const
{
	if (w != NULL)
	{
		cout << w->dane << " ";
		PreOrderPom(w->lewy);
		PreOrderPom(w->prawy);
	}
}
///////////////////////////////////////////////////
template<class T>
void DrzewoBST<T>::PreOrder()const
{
	PreOrderPom(korzen);
}
/*====================================================================================================================================================================  PostOrder  =============================================*/
template<class T>
void DrzewoBST<T>::PostOrderPom(wskw w)const
{
	if (w != NULL)
	{
		PostOrderPom(w->lewy);
		PostOrderPom(w->prawy);
		cout << w->dane << " ";
	}
}
////////////////////////////////////////////////
template <class T>
void DrzewoBST<T>::PostOrder()const
{
	PostOrderPom(korzen);
}
/*=====================================================================================================================================================================  InOrder  ==============================================*/
template<class T>
void DrzewoBST<T>::InOrderPom(wskw w)const
{
	if (w != NULL)
	{
		InOrderPom(w->lewy);
		cout << w->dane << " ";
		InOrderPom(w->prawy);
	}
}
/////////////////////////////////////////////////////
template<class T>
void DrzewoBST<T>::InOrder()const
{
	InOrderPom(korzen);
}
/*=====================================================================================================================================================================  Usun  =================================================*/
template<class T>
bool DrzewoBST<T>::Usun(const T &d)
{
	wskw rodzic, usuwany, zamienny;
	usuwany = korzen; //na pocz¹tku zaczynamy szukaæ od korzenia;
	rodzic = NULL; //ustawiamy rodzica aktualnie wskazywanego miejsca na NULL (korzen nie ma rodzica bo jest pierwszy);
	while (usuwany != NULL && usuwany->dane != d) //dopóki usuwany nie jest koñcem i usuwany nie jest szukan¹ dan¹;
	{
		rodzic = usuwany; //rodzicem bêdzie nasz podejrzany;
		if (d < rodzic->dane) //sprawdzamy w któr¹ strone warto pójœæ by znaleŸæ dan¹ (drzewo jest przecierz posortowane);
			usuwany = rodzic->lewy; //w lewo gdy "dana_szukana < dana_obecna";
		else
			usuwany = rodzic->prawy; //w prawo gdy "dana_szukana > dana_obecna";
	}//wiemy ju¿ w którym miejscu jest element do usuniêcia
	if (usuwany == NULL) return false; //sprawdzamy czy znaleziono, jak nie to koñczymy;
	if (usuwany->lewy == NULL && usuwany->prawy == NULL) //sprawdzamy czy jesteœmy w liœciu;
	{
		if (rodzic == NULL) //sprawdzamy czy usuwany element jest korzeniem (tzn. ¿e nawet nie weszliœmy do while);
			korzen = NULL; //nie ma drzewa;
		else
			if (rodzic->lewy == usuwany) //sprawdzamy czy usuwamy lew¹ stronê poddrzewa;
				rodzic->lewy = NULL;
			else
				rodzic->prawy = NULL; //jak nie jest lewym poddrzewem, no to jest prawym;
		delete usuwany;
	}
	else //usuwanym elementem nie jest jednak liœæ;
	{
		if (usuwany->lewy == NULL || usuwany->prawy == NULL) //pytamy czy mamy przynajmniej jedn¹ pust¹ ga³¹Ÿ/krawêdŸ (przypadek z poddrzewem);
		{
			if (usuwany->lewy == NULL) //sprawdzamy czy lewe poddrzewo jest puste (nie ma go);
				zamienny = usuwany->prawy; //brak lewego poddrzewa, wiêc idzemy w prawo;
			else
				zamienny = usuwany->lewy; //istnieje lewe poddrzewo, wiêc idzemy w lewo;
			*usuwany = *zamienny; //przekopiuj bajt po bajcie (dos³ownie wszystko);
		}// to by³o z jednym poddrzewem;
		else // z dwoma poddrzewami;
		{// wiemy ¿e mamy 2 rozga³êzienia, bo ani prawy, ani lewy nie jest pusty;
			rodzic = usuwany;
			zamienny = rodzic->lewy; //przechodzimy o jeden w lewo i;
			while (zamienny->prawy != NULL) //szukamy najwiêkszego elementu po prawej stronie, po to by podmieniæ pod element usuwany;
			{
				rodzic = zamienny; //po to, by wiedzieæ co jest wy¿ej zmiennej, która zniknie;
				zamienny = zamienny->prawy; //przesuwamy siê o jeden w prawo
			}
			usuwany->dane = zamienny->dane; //podmieniamy najwiêksz¹ dan¹ po lewej stronie usuwanego elementu, by drzewo mia³o dlasz¹ zgodnoœæ;
			if (rodzic == usuwany) //sprawdzamy czy pêtla while w ogóle ruszy³a;
				rodzic->lewy = zamienny->lewy; /*jeœli nie ruszy³a, to element(Z), po lewej usuwanego(U), jest tym najwiêkszym, wiêc mówimy rodzicowi(R) tego elementu(Z), który zniknie, ¿e jego potomkiem bêdzie element(P) o jeden dalej {(R=U -> Z -> P -> ...) -> (R=U -> P -> ...)} (jeœli taki element nie istnieje to bêdze NULL); */
			else 
				rodzic->prawy = zamienny->lewy; /*jeœli ruszy³a, to teraz elementem po prawej od rodzica, bêdzie (jeœli taki istnieje) element,który by³ po lewej zamiennego;*/
		}
		delete zamienny; //usuwamy element, który podmieniliœmy pod usuwany;
		return true; //usuwanie siê powiod³o;
	}
	
	
	
	//jeszcze jakieœ usuwanie z prawej strony ale nie wiem gdzie
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}
/*=====================================================================================================================================================================  ilWierzcholkow  =======================================*/
template<class T>
int DrzewoBST<T>::ilWierzcholkowPom(wskw w)
{
	if (w == NULL) return 0;
	return 1 + ilWierzcholkowPom(w->lewy) + ilWierzcholkowPom(w->prawy);
}
/////////////////////////////////////////////////////////
template<class T>
int DrzewoBST<T>::ilWierzcholkow()
{
	return ilWierzcholkowPom(korzen);
}
/*=====================================================================================================================================================================  ilLisci  ==============================================*/
template<class T>
int DrzewoBST<T>::ilLisciPom(wskw w)
{
	if (w == NULL) return 0;
	else if (w->lewy == NULL && w->prawy == NULL) //sprawdz czy jest liœciem;
		return 1;
	return ilLisciPom(w->lewy) + ilLisciPom(w->prawy);
}
////////////////////////////////////////////////////////////
template<class T>
int DrzewoBST<T>::ilLisci()
{
	return ilLisciPom(korzen);
}
/*=====================================================================================================================================================================  WysDrzewa  ============================================*/
template<class T>
int DrzewoBST<T>::WysDrzewaPom(wskw w)
{
	if (w == NULL) return 0;
	if (w->lewy == NULL && w->prawy == NULL) return 0; //sprawdz czy jest liœciem;
	int hl = WysDrzewaPom(w->lewy); //oblicz wysokoœæ lewego poddrzewa; 
	int hp = WysDrzewaPom(w->prawy); //oblicz wysokoœæ prawego pddrzewa;
	if (hl > hp) //sprawdz które poddrzewo dalej siêga (jest wy¿sze);
		return hl + 1;
	else return 1 + hp;
}
////////////////////////////////////////////////////////////
template<class T>
int DrzewoBST<T>::WysDrzewa()
{
	return WysDrzewaPom(korzen);
}
/*=====================================================================================================================================================================  TakieSameWys  =========================================*/
template<class T>
int DrzewoBST<T>::TakieSameWysPom(wskw w)
{
	if (w == NULL) return 0;
	if (w->lewy == NULL && w->prawy == NULL) return 0; //sprawdz czy jest liœciem;
	int l = 0; //licznik;
	int hl = WysDrzewaPom(w->lewy); //oblicz wysokoœæ lewego poddrzewa; 
	int hp = WysDrzewaPom(w->prawy); //oblicz wysokoœæ prawego pddrzewa;
	if (hp == hl && hp != 0) //sprawdza czy wysokoœci s¹ równe oraz czy nie stane³o na korzeniu;
		l++; //jeœli nie to powieksz iloœæ takich samych wysokoœci o jeden;
	return l + TakieSameWysPom(w->lewy) + TakieSameWysPom(w->prawy);
}
////////////////////////////////////////////////////////////
template<class T>
int DrzewoBST<T>::TakieSameWys()
{
	return TakieSameWysPom(korzen);
}
/*=====================================================================================================================================================================  ilWierzcholkowJedenPotomek  =========================*/
template<class T>
int DrzewoBST<T>::ilWierzcholkowJedenPotomekPom(wskw w)
{
	if (w == NULL) return 0;
	if (w->lewy == NULL && w->prawy == NULL) return 0; //sprawdz czy jest lisciem;
	if ((w->lewy == NULL && w->prawy != NULL) || (w->lewy != NULL && w->prawy == NULL))
		return 1;
	return ilWierzcholkowJedenPotomekPom(w->lewy) + ilWierzcholkowJedenPotomekPom(w->prawy);
}
////////////////////////////////////////////////////////////
template<class T>
int DrzewoBST<T>::ilWierzcholkowJedenPotomek()
{
	return ilWierzcholkowJedenPotomekPom(korzen);
}

/*=====================================================================================================================================================================  LiscieRosnaco  ======================================*/
template<class T>
void DrzewoBST<T>::WyswietlLiscieRosnacoPom(wskw w)const
{
	if (w != NULL)
	{
		WyswietlLiscieRosnacoPom(w->lewy); //przejdŸ najbardziej w lewo;
		WyswietlLiscieRosnacoPom(w->prawy); //a potem najbardziej w prawo (Teraz jesteœmy w najmniejszej wielkoœci w drzewie); 
		if (w->prawy == NULL && w->lewy == NULL)
			cout << w->dane << " "; //wyœwietl wartoœæ
	}
}
////////////////////////////////////////////////////////////
template<class T>
void DrzewoBST<T>::WyswietlLiscieRosnaco()const
{
	WyswietlLiscieRosnacoPom(korzen);
}
/*=====================================================================================================================================================================  OdwrocDrzewo  =======================================*/
template<class T>
void DrzewoBST<T>::OdwrocDrzewoPom(wskw w)
{
	if (w != NULL)
	{
		OdwrocDrzewoPom(w->lewy); //przejdŸ najbardziej po lewo;
		OdwrocDrzewoPom(w->prawy); //przejdŸ najbardziej po prawo;
		if (w->lewy != NULL && w->prawy == NULL) //jeœli dany wierzcho³ek ma jedno poddrzewo po lewej;
		{
			w->prawy = w->lewy; //teraz prawe poddrzewo bêdzie lewym;
			w->lewy = NULL; //teraz lewe bêdzie puste;
		}
		if (w->lewy == NULL && w->prawy != NULL) //jeœli dany wierzcho³ek ma jedno poddrzewo po prawej;
		{
			w->lewy = w->prawy; //teraz lewe poddrzewo bêdzie prawym;
			w->prawy = NULL; //teraz prawe bêdzie puste;
		}
		if (w->lewy != NULL && w->prawy != NULL) //jeœli dany wierzcho³ek ma dwa poddrzewa;
		{
			wskw temp = w->lewy;  //
			w->lewy = w->prawy;  //  Zamiana poddrzew ze sob¹;
			w->prawy = temp;    //
		}
	}
}
////////////////////////////////////////////////////////////
template<class T>
void DrzewoBST<T>::OdwrocDrzewo()
{
	OdwrocDrzewoPom(korzen);
}