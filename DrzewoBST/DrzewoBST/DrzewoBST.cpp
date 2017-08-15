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
	DrzewoBST(const DrzewoBST &); /*konstruktor kopiuj�cy bez implementacji po to, by nie da�o si� utworzey� kopii (taka blokada) |to m�wi, �e nie chce konstruktora kopiuj�cego bo b�de mia� sw�j, a sw�j niec nie bedzie robi�|;*/
	bool Wstaw(const T &); //Wstawianie danej do Drzewa;
	void PreOrder()const; //Wy�wietlanie w kolejno�ci: 1. korze�; 2.PreOrder lewe poddrzewo; 3.PreOrder prawe poddrzewo;
	void InOrder()const; //Wy�wietlanie w kolejno�ci: 1.InOrder lewe poddrzewo; 2.korze� 3.InOrder prawe poddrzewo;
	void PostOrder()const; //Wy�wietlanie w kolejno�ci: 1.PostOrder lewe poddrzewo; 2.PostOrder prawe poddrzewo; 3.korze�;
	bool Usun(const T &); //Usuwa wybran� dan� z Drzewa;
	int ilWierzcholkow(); //Zwraca ilo�� wierzcho�k�w;
	int ilLisci(); //Zwraca ilo�� Li�ci;
	int WysDrzewa(); //Zwraca wysoko�� Drzewa;
	int TakieSameWys(); //Zwraca ilo�� takich samych wysoko�ci poddrzew;
	int ilWierzcholkowJedenPotomek(); //Wyznacza liczb� wierzcho�k�w maj�cych tylko jednego potomka
	void WyswietlLiscieRosnaco()const; //Wy�wietla li�cie w kolejno�ci rosn�cej
	void OdwrocDrzewo(); //Odwraca drzewo tzn. dla ka�dego wierzcho�ka zamieni� miejscami jego poddrzewa
	~DrzewoBST(); //Destruktor;
protected:
	typedef Wierzcholek * wskw; //wska�nik wierzcho�ka;
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
	if (w == NULL) //je�li wierzcho�ek jest pusty to wstaw dan�;
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
	else //je�li wierzcho�ek nie jest pusty to ...;
	{
		if (d < w->dane) //sprawd� czy dana jest mniejsza od aktualnego wierzcho�ka;
			return WstawPom(w->lewy, d); //je�li jest, to przejd� w lewo od wierzcho�ka;
		else
			if (w->dane < d) //sprawd� czy dana jest wi�ksza od aktualnego wierzcho�ka;
				return WstawPom(w->prawy, d); //je�li jest, to przejd� w prawo od wierzcho�ka;
			else
				return false; //je�li dana jest r�wna wierzcho�kowi, to zako�cz funkcje (Drzewo nie przyjmuje duplikat�w)
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
	if (w != NULL) //je�li drzewo/wierzcho�ek istnieje to;
	{
		UsunDrzewo(w->lewy); //przejd� najbardziej na lewo;
		UsunDrzewo(w->prawy); //potem najbardziej na prawo;
		delete w; //usu� dany wierzcho�ek;
		w = NULL; //nadaj mu warto�� NULL/pust�;
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
	usuwany = korzen; //na pocz�tku zaczynamy szuka� od korzenia;
	rodzic = NULL; //ustawiamy rodzica aktualnie wskazywanego miejsca na NULL (korzen nie ma rodzica bo jest pierwszy);
	while (usuwany != NULL && usuwany->dane != d) //dop�ki usuwany nie jest ko�cem i usuwany nie jest szukan� dan�;
	{
		rodzic = usuwany; //rodzicem b�dzie nasz podejrzany;
		if (d < rodzic->dane) //sprawdzamy w kt�r� strone warto p�j�� by znale�� dan� (drzewo jest przecierz posortowane);
			usuwany = rodzic->lewy; //w lewo gdy "dana_szukana < dana_obecna";
		else
			usuwany = rodzic->prawy; //w prawo gdy "dana_szukana > dana_obecna";
	}//wiemy ju� w kt�rym miejscu jest element do usuni�cia
	if (usuwany == NULL) return false; //sprawdzamy czy znaleziono, jak nie to ko�czymy;
	if (usuwany->lewy == NULL && usuwany->prawy == NULL) //sprawdzamy czy jeste�my w li�ciu;
	{
		if (rodzic == NULL) //sprawdzamy czy usuwany element jest korzeniem (tzn. �e nawet nie weszli�my do while);
			korzen = NULL; //nie ma drzewa;
		else
			if (rodzic->lewy == usuwany) //sprawdzamy czy usuwamy lew� stron� poddrzewa;
				rodzic->lewy = NULL;
			else
				rodzic->prawy = NULL; //jak nie jest lewym poddrzewem, no to jest prawym;
		delete usuwany;
	}
	else //usuwanym elementem nie jest jednak li��;
	{
		if (usuwany->lewy == NULL || usuwany->prawy == NULL) //pytamy czy mamy przynajmniej jedn� pust� ga���/kraw�d� (przypadek z poddrzewem);
		{
			if (usuwany->lewy == NULL) //sprawdzamy czy lewe poddrzewo jest puste (nie ma go);
				zamienny = usuwany->prawy; //brak lewego poddrzewa, wi�c idzemy w prawo;
			else
				zamienny = usuwany->lewy; //istnieje lewe poddrzewo, wi�c idzemy w lewo;
			*usuwany = *zamienny; //przekopiuj bajt po bajcie (dos�ownie wszystko);
		}// to by�o z jednym poddrzewem;
		else // z dwoma poddrzewami;
		{// wiemy �e mamy 2 rozga��zienia, bo ani prawy, ani lewy nie jest pusty;
			rodzic = usuwany;
			zamienny = rodzic->lewy; //przechodzimy o jeden w lewo i;
			while (zamienny->prawy != NULL) //szukamy najwi�kszego elementu po prawej stronie, po to by podmieni� pod element usuwany;
			{
				rodzic = zamienny; //po to, by wiedzie� co jest wy�ej zmiennej, kt�ra zniknie;
				zamienny = zamienny->prawy; //przesuwamy si� o jeden w prawo
			}
			usuwany->dane = zamienny->dane; //podmieniamy najwi�ksz� dan� po lewej stronie usuwanego elementu, by drzewo mia�o dlasz� zgodno��;
			if (rodzic == usuwany) //sprawdzamy czy p�tla while w og�le ruszy�a;
				rodzic->lewy = zamienny->lewy; /*je�li nie ruszy�a, to element(Z), po lewej usuwanego(U), jest tym najwi�kszym, wi�c m�wimy rodzicowi(R) tego elementu(Z), kt�ry zniknie, �e jego potomkiem b�dzie element(P) o jeden dalej {(R=U -> Z -> P -> ...) -> (R=U -> P -> ...)} (je�li taki element nie istnieje to b�dze NULL); */
			else 
				rodzic->prawy = zamienny->lewy; /*je�li ruszy�a, to teraz elementem po prawej od rodzica, b�dzie (je�li taki istnieje) element,kt�ry by� po lewej zamiennego;*/
		}
		delete zamienny; //usuwamy element, kt�ry podmienili�my pod usuwany;
		return true; //usuwanie si� powiod�o;
	}
	
	
	
	//jeszcze jakie� usuwanie z prawej strony ale nie wiem gdzie
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
	else if (w->lewy == NULL && w->prawy == NULL) //sprawdz czy jest li�ciem;
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
	if (w->lewy == NULL && w->prawy == NULL) return 0; //sprawdz czy jest li�ciem;
	int hl = WysDrzewaPom(w->lewy); //oblicz wysoko�� lewego poddrzewa; 
	int hp = WysDrzewaPom(w->prawy); //oblicz wysoko�� prawego pddrzewa;
	if (hl > hp) //sprawdz kt�re poddrzewo dalej si�ga (jest wy�sze);
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
	if (w->lewy == NULL && w->prawy == NULL) return 0; //sprawdz czy jest li�ciem;
	int l = 0; //licznik;
	int hl = WysDrzewaPom(w->lewy); //oblicz wysoko�� lewego poddrzewa; 
	int hp = WysDrzewaPom(w->prawy); //oblicz wysoko�� prawego pddrzewa;
	if (hp == hl && hp != 0) //sprawdza czy wysoko�ci s� r�wne oraz czy nie stane�o na korzeniu;
		l++; //je�li nie to powieksz ilo�� takich samych wysoko�ci o jeden;
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
		WyswietlLiscieRosnacoPom(w->lewy); //przejd� najbardziej w lewo;
		WyswietlLiscieRosnacoPom(w->prawy); //a potem najbardziej w prawo (Teraz jeste�my w najmniejszej wielko�ci w drzewie); 
		if (w->prawy == NULL && w->lewy == NULL)
			cout << w->dane << " "; //wy�wietl warto��
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
		OdwrocDrzewoPom(w->lewy); //przejd� najbardziej po lewo;
		OdwrocDrzewoPom(w->prawy); //przejd� najbardziej po prawo;
		if (w->lewy != NULL && w->prawy == NULL) //je�li dany wierzcho�ek ma jedno poddrzewo po lewej;
		{
			w->prawy = w->lewy; //teraz prawe poddrzewo b�dzie lewym;
			w->lewy = NULL; //teraz lewe b�dzie puste;
		}
		if (w->lewy == NULL && w->prawy != NULL) //je�li dany wierzcho�ek ma jedno poddrzewo po prawej;
		{
			w->lewy = w->prawy; //teraz lewe poddrzewo b�dzie prawym;
			w->prawy = NULL; //teraz prawe b�dzie puste;
		}
		if (w->lewy != NULL && w->prawy != NULL) //je�li dany wierzcho�ek ma dwa poddrzewa;
		{
			wskw temp = w->lewy;  //
			w->lewy = w->prawy;  //  Zamiana poddrzew ze sob�;
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