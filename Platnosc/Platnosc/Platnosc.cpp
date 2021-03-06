// Platnosc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
using namespace std;
class Platnosc
{
private:
	char * nazwaplatnosci{nullptr};
	double kwotaplatnosci;
	int dzien;
	int miesiac;
	int rok;
public: 
	Platnosc()
	{

	}
	Platnosc(char * nazwaplatnosci, double kwotaplatnosci, int dzien, int miesiac, int rok)
	{
		this->nazwaplatnosci = nazwaplatnosci;
		this->kwotaplatnosci = kwotaplatnosci;
		this->dzien = dzien;
		this->miesiac = miesiac;
		this->rok = rok;
	}
	Platnosc(const Platnosc & pr)
	{
		this->nazwaplatnosci = pr.nazwaplatnosci;
		this->kwotaplatnosci = pr.kwotaplatnosci;
		this->dzien = pr.dzien;
		this->miesiac = pr.miesiac;
		this->rok = pr.rok;
	}
	bool operator > (Platnosc & a); //porownuje daty, true zwraca gdy a jest mniejsze, false gdy a jest wieksze 
	/*Platnosc & operator = (Platnosc & a)
	{
			this->nazwaplatnosci = a.nazwaplatnosci;
			this->kwotaplatnosci = a.kwotaplatnosci;
			this->dzien = a.dzien;
			this->miesiac = a.miesiac;
			this->rok = a.rok;
			return (*this);
	}*/
	double GetKwotaPlatnosci()
	{
		return kwotaplatnosci;
	}
	friend ostream & operator << (ostream & os, Platnosc & pr);
};
ostream &operator << (ostream & os, Platnosc & pr)
{
	os << pr.nazwaplatnosci;
	os << " ";
	os << pr.kwotaplatnosci;
	os << " ";
	os << pr.dzien;
	os << " ";
	os << pr.miesiac;
	os << " ";
	os << pr.rok;
	return os;
}
bool Platnosc::operator > (Platnosc & a)
{
	if (rok == a.rok)
	{
		if (miesiac = a.miesiac)
		{
			if (dzien == a.dzien)
			{
				return true;
			}
			else if (dzien > a.dzien)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (miesiac > a.miesiac)
		{
			return true;
		}
		else
		{
			false;
		}
	}
	else if (rok > a.rok)
	{
		return true;
	}
	else
	{
		false;
	}
}
class Spisplatnosci
{
protected:
	int IleElementow;
	Platnosc * Tab;
public: 
	//konstruktory 
	Spisplatnosci(int x)
	{
		this->IleElementow = x;
		Tab = new Platnosc[IleElementow];
	}
	//konstruktor kopiujacy 
	Spisplatnosci(const Spisplatnosci & pr)
	{
		IleElementow = pr.IleElementow;
		if (Tab)
		{
			delete[] Tab; 
			Tab = nullptr;
		}
		if (pr.Tab)
		{	
			Tab = new Platnosc[IleElementow];
			for (int i = 0; i < IleElementow; i++)
			{
				this->Tab[i] = pr.Tab[i];
			}
		}
		//opcja 2 Grembosz
		//IleElementow = pr.IleElementow;
		//Tab = new Platnosc[IleElementow];
		//memcpy(Tab, pr.Tab, IleElementow);
	}
	Spisplatnosci(Spisplatnosci && pr)
	{
		//kopiujemy skladniki 
		Tab = pr.Tab;
		IleElementow = pr.IleElementow;
		//zacieramy slady po przejeciu tablicy 
		pr.Tab = nullptr;
		pr.IleElementow = 0;
		//moze tez byc z move 
	}
	//operator strumieniowy 
	friend ostream & operator << (ostream &os, const Spisplatnosci & spis);
	//dodawanie nowej platnosci do listy na koniec tablicy 
	virtual Spisplatnosci & operator += (const Platnosc & p1)
	{
		Platnosc * wiekszaTablica = new Platnosc[IleElementow + 1];
		for (int i = 0; i < IleElementow; i++ )
		{
			wiekszaTablica[i] = Tab[i];
		}
		wiekszaTablica[IleElementow] = p1;
		delete[] this->Tab;
		this->Tab = wiekszaTablica;
		this->IleElementow++;
		return (*this);
	}
};
ostream & operator << (ostream &os, const Spisplatnosci & spis)
{
	for (int i = 0; i < spis.IleElementow; i++)
	{
		os << spis.Tab << " ";
	}
	return os; 
}

class kolejkaWydatkow : Spisplatnosci
{
public:
	kolejkaWydatkow & operator +=(Platnosc & p1)
	{
		if (!this->Tab)
		{
			this->Tab = new Platnosc[1];
			this->Tab[0] = p1;
			this->IleElementow = 1;
			return(*this);
		}
		Platnosc * tmp = this->Tab;
		Platnosc * wiekszaTablica = new Platnosc[IleElementow + 1];
		bool insert = false; 
		for (int i = 0; i < IleElementow + 1; i++)
		{
			if (p1 > tmp[i])
			{
				this->Tab[i] = tmp[i];
			}
			else
			{
				if (insert == false)
				{
					this->Tab[i] = p1;
					insert = true;
				}
				else
				{
					this->Tab[i] = tmp[i - 1];
				}
			}
		}
		IleElementow++;
		delete[] tmp;
		return (*this);
	}
	operator double()
	{
		double suma = 0;
		for (int i = 0; i < IleElementow; i++)
		{
			suma += Tab[i].GetKwotaPlatnosci();
		}
		return suma;
	}
	Spisplatnosci Przeterminowane(int rok, int miesiac, int dzien)
	{
		
	}
	Platnosc & pobierz()
	{
		if (!this->Tab)
		{
			throw - 1;
		}
		Platnosc * tmp = this->Tab;
		Platnosc p;
		p = Tab[0];
		delete[] this->Tab;
		this->Tab = new Platnosc[IleElementow - 1];
		for (int i = 1; i < IleElementow - 1; i++)
		{
			for (int j = 0; j < IleElementow - 1; i++)
			{
				this->Tab[j] = tmp[i];
			}
		}
		IleElementow--;
		delete[] tmp;
	}
};
int main()
{
    std::cout << "Hello World!\n"; 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
