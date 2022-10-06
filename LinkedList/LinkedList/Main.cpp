#include <iostream>

#include "LinkedList.h"

int main()
{
	LinkedList myList;

	myList.insertBack(5);
	myList.insertBack(4);
	myList.insertBack(3);
	myList.insertFront(2);
	myList.insertFront(1);

	myList.remove(4);
	myList.remove(1);

	myList[0] = 69;

	LinkedList newList = myList;

	myList.sort();
	myList.print();

	std::cout << std::endl;

	newList.print();

}