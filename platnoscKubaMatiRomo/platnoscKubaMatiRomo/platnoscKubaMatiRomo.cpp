#include "pch.h"
#include <iostream>

using namespace std;

class platnosc
{
private:
	char * nazwa;
	double kwota = 0;
	int dzien = 0;
	int miesiac = 0;
	int rok = 0;
public:
	platnosc(char * nazwa, double kwota, int dzien, int miesiac, int rok);
//	platnosc(double k) : kwota(k) { };
	platnosc(int rok) : rok(rok) { };
	platnosc() { };
	friend ostream& operator << (ostream & os, platnosc & plat)
	{ 
		os << plat.rok;
		return os; 
	};
	bool operator < (const platnosc & p);
	bool operator > (const platnosc & p);
	bool wiekszeOd(int rok, int miesiac, int dzien);
	double getKwota();
};

bool platnosc::operator < (const platnosc & p)
{
	if (this->rok < p.rok)
		return true;
	else
		return false;
}

bool platnosc::operator > (const platnosc & p)
{

	if (this->rok > p.rok)
		return true;
	else
		return false;
}

bool platnosc::wiekszeOd(int rok, int miesiac, int dzien)
{
	if (this->rok > rok)
	{
		return true;
	}
	else
	{
		return false;
	}
}

double platnosc::getKwota()
{
	return kwota;
}

class spis_platnosci // tablica dynamiczna LIFO
{
protected:
	platnosc * tablica;
	int rozmiar = 0;
public:
	spis_platnosci() { };
	void empty();
	spis_platnosci(spis_platnosci & spis);
	spis_platnosci(spis_platnosci && spis);
	friend ostream& operator << (ostream & os,const spis_platnosci & spis);
	spis_platnosci & operator += (const platnosc & p);
};

void spis_platnosci::empty()
{
	delete[] tablica;
	rozmiar = 0;
}

spis_platnosci::spis_platnosci(spis_platnosci & spis)
{
	this->empty();
	tablica = move(spis.tablica);
	rozmiar = spis.rozmiar;
}
spis_platnosci::spis_platnosci(spis_platnosci && spis)
{
	this->empty();
	this->tablica = new platnosc[spis.rozmiar];
	for (int i = 0; i < spis.rozmiar; i++)
	{
		tablica[i] = spis.tablica[i];
	}
	rozmiar = spis.rozmiar;
	spis.empty();
}

ostream& operator << (ostream & os,const spis_platnosci & spis)
{
	for (int i = 0; i < spis.rozmiar; i++)
	{
		os << spis.tablica[i];
	}
	return os;
}

spis_platnosci & spis_platnosci::operator += (const platnosc & p)
{
	spis_platnosci zapamietaj(*this);
	this->tablica = new platnosc[rozmiar + 1]; // 1 wiecej miejsca
	for (int i = rozmiar; i > 0; i--) // od tylu
	{
		this->tablica[i] = zapamietaj.tablica[i - 1];
	}
	this->tablica[0] = p; // wartosc na samym poczatku [0]
	rozmiar++;

	return *this;

}

class kolejka_wydatkow : public spis_platnosci
{
public:
	kolejka_wydatkow & operator+= (const platnosc & p);
	operator double();
	spis_platnosci & przeterminowane(int rok, int miesiac, int dzien);
	platnosc & pobierz();
};

kolejka_wydatkow & kolejka_wydatkow::operator+= (const platnosc & p)
{
	if (tablica != nullptr)
	{
		this->tablica = new platnosc[rozmiar + 1]; // 1 wiecej miejsca
		for (int i = rozmiar; i > 0; i--) // od tylu
		{
			if (this->tablica[i - 1] < p) // zostajemy w miejscu i dodajemy
			{
				tablica[i] = p;
				break;
			}
			else // lecimy dalej w lewo
			{
				this->tablica[i] = this->tablica[i - 1];
			}
		} // petla nie wstawi nam platnosci jezeli platnosc jest najmniejsza [najwczesniejsza data]

		if (tablica[0] > p)
		{
			tablica[0] = p;
		}
		rozmiar++;
	}
	else
	{
		this->tablica = new platnosc[1];
		this->tablica[0] = p;
		rozmiar = 1;
	}

	return *this;
}

kolejka_wydatkow::operator double()
{
	double suma = 0;
	for (int i = 0; i < rozmiar; i++)
	{
		suma += tablica[i].getKwota();
	}
	return suma;
}

spis_platnosci & kolejka_wydatkow::przeterminowane(int rok, int miesiac, int dzien)
{
	spis_platnosci przeterminowane;
	kolejka_wydatkow pozostale;
	for (int i = 0; i < rozmiar; i++)
	{
		if (!this->tablica[i].wiekszeOd(rok, miesiac, dzien))
		{ // przeterminowane
			przeterminowane += tablica[i];
		}
		else // jest ok
		{
			pozostale += tablica[i];
		}
	}

	this->tablica = pozostale.tablica; // opetator juz napisalismy
	// ktory czysci, zmienia rozmiar i przepisuje
	pozostale.empty();

	return przeterminowane;
}

platnosc & kolejka_wydatkow::pobierz()
{
	if (this->tablica == nullptr)
	{
		throw "pusta kolejka";
	}
	else
	{
		platnosc zwrot;
		zwrot = tablica[0];

		kolejka_wydatkow nowa;
		for (int i = 1; i < rozmiar; i++)
		{
			nowa += tablica[i];
		}

		this->tablica = nowa.tablica; 
		// usuwa, zmienia rozmiar i przepisuje w naszym operatorze
		nowa.empty(); 

		return zwrot;
	}
}

int main()
{
	platnosc jeden(1);
	platnosc dwa(2);
	platnosc trzy(3);
	platnosc cztery(4);

	spis_platnosci spis;
	kolejka_wydatkow kolejka;
	
	spis += jeden;
	spis += dwa;
	spis += trzy;
	spis += cztery;

	cout << spis;

	spis_platnosci nowyspis(move(spis));

	kolejka += cztery;
	kolejka += dwa;
	kolejka += jeden;
	kolejka += trzy;

	return 0;
}
