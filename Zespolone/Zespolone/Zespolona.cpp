#include "pch.h"
#include <iostream>
#include <thread>
#include "Zespolona.h"

zespolona::zespolona()
{

}
zespolona::zespolona(double rzeczywista, double urojona)
{
	this->rzeczywista = rzeczywista;
	this->urojona = urojona;
}

tabzes::tabzes(int rozmiar)
{
	tablica = new zespolona[rozmiar];
}

// 2B operator [ int index ] zwracajacy wartosc tablicy czyli zespolona

zespolona& tabzes::operator[ ](const int index)
{
	if (index >= rozmiar || index < 0)
	{
		const char * wyjatek = "zly index";
		throw wyjatek;
	}
	else
	{
		return *(tablica + index); // tablica[index]
	}
}

// 2C operator przypisania i operator przenoszacy operator przypisania

// przypisania (kopiujący)
tabzes& tabzes::operator =(const tabzes& tab)
{
	rozmiar = tab.rozmiar;

	if (tablica)
	{
		delete[] tablica;
		tablica = nullptr;
	}
	if (tab.tablica)
	{
		tablica = new zespolona[rozmiar];
		memcpy(tablica, tab.tablica, rozmiar);
	}

	return * this;
}
// przypisania (przenoszacy)
tabzes& tabzes::operator =(tabzes && tab)
{
	rozmiar = tab.rozmiar;

	if (tablica)
	{
		delete[] tablica;
		tablica = nullptr;
	}
	tablica = tab.tablica;
	tab.tablica = nullptr;

	return * this;
}

// 2 D operator += wstawiający na koniec zespoloną

tabzes& tabzes::operator+=(const zespolona &z)
{
	zespolona * wiekszaTablica = new zespolona[rozmiar + 1];
	wiekszaTablica = this->tablica; //  przenoszenie starej do nowej
	wiekszaTablica[rozmiar] = z;

	// tablica zawiera teraz dodatkowy element
	delete[] this->tablica;
	this->tablica = wiekszaTablica;
	return *this;
}

int main()
{
	zespolona jeden(1, 2);
	zespolona dwa(3, 4);
	zespolona trzy(5, 6);



	return 0;
}