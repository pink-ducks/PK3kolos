#include "pch.h"
#include <iostream>

using namespace std;

class wymierna {
private:
	int licznik;
	int mianownik;
public:
	wymierna() {};
	friend istream&operator>>(istream & is, wymierna & w);
	friend ostream&operator<<(ostream &os, wymierna & w);
	int wartosc();
};

struct stos {
	wymierna w;
	stos *Next = nullptr;
	stos *Prev = nullptr;
	stos(const wymierna &wym) : w(wym), Next(nullptr), Prev(nullptr) {};
};

class stos_w {
protected:
	stos *Head=nullptr;
	stos *Tail=nullptr;
public:
	friend std::istream& operator>>(std::istream& is, stos_w& stos_wym);
	void empty() {
		while (Head) {
			const stos *usun = Head;
			Head = Head->Next;
			delete usun;
		}
	}
	virtual stos_w &operator +=(const wymierna &w) {
		stos *st = new stos(w);
		if (Head == nullptr) {
			Head = st;
			Tail = st;
		}
		else {
			Head->Prev = st;
			st->Next = Head;
			Head = st;
		}
		return *this;
	}

	int pop() {
		if (!Head) {
			throw "pusty stos :(";
		}
		else {
			stos *temp = Head;
			Head = Head->Next;
			delete Head->Prev;
			return temp->w.wartosc();
		}
	}
	void push(const wymierna& st) {
		*this += st;
	}
	stos_w &operator=(stos_w&st) {
		this->empty();
		Head = move(st.Head);
		Tail = move(st.Tail);
		return *this;
	}
	stos_w &operator=(stos_w&&st) {
		this->empty();
		Head = move(st.Head);
		Tail = move(st.Tail);
		st.empty();

		return *this;
	}
};

std::istream& operator>>(std::istream& is, stos_w& stos_wym) {
	wymierna w;
	stos_wym.empty();
	
	while (is >> w) {
		stos_wym += w;
	}
	return is;
}

class zbior_w :public stos_w {
public:
	bool czyZawiera(wymierna wym) {
		stos *temp=Head;
		while (temp) {
			if (temp->w.wartosc() == wym.wartosc()) {
				return true;
			}
			temp = temp->Next;
		}
		return false;
	}
	zbior_w& operator+=(const zbior_w &zbior) {
		stos*temp = zbior.Head;
		while (temp) {
			if (czyZawiera(temp->w) == false) {
				*this += temp->w;
		   }
			temp = temp->Next;
		}
		return *this;
	}
	zbior_w& operator+=(const wymierna &wym) {
		if (czyZawiera(wym) == false) {
			*this->operator+= *wym;
		}
		return *this;
	}
	operator int() {
		int i = 0;
		stos *temp = Head;
		while (temp) {
			temp=temp->Next;
			i++;
		}
		return i;
	}
};

int main()
{
    
	return 0;
}
