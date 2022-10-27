#ifndef DOUBLY_LINKED_LIST_H

#define DOUBLY_LINKED_LIST_H

#include <initializer_list>
#include <algorithm>
#include <stdexcept>

template <typename Type>
class DoublyLinkedList
{
	struct Node;

public:
	class ConstIterator;
	class Iterator;

	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList& other);
	DoublyLinkedList(DoublyLinkedList&& other) noexcept;
	DoublyLinkedList(const Type* data, size_t size);
	template<typename It>
	DoublyLinkedList(It begin, It end);
	DoublyLinkedList(const std::initializer_list<Type>& initList);
	~DoublyLinkedList();

	DoublyLinkedList& operator= (const DoublyLinkedList& other);
	DoublyLinkedList& operator= (DoublyLinkedList&& other) noexcept;
	
	// -------- ELEMENT ACCESS --------
	Type& front();
	const Type& front() const;

	Type& back();
	const Type& back() const;

	// -------- ITERATORS --------
	Iterator begin();
	ConstIterator begin() const;

	Iterator rbegin();
	ConstIterator rbegin() const;

	Iterator end();
	ConstIterator end() const;

	Iterator rend();
	ConstIterator rend() const;

	// -------- CAPACITY --------
	bool isEmpty() const;
	size_t size() const;

	// -------- MODIFIERS --------
	DoublyLinkedList& pushFront(const Type& item);
	DoublyLinkedList& pushBack(const Type& item);
	DoublyLinkedList& popFront();
	DoublyLinkedList& popBack();
	
	DoublyLinkedList& clear();

	// -------- OPERATIONS --------
	DoublyLinkedList& reverse();
	DoublyLinkedList& sort();
	DoublyLinkedList& merge(DoublyLinkedList<Type>& other);
	DoublyLinkedList& remove(const Type& target);
	template<typename UnaryPredicate>
	DoublyLinkedList& removeIf(UnaryPredicate predicate);

private:
	Node* m_Head;
	Node* m_Tail;

	void copy(const DoublyLinkedList& other);

public:
	class ConstIterator
	{
	public:
		ConstIterator(Node* ptr = nullptr);

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);

		bool operator==(ConstIterator other) const;
		bool operator!=(ConstIterator other) const;

		const Type& operator*() const;
		const Type* operator->() const;

	protected:
		Node* m_Ptr;
	};

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Node* ptr = nullptr);

		Type& operator*();
		Type* operator->();
	};

private:
	struct Node
	{
		Type data;
		Node* prev;
		Node* next;

		Node(const Type& data, Node* prev = nullptr, Node* next = nullptr)
			: data(data), prev(prev), next(next)
		{}
	};
};

template<typename Type>
bool operator== (const DoublyLinkedList<Type>& lhs, const DoublyLinkedList<Type>& rhs);
template<typename Type>
bool operator!= (const DoublyLinkedList<Type>& lhs, const DoublyLinkedList<Type>& rhs);

#include "DoublyLinkedList.inl";

#endif // !DOUBLY_LINKED_LIST_H
