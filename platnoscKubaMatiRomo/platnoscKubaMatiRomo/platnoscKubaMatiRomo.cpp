#include "pch.h"
#include <iostream>

using namespace std;

class platnosc {
private:
	char* nazwa;
	double kwota;
	int dzien;
	int miesiac;
	int rok;
public: 
	platnosc() {};
	platnosc(char* nazwa, double kwota, int dzien, int miesiac, int rok) :
		nazwa(nazwa), kwota(kwota), dzien(dzien), miesiac(miesiac), rok(rok);
	~platnosc() {};
	friend ostream&operator<<(ostream& os, platnosc & plat);
	bool operator<(const platnosc & plat);//sól ubranie
	bool operator>(const platnosc & plat);
	bool czyStarsze(int dzien, int miesiac, int rok);
	double getKwota();
};

class spis_platnosci {
protected:
	platnosc * tablica;
	int rozmiar = 0;
public:
	spis_platnosci(platnosc *tablica, int rozmiar) : tablica(tablica), rozmiar(rozmiar) {};
	void empty() {
		for (int i = 0;i < rozmiar;i++) {
			delete &this->tablica[i];
		}
		delete tablica;
		rozmiar = 0;
	}
	spis_platnosci() {};
	spis_platnosci(spis_platnosci & spis) {
		this->empty();
		this->tablica = move(spis.tablica);
		rozmiar = spis.rozmiar;
	}
	spis_platnosci(spis_platnosci && spis) {
		this->empty();
		this->tablica = move(spis.tablica);
		this->rozmiar = move(spis.rozmiar);
		spis.empty();
	}

	friend ostream&operator<<(ostream&os, spis_platnosci& spis) {
		for (int i = 0;i < rozmiar;i++) {
			os << spis;
		}
		return os;
	}
	spis_platnosci& operator+=(const platnosc& plat) {
		this->tablica = new platnosc[rozmiar + 1];
		rozmiar++;
		for (int i = rozmiar-1;i >0;i--) {
			tablica[i] = tablica[i - 1];
		}
		tablica[0] = plat;
		return *this;
	}
};

class kolejka_wydatkow : public spis_platnosci {
public:
	kolejka_wydatkow& operator+=(const platnosc& plat) {
		
		this->tablica = new platnosc[this->rozmiar + 1];
		for (int i = rozmiar;i >0;i--) {
			if (this->tablica[i - 1]< plat) {
				tablica[i] = plat;
				break;
			}
			else {
				this->tablica[i] = tablica[i - 1];
			}

		}
		if (tablica[0]>plat) {
			tablica[0] = plat;
		}
		rozmiar++;
		return *this;
	}

	operator double() {
		double suma=0;
		for (int i = 0;i < rozmiar;i++) {
			suma += tablica[i].getKwota();
		}
		return suma;
	}
	spis_platnosci &przeterminowane(int rok, int miesiac, int dzien) {
		spis_platnosci przet;
		kolejka_wydatkow pozostale;

		for (int i = 0;i < rozmiar;i++) {
			if (this->tablica[i].czyStarsze(dzien, miesiac, rok)) {
				przet += tablica[i];
			}
			else {
				pozostale += tablica[i];
			}
		}
		tablica = pozostale.tablica;
		pozostale.empty();
		return przet;
	}

	platnosc& pobierz() {
		if (tablica == nullptr) {
			throw "pusta kolejka :(";
		}
		else {
			kolejka_wydatkow nowa;
			platnosc do_zwortu = tablica[0];
			for(int i=1;i<rozmiar;i++){
				nowa += tablica[i];
			}
			tablica = nowa.tablica;
			nowa.empty();

			return do_zwortu;
		}
	}
};