#include "LinkedList.h"

#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <iostream>

// --------  Iterator  --------

template<typename Type>
inline LinkedList<Type>::Iterator::Iterator(pointer ptr)
	: m_Ptr(ptr)
{
}

template<typename Type>
inline LinkedList<Type>::Iterator& LinkedList<Type>::Iterator::operator++()
{
	*this++;
	return *this;
}

template<typename Type>
inline LinkedList<Type>::Iterator LinkedList<Type>::Iterator::operator++(int)
{
	Node* oldValue = m_Ptr;
	*this++;
	return oldValue;
}

template<typename Type>
inline bool LinkedList<Type>::Iterator::operator==(const Iterator& other) const
{
	return m_Ptr == other.m_Ptr;
}

template<typename Type>
inline bool LinkedList<Type>::Iterator::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

template<typename Type>
inline LinkedList<Type>::Node* LinkedList<Type>::Iterator::operator->()
{
	return m_Ptr;
}

template<typename Type>
inline LinkedList<Type>::Node& LinkedList<Type>::Iterator::operator*()
{
	return m_Ptr;
}

template<typename Type>
inline LinkedList<Type>::Node& LinkedList<Type>::Iterator::operator*() const
{
	return m_Ptr;
}

template<typename Type>
inline LinkedList<Type>::Node* LinkedList<Type>::Iterator::getPtr() const noexcept
{
	return m_Ptr;
}


// -------- LinkedList --------
template<typename Type>
inline LinkedList<Type>::LinkedList()
	: m_Head(nullptr), m_Tail(nullptr)
{
}

template<typename Type>
inline LinkedList<Type>::LinkedList(std::initializer_list<Type> initList)
	: LinkedList()
{
	for (auto item : initList)
		pushBack(item);
}

template<typename Type>
inline LinkedList<Type>::LinkedList(const LinkedList& other)
	: LinkedList()
{
	copy(other);
}

template<typename Type>
inline LinkedList<Type>::LinkedList(LinkedList&& other) noexcept
	: LinkedList()
{
	move(other);
}

template<typename Type>
inline LinkedList<Type>::~LinkedList()
{
	clearData();
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::operator=(const LinkedList<Type>& other)
{
	if (this != &other)
	{
		clearData();
		copy(other);
	}

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::operator=(LinkedList<Type>&& other) noexcept
{
	move(std::move(other));

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::pushFront(const Type& data)
{
	m_Head = new Node(data, m_Head);

	if (!m_Tail)
		m_Tail = m_Head;

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::pushBack(const Type& data)
{
	if (!m_Tail)
	{
		pushFront(data);
		return *this;
	}

	m_Tail->next = new Node(data);
	m_Tail = m_Tail->next;

	return *this;
}

template<typename Type>
inline Type LinkedList<Type>::popFront()
{
	throwIfNull(m_Head);

	Type poppedValue = m_Head->data;

	Node* nextNode = m_Head->next;
	
	if (m_Tail == m_Head)
		m_Tail = nextNode;

	delete m_Head;

	m_Head = nextNode;

	return poppedValue;
}

template<typename Type>
inline Type LinkedList<Type>::popBack()
{
	throwIfNull(m_Head);

	if (m_Head == m_Tail)
		return popFront();

	Node* currNode = m_Head;

	while (currNode->next != m_Tail)
	{
		currNode = currNode->next;
	}

	Type poppedValue = m_Tail->data;

	delete m_Tail;
	m_Tail = currNode;
	m_Tail->next = nullptr;

	return poppedValue;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::clear()
{
	clearData();

	m_Head = nullptr;
	m_Tail = nullptr;

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::reverse()
{
	LinkedList reversedList;

	while (!empty())
		reversedList.pushFront(this->popFront());

	*this = std::move(reversedList);

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::sort()
{
	Node* currNode = m_Head;
	Node* minNode = currNode;

	Node* innerNode;

	// Selection Sort -> O(n^2)
	while (currNode)
	{
		innerNode = currNode->next;
		while (innerNode)
		{
			if (innerNode->data < minNode->data)
				minNode = innerNode;

			innerNode = innerNode->next;
		}

		if (currNode != minNode)
			std::swap(currNode->data, minNode->data);

		currNode = currNode->next;
		minNode = currNode;
	}

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::remove(const Type& target)
{
	Node* currNode = m_Head;

	while (currNode)
		removeHelper(target, currNode);

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::removeFirst(const Type& target)
{
	Node* currNode = m_Head;

	return removeHelper(target, currNode);
}

template<typename Type>
inline Type& LinkedList<Type>::search(const Type& data)
{
	Node* currNode = m_Head;

	while (currNode)
	{
		if (currNode->data == data)
			return currNode->data;

		currNode = currNode->next;
	}
}

template<typename Type>
inline const Type& LinkedList<Type>::search(const Type& data) const
{
	throwIfNull(m_Head);

	Node* currNode = m_Head;

	while (currNode)
	{
		if (currNode->data == data)
			return currNode->data;

		currNode = currNode->next;
	}
}

template<typename Type>
inline Type& LinkedList<Type>::front()
{
	throwIfNull(m_Head);

	return m_Head->data;
}

template<typename Type>
inline const Type& LinkedList<Type>::front() const
{
	throwIfNull(m_Head);

	return m_Head->data;
}

template<typename Type>
inline Type& LinkedList<Type>::back()
{
	throwIfNull(m_Head);

	return m_Tail->data;
}

template<typename Type>
inline const Type& LinkedList<Type>::back() const
{
	throwIfNull(m_Head);

	return m_Tail->data;
}

template<typename Type>
inline const Type& LinkedList<Type>::read(int nodeIndex) const
{
	Node* currNode = m_Head;

	int i = 0;
	while (currNode)
	{
		if (i == nodeIndex)
			return currNode->data;

		currNode = currNode->next;
		i++;
	}

	throwIfNull(currNode);
}

template<typename Type>
inline int LinkedList<Type>::size() const
{
	int size = 0;
	Node* currNode = m_Head;

	while (currNode)
	{
		currNode = currNode->next;
		size++;
	}

	return size;
}

template<typename Type>
inline void LinkedList<Type>::print() const
{
	Node* currentNode = m_Head;

	while (currentNode)
	{
		std::cout << currentNode->data << " ";
		currentNode = currentNode->next;
	}
}

template<typename Type>
inline bool LinkedList<Type>::empty() const
{
	return !m_Head;
}

template<typename Type>
void LinkedList<Type>::copy(const LinkedList& other)
{
	if (other.m_Head)
	{
		m_Head = new Node(other.m_Head->data);

		Node* currNode = m_Head;
		Node* otherNode = other.m_Head;

		while (otherNode->next)
		{
			currNode->next = new Node(otherNode->next->data);
			currNode = currNode->next;
			otherNode = otherNode->next;
		}

		m_Tail = currNode;
	}
}

template<typename Type>
void LinkedList<Type>::move(LinkedList<Type>&& other)
{
	std::swap(m_Head, other.m_Head);
	std::swap(m_Tail, other.m_Tail);
}

template<typename Type>
void LinkedList<Type>::clearData()
{
	Node* tempNode;

	while (m_Head)
	{
		tempNode = m_Head->next;
		delete m_Head;
		m_Head = tempNode;
	}
}

// Needs a solid refactoring lmao
template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::removeHelper(const Type& target, Node*& from)
{
	if (empty())
		return *this;

	if (from == m_Head)
	{
		if (from->data == target)
		{
			popFront();
			from = m_Head;
			return *this;
		}
	}

	Node* prevNode = from;
	Node* currNode = from->next;

	while (currNode)
	{
		if (currNode->data == target)
		{
			if (m_Tail == m_Head)
			{
				popFront();
				return *this;
			}

			Node* nextNode = currNode->next;
			prevNode->next = nextNode;

			if (m_Tail == currNode)
				m_Tail = prevNode;

			from = prevNode;
			delete currNode;

			return *this;
		}

		prevNode = prevNode->next;
		currNode = prevNode->next;
	}

	from = nullptr;
	return *this;
}

template<typename Type>
inline void LinkedList<Type>::throwIfNull(const Node* node) const
{
	if (!node)
		throw std::out_of_range("The linked list is empty or the index is invalid!");
}