#include <iostream>
#include <utility>
#include <string>
using namespace std;


///////////////////////////////////////////////////////////////////////////////
class task
{
	string todo = "empty task";
	int date = 0;

public:
	task(string, int);

	task() = default;
	task(const task &) = default;
	task & operator=(const task &) = default;

	void complete(void);
	int operator>(const task &);	// porownoje daty
	int operator==(const task &);	// porownuje cale zadania
	friend ostream & operator<<(ostream &, const task &);
	friend istream & operator>>(istream &, task &);
};

task::task(string todo, int date) : todo(todo), date(date) {}

void task::complete(void)
{
	cout << "\ntask " << todo << " scheduled for " << date << " done successfully!";
}

int  task::operator>(const task &rt)
{
	return date > rt.date;
}

int  task::operator==(const task &rt)
{
	return ((todo == rt.todo) && (date == rt.date));
}

ostream & operator<<(ostream &os, const task &rt)
{
	os << rt.todo;
	os << " ";
	os << rt.date;
	return os;
};

istream & operator>>(istream &is, task &rt)
{
	return is >> rt.todo >> rt.date;
};


struct q_elem
{
	task t;
	q_elem * next;
	q_elem(const task &ctr) :t(ctr), next(nullptr) {};
};


///////////////////////////////////////////////////////////////////////////////
class queue
{
protected:
	q_elem *head, /* nullptr dla pustej kolejki */
		*tail; /* istotny jesli head != nullptr */

public:
	queue() :head(nullptr) {}

	virtual queue & operator+=(const task &rq) // virtual!!!
	{
		q_elem *qep = new q_elem(rq);
		if (head)
			tail->next = qep;
		else
			head = qep;

		tail = qep;

		return *this;
	}

	queue(const queue &rq) :head(nullptr)
	{
		q_elem *qep = rq.head;

		while (qep)
		{
			(*this) += qep->t;
			qep = qep->next;
		}
	}

	queue(queue &&rrq) : head(rrq.head), tail(rrq.tail)
	{
		rrq.head = rrq.tail = nullptr;
	}

	~queue()
	{
		while (head)
		{
			const q_elem * qep = head;
			head = head->next;
			delete qep;
		}
	}

	void empty()	// pozostawia obiekt pusty (head==nullptr)
	{
		while (head)
		{
			const q_elem * qep = head;
			head = head->next;
			delete qep;
		}
	}

	queue & operator=(const queue &rq)
	{
		if (&rq == this)
			return *this;

		empty();

		q_elem *qep = rq.head;
		while (qep)
		{
			(*this) += qep->t;
			qep = qep->next;
		}

		return *this;
	}

	queue & operator=(queue &&rq)
	{
		swap(head, rq.head);
		swap(tail, rq.tail);
		return *this;
	}

	int contains(const task & ctr)
	{
		q_elem *qep = head;
		while (qep)
			if (qep->t == ctr)
				return 1;
			else
				qep = qep->next;

		return 0;
	}

	friend istream & operator>>(istream &is, queue &rq)
	{
		task t;		// wymaga konstruktora bezargumentowego task()

		rq.empty();

		while (is >> t)
			rq += t;

		return is;
	}

	friend ostream & operator<<(ostream &os, const queue &rq)
	{
		q_elem *qep = rq.head;
		while (qep)
		{
			os << qep->t << " ";
			qep = qep->next;
		}

		return os;
	}

};

///////////////////////////////////////////////////////////////////////////////
class sorted_q :public queue
{
public:
	sorted_q & operator+=(const task &rq)	// inny typ zwracany - ok tutaj 
	{
		q_elem * const newel = new q_elem(rq);

		if ((!head) || (head->t > rq))	// wstaw na pocz�tek
		{
			newel->next = head;
			head = newel;
		}
		else
		{
			q_elem * pq = head;
			while (pq->next && !(pq->next->t > rq))
				pq = pq->next;

			newel->next = pq->next;
			pq->next = newel;
		}

		if (!newel->next)
			tail = newel;

		return *this;
	}

	void complete(queue &tobedone)
	{
		q_elem *qep = head;
		while (qep)
		{
			if (tobedone.contains(qep->t))
				qep->t.complete();
			qep = qep->next;
		}
	}

	using queue::operator=;

	//	kolejno�� wywo�ywania konstruktor�w powoduje ze poni�sza deklaracja nie jest potrzebna
	//
	//	using queue::queue;

	//	automatyczne konwersje o kl. bazowej i metody wirtualne powoduj� �e poni�sze nie s� niezb�dne
	//
	//	friend istream & operator>>(istream &is, sorted_q &rq)
	//	friend ostream & operator<<(ostream &os, const sorted_q &rq)

};

int main()
{
	queue q1;
	sorted_q s1;

	q1 += task("task a", 20161020);
	q1 += task("task b", 20161020);
	q1 += task("task c", 20161515);
	q1 += task("task d", 20160505);

	queue q2 = move(q1);
	cout << "q1 " << q1 << endl << "q2 " << q2 << endl;
	q1 = move(q2);
	cout << "q1 " << q1 << endl << "q2 " << q2 << endl;
	q2 = q1;
	q1 += task("task e", 20160505);
	cout << endl << q1;
	q1 = q2;
	cout << endl << q1;

	s1 = q1;

	cout << endl << s1;
	s1 += task("task f", 900000000);
	s1 += task("task g", 00000);
	cout << endl << s1;
	s1.complete(q1);
	cin >> s1;
	cout << endl << s1;
	cout.flush();
}