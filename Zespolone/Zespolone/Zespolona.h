#pragma once

// 1A

class zespolona
{
private:
	double rzeczywista = 0;
	double urojona = 0;
public:
	zespolona();
	zespolona(double rzeczywista, double urojona);
	// potrzebne metody i operatory
	double getRzeczywista();
	double getUrojona();
};

// 2A

class tabzes
{
private:
	zespolona * tablica;
	int rozmiar;
public:
	tabzes(int rozmiar);
	zespolona& operator[ ](const int rozmiar);  // 2B
	tabzes& operator =(const tabzes& tablica); // 2C
	tabzes& operator =(tabzes && tablica); // 2C
	tabzes& operator+=(const zespolona &z); // 2D
	

};