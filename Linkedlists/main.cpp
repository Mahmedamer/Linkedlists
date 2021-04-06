#include "LinkedList.h"
#include <iostream>
using namespace std;

//Function prototypes 

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


///////////////////////////////////////////////////////////////////////

int main()
{
	LinkedList<int> L1;	//create an object of class LinkedList
	LinkedList<int> L2;	//create an object of class LinkedList
	LinkedList<Dictionary<int>> L3;	//create an object of class LinkedList
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
	L3 = *MakeDictionary(L1);
	cout << "List 1 :" ;
	L1.PrintList();
	//cout << "List 2 :";
	//L2.PrintList();
	cout << "List 3 :";
	L3.PrintList();
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
	return 0;
}

