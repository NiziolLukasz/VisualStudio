#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

class Kwota
{
private:
	int zlote;
	int grosze;
public:
	void ustaw(int, int); // ustawianie pól z³ote, grosze
	Kwota(int zlote = 0, int grosze = 0); // konstrukcja obiektu | Domyœlnie zlote = grosze = 0
	Kwota operator +(const Kwota&)const; // dodawanie kwot
	Kwota & operator +=(const Kwota&); // dodawanie kwot
	Kwota operator *(double); // mno¿enie kwot przez nieujemn¹ liczbê rzeczywist¹
	Kwota & operator *=(double); // mno¿enie kwot przez nieujemn¹ liczb¹ rzeczywist¹
	Kwota & operator =(const Kwota&); // przypisanie jednej kwoty do drugiej
	Kwota & operator ++(); // ++k zwiêkszy siê o 1 zl
	Kwota & operator ++(int);// k++ zwiêkszy siê o 10 gr
	bool operator ==(const Kwota&)const; // porównanie kwot
	bool operator >(const Kwota&)const; // porównanie kwot
	bool operator >=(const Kwota&)const; // porównanie kwot
	friend istream & operator >>(istream&, Kwota&); // wczytanie kwoty
	friend ostream & operator <<(ostream&, Kwota&); // wyœwietlenie kwoty np. 65 zl 07 gr (zlote ^ grosze != 0) | 09 gr (zlote = 0) | 6 zl (grosze = 0) | 0 zl (zlote = grosze = 0)
};
class TLokata 
	:Kwota 
{
private:
	const Kwota kwota_startowa; // wartoœæ pocz¹tkowa za³o¿onej lokaty
	const double opr; // wartoœæ oprocentowania w skali roku (np. wartoœæ pola 3.4 oznacza lokatê z  oprocentowaniem 3.4% w skali roku)
	Kwota ods; // wartoœæ dotychczas naliczanych odsetek
public:
	TLokata(Kwota ks, double o) :kwota_startowa(ks), opr(o <= 0 ? 0 : o) //Konstruktor inicjalizuj¹cy pola sta³e wartoœciami swoich parametrów
	{
	}
	Kwota KwotaStartowa(); // zwraca kwotê pocz¹tkow¹ lokaty
	Kwota Odsetki(); // zwraca kwotê odsetek w danym momencie
	void NaliczOdsetki(int); // zwiêksza wartoœæ pola ods o kwotê wynikaj¹c¹ z oprocentowania lokaty (naliczanie odsetek odbywa siê na koniec roku trwania lokaty)
	bool WyplacOdsetki(Kwota); // metoda logiczna zmiejszaj¹ca wartoœæ pola ods o kwotê przekazan¹ w parametrze (o ile kwota odsetek jest wystarczaj¹ca)
	Kwota WyplacOdsetki(); // wyp³aca ca³kowit¹ kwotê odsetek; wynikiem metody jest kwota wyp³aconych odsetek

};
//============================ Metody TLokata =============================================
Kwota TLokata::KwotaStartowa()
{
	return kwota_startowa;
}
Kwota TLokata::Odsetki()
{
	return ods;
}
void TLokata::NaliczOdsetki(int lata)
{
	ods.ustaw(0, 0);
	Kwota pom = KwotaStartowa();
	if (lata > 0)
	{
		for (int i = 1; i <= lata; i++)
			pom += pom * opr;
		ods = pom;
	}

}
bool TLokata::WyplacOdsetki(Kwota k)
{	// Wystarczaj¹ca to znaczy 1)  2) ?

	/*
	if (ods >= k) // 1) Kwota ma nie przekraczaæ wysokoœæ odsetek, by nie powsta³a nadp³ata
	{
	//odejmowanie k - ods ( Kwota - Kwota ); brak operatora (operator ten nie zosta³ w zadaniu "zamówiony")
	// nie mam jak narazie pomys³u jak wykonaæ odejmowanie bez operatora
	return true;
	}
	return false;
	*/
	if (k == ods) // 2) Kwota ma byæ wystarczaj¹ca by sp³aciæ odsetki za pierwszym razem
	{
		ods.ustaw(0, 0);
		return true;
	}
	return false;
}
Kwota TLokata::WyplacOdsetki()
{
	return ods;
}
//=========================================================================================
//============================ Metody Kwota ===============================================
void Kwota::ustaw(int zlote, int grosze)
{
	this->grosze = grosze;
	this->zlote = zlote < 0 ? 0 : zlote;
	if (this->grosze < 0) this->grosze = 0;
	else
		if (this->grosze>99)
		{
			this->zlote += this->grosze / 100;
			this->grosze %= 100;
		}

}
Kwota::Kwota(int zlote, int grosze)
{
	ustaw(zlote, grosze);
}
Kwota Kwota::operator +(const Kwota& k)const
{
	return Kwota(zlote + k.zlote, grosze + k.grosze);
}
Kwota &Kwota::operator +=(const Kwota& k)
{
	ustaw(zlote + k.zlote, grosze + k.grosze);
	return *this;
}
Kwota Kwota::operator *(double x)
{
	if (x >= 0)
		return Kwota(0, int(x * (zlote * 100 + grosze)));
}
Kwota &Kwota::operator *=(double x)
{
	if (x >= 0)
		ustaw(0, int(x * (zlote * 100 + grosze)));
	return *this;
}
Kwota &Kwota::operator =(const Kwota& k)
{
	ustaw(k.zlote, k.grosze);
	return *this;
}
Kwota &Kwota::operator ++()
{
	ustaw(zlote + 1, grosze);
	return *this;
}
Kwota &Kwota::operator ++(int d)
{
	ustaw(zlote, grosze + 10);
	return *this;
}
bool Kwota::operator ==(const Kwota& k)const
{
	return (zlote * 100 + grosze) == (k.zlote * 100 + k.grosze);
}
bool Kwota::operator >(const Kwota& k)const
{
	return (zlote * 100 + grosze) > (k.zlote * 100 + k.grosze);
}
bool Kwota::operator >=(const Kwota& k)const
{
	return (zlote * 100 + grosze) >= (k.zlote * 100 + k.grosze);
}
istream & operator >>(istream& wej, Kwota& k)
{
	int z, g;
	wej >> z >> g;
	k.ustaw(z, g);
	return wej;
}
ostream & operator <<(ostream& wyj, Kwota& k)
{
	if (k.zlote == 0 && k.grosze == 0)
		wyj << 0 << " zl";
	else if (k.grosze == 0)
		wyj << k.zlote << " zl";
	else if (k.zlote == 0)
		if (k.grosze <= 9)
			wyj << "0" << k.grosze << " gr";
		else
			wyj << k.grosze << " gr";
	else
		if (k.grosze <= 9)
			wyj << k.zlote << " zl " << "0" << k.grosze << " gr";
		else
			wyj << k.zlote << " zl " << k.grosze << "gr";
	return wyj;

}
//=========================================================================================
int main()
{
	TLokata L(7000, 5.5);
	L.NaliczOdsetki(1);  //...
	cout << L.Odsetki() << endl; //...wyœwietl wartoœæ odsetek po roku

	L.NaliczOdsetki(2);  //...
	cout << L.Odsetki() << endl; //...wyœwietl wartoœæ odsetek po dwóch latach

	L.NaliczOdsetki(1);  //...
	cout << L.WyplacOdsetki() << endl; //...wyp³aæ kwotê odsetek (naliczon¹ po roku)

	cout << L.KwotaStartowa() + L.Odsetki() << endl; //wyœwietl aktualn¹ wartoœæ lokaty

	system("pause");
	return 0;
}
