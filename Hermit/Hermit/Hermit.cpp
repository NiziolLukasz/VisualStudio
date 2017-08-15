#include "stdafx.h"
#include <iostream>
using namespace std;
class THermit {
private:
	int n;
	double *a, *x, *y, *kx;
	int silnia(int x); //liczenie silni
	void Oblicz_kx(); // liczenie wektora kx
	void WysWek(double *w); //wyœwietla wektor [x, x, x, x, x]
public:
	THermit();
	THermit(int, double *, double *);
	void Hermit();
	void Wyswietl();
};
THermit::THermit()
{
	cout << "Podaj wielkosc wektora (! Pamietaj, ze indeksowanie jest od 0 !): ";
	cin >> n;
	x = new double[n + 1];
	y = new double[n + 1];
	cout << "Podaj wektor x zawierajacy " << n + 1 << " elementow: " << endl;
	for (int i = 0; i <= n; i++)
	{
		cout << "x_" << i << " = ";
		cin >> x[i];
	}
	Oblicz_kx();
	cout << "Podaj wektor y zawierajacy " << n + 1 << " pochodnych:" << endl;
	for (int i = 0; i <= n; i++)
	{
		cout << "y(" << x[i] << ")";
		for (int j = 0; j < kx[i]; j++)
			cout << "'";
		cout << " = ";
		cin >> y[i];
	}

}
THermit::THermit(int n, double *x, double *y)
{
	this->n = n;
	this->x = x;
	this->y = y;
	Oblicz_kx();
}
void THermit::Oblicz_kx()
{
	kx = new double[n + 1];
	kx[0] = 0;
	for (int i = 1; i <= n; i++)
		if (x[i] == x[i - 1])
			kx[i] = kx[i - 1] + 1;
		else
			kx[i] = 0;
}
int THermit::silnia(int x)
{
	if (x <= 0) return 1;
	return silnia(x - 1) * x;
}
void THermit::Hermit()
{
	a = new double[n + 1];
	double * r = new double[n + 1];
	double pom; int indeks;
	for (int i = 0; i <= n; i++)
	{
		if (kx[i] == 0)
		{
			r[i] = y[i];
			pom = y[i];
			indeks = i; //pierwsze wyst¹pienie wêz³a
		}
		else
			r[i] = pom; //kolejny ten sam
		for (int k = i - 1; k >= 0; k--)
		{
			if (x[i] != x[k])
				r[k] = (r[k + 1] - r[k]) / (x[i] - x[k]);
			else
				r[k] = y[indeks + i - k] / silnia(kx[indeks + i - k]);
		}
		a[i] = r[0];
	}
	delete[] r;
}
void THermit::WysWek(double *w)
{
	cout << "[";
	for (int i = 0; i <= n; i++)
	{
		cout << w[i];
		if (i == n)
		{
			cout << "]" << endl;
			break;
		}
		cout << ", ";
	}
}
void THermit::Wyswietl()
{
	cout << "\nRozklad:\n";
	cout << "x = ";
	WysWek(x);
	cout << "kx = ";
	WysWek(kx);
	cout << "y = ";
	WysWek(y);
	cout << "a = ";
	WysWek(a);
	cout << "p(x) = ";
	for (int i = 0; i <= n; i++)
	{
		if (a[i] == 0)
			continue;
		else if (i == 0)
			cout << a[0];
		else if (a[i] < 0)
			if (a[i] == -1)
				cout << "-";
			else
				cout << a[i];
		else
			if (a[i] == 1)
				cout << "+";
			else
				cout << "+" << a[i];
		for (int k = 0; k < i; k++)
		{
			if (x[k] == 0)
			{
				cout << "x";
			}
			cout << "(x";
			if (x[k] < 0)
				cout << "+" << -x[k];
			else
				cout << "-" << x[k];
			cout << ")";
		}
	}
	cout << endl;
}


int main()
{
	THermit h;
	h.Hermit();
	h.Wyswietl();
	system("pause");
	return 0;
}