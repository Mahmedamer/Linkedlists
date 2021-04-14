#pragma once
#include<iostream>
using namespace std;
#include "Node.h"
#include "Term.h"

class Polynomial
{
public:
	Polynomial() 
	{ 
		Head = nullptr;
		degree = 0;
	};

	~Polynomial() {};
	
	void AddTerm(const Term & newTerm)
	{
		Node<Term>* ptr = Head;
		Node<Term>* prev = nullptr;
		while (ptr)
		{
			if (ptr->getItem().getPower() < newTerm.getPower())
			{
				break;
			}
			prev = ptr;
			ptr = ptr->getNext();
		}
		if (prev)
		{
			Node<Term>* N = new Node<Term>();
			N->setItem(newTerm);
			N->setNext(prev->getNext());
			prev->setNext(N);
		}
		else
		{
			Node<Term>* N = new Node<Term>();
			N->setItem(newTerm);
			N->setNext(Head);
			Head = N;
			degree = newTerm.getPower();
		}
	}

	void DeleteTerm(int power)
	{
		Node<Term>* ptr = Head;
		if (!ptr)
			return;
		bool found = false;
		Node<Term>* prev = nullptr;
		while (ptr)
		{
			if (ptr->getItem().getPower() == power)
			{
				found = true;
				break;
			}
			prev = ptr;
			ptr = ptr->getNext();
		}
		if(found)
		{
			if (prev)
			{
				prev->setNext(ptr->getNext());
				delete ptr;
			}
			else
			{
				Head = Head->getNext();
				if (Head)
				{
					degree = Head->getItem().getPower();
				}
				else
				{
					degree = 0;
				}
				delete ptr;
			}
		}
	}

	void PrintPoly() const
	{
		Node<Term>* ptr = Head;
		while (ptr)
		{
			if (ptr->getItem().getPower() == 0) 
			{
				if (ptr->getItem().getCoeff() < 0)
				{
					cout << "(" << ptr->getItem().getCoeff() << ")";
				}
				else
				{
					cout << ptr->getItem().getCoeff();
				}
			}
			else
			{
				if (ptr->getItem().getCoeff() < 0)
				{
					cout << "(" << ptr->getItem().getCoeff() << ")" <<" X^" << ptr->getItem().getPower();
				}
				else
				{
					cout << ptr->getItem().getCoeff() << " X^" << ptr->getItem().getPower();
				}
			}
			if (ptr->getNext())
			{
				cout << " + ";
			}
			ptr = ptr->getNext();
		}
		cout << endl;
	}

	double getCoeff(int power) const 
	{
		Node<Term>* ptr = Head;
		while (ptr)
		{
			if (ptr->getItem().getPower() == power)
			{
				return ptr->getItem().getCoeff();
			}
			ptr = ptr->getNext();
		}
		return 0;
	}

	void setCoeff(double newCoeff, int power)
	{
		if (newCoeff == 0)
		{
			DeleteTerm(power);
			return;
		}
		else
		{
			Node<Term>* ptr = Head;
			while (ptr)
			{
				if (ptr->getItem().getPower() == power)
				{
					ptr->setItem(Term(power, newCoeff));
					return;
				}
				ptr = ptr->getNext();
			}
			AddTerm(Term(power, newCoeff));
		}
	}

	void AddPoly(Polynomial P)
	{
		Node<Term>* ptr = P.Head;
		while (ptr)
		{
			int pow = ptr->getItem().getPower();
			double newCoeff = ptr->getItem().getCoeff() + getCoeff(ptr->getItem().getPower());
			setCoeff(newCoeff, pow);
			ptr = ptr->getNext();
		}
	}

private:
	Node<Term>* Head;
	int degree;
};