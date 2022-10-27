#include <iostream>

#include "FixedStack.h"
#include <stack>

int main()
{
	FixedStack<int, 20> myStack;

	for (int i = 0; i < 10; i++)
	{
		myStack.push(i);
	}

	FixedStack<int, 20> newStack = myStack;
	newStack.push(69);

	std::cout << (newStack == myStack);
}