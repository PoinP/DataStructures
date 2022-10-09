#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include "LinkedList.h"

int main()
{
	{
		LinkedList<int> list = LinkedList<int>({ 1, 2, 3, 4 });
	}

	_CrtDumpMemoryLeaks();
}