#include "LinkedList.h"
#include <iostream>
using namespace std;

//Function prototypes 

///////////////////////////////////////////////////////////////////////

int main()
{
	LinkedList<int> L1;	//create an object of class LinkedList
	LinkedList<int> L2;	//create an object of class LinkedList
	int val;

	cout<<"Please enter int values to add to the list 1 (-1 to stop):\n";
	cin>>val;
	while(val != -1)
	{
		L1.InsertEnd(val);
		cin>>val;
	}
	cout << "Please enter int values to add to the list 2 (-1 to stop):\n";
	cin >> val;
	while (val != -1)
	{
		L2.InsertEnd(val);
		cin >> val;
	}
	cout << "List 1 :" ;
	L1.PrintList();
	cout << "List 2 :";
	L2.PrintList();
	cout << "-----------------Delete First Element of List 1-----------------" << endl;
	L1.DeleteFirst();
	cout << "List 1 :";
	L1.PrintList();
	cout << "-----------------Delete Last Element of List 2-----------------" << endl;
	L2.DeleteLast();
	cout << "List 2 :";
	L2.PrintList();
	cout << "----------------Searching For 2 in List 1 using Find---------------" << endl;
	cout << L1.Find(2) << endl;
	cout << "-------------Searching For 2 in List 2 using CountOccurances----------" << endl;
	cout << L2.CountOccurance(2) << endl;
	cout << "----------------Searching For 100 in List 1 using Find---------------" << endl;
	cout << L1.Find(100) << endl;
	cout << "-------------Searching For 100 in List 2 using CountOccurances----------" << endl;
	cout << L2.CountOccurance(100) << endl;
	cout << "----------------Deleting 3 From List 1 using DeleteNode---------------" << endl;
	L1.DeleteNode(3);
	cout << "List 1 :";
	L1.PrintList();
	cout << "----------------Deleting 3 From List 2 using DeleteNodes---------------" << endl;
	L2.DeleteNodes(3);
	cout << "List 2 :";
	L2.PrintList();
	cout << "-------------------Merge List 2 To List 1---------------------" << endl;
	L1.Merge(L2);
	cout << "List 1 :";
	L1.PrintList();
	cout << "List 2 :";
	L2.PrintList();
	cout << "-----------------------Reverse List 1------------------------" << endl;
	L1.Reverse();
	cout << "List 1 :";
	L1.PrintList();
	return 0;
}

