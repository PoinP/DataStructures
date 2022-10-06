#ifndef LINKED_LIST

#define LINKED_LIST

#include <stdexcept>

class LinkedList
{
	struct Node
	{
		int value;
		Node* next;

		Node() : value(0), next(nullptr) {}
		Node(int x) : value(x), next(nullptr) {}
		Node(int x, Node* ptr) : value(x), next(ptr) {}

		~Node()
		{
			delete next;
		}
	};

public:
	LinkedList();
	LinkedList(const LinkedList& other);
	LinkedList(LinkedList&& other) noexcept;
	~LinkedList();

	LinkedList& operator=(const LinkedList& other);
	LinkedList& operator=(LinkedList&& other) noexcept;

	int& operator[](int index);
	const int& operator[](int index) const;

	int* search(int value);
	const int* search(int value) const;

	void insertFront(int value);
	void insertBack(int value);
	void remove(int value);
	void sort();

	void print() const;

	int read(int index) const;

private:
	Node* m_Head;
};

#endif // !LINKED_LIST
