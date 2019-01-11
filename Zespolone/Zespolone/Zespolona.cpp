#include "pch.h"
#include <iostream>
#include <thread>
#include <stdio.h>
#include <string.h>
#include "Zespolona.h"

zespolona::zespolona()
{

}
zespolona::zespolona(double rzeczywista, double urojona)
{
	this->rzeczywista = rzeczywista;
	this->urojona = urojona;
}

double zespolona::getRzeczywista()
{
	return rzeczywista;
}
double zespolona::getUrojona()
{
	return urojona;
}

tabzes::tabzes(int rozmiar)
{
	this->rozmiar = rozmiar;
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
		for (int i = 0; i < rozmiar; i++)
		{
			tablica[i] = tab.tablica[i];
		}
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
	
	for (int i = 0; i < rozmiar; i++) // przenosimy stare wartosci do nowej
	{
		wiekszaTablica[i] = tablica[i];
	}

	wiekszaTablica[rozmiar] = z;

	// tablica zawiera teraz dodatkowy element
	delete[] this->tablica;
	this->tablica = wiekszaTablica;

	this->rozmiar++;
	return *this;
}

int main()
{
	zespolona jeden(1, 2);
	zespolona dwa(3, 4);
	zespolona trzy(5, 6);

	tabzes tablica(0);

	tablica += jeden; // dodajemy (1,2)
	tablica += dwa; // dodajemy (3,4)

	std::cout << tablica[0].getRzeczywista(); // wyswietla 1 2
	std::cout << tablica[1].getRzeczywista(); // wyswietla 3 4

	tabzes kopia(10); 
	kopia = tablica; // kopia dostaje taki sam rozmiar i wartosci jak tablica

	std::cout << kopia[0].getRzeczywista(); // wyswietla 1 2
	std::cout << kopia[1].getRzeczywista(); // wyswietla 3 4

	return 0;
}