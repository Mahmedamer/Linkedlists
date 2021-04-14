#include "LinkedList.h"
#include <iostream>
#include "Polynomial.h"
using namespace std;

//Functions 
#pragma region Global
template<class T>
bool InsertSorted(LinkedList<T>& L, T data)
{
	Node<T>* ptr = L.getHead();
	if (!ptr)
	{
		Node<T>* N = new Node<T>(data);
		L.setHead(N);
		return true;
	}
	if (!ptr->getNext())
	{
		if (ptr->getItem() > data)
		{
			Node<T>* N = new Node<T>(data);
			N->setNext(L.getHead());
			L.setHead(N);
			return true;
		}
		else if (ptr->getItem() < data)
		{
			Node<T>* N = new Node<T>(data);
			L.getHead()->setNext(N);
			return true;
		}
		else
		{
			return false;
		}
	}
	Node<T>* prev = ptr;
	ptr = ptr->getNext();
	while (ptr)
	{
		if (ptr->getItem() > data)
		{
			Node<T>* N = new Node<T>(data);
			prev->setNext(N);
			N->setNext(ptr);
			return true;
		}
		else if (ptr->getItem() < data)
		{
			prev = ptr;
			ptr = ptr->getNext();
		}
		else
		{
			return false;
		}
	}
	Node<T>* N = new Node<T>(data);
	prev->setNext(N);
	return true;
}

template<class T>
LinkedList<T>* CloneList(LinkedList<T>& L)
{
	LinkedList<T>* Clone = new LinkedList<T>();
	Node<T>* ptr = L.getHead();
	if (!ptr)
	{
		return Clone;
	}
	Node<T>* N = new Node<T>(ptr->getItem());
	Clone->setHead(N);
	Node<T>* prev = N;
	ptr = ptr->getNext();
	while (ptr)
	{
		Node<T>* N = new Node<T>(ptr->getItem());
		prev->setNext(N);
		prev = N;
		ptr = ptr->getNext();
	}
	return Clone;
}

template<class T>
void SignSplit(LinkedList<T>& L, LinkedList<T>& Lneg, LinkedList<T>& Lpos)
{
	Node<T>* ptr = L.getHead();
	Node<T>* posptr = Lneg.getHead();
	Node<T>* negptr = Lpos.getHead();
	while (ptr)
	{
		if (ptr->getItem() > 0)
		{
			Node<T>* N = new Node<T>(ptr->getItem());
			if (!posptr)
			{
				Lpos.setHead(N);
				posptr = N;
			}
			else
			{
				posptr->setNext(N);
				posptr = N;
			}
		}
		else if (ptr->getItem() < 0)
		{
			Node<T>* N = new Node<T>(ptr->getItem());
			if (!negptr)
			{
				Lneg.setHead(N);
				negptr = N;
			}
			else
			{
				negptr->setNext(N);
				negptr = N;
			}
		}
		ptr = ptr->getNext();
	}
}

template<class T>
class Dictionary
{
public:
	T data;
	int occurance;
	Dictionary() {};
	Dictionary(const T& d, int o) { data = d; occurance = o; };
	virtual ~Dictionary() {};
	bool operator == (const Dictionary& D)
	{
		if (D.data == data)
			return true;
		return false;
	}
};
template<class T>
ostream& operator << (ostream& out, const Dictionary<T>& D)
{
	out << "{ " << D.data << " -> " << D.occurance << " }";
	return out;
}
template<class T>
LinkedList<Dictionary<T>>* MakeDictionary(LinkedList<T>& L)
{
	LinkedList<Dictionary<T>>* Result = new LinkedList<Dictionary<T>>();
	Node<Dictionary<T>>* resultptr = Result->getHead();
	Node<T>* ptr = L.getHead();
	while (ptr)
	{
		T data = ptr->getItem();
		int occurance = L.CountOccurance(data);
		Node<Dictionary<T>>* N = new Node<Dictionary<T>>();
		N->setItem(Dictionary<T>(data, occurance));
		if (Result->CountOccurance(N->getItem()) == 0)
		{
			if (resultptr)
			{
				resultptr->setNext(N);
				resultptr = N;
			}
			else
			{
				Result->setHead(N);
				resultptr = N;
			}
		}
		ptr = ptr->getNext();
	}
	return Result;
}

template<class T>
LinkedList<T> MergeSorted(LinkedList<T>& L1, LinkedList<T>& L2)
{
	LinkedList<T> L;
	Node<T>* Lptr = L.getHead();
	Node<T>* L1ptr = L1.getHead();
	Node<T>* L2ptr = L2.getHead();
	while (L1ptr || L2ptr)
	{
		if (L1ptr && L2ptr)
		{
			if (L1ptr->getItem() < L2ptr->getItem())
			{
				Node<T>* N = new Node<T>(L1ptr->getItem());
				L1ptr = L1ptr->getNext();
				if (!Lptr)
				{
					L.setHead(N);
					Lptr = N;
				}
				else
				{
					Lptr->setNext(N);
					Lptr = N;
				}
			}
			else
			{
				Node<T>* N = new Node<T>(L2ptr->getItem());
				L2ptr = L2ptr->getNext();
				if (!Lptr)
				{
					L.setHead(N);
					Lptr = N;
				}
				else
				{
					Lptr->setNext(N);
					Lptr = N;
				}
			}
		}
		else if (L1ptr)
		{
			Node<T>* N = new Node<T>(L1ptr->getItem());
			L1ptr = L1ptr->getNext();
			if (!Lptr)
			{
				L.setHead(N);
				Lptr = N;
			}
			else
			{
				Lptr->setNext(N);
				Lptr = N;
			}
		}
		else
		{
			Node<T>* N = new Node<T>(L2ptr->getItem());
			L2ptr = L2ptr->getNext();
			if (!Lptr)
			{
				L.setHead(N);
				Lptr = N;
			}
			else
			{
				Lptr->setNext(N);
				Lptr = N;
			}
		}
	}
	return L;
}

template<class T>
LinkedList<T>* SumLists(LinkedList<T>& L1, LinkedList<T>& L2)
{
	if (L1.getCount() != L2.getCount())
	{
		return nullptr;
	}
	LinkedList<T>* L = new LinkedList<T>();
	Node<T>* Lptr = L->getHead();
	Node<T>* L1ptr = L1.getHead();
	Node<T>* L2ptr = L2.getHead();
	while (L1ptr || L2ptr)
	{
		Node<T>* N = new Node<T>(L1ptr->getItem() + L2ptr->getItem());
		if (!Lptr)
		{
			L->setHead(N);
			Lptr = N;
		}
		else
		{
			Lptr->setNext(N);
			Lptr = N;
		}
		L1ptr = L1ptr->getNext();
		L2ptr = L2ptr->getNext();
	}
	return L;
}

template<class T>
void Reorder_X(LinkedList<T>& L, T X)
{
	Node<T>* ptr = L.getHead();
	if (!ptr || !ptr->getNext())
		return;
	Node<T>* prev = ptr;
	ptr = ptr->getNext();
	while (ptr)
	{
		if (ptr->getItem() <= X)
		{
			prev->setNext(ptr->getNext());
			ptr->setNext(L.getHead());
			L.setHead(ptr);
		}
		else
		{
			prev = ptr;
		}
		ptr = prev->getNext();
	}

}


template<class T>
void ShiftLargest(LinkedList<T>& L)
{
	Node<T>* ptr = L.getHead();
	if (!ptr || !ptr->getNext())
		return;
	while (ptr->getNext())
	{
		if (ptr->getItem() > ptr->getNext()->getItem())
		{
			T item1 = ptr->getItem();
			ptr->setItem(ptr->getNext()->getItem());
			ptr->getNext()->setItem(item1);
		}
		ptr = ptr->getNext();
	}

}

template<class T>
void RemoveDuplicates(LinkedList<T>& L)
{
	Node<T>* ptr = L.getHead();
	if (!ptr || !ptr->getNext())
		return;
	while (ptr)
	{
		T data = ptr->getItem();
		Node<T>* prev = ptr;
		Node<T>* Next = ptr->getNext();
		while (Next)
		{
			if (Next->getItem() == data)
			{
				prev->setNext(Next->getNext());
				delete Next;
			}
			else
			{
				prev = Next;
			}
			Next = prev->getNext();
		}
		ptr = ptr->getNext();
	}
}

///////////////////////////////////////////////////////////////////////
#pragma endregion

int main()
{
	LinkedList<int> L1;	//create an object of class LinkedList
	//LinkedList<int> L2;	//create an object of class LinkedList
	//LinkedList<int> L3;	//create an object of class LinkedList
	int val;

	cout<<"Please enter int values to add to the list 1 (-1 to stop):\n";
	cin>>val;
	while(val != -1)
	{
		L1.InsertEnd(val);
		cin>>val;
	}
	//cout << "Please enter int values to add to the list 2 (-1 to stop):\n";
	//cin >> val;
	//while (val != -1)
	//{
	//	L2.InsertEnd(val);
	//	cin >> val;
	//}
	/*----------------------------------------------*/
	//cout<<"List 1 : "<<endl;
	//for(int i=0 ;i<=L1.getCount()+1;i++)
	//	L1.PrintKth(i);
	//cout<<endl;
	/*----------------------------------------------*/
	//L1.InsertSorted(1);
	//L1.InsertSorted(3);
	//L1.InsertSorted(10);
	L1.newReverse();
	cout << "List 1 :" ;
	L1.PrintList();
	/*----------------------------------------------*/
	//L2 = *L1.CloneList();
	//cout << "List 2 :" ;
	//L2.PrintList();
	/*----------------------------------------------*/
	//cout<<"After Split "<<endl;
	//LinkedList<int>* LN;
	//LinkedList<int>* LP;
	//L1.SignSplit(LN,LP);
	//cout << "List 1 :" ;
	//L1.PrintList();
	//cout << "List 2 :" ;
	//LN->PrintList();
	//cout << "List 3 :" ;
	//LP->PrintList();
	//delete LN;
	//delete LP;
	/*-------------------------------------------------*/
	//Node<int> *N = L1.RemoveMin();
	//cout << "Removed : "<<N->getItem()<<endl;
	//cout << "List 1 :" ;
	//L1.PrintList();
	//cout << "-----------------Delete First Element of List 1-----------------" << endl;
	//L1.DeleteFirst();
	//cout << "List 1 :";
	//L1.PrintList();
	//cout << "-----------------Delete Last Element of List 2-----------------" << endl;
	//L2.DeleteLast();
	//cout << "List 2 :";
	//L2.PrintList();
	//cout << "----------------Searching For 2 in List 1 using Find---------------" << endl;
	//cout << L1.Find(2) << endl;
	//cout << "-------------Searching For 2 in List 2 using CountOccurances----------" << endl;
	//cout << L2.CountOccurance(2) << endl;
	//cout << "----------------Searching For 100 in List 1 using Find---------------" << endl;
	//cout << L1.Find(100) << endl;
	//cout << "-------------Searching For 100 in List 2 using CountOccurances----------" << endl;
	//cout << L2.CountOccurance(100) << endl;
	//cout << "----------------Deleting 3 From List 1 using DeleteNode---------------" << endl;
	//L1.DeleteNode(3);
	//cout << "List 1 :";
	//L1.PrintList();
	//cout << "----------------Deleting 3 From List 2 using DeleteNodes---------------" << endl;
	//L2.DeleteNodes(3);
	//cout << "List 2 :";
	//L2.PrintList();
	//cout << "-------------------Merge List 2 To List 1---------------------" << endl;
	//L1.Merge(L2);
	//cout << "List 1 :";
	//L1.PrintList();
	//cout << "List 2 :";
	//L2.PrintList();
	//cout << "-----------------------Reverse List 1------------------------" << endl;
	//L1.Reverse();
	//cout << "List 1 :";
	//L1.PrintList();

	//Polynomial P1, P2;
	//P1.AddTerm(Term(0, -20));
	//P1.AddTerm(Term(2, -7));
	//P1.AddTerm(Term(4, 52));
	//P2.AddTerm(Term(5, 30));
	//P2.AddTerm(Term(3, 2));
	//P2.AddTerm(Term(0, -10));
	//P2.AddTerm(Term(4, -10));
	//P1.PrintPoly();
	//P2.PrintPoly();
	//cout << P1.getCoeff(4) << endl;
	//cout << P1.getCoeff(3) << endl;
	//cout << P1.getCoeff(2) << endl;
	//cout << P2.getCoeff(2) << endl;
	//cout << P2.getCoeff(1) << endl;
	//cout << P2.getCoeff(0) << endl;
	//P1.setCoeff(0, 2);
	//P1.setCoeff(10, 5);
	//P1.setCoeff(20, 5);
	//P1.setCoeff(20, 0);
	//P1.PrintPoly();
	//P2.PrintPoly();
	//P1.AddPoly(P2);
	//P1.PrintPoly();
	//P2.PrintPoly();
	return 0;
}

