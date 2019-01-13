#pragma once
#include "pch.h"
#include <string.h>
#include <stdio.h>
#include <iostream>

class zespolona {
private:
	double rzeczywista;
	double urojona;

public:
	zespolona() {};
	zespolona(double rzeczywista, double urojona);
	double getRzeczywista() const;
	double getUrojona() const;
};


class tabzes {
private:
	zespolona *tablica;
	int rozmiar;

public:
	tabzes(int rozmiar);

	zespolona* getTablica();
	int getRozmiar();

	zespolona& operator[](const int);
	tabzes& operator= (const tabzes& tablica);
	tabzes& operator= (tabzes&&tablica);
	tabzes& operator+= (const zespolona &z);
};


class kolzes :public tabzes {
public:
	friend std::istream& operator>>(std::istream& is, const kolzes& kolejka);
	kolzes& operator+=(const zespolona &z);
};

struct liczba {
	zespolona head;
	zespolona *pNext;
	liczba(const k &ctr) :t(ctr), next(nullptr) {};
};