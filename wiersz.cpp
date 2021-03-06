

#include "pch.h"
#include <iostream>

using namespace std;

class wiersz
{
public:
	char* znaki=nullptr;
	wiersz();
	wiersz(const char*);
	~wiersz();
	wiersz& operator=(const wiersz&w);
private:

};

wiersz::wiersz()
{
}

wiersz::wiersz(const char *zn)
{
	znaki = new char[strlen(zn)];
	strcpy(znaki,zn);
}

wiersz::~wiersz()
{
}

wiersz& wiersz::operator=(const wiersz&w)
{
	znaki = new char[strlen(w.znaki)];
	strcpy(this->znaki,w.znaki);
	return *this;
}

struct lista
{
	wiersz wier;
	lista*pnext=nullptr;
	lista*pprev=nullptr;
};

class tekst
{
public:
	lista *pHead=nullptr;
	lista *pTail=nullptr;

	tekst();
	~tekst();
	friend ostream& operator<<(ostream&os, tekst&text);
	tekst& operator+=(const wiersz&);
private:

};

tekst::tekst()
{
	
}

tekst::~tekst()
{
}

ostream& operator<<(ostream&os, tekst&text)
{
	lista*ptr = text.pHead;
	while (ptr)
	{
		cout << ptr->wier.znaki;
		ptr = ptr->pnext;
	}
	return os;
}

tekst& tekst::operator+=(const wiersz& w)
{
	lista* ptr = this->pHead;
	if (!ptr)
	{
		this->pHead = new lista;
		this->pHead->wier = w;
		this->pTail = this->pHead;
		return *this;
	}
	else
	{
		while (ptr->pnext)
		{
			ptr = ptr->pnext;
		}
		ptr->pnext = new lista;
		ptr->pnext->wier = w;
		this->pTail = ptr->pnext;
	}
	return *this;
}

class edytor_tekstu:public tekst
{
public:
	int nrlinii=0;
	edytor_tekstu();
	~edytor_tekstu();
	edytor_tekstu& operator+=(const wiersz& w);
	void paste(tekst&);
	edytor_tekstu copy(int ilewierszt);
	operator int();
private:

};

edytor_tekstu::edytor_tekstu()
{
}

edytor_tekstu::~edytor_tekstu()
{
}

edytor_tekstu& edytor_tekstu::operator+=(const wiersz&w)
{
	lista* ptr = this->pHead;
	if (!ptr)
	{
		this->pHead = new lista;
		this->pHead->wier = w;
		this->pTail = this->pHead;
		return *this;
	}
	else
	{
		int iterator=0;
		while (ptr->pnext&&iterator!=nrlinii)
		{
			iterator++;
			ptr = ptr->pnext;
		}
		lista*temp = ptr->pnext;
		ptr->pnext = new lista();
		ptr->pnext->wier = w;
		ptr->pnext->pnext = temp;
		while (ptr->pnext)
		{
			ptr = ptr->pnext;
		}
		this->pTail = ptr;
	}
	return *this;
}

void edytor_tekstu::paste(tekst &tex)
{
	lista* ptr = this->pHead;
	lista* tptr = tex.pHead;
	if (!ptr)
	{
		ptr = new lista;
		this->pHead = ptr;
		ptr->wier = tptr->wier;
		tptr = tptr->pnext;
		while (tptr)
		{
			ptr->pnext= new lista;
			ptr->pnext->wier = tptr->wier;
			tptr = tptr->pnext;
			ptr = ptr->pnext;
		}
		this->pTail = ptr;
		return;
	}
	else
	{
		int iterator = 0;
		while (ptr->pnext&&iterator != nrlinii)
		{
			iterator++;
			ptr = ptr->pnext;
		}
		lista*temp = ptr->pnext;
		while (tptr)
		{
			ptr->pnext = new lista;
			ptr->pnext->wier = tptr->wier;
			tptr = tptr->pnext;
			ptr = ptr->pnext;
		}
		while(ptr->pnext)
		{
			ptr = ptr->pnext;
		}
		this->pTail = ptr;
	}
}

edytor_tekstu edytor_tekstu::copy(int ilewierszy)
{
	edytor_tekstu et;
	lista* ptr = this->pHead;
	if (!ptr)
	{
		return et;
	}
	else
	{
		int iterator=0;
		while (ptr->pnext&&iterator != ilewierszy)
		{
			et += ptr->wier;
			ptr = ptr->pnext;
		}
		return et;
	}
}

edytor_tekstu::operator int()
{
	int i = 0;
	lista*ptr = this->pHead;
	while (ptr)
	{
		i++;
		ptr = ptr->pnext;
	}
	return i;
}

int main()
{
	tekst tex;
	tex += wiersz("x-2\n");
	tex += wiersz("x-1\n");
	tex += wiersz("x0\n");
	tex += wiersz("x1\n");
	tex += wiersz("x2\n");
	cout << tex;
	edytor_tekstu et;
	et.nrlinii = 1;
	et.paste(tex);
	et.paste(tex);
	cout << et;
	edytor_tekstu et2;
	et.nrlinii = 1;
	et2=et.copy(2);
	cout << et2;

	return 0;
}


