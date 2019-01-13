#include "pch.h"
#include "Zespolone.h"
#include <iostream>

//bez tego na kolosie
zespolona::zespolona(double rzeczywista, double urojona) :rzeczywista(rzeczywista), urojona(urojona){
}

double zespolona::getRzeczywista() const
{
	return this->rzeczywista;
}

double zespolona::getUrojona() const
{
	return this->urojona;
}
//

tabzes::tabzes(int rozmiar) {
	tablica =new zespolona[rozmiar];
	this->rozmiar = rozmiar;
}

zespolona * tabzes::getTablica()
{
	return this->tablica;
}

int tabzes::getRozmiar()
{
	return this->rozmiar;
}

zespolona& tabzes::operator[](const int index)
{
	if (index >= this->rozmiar ||index<0) {
		const char *wyjatek = "zly index";
		throw wyjatek;
	}
	else {
		return *(tablica + index);
	}
}

tabzes& tabzes::operator= (const tabzes& tab) {
	rozmiar = tab.rozmiar;
	
	if (tablica) {
		delete[]tablica;
		tablica = nullptr;
	}

	if (tab.tablica) {
		tablica = new zespolona[rozmiar];
		for (int i = 0;i < rozmiar;i++) {
			tablica[i] = tab.tablica[i];
		}
	}


	return *this;
}

tabzes& tabzes::operator=(tabzes&& tab) {
	rozmiar = tab.rozmiar;
	if (tablica) {
		delete[]tablica;
	}
	tablica = tab.tablica;
	tab.tablica = nullptr;
	return *this;
}

tabzes& tabzes::operator+=(const zespolona &z) {
	zespolona *tab = new zespolona[this->rozmiar+1];
	for (int i = 0;i < rozmiar;i++) {
		tab[i] = tablica[i];
	}
	tab[rozmiar] = z;
	
	delete[]this->tablica;
	this->tablica = tab;
	this->rozmiar++;
	return *this;
}


std::istream & operator>>(std::istream & is, const kolzes & kolejka)
{
	is >> kolejka;
	return is;
}

kolzes& kolzes::operator+=(const zespolona &z) {
	int index = 0;
	zespolona*temp = getTablica();
	while (abs(z.getRzeczywista() + z.getUrojona()) > abs((temp + index)->getRzeczywista() + (temp + index)->getUrojona())) {

	}
}

int main() {
	zespolona liczba1(10.0, 4.3);
	zespolona liczba2(31, 2);
	zespolona liczba3(3, 2);

	tabzes tablica(3);
	tabzes tab(3);
	tablica += liczba1;
	tab = tablica;

	std::cout << tab[3].getRzeczywista();
	std::cout <<" " << tablica[3].getRzeczywista();
	return 0;
}

