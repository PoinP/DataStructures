#ifndef LINKED_LIST_H

#define LINKED_LIST_H

#include <initializer_list>

// TODO: Add iterator

template<typename Type>
class LinkedList
{
	struct Node
	{
		Type data;
		Node* next;

		Node(const Type& data, Node* next = nullptr) : data(data), next(next) {}
	};

public:
	LinkedList();
	explicit LinkedList(std::initializer_list<Type> initList);
	LinkedList(const LinkedList& other);
	LinkedList(LinkedList&& other) noexcept;
	~LinkedList();

	LinkedList& operator=(const LinkedList& other);
	LinkedList& operator=(LinkedList&& other) noexcept;

	// -------- MODIFIERS --------

	LinkedList& pushFront(const Type& data);
	LinkedList& pushBack(const Type& data);

	Type popFront();
	Type popBack(); // Note: It takes O(n) complexity to popBack an item!

	LinkedList& clear();
	LinkedList& reverse();
	LinkedList& sort(); // Sorts in ascending order

	LinkedList& remove(const Type& target);
	LinkedList& removeFirst(const Type& target);

	// -------- ELEMENT ACCESS --------

	Type& search(const Type& data);
	const Type& search(const Type& data) const;

	Type& front();
	const Type& front() const;

	Type& back();
	const Type& back() const;

	const Type& read(int nodeIndex) const;

	// -------- CAPACITY AND MISC --------

	// Returns the size by traversing the list. O(n) time complexity
	int size() const;
	void print() const;
	bool empty() const;

private:
	Node* m_Head;
	Node* m_Tail;

	void copy(const LinkedList& other);
	void move(LinkedList&& other);
	void clearData();

	LinkedList& removeHelper(const Type& target, Node*& from);
	void throwIfNull(const Node* node) const;
};

#include "LinkedList.inl"

#endif // !LINKED_LIST_H