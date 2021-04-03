#include "LinkedList.h"
#include <iostream>
using namespace std;

//Function prototypes 

///////////////////////////////////////////////////////////////////////

int main()
{
	LinkedList<int> L;	//create an object of class LinkedList
	int val;

	cout<<"Please enter int values to add to the list (-1 to stop):\n";
	cin>>val;
	while(val != -1)
	{
		L.InsertEnd(val);
		cin>>val;
	}
	L.PrintList();
	L.Reverse();
	L.PrintList();

	cout<<" \n ..............  Lab Requirements .............\n";
	cout<<"\n Check File LinkedList.h and write the required member functions";
	cout<<"\n Then test these functions by calling them from the main()";

	cout<<endl;
	return 0;
}

