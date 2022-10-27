#ifndef LINKED_LIST_H

#define LINKED_LIST_H

#include <initializer_list>

template<typename Type>
class LinkedList
{
	struct Node
	{
		Type data;
		Node* next;

		Node(const Type& data, Node* next = nullptr) : data(data), next(next) {}
	};

	class Iterator
	{
	public:

		using difference_type = std::ptrdiff_t;
		using value_type = Node;
		using pointer = Node*;
		using reference = Node&;
		using const_reference = const Node&;
		using iterator_category = std::forward_iterator_tag;

		Iterator(pointer ptr);

		Iterator& operator++();
		Iterator operator++(int);

		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;

		pointer operator->();
		reference operator*();
		reference operator*() const;

		pointer getPtr() const noexcept;

	private:
		pointer m_Ptr;
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
