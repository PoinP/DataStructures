#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER
#include "Catch.hpp"

#include "../src/DoublyLinkedList.h"
#include <vector>

//int main()
//{
//	{
//		DoublyLinkedList<int> damn = { 1, 2, 3, 4, 5 };
//		damn.popBack();
//		damn.popFront();
//	}
//
//	_CrtDumpMemoryLeaks();
//}

TEST_CASE("Constructing DoublyLinkedList objects")
{
	SECTION("Default construction")
	{
		DoublyLinkedList<int> list;

		REQUIRE(list.isEmpty());
		REQUIRE(list.size() == 0);
	}

	SECTION("Copy construction and assignment")
	{
		DoublyLinkedList<int> origin {1, 2, 3, 4, 5};

		SECTION("Copy construction")
		{
			DoublyLinkedList<int> copy(origin);

			auto originIt = origin.begin();

			for (auto el : copy)
			{
				REQUIRE(el == *originIt);
				originIt++;
			}

			REQUIRE(origin.size() == copy.size());
		}

		SECTION("Copy assignment")
		{
			DoublyLinkedList<int> copy;
			copy = origin;

			auto originIt = origin.begin();

			for (auto el : copy)
			{
				REQUIRE(el == *originIt);
				originIt++;
			}

			REQUIRE(origin.size() == copy.size());
		}

		SECTION("Copy assignment itself")
		{
			DoublyLinkedList<int> copy;
			copy = origin;
			copy = copy;

			auto originIt = origin.begin();

			for (auto el : copy)
			{
				REQUIRE(el == *originIt);
				originIt++;
			}

			REQUIRE(origin.size() == copy.size());
		}
	}

	SECTION("Range based constrcution on populated array")
	{
		int arr[] = { 1, 2, 3, 4, 5 };
		DoublyLinkedList<int> list(arr, sizeof(arr) / sizeof(int));

		int i = 0;
		for (int el : list)
			REQUIRE(el == arr[i++]);

		REQUIRE(list.size() == sizeof(arr) / sizeof(int));
	}

	SECTION("Range based construction with iterators")
	{
		std::vector<int> vec = { 1, 2, 3, 4, 5 };
		DoublyLinkedList<int> list(vec.begin(), vec.end());

		auto vecIter = vec.begin();

		for (int el : list)
			REQUIRE(el == *(vecIter++));

		REQUIRE(list.size() == vec.size());
	}

	SECTION("Initalizer list construction")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 4, 5 };
		
		int i = 0;
		for (int el : list)
			REQUIRE(el == ++i);

		REQUIRE(list.size() == 5);
	}

	SECTION("Move construction and assignment")
	{
		DoublyLinkedList<int> origin{ 1, 2, 3, 4, 5 };

		SECTION("Move construction")
		{
			DoublyLinkedList<int> movedList(std::move(origin));

			int i = 0;
			for (int el : movedList)
				REQUIRE(el == ++i);

			REQUIRE(movedList.size() == 5);
		}
		SECTION("Move assignment")
		{
			DoublyLinkedList<int> movedList;
			movedList = std::move(origin);

			int i = 0;
			for (int el : movedList)
				REQUIRE(el == ++i);

			REQUIRE(movedList.size() == 5);
			REQUIRE(origin.size() == 0);
		}
	}
}

TEST_CASE("Front/back element access")
{
	SECTION("Populated list")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 4, 5 };

		REQUIRE(list.front() == 1);
		REQUIRE(list.back() == 5);
	}

	SECTION("List with only one element")
	{
		DoublyLinkedList<int> list = { 1 };

		REQUIRE(list.front() == list.back());
	}

	SECTION("Empty list")
	{
		DoublyLinkedList<int> list;

		REQUIRE_THROWS(list.front());
		REQUIRE_THROWS(list.back());
	}
}

TEST_CASE("Pushing elements to the front of the list")
{
	SECTION("Empty list")
	{
		DoublyLinkedList<int> list;
		REQUIRE(list.pushFront(68).front() == 68);
	}

	SECTION("Populated list")
	{
		DoublyLinkedList<char> list = { 'a', 'b', 'c', 'd', 'e'};
		REQUIRE(list.pushFront('z').front() == 'z');
	}

	SECTION("Pushing multiple elements")
	{
		DoublyLinkedList<int> list = { 6, 7, 8, 9, 10 };

		for (int i = 5; i > 0; --i)
			REQUIRE(list.pushFront(i).front() == i);

		int i = 1;
		for (int el : list)
			REQUIRE(el == i++);

		REQUIRE(list.size() == 10);
	}

	SECTION("Pushing multiple elements with reverse iteration")
	{
		DoublyLinkedList<int> list = { 6, 7, 8, 9, 10 };

		for (int i = 5; i > 0; --i)
			REQUIRE(list.pushFront(i).front() == i);

		int i = 10;
		for (auto rIt = list.rbegin(); rIt != list.rend(); --rIt)
			REQUIRE(*rIt == i--);

		REQUIRE(list.size() == 10);
	}
}

TEST_CASE("Pushing elements to the end of the list")
{
	SECTION("Empty list")
	{
		DoublyLinkedList<int> list;
		REQUIRE(list.pushBack(68).back() == 68);
	}

	SECTION("Populated list")
	{
		DoublyLinkedList<char> list = { 'a', 'b', 'c', 'd', 'e' };
		REQUIRE(list.pushBack('z').back() == 'z');
	}

	SECTION("Pushing multiple elements")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 4, 5 };

		for (int i = 6; i <= 10; ++i)
			REQUIRE(list.pushBack(i).back() == i);

		int i = 1;
		for (int el : list)
			REQUIRE(el == i++);

		REQUIRE(list.size() == 10);
	}

	SECTION("Pushing multiple elements with reverse iteration")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 4, 5 };

		for (int i = 6; i <= 10; ++i)
			REQUIRE(list.pushBack(i).back() == i);

		int i = 10;
		for (auto rIt = list.rbegin(); rIt != list.rend(); --rIt)
			REQUIRE(*rIt == i--);

		REQUIRE(list.size() == 10);
	}
}

TEST_CASE("Popping from the front")
{
	SECTION("Popping from empty list")
	{
		DoublyLinkedList<int> list;

		REQUIRE_THROWS(list.popFront());
	}

	SECTION("Popping from a list with one element")
	{
		DoublyLinkedList<int> list = { 1 };

		REQUIRE(list.popFront().isEmpty());
	}

	SECTION("Popping from a populated list")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 4, 5 };
		list.popFront();

		int i = 2;
		for (int el : list)
			REQUIRE(el == i++);
	}
}

TEST_CASE("Popping from the back")
{
	SECTION("Popping from empty list")
	{
		DoublyLinkedList<int> list;

		REQUIRE_THROWS(list.popBack());
	}

	SECTION("Popping from a list with one element")
	{
		DoublyLinkedList<int> list = { 1 };

		REQUIRE(list.popBack().isEmpty());
	}

	SECTION("Popping from a populated list")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 4, 5 };
		list.popBack();

		int i = 1;
		for (int el : list)
			REQUIRE(el == i++);

		REQUIRE(list.back() == 4);
	}
}

TEST_CASE("Clearing list")
{
	SECTION("Empty list")
	{
		DoublyLinkedList<int> list;
		REQUIRE_NOTHROW(list.clear());
	}

	SECTION("Filled list")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 4, 5, 6 };

		list.clear();

		REQUIRE(list.isEmpty());
		REQUIRE(list.size() == 0);
	}
}

TEST_CASE("Operators")
{
	SECTION("Empty lists")
	{
		DoublyLinkedList<int> rhs;
		DoublyLinkedList<int> lhs;

		REQUIRE(rhs == lhs);
	}

	SECTION("Filled lists")
	{
		DoublyLinkedList<int> rhs = { 1, 2, 3, 4, 5 };
		DoublyLinkedList<int> lhs;

		SECTION("Equal")
		{
			lhs = rhs;

			REQUIRE(lhs == rhs);
		}

		SECTION("Not equal")
		{
			REQUIRE(lhs != rhs);

			lhs.pushBack(1);

			REQUIRE(lhs != rhs);
		}
	}
}

TEST_CASE("Reverse list")
{
	SECTION("Empty list")
	{
		DoublyLinkedList<int> list = {};
		list.reverse();

		REQUIRE(list.isEmpty());
	}

	SECTION("Filled list")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 4, 5 };
		list.reverse();

		int i = 5;

		for (int el : list)
			REQUIRE(el == i--);
	}
}

TEST_CASE("Sorting")
{
	SECTION("Empty list")
	{
		DoublyLinkedList<int> list = {};
		list.sort();

		REQUIRE(list.isEmpty());
	}

	SECTION("Filled list")
	{
		DoublyLinkedList<int> list = { 3, 4, 5, 2, 1 };
		list.sort();
	
		int i = 1;

		for (int el : list)
			REQUIRE(el == i++);
	}
}

TEST_CASE("Merging")
{
	SECTION("Empty with empty list")
	{
		DoublyLinkedList<int> list = { };
		DoublyLinkedList<int> toMerge = { };

		list.merge(toMerge);

		REQUIRE(toMerge.isEmpty());
		REQUIRE(list.size() == 0);
		REQUIRE(list.isEmpty());
	}

	SECTION("Empty with filled list")
	{
		DoublyLinkedList<int> list = { };
		DoublyLinkedList<int> toMerge = { 1, 2, 3, 4, 5 };

		list.merge(toMerge);

		REQUIRE(toMerge.isEmpty());

		int i = 1;

		for (int el : list)
			REQUIRE(el == i++);

		REQUIRE(list.size() == 5);
	}

	SECTION("Filled with empty list")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 4, 5 };
		DoublyLinkedList<int> toMerge = { };

		list.merge(toMerge);

		REQUIRE(toMerge.isEmpty());

		int i = 1;

		for (int el : list)
			REQUIRE(el == i++);

		REQUIRE(list.size() == 5);
	}

	SECTION("Filled with filled list")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 4, 5 };
		DoublyLinkedList<int> toMerge = { 6, 7, 8, 9, 10 };

		list.merge(toMerge);

		REQUIRE(toMerge.isEmpty());

		int i = 1;

		for (int el : list)
			REQUIRE(el == i++);

		REQUIRE(list.size() == 10);
	}
}

TEST_CASE("Elements removal")
{
	SECTION("Removal of elements as the head")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 1, 4, 5 };
		list.remove(1);

		int i = 2;

		for (int el : list)
			REQUIRE(el == i++);
	}

	SECTION("Removal of elements as the tail")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 5, 4, 5, 5 };
		list.remove(5);

		int i = 1;

		for (int el : list)
			REQUIRE(el == i++);
	}

	SECTION("Removal with no mathcing element")
	{
		DoublyLinkedList<int> list = { 1, 2, 3, 4, 5, 6, 7, 8 };
		list.remove(9);

		int i = 1;

		for (int el : list)
			REQUIRE(el == i++);
	}

	SECTION("Removal with empty list")
	{
		DoublyLinkedList<int> list;
		REQUIRE_NOTHROW(list.remove(0));
	}
	
}