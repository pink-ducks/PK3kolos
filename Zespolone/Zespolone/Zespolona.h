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
	double getRzeczywista() const;
	double getUrojona() const;
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

	zespolona * getTablica() const;
	int getRozmiar() const;
};

// 3

class kolzes : public tabzes // przechowuje kolejke priorytetowych
	// liczb zespolonych uszeregowanych w kolejnosci rosnacych wartosci
	// bezwzglednych liczb zespolonych
{
public:
	friend std::istream& operator>> (std::istream & is, const kolzes& kolejka);
	kolzes& operator += (const zespolona &z);
};
