#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <vector>

#include "../src/Dictionary.h"

TEST_CASE("Dictionary init")
{
	SUBCASE("Default Ctor")
	{
		Dictionary<int, int> dic;

		CHECK(dic.isEmpty());
		CHECK(dic.size() == 0);
		CHECK(dic.begin() == dic.end());
	}

	SUBCASE("Assignable Ctors")
	{
		Dictionary<int, int> dic;

		dic.add(1, 11);
		dic.add(4, 44);
		dic.add(-1, -11);
		dic.add(3, 33);

		SUBCASE("Copy Ctor")
		{
			Dictionary<int, int> dicCopy(dic);

			CHECK(dic.size() == dicCopy.size());
			CHECK(!dicCopy.isEmpty());

			auto dicIter = dic.begin();
			auto copyIter = dicCopy.begin();

			while (dicIter != dic.end() && copyIter != dicCopy.end())
			{
				CHECK(*dicIter == *copyIter);

				dicIter++;
				copyIter++;
			}
		}

		SUBCASE("Move Ctor")
		{
			Dictionary<int, int> dicMove(std::move(dic));

			CHECK(dic.size() == 0);
			CHECK(dic.isEmpty());

			CHECK(dicMove.size() == 4);
			CHECK(!dicMove.isEmpty());

			int vecIter = 0;
			std::vector<int> elements = { -11, 11, 33, 44 };
			for (auto iter = dic.begin(); iter != dic.end(); ++iter)
			{
				CHECK(elements[vecIter++] == *iter);
				CHECK(iter.operator->() == &*iter);
			}
		}

		SUBCASE("Initializer List")
		{
			Dictionary<int, int> dic = { {5, 5}, {3, 3}, {6, 6}, {1, 1}, {4, 4}, {7, 7} };
			CHECK(dic.size() == 6);
			CHECK(!dic.isEmpty());

			std::vector<int> elements = { 1, 2, 3, 4, 5, 6, 7 };

			int iter = 0;
			for (Dictionary<int, int>::mapped_type el : dic)
			{
				el == elements[iter++];
			}
		}
	}
}

TEST_CASE("Assignment Operators")
{
	Dictionary<int, int> dic;

	dic.add(1, 11);
	dic.add(4, 44);
	dic.add(-1, -11);
	dic.add(3, 33);

	SUBCASE("Copy Assignment")
	{
		SUBCASE("Same address")
		{
			Dictionary<int, int> &sameDic = dic;

			sameDic = dic;

			CHECK(sameDic.size() == 4);
			CHECK(!sameDic.isEmpty());

			CHECK(dic.size() == 4);
			CHECK(!dic.isEmpty());
		}

		SUBCASE("Different Address")
		{
			Dictionary<int, int> dicCopy = dic;

			CHECK(dic.size() == dicCopy.size());
			CHECK(!dicCopy.isEmpty());

			auto dicIter = dic.begin();
			auto copyIter = dicCopy.begin();

			while (dicIter != dic.end() && copyIter != dicCopy.end())
			{
				CHECK(*dicIter == *copyIter);

				dicIter++;
				copyIter++;
			}
		}
	}

	SUBCASE("Move Assignment")
	{
		Dictionary<int, int> dicMove = std::move(dic);

		CHECK(dic.size() == 0);
		CHECK(dic.isEmpty());

		CHECK(dicMove.size() == 4);
		CHECK(!dicMove.isEmpty());

		int vecIter = 0;
		std::vector<int> elements = { -11, 11, 33, 44 };
		for (auto iter = dic.begin(); iter != dic.end(); ++iter)
		{
			CHECK(elements[vecIter++] == *iter);
			CHECK(iter.operator->() == &*iter);
		}
	}
}

TEST_CASE("Iteration")
{
	Dictionary<int, int> dic;

	dic.add(1, 11);
	dic.add(4, 44);
	dic.add(-1, -11);
	dic.add(3, 33);

	std::vector<int> elements = { -11, 11, 33, 44 };

	int vecIter = 0;

	for (auto iter = dic.begin(); iter != dic.end(); ++iter)
	{
		CHECK(elements[vecIter++] == *iter);
		CHECK(iter.operator->() == &*iter);
	}
}

TEST_CASE("Element Access")
{
	Dictionary<int, int> dic;

	dic.add(1, 11);
	dic.add(4, 44);
	dic.add(-1, -11);
	dic.add(3, 33);

	SUBCASE("Using 'at'")
	{
		SUBCASE("Empty dictionary")
		{
			Dictionary<int, int> dic;
			CHECK_THROWS(dic.at(1));
		}

		SUBCASE("Found element")
		{
			CHECK(dic.at(3) == 33);
		}

		SUBCASE("Element not found")
		{
			CHECK_THROWS(dic.at(6));
		}
	}

	SUBCASE("Using operator []")
	{
		SUBCASE("Empty dictionary")
		{
			Dictionary<int, int> dic;
			CHECK_THROWS(dic[1]);
		}

		SUBCASE("Found element")
		{
			CHECK(dic[3] == 33);
		}

		SUBCASE("Element not found")
		{
			CHECK_THROWS(dic[6]);
		}
	}
}

TEST_CASE("Adding Elements")
{
	Dictionary<int, int> dic;

	CHECK(dic.isEmpty());

	SUBCASE("Adding to empty dictionary")
	{
		dic.add(1, 11);
		CHECK(dic.size() == 1);
		CHECK(*dic.begin() == 11);
		CHECK(!dic.isEmpty());
	}

	SUBCASE("Adding to filled dictionary")
	{
		dic.add(1, 11);
		dic.add(4, 44);
		dic.add(-1, -11);
		dic.add(3, 33);

		CHECK(dic.size() == 4);

		std::vector<int> elements = { -11, 11, 33, 44 };

		int iter = 0;

		for (int value : dic)
		{
			CHECK(elements[iter++] == value);
		}
	}
}

TEST_CASE("Deleting elements")
{
	Dictionary<int, int> dic;

	SUBCASE("Empty dictionary")
	{
		CHECK_NOTHROW(dic.erase(1));
	}

	SUBCASE("Single element")
	{
		dic.add(1, 11);
		dic.erase(1);
		CHECK(dic.isEmpty());
		CHECK(dic.size() == 0);
	}

	SUBCASE("Deleting root")
	{
		dic.add(1, 11);
		dic.add(4, 44);
		dic.add(-1, -11);
		dic.add(3, 33);

		std::vector<int> beforeDel = { -11, 11, 33, 44 };

		int iter = 0;
		for (Dictionary<int, int>::mapped_type v : dic)
		{
			CHECK(v == beforeDel[iter++]);
		}

		dic.erase(1);
		std::vector<int> afterDel = { -11, 33, 44 };

		CHECK(!dic.contains(1));
		CHECK(dic.size() == 3);

		iter = 0;
		for (Dictionary<int, int>::mapped_type v : dic)
		{
			CHECK(v == afterDel[iter++]);
		}
	}

	SUBCASE("Deleting leaf without parents")
	{
		dic.add(1, 11);
		dic.add(4, 44);
		dic.add(-1, -11);
		dic.add(3, 33);

		dic.erase(3);

		CHECK(!dic.contains(3));
		CHECK(dic.size() == 3);
	}

	SUBCASE("Deleting node with only left child")
	{
		dic.add(1, 11);
		dic.add(4, 44);
		dic.add(-1, -11);
		dic.add(3, 33);

		std::vector<int> beforeDel = { -11, 11, 33, 44 };

		int iter = 0;
		for (Dictionary<int, int>::mapped_type v : dic)
		{
			CHECK(v == beforeDel[iter++]);
		}

		dic.erase(4);
		std::vector<int> afterDel = { -11, 11, 33 };

		CHECK(!dic.contains(4));
		CHECK(dic.size() == 3);

		iter = 0;
		for (Dictionary<int, int>::mapped_type v : dic)
		{
			CHECK(v == afterDel[iter++]);
		}
	}

	SUBCASE("Deleting node with only right child")
	{
		dic.add(1, 11);
		dic.add(4, 44);
		dic.add(-1, -11);
		dic.add(5, 55);

		std::vector<int> beforeDel = { -11, 11, 44, 55 };

		int iter = 0;
		for (Dictionary<int, int>::mapped_type v : dic)
		{
			CHECK(v == beforeDel[iter++]);
		}

		dic.erase(4);
		std::vector<int> afterDel = { -11, 11, 55 };

		CHECK(!dic.contains(4));
		CHECK(dic.size() == 3);

		iter = 0;
		for (Dictionary<int, int>::mapped_type v : dic)
		{
			CHECK(v == afterDel[iter++]);
		}
	}

	SUBCASE("Deleting middle node")
	{
		dic.add(5, 55);
		dic.add(2, 22);
		dic.add(6, 66);
		dic.add(1, 11);
		dic.add(4, 44);
		dic.add(3, 33);
		dic.add(7, 77);

		std::vector<int> beforeDel = { 11, 22, 33, 44, 55, 66, 77 };

		int iter = 0;
		for (Dictionary<int, int>::mapped_type v : dic)
		{
			CHECK(v == beforeDel[iter++]);
		}

		dic.erase(dic.find(2));
		std::vector<int> afterDel = { 11, 33, 44, 55, 66, 77 };

		iter = 0;
		for (Dictionary<int, int>::mapped_type v : dic)
		{
			CHECK(v == afterDel[iter++]);
		}
	}

	SUBCASE("Deleting multiple nodes")
	{
		dic.add(5, 55);
		dic.add(2, 22);
		dic.add(6, 66);
		dic.add(1, 11);
		dic.add(4, 44);
		dic.add(3, 33);
		dic.add(7, 77);

		std::vector<int> beforeDel = { 11, 22, 33, 44, 55, 66, 77 };

		int iter = 0;
		for (Dictionary<int, int>::mapped_type v : dic)
		{
			CHECK(v == beforeDel[iter++]);
		}

		dic.erase(dic.find(3), dic.find(7));
		std::vector<int> afterDel = { 11, 22, 77 };

		iter = 0;
		for (Dictionary<int, int>::mapped_type v : dic)
		{
			CHECK(v == afterDel[iter++]);
		}
	}
}

TEST_CASE("Clearing dictionary")
{
	Dictionary<int, int> dic;

	SUBCASE("Empty dictionary")
	{
		CHECK_NOTHROW(dic.clear());
	}

	SUBCASE("Filled dictionary")
	{
		dic.add(1, 11);
		dic.add(4, 44);
		dic.add(-1, -11);
		dic.add(3, 33);

		dic.clear();
		CHECK(dic.isEmpty());
		CHECK(dic.size() == 0);
	}
}

TEST_CASE("Look up methods")
{
	Dictionary<int, int> dic;

	dic.add(1, 11);
	dic.add(4, 44);
	dic.add(-1, -11);
	dic.add(3, 33);

	SUBCASE("Find method")
	{
		SUBCASE("Empty dictionary")
		{
			Dictionary<int, int> dic;
			CHECK(dic.find(1) == dic.end());
		}

		SUBCASE("Single element")
		{
			Dictionary<int, int> dic;
			dic.add(1, 11);
			CHECK(*dic.find(1) == 11);
		}

		SUBCASE("Filled dictionary")
		{
			bool isCorrect = false;
			Dictionary<int, int>::iterator found = dic.find(3);

			CHECK(*found == 33);

			for (auto iter = dic.begin(); iter != dic.end(); iter++)
			{
				if (iter == found)
					isCorrect = true;
			}

			CHECK(isCorrect);
		}
	}

	SUBCASE("Contains method")
	{
		SUBCASE("Empty dictionary")
		{
			Dictionary<int, int> dic;
			CHECK(!dic.contains(1));
		}

		SUBCASE("Single element")
		{
			Dictionary<int, int> dic;
			dic.add(1, 11);
			CHECK(dic.contains(1));
		}

		SUBCASE("Filled dictionary")
		{
			CHECK(dic.contains(3));

			SUBCASE("Not containing an element")
			{
				CHECK(!dic.contains(6));
			}
		}
	}
}

TEST_CASE("Swapping two dictionaries")
{
	Dictionary<int, int> dic1;

	dic1.add(1, 11);
	dic1.add(4, 44);
	dic1.add(-1, -11);
	dic1.add(3, 33);

	Dictionary<int, int> dic2;

	dic2.add(5, 55);
	dic2.add(2, 22);
	dic2.add(6, 66);
	dic2.add(1, 11);
	dic2.add(4, 44);
	dic2.add(3, 33);
	dic2.add(7, 77);

	std::vector<int> dic1El = { -11, 11, 33, 44, };
	std::vector<int> dic2El = { 11, 22, 33, 44, 55, 66, 77 };

	dic1.swap(dic2);

	int iter = 0;
	for (auto el : dic1)
	{
		CHECK(dic2El[iter++] == el);
	}

	iter = 0;
	for (auto el : dic2)
	{
		CHECK(dic1El[iter++] == el);
	}
}

int main()
{
	doctest::Context().run();
}