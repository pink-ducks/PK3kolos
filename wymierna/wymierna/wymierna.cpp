#include "pch.h"
#include <iostream>

using namespace std;

// 1
class wymierna
{
private:
	int licznik;
	int mianownik;
	// wszelkie potrzebne metody i operatory ktorych nie trzeba definiowac:
protected:
	friend istream & operator>>(istream & i, wymierna & w);
public:
	double getWartosc();
	wymierna() {};
	wymierna(int l, int m) : licznik(l), mianownik(m) { };
};

// nie trzeba pisac na kolosie
istream & operator>>(istream &i, wymierna & w)
{
	return i >> w.licznik >> w.mianownik;
};

double wymierna::getWartosc()
{
	if (mianownik != 0)
	{
		return (double(licznik) / double(mianownik));
	}
	else
	{
		throw "nie dziel przez 0";
	}
}

// 2
struct stos
{
	wymierna liczba;
	stos *next = nullptr;
	stos *prev = nullptr;
	stos(const wymierna &liczba) :liczba(liczba), next(nullptr), prev(nullptr) {};
};

class stos_w
{
protected:
	stos * head;
	stos * tail;
public:
	// funkcje 
	void empty();
	double pop(); // 2.2
	void push(wymierna & w); // 2.3
	// operatory
	friend istream & operator >> (istream &i, stos_w & s); // 2.1
	virtual stos_w & operator += (const wymierna & w);
	stos_w & operator = (stos_w & s); 
	stos_w & operator = (stos_w && s); 
	// konstruktor
	stos_w() {	};
};

// 2.1
istream & operator >> (istream &i, stos_w & s)
{
	wymierna w;

	s.empty();

	while (i >> w)
	{
		s += w;
	}

	return i;
}

stos_w & stos_w::operator+= (const wymierna & w)
{

	stos * nowa = new stos(w);
	stos * zapamietaj = head;
	if (head)
	{
		head->prev = nowa;
		nowa->next = head;
		head = nowa;
	}
	else
	{
		head = nowa;
		tail = nowa;
	}

	return *this;	
}

void stos_w::empty() // czysci liste
{
	while (head)
	{
		const stos * zapamietaj = head;
		head = head->next;
		delete zapamietaj;
	}
}

// 2.2
double stos_w::pop()
{
	if (!head)
	{
		throw "pusty stos";
	}
	else
	{
		double usunietaWartosc = head->liczba.getWartosc();
	
		head = head->next;
		delete head->prev;
		head->prev = nullptr;

		return usunietaWartosc;
	}
}

// 2.3
void stos_w::push(wymierna & w)
{
	*this += w;
}

// 2.4

stos_w & stos_w::operator = (stos_w & s) // kopiujacy
{
	this->empty();
	head = s.head;
	tail = s.tail;
	return *this;
}
stos_w & stos_w::operator = (stos_w && s) // przenoszacy
{
	this->empty();
	head = move(s.head);
	tail = move(s.tail);
	s.empty();

	return *this;
}

// 3
class zbior_w : public stos_w
{
public:
	bool sprawdzCzyZawiera(wymierna w);
	zbior_w & operator += (const zbior_w & zbior);
	zbior_w & operator += (const wymierna & w);
	operator int ();
};

bool zbior_w::sprawdzCzyZawiera(wymierna w)
{
	stos * zapamietaj = head;
	while (zapamietaj != nullptr)
	{
		if (zapamietaj->liczba.getWartosc() == w.getWartosc())
		{
			return true;
		}
		zapamietaj = zapamietaj->next;
	}
	return false;
}
// 3.1
zbior_w & zbior_w::operator+=(const zbior_w & zbior)
{
	stos * zapamietaj = zbior.head;
	while (zapamietaj)
	{
		if (!sprawdzCzyZawiera(zapamietaj->liczba))
		{
			*this += zapamietaj->liczba; //wykorzystujemy operator z klasy bazowej
		}
		zapamietaj = zapamietaj->next;

	}
	return *this;
}
// 3.2
zbior_w & zbior_w::operator += (const wymierna & w)
{
	
	
	if (!sprawdzCzyZawiera(w))
	{
	//	*this += w; // NIE DZIALA WYKORZYSTANIE OPERATORA Z KLASY BAZOWEJ
		// skopiowany kawalek z klasy bazowej do testowania:
		stos * nowa = new stos(w);
		stos * zapamietaj = head;
		if (head)
		{
			head->prev = nowa;
			nowa->next = head;
			head = nowa;
		}
		else
		{
			head = nowa;
			tail = nowa;
		}
	}
	return *this;
}

// 3.3
zbior_w::operator int()
{
	int liczbaElementow = 0;
	stos * zapamietaj = head;
	
	while (zapamietaj)
	{
		liczbaElementow++;
		zapamietaj = zapamietaj->next;
	}
	return liczbaElementow;
}

int main()
{
	wymierna jeden(1, 2);
	wymierna dwa(3, 4);
	wymierna trzy(5, 6);

	stos_w sztos;
	sztos.push(jeden);
	sztos.push(dwa);
	sztos.push(trzy);

	cout << sztos.pop(); // usuwa ze stosu ulamek 5/6

	zbior_w zbiorek;
	zbiorek += jeden;
	zbiorek += dwa;
	zbiorek += jeden; // nie doda się <3

	return 0;
}
