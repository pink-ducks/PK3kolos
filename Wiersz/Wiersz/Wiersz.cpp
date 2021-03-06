// Wiersz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string.h>
using namespace std;
class wiersz
{
private:
	char * znak{ nullptr };
public:
	char * GetZnak();
	void SetZnak(char *);
	wiersz() = default;
	wiersz(const char*);
	wiersz(const wiersz &) = default;
	friend ostream & operator << (ostream & os, const wiersz & w);
};
void wiersz::SetZnak(char * znak)
{
	this->znak = znak;
}
wiersz::wiersz(const char * zn)
{
	znak = new char[strlen(zn)];
	strcpy(znak, zn);
}
char * wiersz::GetZnak()
{
	return znak;
}
ostream & operator << (ostream & os, const wiersz & w)
{
	os << w.znak;
	os << " ";
	return os;
}
struct Lista
{
	Lista * next;
	wiersz w;
	Lista(const wiersz & w) : w(w), next(nullptr) {};
};
class tekst
{
protected:
	Lista * head;
	Lista * tail;
public:
	tekst() : head(nullptr){}
	tekst(const tekst & w);
	virtual tekst & operator += (const wiersz & w)
	{
		Lista * elem = new Lista(w);
		if (head)
		{
			tail->next = elem;
		}
		else
		{
			head = elem;
		}
		tail = elem;
		return (*this);
	}
	friend ostream & operator << (ostream & os, const tekst & list);
	~tekst()
	{
		while (head)
		{
			const Lista * tmp = head;
			head = head->next;
			delete tmp;
		}
	}
	
};
tekst::tekst(const tekst & w) :head(nullptr)
{
	Lista * elem = w.head;
	while (elem)
	{
		(*this) += elem->w;
		elem = elem->next;
	}
}
ostream & operator << (ostream & os, const tekst & rq)
{
	Lista * tmp = rq.head;
	while (tmp)
	{
		os << tmp->w << " ";
		tmp = tmp->next;
	}
	return os;
}
class EdytorTekstu : tekst
{

	
public: 
	int numeraktualnegowiersza = 0;
	EdytorTekstu()
	{

	}
	~EdytorTekstu()
	{

	}
	operator int()
	{
		int suma = 0;
		Lista * l1 = head;
		while (l1)
		{
			suma++;
			l1 = l1->next;
		}
		return suma; 
	}
	//operator usuwający aktualny wiersz
	EdytorTekstu & operator- ()
	{
		Lista * ToDelete = head;
		Lista * tmp = head->next;
		if (head)
		{
			delete ToDelete;
			head = tmp;
			return *this;
		}
		else
		{
			throw - 1;
		}
	}
	EdytorTekstu copy(int ilewierszy)
	{
		EdytorTekstu t;
		Lista * tmp = head;
		if (!tmp)
		{
			return t;
		}
		else
		{
			int i = 0;
			while (tmp->next && i != ilewierszy)
			{
				t += tmp->w;
				tmp = tmp->next;
			}
			return t;
		}
	}
};
int main()
{
	tekst t;
	t += wiersz("Psy");
	t += wiersz("sa");
	t += wiersz("super");
	cout << t;
	EdytorTekstu et;
	et.numeraktualnegowiersza = 1;
	EdytorTekstu et2;
	et2 = et.copy(1);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
