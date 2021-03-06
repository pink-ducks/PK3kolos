// Osoba.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
using namespace std;
class Person
{
private:
	string name; 
string surname;
int yearBirth;
int monthBirth;
int dayBirth;
//metody 

public:
	Person(string, string, int, int, int);
	Person()= default;
	Person(const Person &) = default;
	//~Person();
	int GetYear()
	{
		return yearBirth;
	}
	int GetMonth()
	{
		return monthBirth;
	}
	int GetdayBirth()
	{
		return dayBirth;
	}
	friend istream & operator>>(istream &is, Person &rt);
	int operator > (const Person &);
	Person & operator = (const Person &) = default;
};
Person::Person(string name, string surname, int datebirth, int monthbirth, int yearbirth)
{
	this->name = name;
	this->surname = surname;
	this->dayBirth = datebirth;
	this->monthBirth = monthbirth;
	this->yearBirth = yearbirth;
}
int Person ::operator > (const Person &rt)
{
	return yearBirth > rt.yearBirth;
}
istream & operator>>(istream &is, Person & rt)
{
	return is >> rt.name >> rt.surname >> rt.yearBirth >> rt.monthBirth >> rt.dayBirth;
};

//struktura do kolejki
struct queue
{
	Person p;
	queue * next;
	queue(const Person & ctr) : p(ctr), next(nullptr) {};
};
class stack
{
protected:
	queue * head; //nullptr for empty queue
	queue * tail; //important ih head != nullptr
public:
	//kontruktor bezargumentowy
	stack() : head(nullptr)
	{}
	//konstruktor kopiujący 
	stack(const stack & st) : head(nullptr)
	{
		queue * qep = st.head;
		while (qep)
		{
			(*this) += qep->p;
			qep = qep->next;
		}
	}
	//operator wstawiający osobę do stosu 
	virtual stack & operator += (const Person & rq)
	{
		queue * qep = new queue(rq);
		if (head)
		{
			tail->next = qep;
		}
		else
		{
			head = qep;
		}
		tail = qep;
		return *this;
	}
	//operator przypisania
	stack & operator = (const stack & rq)
	{
		if (&rq == this)
		{
			return *this;
		}
		queue * qep = rq.head;
		while (qep)
		{
			(*this) += qep->p;
			qep = qep->next;
		}
		return *this;
	}
	//operator przenoszący 
	//stack & operator=(const stack && rq)
	//{
		//swap(head, rq.head);
		//swap(tail, rq.tail);
	//	return (*this);
	//}
	~stack()
	{
		while (head)
		{
			const queue * qep = head;
			head = head->next;
			delete qep;
		}
	}
};
class list : stack
{
public:
	friend istream & operator >> (istream &is, stack & rq);
	list & operator += (const Person & rq)
	{
		queue * const newel = new queue(rq);
		if ((!head) || head->p > rq)
		{
			newel->next = head;
			head = newel;
		}
		else
		{
			queue * pq = head;
			while (pq->next && !(pq->next->p > rq))
			{
				pq = pq->next;
			}
			newel->next = pq->next;
			pq->next = newel;
		}
		if (!newel->next)
		{
			tail = newel;
		}
		return (*this);
	}
	using stack::operator=;
	//operator do konwersji int 
	operator int()
	{
		int i = 0;
		queue * qep = head;
		while (qep)
		{
			i++;
			qep = qep->next;
		}
		return i; 
	}
	Person operator--()
	{
			queue * toReturn = head;
			queue * toDelete = head;
			queue * tmp = head->next;
			if (head) //wyrzucaj pierwszy
			{
				delete toDelete;
				head = tmp;
				return toReturn->p;
			}
			else //nie ma glowy wyrzucaj wyjatek
			{
				throw "Exeption e"; 
			}
	}
};
istream & operator >> (istream &is, stack & rt)
{
	Person p;
	while (is >> p)
		rt += p;
	return is;
}

int main()
{
	stack s1;
	s1 += Person("Lewis", "Hamilton", 7, 1, 1985);
	s1 += Person("Max", "Verstapen", 3, 9, 1997);
	s1 += Person("Daniel", "Ricciardo", 1, 7, 1989);
	s1 += Person("Niki", "Lauda", 22, 2, 1949);
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
