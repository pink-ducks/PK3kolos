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
	double getRzeczywista();
};


class tabzes {
private:
	zespolona *tablica;
	int rozmiar;

public:
	tabzes(int rozmiar);
	zespolona& operator[](const int);
	tabzes& operator= (const tabzes& tablica);
	tabzes& operator= (tabzes&&tablica);
	tabzes& operator+= (const zespolona &z);
};


class kolzes :public tabzes {

};