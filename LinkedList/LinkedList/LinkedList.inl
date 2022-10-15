#include "LinkedList.h"

#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <iostream>

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
inline LinkedList<Type>& LinkedList<Type>::assign(const Type* values, size_t count)
{
	clearData();

	for (size_t i = 0; i < count; ++i)
		pushBack(values[i]);

	return *this;
}

template<typename Type>
template<typename InputIt>
inline LinkedList<Type>& LinkedList<Type>::assign(InputIt begin, InputIt end)
{
	clearData();

	for (InputIt it = begin; it != end; ++it)
		pushBack(*it);

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::assign(std::initializer_list<Type> initList)
{
	return assign(initList.begin(), initList.end());
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
inline LinkedList<Type>& LinkedList<Type>::insertAfter(ConstIterator pos, const Type& value)
{
	if (!pos.m_Ptr)
		throw std::invalid_argument("Iterator postion was nullptr!");

	Node* prevNext = pos.m_Ptr->next;
	pos.m_Ptr->next = new Node(value, prevNext);

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::insertAfter(ConstIterator pos, const Type* values, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		insertAfter(pos, values[i]);
		pos++;
	}

	return *this;
}

template<typename Type>
template<typename InputIt>
inline LinkedList<Type>& LinkedList<Type>::insertAfter(ConstIterator pos, InputIt begin, InputIt end)
{
	for (InputIt it = begin; it != end; ++it)
	{
		insertAfter(pos, *it);
		pos++;
	}

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::insertAfter(ConstIterator pos, std::initializer_list<Type> initList)
{
	return insertAfter(pos, initList.begin(), initList.end());
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::eraseAfter(ConstIterator pos)
{
	if (!pos.m_Ptr)
		throw std::invalid_argument("Iterator postion was nullptr!");

	if (!pos.m_Ptr->next)
		return *this;

	Node* afterErased = pos.m_Ptr->next->next;
	delete pos.m_Ptr->next;
	pos.m_Ptr->next = afterErased;

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::eraseAfter(ConstIterator first, ConstIterator last)
{
	while (first.m_Ptr->next != last.m_Ptr)
		eraseAfter(first);

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::swap(LinkedList& other)
{
	swap(m_Head, other.m_Head);
	swap(m_Tail, other.m_Tail);

	return *this;
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
inline typename LinkedList<Type>::Iterator LinkedList<Type>::begin()
{
	return Iterator(m_Head);
}

template<typename Type>
inline typename LinkedList<Type>::ConstIterator LinkedList<Type>::begin() const
{
	return ConstIterator(m_Head);
}

template<typename Type>
inline typename LinkedList<Type>::Iterator LinkedList<Type>::end()
{
	return Iterator();
}

template<typename Type>
inline typename LinkedList<Type>::ConstIterator LinkedList<Type>::end() const
{
	return ConstIterator();
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::merge(LinkedList& other)
{
	if (other.empty())
		return *this;

	if (empty())
	{
		m_Head = other.m_Head;
		m_Tail = other.m_Tail;
		other.m_Head = other.m_Tail = nullptr;

		sort();

		return *this;
	}

	m_Tail->next = other.m_Head;
	m_Tail = other.m_Tail;
	other.m_Head = other.m_Tail = nullptr;;

	sort();

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::remove(const Type& target)
{
	return removeIf([&target](const Type& value) { return value == target; });
}

template<typename Type>
template<typename Predicate>
inline LinkedList<Type>& LinkedList<Type>::removeIf(Predicate predicate)
{
	if (empty())
		return *this;

	Node* beforeHead = new Node(0, m_Head);
	Node* currNode = beforeHead;
	Node* nextNode = nullptr;

	while (currNode->next)
	{
		if (predicate(currNode->next->data))
		{
			if (currNode->next == m_Head)
				m_Head = m_Head->next;

			if (currNode->next == m_Tail)
				m_Tail = m_Head ? currNode : nullptr;

			nextNode = currNode->next->next;
			delete currNode->next;
			currNode->next = nextNode;
			continue;
		}

		currNode = currNode->next;
	}

	delete beforeHead;

	return *this;
}

template<typename Type>
inline LinkedList<Type>& LinkedList<Type>::reverse()
{
	// Old way
	//LinkedList reversedList;

	//while (!empty())
	//	reversedList.pushFront(this->popFront());

	//*this = std::move(reversedList);

	if (empty())
		return *this;

	Node* last = nullptr;
	Node* curr = m_Head;
	Node* next = curr->next;

	while (next)
	{
		curr->next = last;
		last = curr;
		curr = next;
		next = next->next;
	}

	curr->next = last;
	swap(m_Head, m_Tail);

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
inline void LinkedList<Type>::swap(Node*& firstNode, Node*& secondNode)
{
	Node* tempNode = firstNode;
	firstNode = secondNode;
	secondNode = tempNode;
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

	m_Tail = nullptr;
}

template<typename Type>
inline void LinkedList<Type>::throwIfNull(const Node* node) const
{
	if (!node)
		throw std::out_of_range("The linked list is empty or the index is invalid!");
}

// -------- ITERATORS --------

template<typename Type>
inline LinkedList<Type>::ConstIterator::ConstIterator(Node* ptr)
	: m_Ptr(ptr)
{
}

template<typename Type>
inline typename LinkedList<Type>::ConstIterator& LinkedList<Type>::ConstIterator::operator++()
{
	m_Ptr = m_Ptr->next;
	return *this;
}

template<typename Type>
inline typename LinkedList<Type>::ConstIterator LinkedList<Type>::ConstIterator::operator++(int)
{
	ConstIterator oldIt = ConstIterator(*this);
	++(*this);
	return oldIt;
}

template<typename Type>
inline typename const Type& LinkedList<Type>::ConstIterator::operator*() const
{
	return m_Ptr->data;
}

template<typename Type>
inline typename const Type* LinkedList<Type>::ConstIterator::operator->() const
{
	return &m_Ptr->data;
}

template<typename Type>
inline typename bool LinkedList<Type>::ConstIterator::operator==(const ConstIterator& other) const
{
	return m_Ptr == other.m_Ptr;
}

template<typename Type>
inline typename bool LinkedList<Type>::ConstIterator::operator!=(const ConstIterator& other) const
{
	return !(*this == other);
}

template<typename Type>
inline LinkedList<Type>::Iterator::Iterator(Node* ptr)
	: ConstIterator(ptr)
{
}

template<typename Type>
inline typename Type& LinkedList<Type>::Iterator::operator*()
{
	return ConstIterator::m_Ptr->data;
}

template<typename Type>
inline typename Type* LinkedList<Type>::Iterator::operator->()
{
	return &ConstIterator::m_Ptr->data;
}
