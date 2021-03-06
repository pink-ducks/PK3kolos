// Kolos1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Author Fanish

#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

class zwierzak
{
private:
	char* nazwa = nullptr;
	char* gatunek = nullptr;
	int DUdzien;
	int DUmiesiac;
	int DUrok;
public:
	~zwierzak();
	zwierzak()=default;
	zwierzak(const char* _nazwa,const char* _gatunek, int _dzien, int _miesiac, int _rok);
	zwierzak(const zwierzak&);//konstruktor kopiujacy
	zwierzak(const zwierzak*);
	char*getNazwa();
	char*getGatunek();
	int getD();
	int getM();
	int getY();
};

zwierzak::~zwierzak()
{

}

//konstruktor kopiujący zwierzaka
zwierzak::zwierzak(const zwierzak & other)//konstruktor kopiujacy
{
	nazwa = new char(strlen(other.nazwa));
	gatunek = new char(strlen(other.gatunek));
	strcpy(nazwa,other.nazwa);
	strcpy(gatunek, other.gatunek);
	DUdzien = other.DUdzien;
	DUmiesiac = other.DUmiesiac;
	DUrok = other.DUrok;
}

zwierzak::zwierzak(const zwierzak*other)
{
	nazwa = new char(strlen(other->nazwa));
	gatunek = new char(strlen(other->gatunek));
	strcpy(nazwa, other->nazwa);
	strcpy(gatunek, other->gatunek);
	DUdzien = other->DUdzien;
	DUmiesiac = other->DUmiesiac;
	DUrok = other->DUrok;
}


zwierzak::zwierzak(const char* _nazwa,const char* _gatunek, int _dzien, int _miesiac, int _rok)
{
	nazwa = new char(strlen(_nazwa));
	gatunek = new char(strlen(_gatunek));
	strcpy(nazwa, _nazwa);
	strcpy(gatunek, _gatunek);
	DUdzien = _dzien;
	DUmiesiac = _miesiac;
	DUrok = _rok;
}

char * zwierzak::getNazwa()
{
	return this->nazwa;
}

char * zwierzak::getGatunek()
{
	char* cpy = this->gatunek;
	return cpy;
}

int zwierzak::getD()
{
	return DUdzien;
}

int zwierzak::getM()
{
	return DUmiesiac;
}

int zwierzak::getY()
{
	return DUrok;
}

class spis_zwierzakow
{
public:
	zwierzak* zw;
	spis_zwierzakow* pnext;
public:
	spis_zwierzakow();
	spis_zwierzakow(const spis_zwierzakow&);//konstruktor kopiujacy
	spis_zwierzakow(const spis_zwierzakow *);
	spis_zwierzakow(const spis_zwierzakow&&);//konstruktor przenoszacy
	spis_zwierzakow(zwierzak& zw);
	~spis_zwierzakow();
	spis_zwierzakow& operator +=(const zwierzak&);//operator+=
	friend ostream& operator<<(ostream& os, spis_zwierzakow& spis);//strumien zaprzyjazniony
};

ostream& operator<<(ostream& os, spis_zwierzakow&spis)//strumien zaprzyjazniony
{
	spis_zwierzakow*ptr = &spis;
	while (ptr)
	{
		os << "Zwierzak " << ptr->zw->getNazwa() << " gatunku " << ptr->zw->getGatunek() << endl;
		ptr = ptr->pnext;
	}
	return os;
}

spis_zwierzakow::spis_zwierzakow()
{
}

spis_zwierzakow::spis_zwierzakow(zwierzak& zw)
{
	this->zw = new zwierzak(zw);
	this->pnext = nullptr;
}

spis_zwierzakow::spis_zwierzakow(const spis_zwierzakow& other)//konstruktor kopiujacy
{
	this->zw = new zwierzak(other.zw);
	other.pnext?this->pnext = new spis_zwierzakow(other.pnext):false;
}

spis_zwierzakow::spis_zwierzakow(const spis_zwierzakow*spis)
{
	this->zw = spis->zw;
	this->pnext = spis->pnext;
}

spis_zwierzakow::spis_zwierzakow(const spis_zwierzakow&& spis)//konstruktor przenoszacy
{
	if (this!=&spis)
	{
		this->zw = move(spis.zw);
		this->pnext = move(spis.pnext);
	}
}

spis_zwierzakow::~spis_zwierzakow()
{
}

spis_zwierzakow & spis_zwierzakow::operator+=(const zwierzak &nowyzwierzak)
{
	if (this->zw==nullptr)
	{
		this->zw = new zwierzak(nowyzwierzak);
		return *this;
	}
	else
	{
		this->pnext = new spis_zwierzakow(this);
		this->zw = new zwierzak(nowyzwierzak);
		return *this;
	}
}

class zbior_zwierzakow:public spis_zwierzakow
{
public:
	zbior_zwierzakow();
	~zbior_zwierzakow();
	zbior_zwierzakow& operator+=(zwierzak&);
	operator int();
	spis_zwierzakow starszeniz(char*gatunek,int rok, int miesiac, int dzien);
	zwierzak* pobierz();
private:

};

zwierzak* zbior_zwierzakow::pobierz()
{
	if (!this->zw)
	{
		throw 0;
	}
	srand(time(NULL));
	int len=(int)*this;
	int id = rand() % len;
	spis_zwierzakow*ptr=this;
	for (int i = 0; i < id; i++)
	{
		ptr = ptr->pnext;
	}
	return ptr->zw;
}

zbior_zwierzakow::zbior_zwierzakow()
{
}

zbior_zwierzakow::~zbior_zwierzakow()
{
}

zbior_zwierzakow& zbior_zwierzakow::operator+=(zwierzak& zw)
{
	if (this->zw==nullptr)
	{
		this->zw = new zwierzak(zw);
		this->pnext = nullptr;
	}
	int res = strcmp(this->zw->getGatunek(),zw.getGatunek());
	if (res==0)
	{
		if (this->zw->getY()==zw.getD())
		{
			if (this->zw->getM()==zw.getM())
			{
				if (this->zw->getD() >= zw.getD())
				{
					this->pnext = new zbior_zwierzakow(*this);
					this->zw = new zwierzak(zw);
				}
				if (this->zw->getD() < zw.getD())
				{
					if (this->pnext)
					{
					spis_zwierzakow* temp=this->pnext->pnext;
					this->pnext = new spis_zwierzakow(zw);
					this->pnext->pnext = temp;
;					}
					else
					{
						this->pnext = new spis_zwierzakow(zw);
					}
				}
			}
			if (this->zw->getM()>zw.getM())
			{
				this->pnext = new zbior_zwierzakow(*this);
				this->zw = new zwierzak(zw);
			}
			if (this->zw->getM() < zw.getM())
			{
				if (this->pnext)
				{
					spis_zwierzakow* temp = this->pnext->pnext;
					this->pnext = new spis_zwierzakow(zw);
					this->pnext->pnext = temp;
					;
				}
				else
				{
					this->pnext = new spis_zwierzakow(zw);
				}
			}
		}
		if (this->zw->getY() > zw.getY())
		{
			this->pnext = new zbior_zwierzakow(*this);
			this->zw = new zwierzak(zw);
		}
		if (this->zw->getY() < zw.getY())
		{
			if (this->pnext)
			{
				spis_zwierzakow* temp = this->pnext->pnext;
				this->pnext = new spis_zwierzakow(zw);
				this->pnext->pnext = temp;
				;
			}
			else
			{
				this->pnext = new spis_zwierzakow(zw);
			}
		}
	}
	if (res>0)
	{
		this->pnext = new zbior_zwierzakow(*this);
		this->zw = new zwierzak(zw);
	}
	if (res<0)
	{
		if (this->pnext)
		{
			spis_zwierzakow* temp = this->pnext->pnext;
			this->pnext = new spis_zwierzakow(zw);
			this->pnext->pnext = temp;
			;
		}
		else
		{
			this->pnext = new spis_zwierzakow(zw);
		}
	}
	return *this;
}

zbior_zwierzakow::operator int() 
{
	int i = 0;
	spis_zwierzakow* ptr = this;
	if (!this->zw)
	{
		return i;
	}
	while (ptr)
	{
		i++;
		ptr = ptr->pnext;
	}
	return i;
}


//po tej funkcji trzeba posprzatac, co nie jest mozliwe z jej wnetrza
//usuwam tylko wskazniki na zwierze, bo usuwanie calosci mogloby powodowac wycieki pamieci i read access violation w dalszej czesci programu
spis_zwierzakow zbior_zwierzakow::starszeniz(char * _gatunek, int _rok, int _miesiac, int _dzien)
{
	spis_zwierzakow spis;
	spis_zwierzakow*ptr = this;
	while (ptr)
	{
		if (!this->zw)
		{
			ptr = ptr->pnext;
			continue;
		}
		if (strcmp(this->zw->getGatunek(),_gatunek)==0)
		{
			if (this->zw->getY()<_rok)
			{
				spis += this->zw;
				delete this->zw;
				this->zw = nullptr;
				continue;
			}
			if (this->zw->getY() == _rok)
			{
				if (this->zw->getM() < _miesiac)
				{
					spis += this->zw;
					delete this->zw;
					this->zw = nullptr;
					continue;
				}
			}
			if (this->zw->getM() == _miesiac)
			{
				if (this->zw->getD() <= _dzien)
				{
					spis += this->zw;
					delete this->zw;
					this->zw = nullptr;
					continue;
				}
			}
		}
	}
	ptr = this;
	spis_zwierzakow*back_ptr = this;
	while (ptr)//best i could do, no wiecej posprzatac sie nie da
	{
		if (ptr->pnext)
		{
			ptr = ptr->pnext;
			if (ptr->zw==nullptr)
			{
				if (ptr->pnext)
				{
					back_ptr = ptr->pnext;
					delete ptr;
					ptr = back_ptr;
				}
			}
		}
		else
		{
			break;
		}
	}
	return spis;
}




int main()
{
	spis_zwierzakow spis;
	zwierzak falafel("falafel","kret",1,1,2000);
	zwierzak kebab("kebab", "kot", 12, 4, 2005);
	spis += falafel;
	spis += kebab;
	cout << spis;
	spis_zwierzakow spis2=spis;
	spis_zwierzakow spis3move = move(spis2);
	zbior_zwierzakow zbior;
	zbior += kebab;
	zbior += falafel;//kolejnosc podawania nie ma znaczenia, zwierzaki sa posortowane
	cout<<zbior.pobierz()->getGatunek();
    std::cout << "Hello World!\n"; 
}

