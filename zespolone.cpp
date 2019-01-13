#include <iostream>
#include <sstream>
class zespolona
{
public:
	double re;
	double im;
	zespolona();
	zespolona(double, double);
	zespolona(const zespolona& zes);
	~zespolona();
	zespolona operator=(const zespolona& other);
	zespolona operator=(const zespolona&&other);
	bool operator<(const zespolona& a);
private:

};


zespolona::zespolona()
{
	this->im = 0;
	this->re = 0;
}

zespolona::zespolona(double re, double im)
{
	this->re = re;
	this->im = im;
}

zespolona::zespolona(const zespolona& zes)
{
	this->im = zes.im;
	this->re = zes.re;
}

zespolona::~zespolona()
{
}

zespolona zespolona::operator=(const zespolona& other)
{
	re = other.re;
	im = other.im;
	return *this;
}

zespolona zespolona::operator=(const zespolona&& other)
{
	this->re = std::move(other.re);
	this->im = std::move(other.im);
	return *this;
}

bool zespolona::operator<(const zespolona&a)
{
	if (sqrt(this->re*this->re + this->im*this->im)<sqrt(a.re*a.re+a.im*a.im))
	{
		return true;
	}
	else
	{
		return false;
	}
}

class tabzes
{
public:
	zespolona *tablica;
	int count=0;

	tabzes();
	~tabzes();
	zespolona operator [](const int index);
	tabzes& operator =(const tabzes &other);
	tabzes& operator=(const tabzes&&other);
	tabzes& operator+=(const zespolona& zes);

	friend std::istream& operator>>(std::istream& is, tabzes&tab);//dodatkowy operator pomocniczy
private:

};

tabzes::tabzes()
{
}

tabzes::~tabzes()
{
}

zespolona tabzes::operator[](const int index)
{
	zespolona ret;
	if (index>=count)
	{
		throw -1;
	}
	else
	{
		return ret=tablica[index];
	}
}

tabzes& tabzes::operator=(const tabzes &other)//operator przypisania
{
	if (this==&other)
	{
		return *this;
	}
	delete [] this->tablica;//usun stare dane
	this->tablica = new zespolona[other.count];//kopiuj dane z other
	for (int i = 0; i < count; i++)
	{
		this->tablica[i] = other.tablica[i];
	}
	return *this;//zwroc obiekt
}

tabzes& tabzes::operator=(const tabzes&&other)//przenosz¹cy operator przypisania
{
	if (this==&other)
	{
		this->tablica = std::move(other.tablica);
		this->count = std::move(other.count);
	}
	return *this;
}

tabzes& tabzes::operator+=(const zespolona& zes)
{
	zespolona*temp = this->tablica;
	this->tablica = new zespolona[count + 1];
	for (int i = 0; i < count; i++)
	{
		this->tablica[i] = temp[i];
	}
	this->tablica[count] = zes;
	count++;
	return *this;
}

std::istream& operator>>(std::istream&is, tabzes&tab)
{
	zespolona zes;
	while (is)
	{
		is >> zes.re;
		is >> zes.im;
		tab += zes;
	}
	return is;
}

class kolzes:public tabzes
{

public:
	kolzes();
	~kolzes();
	friend std::istream& operator>>(std::istream& is, kolzes&kz);
	kolzes& operator +=(const zespolona&z);
	zespolona& pop();
	operator zespolona();
private:
};

kolzes::kolzes()
{
}

kolzes::~kolzes()
{
}

std::istream& operator>>(std::istream&is, kolzes&kz)
{

	zespolona temp;
	zespolona min;
	int minix;
	while (is)
	{
		is >> kz;
	}	
	for (int i = 0; i < kz.count; i++)
	{
		min = kz[i];
		for (int j = i; i < kz.count; i++)
		{
			if (kz[j]<min)
			{
				min = kz[j];
				minix = j;
			}
		}
		temp = kz[i];
		kz[i] = min;
		kz[minix] = temp;
	}
	return is;
}

kolzes& kolzes::operator+=(const zespolona&z)
{
	if (!this->tablica)
	{
		this->tablica = new zespolona[1];
		this->tablica[0] = z;
		count = 1;
		return *this;
	}
	zespolona* temp = this->tablica;
	this->tablica = new zespolona[this->count + 1];
	bool inserted=false;
	for (int i = 0; i < count+1; i++)
	{
		if (temp[i]<z)
		{
			this->tablica[i] = temp[i];
		}
		else
		{
			if (inserted==false)
			{
				this->tablica[i] = z;
				inserted = true;
			}
			else
			{
				this->tablica[i] = temp[i-1];
			}
		}
	}
	count++;
	delete []temp;
	return *this;
}

zespolona& kolzes::pop()
{
	if (!this->tablica)
	{
		throw -1;
	}
	zespolona*temp=this->tablica;
	zespolona zes;
	zes.im = tablica[0].im;
	zes.re = tablica[0].re;
	this->tablica = new zespolona[this->count - 1];
	for (int i = 1; i < count-1; i++)
	{
		this->tablica[i] = temp[i];
	}
	count--;
	delete[]temp;
	return zes;
}

kolzes::operator zespolona()
{
	zespolona zes;
	for (int i = 0; i < count; i++)
	{
		zes.re = tablica[i].re;
		zes.im = tablica[i].im;
	}
	return zespolona(zes);
}

int main()
{
	kolzes kol;
	tabzes tab;
	zespolona a(1, 2);
	zespolona b(3, 5);
	zespolona c(-1, 3);
	zespolona d(15, 10);
	try {
		tab += a;
		tab += b;
		tab += c;
		tab += d;
		std::cout << " " << std::to_string(tab[0].re) << std::endl;
		std::cout << " " << std::to_string(tab[1].re) << std::endl;
		std::cout << " " << std::to_string(tab[2].re) << std::endl;
		std::cout << " " << std::to_string(tab[3].re) << std::endl;
		kol += a;
		kol += b;
		kol += c;
		kol += d;
		std::cout << " " << std::to_string(kol[0].re) << std::endl;
		std::cout << " " << std::to_string(kol[1].re) << std::endl;
		std::cout << " " << std::to_string(kol[2].re) << std::endl;
		std::cout << " " << std::to_string(kol[3].re) << std::endl;
		
	}
	catch(int i)
	{

	}


	return 0;
}