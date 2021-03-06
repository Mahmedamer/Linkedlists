#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:
	Node<T>* getHead() const
	{
		return Head;
	}
	void setHead(Node<T>*N)
	{
		 Head = N;
	}
	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll(); 
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{		
		cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	int getCount()
	{
		int i = 0;
		Node<T>* ptr = Head;
		while (ptr)
		{
			i++;
			ptr = ptr->getNext();
		}
		return i;
	}

	LinkedList<T> (const LinkedList<T>& L)
	{
		Node<T>* ptr = L.getHead();
		if (!ptr)
		{
			return;
		}
		Node<T>* N = new Node<T>(ptr->getItem());
		Head=N;
		Node<T>* prev = N;
		ptr = ptr->getNext();
		while (ptr)
		{
			Node<T>* N = new Node<T>(ptr->getItem());
			prev->setNext(N);
			prev = N;
			ptr = ptr->getNext();
		}
	}

	void operator = (const LinkedList<T>& L)
	{
		DeleteAll();
		Node<T>* ptr = L.getHead();
		if (!ptr)
		{
			return;
		}
		Node<T>* N = new Node<T>(ptr->getItem());
		Head=N;
		Node<T>* prev = N;
		ptr = ptr->getNext();
		while (ptr)
		{
			Node<T>* N = new Node<T>(ptr->getItem());
			prev->setNext(N);
			prev = N;
			ptr = ptr->getNext();
		}
	}

	////////////////     Requirements of Exercise 1  ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		Node<T>* N = new Node<T>(data);
		// If Current List Is Empty, Set Head To New Node
		if (!Head)
		{
			Head = N;
			return;
		}
		// Otherwise Get Last Node Of Curent Last
		Node<T>* ptr = Head;
		while (ptr->getNext()) 
		{
			ptr = ptr->getNext();
		}
		// Then Append New Node To It
		ptr->setNext(N);
	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(T Key)
	{
		Node<T>* ptr = Head;
		while (ptr) {
			if (ptr->getItem() == Key)
				return true;
			ptr = ptr->getNext();
		}
		return false;
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value)
	{
		int count = 0;
		Node<T>* ptr = Head;
		while (ptr) {
			if (ptr->getItem() == value)
				count++;
			ptr = ptr->getNext();
		}
		return count;
	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst()
	{
		// If Head Is Not Null
		if (Head)
		{
			Node<T>* ptr = Head->getNext();
			delete Head;
			Head = ptr;
		}
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		Node<T>* ptr = Head;
		// List Contains 0 Elements
		if (!ptr) 
		{
			return;
		}
		// List Contains 1 Element 
		if (!ptr->getNext()) 
		{
			delete ptr;
			Head = nullptr;
			return;
		}
		// Otherwise
		Node<T>* beforelast = ptr;
		ptr = ptr->getNext();
		while (ptr->getNext())
		{
			beforelast = ptr;
			ptr = ptr->getNext();
		}
		delete ptr;
		beforelast->setNext(nullptr);
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value)
	{
		Node<T>* ptr = Head;
		// List Contains 0 Elements
		if (!ptr) 
		{
			return false;
		}
		// List Contains 1 Element
		if (!ptr->getNext()) 
		{
			if (ptr->getItem() == value) {
				delete ptr;
				Head = nullptr;
				return true;
			}
		}
		// Otherwise
		Node<T>* prev = ptr;
		ptr = ptr->getNext();
		while (ptr) {
			if (ptr->getItem() == value)
			{
				prev->setNext(ptr->getNext());
				delete ptr;
				return true;
			}
			prev = ptr;
			ptr = ptr->getNext();
		}
		return false;
	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value)
	{
		Node<T>* ptr = Head;
		// List Contains 0 Elements
		if (!ptr)
		{
			return false;
		}
		// List Contains 1 Element
		if (!ptr->getNext())
		{
			if (ptr->getItem() == value) {
				delete ptr;
				Head = nullptr;
				return true;
			}
		}
		// Otherwise
		bool result = false;
		Node<T>* prev = ptr;
		ptr = ptr->getNext();
		while (ptr) {
			if (ptr->getItem() == value)
			{
				prev->setNext(ptr->getNext());
				delete ptr;
				result = true;
			}
			else
			{
				prev = ptr;
			}
			ptr = prev->getNext();
		}
		return result;
	}

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(const LinkedList& L)
	{
		Node<T>* ptr = Head;
		// If Current List Is Not Empty
		if (ptr)
		{
			// Get Last Non-Null Node In The Current List
			while (ptr->getNext())
			{
				ptr = ptr->getNext();
			}
			// Start Appending New Nodes From L To The End Of The Current List
			Node<T>* s = L.Head;
			while (s)
			{
				T item = s->getItem();
				Node<T>* N = new Node<T>(item);
				ptr->setNext(N);
				ptr = N;
				s = s->getNext();
			}
		}
		// Current Last Is Empty
		else
		{
			// If L Is Empty
			Node<T>* s = L.Head;
			if (!s)
			{
				return;
			}
			// Set Head Of Current List To Be The Same As The Head Of L
			Node<T>* N = new Node<T>(s->getItem());
			Head = N;
			ptr = Head;
			s = s->getNext();
			// Start Appending New Nodes From L To The End Of The Current List
			while (s)
			{
				T item = s->getItem();
				Node<T>* N = new Node<T>(item);
				ptr->setNext(N);
				ptr = N;
				s = s->getNext();
			}
		}
	}

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse()
	{
		Node<T>* ptr = Head;
		// If List Contain 0 or Only 1 Element
		if (!ptr || !ptr->getNext())
		{
			return;
		}
		// Otherwise
		Node<T>* prev = ptr; 
		ptr = ptr->getNext();
		prev->setNext(nullptr);
		while (ptr)
		{
			Node<T>* next = ptr->getNext();
			ptr->setNext(prev);
			prev = ptr;
			ptr = next;
		}
		Head = prev;
	}

	void newReverse() {
		newReverse(Head, nullptr, nullptr);
	}
	void newReverse(Node<T>* &head, Node<T>* ptr, Node<T>* next)
	{
		if (head == nullptr || head->getNext() == nullptr)
			return;
		if (next == nullptr && ptr != nullptr)
		{
			head = ptr;
			return;
		}
		if (ptr == nullptr)
		{
			ptr = head;
		}
		if (next == nullptr)
		{
			next = ptr->getNext();
		}
		newReverse(head, next, next->getNext());
		next->setNext(ptr);
	}
	////////////////     Requirements of Exercise 3  ///////////////////

	void PrintKth(int index)
	{
		int i = 1;
		Node<T>* ptr = Head;
		while (ptr)
		{
			if (i == index){
				cout << ptr->getItem() << endl;
				return ;
			}
			ptr = ptr->getNext();
			i++;
		}
		cout << "Beyond List Length" << endl;
	}

	bool InsertSorted(T data)
	{
		Node<T>* ptr = Head;
		if (!ptr)
		{
			Node<T>* N = new Node<T>(data);
			Head = N;
			return true;
		}
		Node<T>* prev = nullptr;
		while (ptr)
		{
			if (ptr->getItem() > data)
			{
				Node<T>* N = new Node<T>(data);
				if(prev == nullptr)
				{
					N->setNext(Head);
					Head = N;
					return true;
				}
				else
				{
					prev->setNext(N);
					N->setNext(ptr);
				}
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
	
	Node<T>* RemoveMin()
	{
		Node<T>* ptr = Head;
		if (!ptr)
		{
			return nullptr;
		}
		if (!ptr->getNext())
		{
			Head = nullptr;
			return ptr;
		}
		Node<T>* min;
		Node<T>* prev = nullptr;
		if(ptr->getItem() < ptr->getNext()->getItem())
		{
			min = ptr;
		}
		else
		{
			prev = ptr;
			min = ptr->getNext();
		}
		Node<T>* rprev = ptr;
		ptr = ptr->getNext();
		while(ptr)
		{
			if(ptr->getItem() < min->getItem())
			{
				min = ptr;
				prev = rprev;
			}
			rprev = ptr;
			ptr= ptr->getNext();
		}
		if(!prev)
		{
			Head = Head->getNext();
		}
		else
		{
			prev->setNext(min->getNext());
		}
		return min;
	}

	LinkedList<T>* CloneList()
	{
		LinkedList<T>* Clone = new LinkedList<T>();
		Node<T>* ptr = Head;
		if (!ptr)
		{
			return Clone;
		}
		Node<T>* N = new Node<T>(ptr->getItem());
		Clone->setHead(N);
		Node<T>* cptr = N;
		ptr = ptr->getNext();
		// same as insert end                                         --------------------------Important-----------------------
		while (ptr)
		{
			Node<T>* N = new Node<T>(ptr->getItem());
			cptr->setNext(N);
			cptr = N;
			ptr = ptr->getNext();
		}
		return Clone;
	}
	
	void SignSplit(LinkedList<T>*& Lneg, LinkedList<T>*& Lpos)
	{
		Lneg = new LinkedList<T>();
		Lpos = new LinkedList<T>();
		Node<T>* ptr = Head;
		Node<T>* posptr = Lneg->Head;
		Node<T>* negptr = Lpos->Head;
		Node<T>* prev = nullptr;
		while (ptr)
		{
			if (ptr->getItem() > 0)
			{
				Node<T>* N = new Node<T>(ptr->getItem());
				if (!posptr)
				{
					Lpos->Head = N;
					posptr = N;
				}
				else
				{
					posptr->setNext(N);
					posptr = N;
				}
				if(prev)
				{
					prev->setNext(ptr->getNext());
					delete ptr;
					ptr = prev->getNext();
				}
				else
				{
					Head = Head->getNext();
					ptr = Head;
				}
			}
			else if (ptr->getItem() < 0)
			{
				Node<T>* N = new Node<T>(ptr->getItem());
				if (!negptr)
				{
					Lneg->Head =N;
					negptr = N;
				}
				else
				{
					negptr->setNext(N);
					negptr = N;
				}
				if(prev)
				{
					prev->setNext(ptr->getNext());
					delete ptr;
					ptr = prev->getNext();
				}
				else
				{
					Head = Head->getNext();
					ptr = Head;
				}
			}
			else
			{
				prev = ptr;
				ptr = prev->getNext();

			}
		}
	}

};

#endif	
