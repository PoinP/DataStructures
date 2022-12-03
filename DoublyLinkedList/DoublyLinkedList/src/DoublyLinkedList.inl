#include "DoublyLinkedList.h";
#include <stdexcept>;

template<typename Type>
inline DoublyLinkedList<Type>::DoublyLinkedList()
	: m_Head(nullptr), m_Tail(nullptr)
{
}

template<typename Type>
inline DoublyLinkedList<Type>::DoublyLinkedList(const DoublyLinkedList& other)
{
	copy(other);
}

template<typename Type>
inline DoublyLinkedList<Type>::DoublyLinkedList(DoublyLinkedList&& other) noexcept
{
	std::swap(m_Head, other.m_Head);
	std::swap(m_Tail, other.m_Tail);
}

template<typename Type>
inline DoublyLinkedList<Type>::DoublyLinkedList(const Type* data, size_t size)
	: DoublyLinkedList()
{
	for (size_t i = 0; i < size; ++i)
		pushBack(data[i]);
}

template<typename Type>
template<typename It>
inline DoublyLinkedList<Type>::DoublyLinkedList(It begin, It end)
	: DoublyLinkedList()
{
	for (; begin != end; ++begin)
		pushBack(*begin);
}

template<typename Type>
inline DoublyLinkedList<Type>::DoublyLinkedList(const std::initializer_list<Type>& initList)
	: DoublyLinkedList()
{
	for (Type item : initList)
		pushBack(item);
}

template<typename Type>
inline DoublyLinkedList<Type>::~DoublyLinkedList()
{
	clear();
}

template<typename Type>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::operator=(const DoublyLinkedList& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}

	return *this;
}

template<typename Type>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::operator=(DoublyLinkedList&& other) noexcept
{
	std::swap(m_Head, other.m_Head);
	std::swap(m_Tail, other.m_Tail);

	return *this;
}

template<typename Type>
inline Type& DoublyLinkedList<Type>::front()
{
	if (!m_Head)
		throw std::invalid_argument("The list is empty!");

	return m_Head->data;
}

template<typename Type>
inline const Type& DoublyLinkedList<Type>::front() const
{
	if (!m_Head)
		throw std::invalid_argument("The list is empty!");

	return m_Head->data;
}

template<typename Type>
inline Type& DoublyLinkedList<Type>::back()
{
	if (!m_Tail)
		throw std::invalid_argument("The list is empty!");

	return m_Tail->data;
}

template<typename Type>
inline const Type& DoublyLinkedList<Type>::back() const
{
	if (!m_Tail)
		throw std::invalid_argument("The list is empty!");

	return m_Tail->data;
}

template<typename Type>
inline typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::begin()
{
	return Iterator(m_Head);
}

template<typename Type>
inline typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::begin() const
{
	return ConstIterator(m_Head);
}

template<typename Type>
inline typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::rbegin()
{
	return Iterator(m_Tail);
}

template<typename Type>
inline typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::rbegin() const
{
	return ConstIterator(m_Tail);
}

template<typename Type>
inline typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::end()
{
	return Iterator(nullptr);
}

template<typename Type>
inline typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::end() const
{
	return ConstIterator(nullptr);
}

template<typename Type>
inline typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::rend()
{
	return Iterator(nullptr);
}

template<typename Type>
inline typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::rend() const
{
	return ConstIterator(nullptr);
}

template<typename Type>
inline bool DoublyLinkedList<Type>::isEmpty() const
{
	return !m_Head;
}

template<typename Type>
inline size_t DoublyLinkedList<Type>::size() const
{
	int i = 0;

	for (auto el : *this)
		++i;

	return i;
}

template<typename Type>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::pushFront(const Type& item)
{
	Node* newNode = new Node(item, nullptr, m_Head);

	if (isEmpty())
		m_Tail = newNode;

	if (!isEmpty())
		m_Head->prev = newNode;

	m_Head = newNode;

	return *this;
}

template<typename Type>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::pushBack(const Type& item)
{
	if (isEmpty())
	{
		pushFront(item);
		return *this;
	}

	Node* newNode = new Node(item, m_Tail);
	m_Tail->next = newNode;
	m_Tail = newNode;

	return *this;
}

template<typename Type>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::popFront()
{
	if (isEmpty())
		throw std::invalid_argument("The list is already empty!");

	Node* nextNode = m_Head->next;
	delete m_Head;

	if (!nextNode)
	{
		m_Head = m_Tail = nullptr;
		return *this;
	}

	nextNode->prev = nullptr;
	m_Head = nextNode;

	return *this;
}

template<typename Type>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::popBack()
{
	if (isEmpty())
		throw std::invalid_argument("The list is already empty!");

	Node* lastNode = m_Tail->prev;
	delete m_Tail;

	if (!lastNode)
	{
		m_Head = m_Tail = nullptr;
		return *this;
	}

	lastNode->next = nullptr;
	m_Tail = lastNode;

	return *this;
}

template<typename Type>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::clear()
{
	while (m_Head)
	{
		Node* nextNode = m_Head->next;
		delete m_Head;
		m_Head = nextNode;
	}

	m_Tail = nullptr;

	return *this;
}

template<typename Type>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::reverse()
{
	Node* currNode = m_Head;
	Node* nextNode = nullptr;
	Node* prevNode = nullptr;

	while (currNode)
	{
		prevNode = currNode->prev;
		nextNode = currNode->next;
		currNode->next = prevNode;
		currNode->prev = nextNode;
		currNode = currNode->prev;
	}

	std::swap(m_Head, m_Tail);

	return *this;
}

template<typename Type>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::sort()
{
	// Selection sort O(n^2) ^^

	if (isEmpty())
		return *this;

	Node* outerNode = m_Head;
	Node* innerNode = outerNode->next;
	Node* minNode = outerNode;

	while (outerNode->next)
	{
		while (innerNode)
		{
			if (minNode->data > innerNode->data)
				minNode = innerNode;

			innerNode = innerNode->next;
		}

		if (outerNode != minNode)
			std::swap(outerNode->data, minNode->data);

		outerNode = outerNode->next;
		innerNode = outerNode->next;
		minNode = outerNode;
	}

	return *this;
}

template<typename Type>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::merge(DoublyLinkedList<Type>& other)
{
	if (other.isEmpty())
		return *this;

	if (isEmpty())
	{
		m_Head = other.m_Head;
		m_Tail = other.m_Tail;
	}
	else
	{

		m_Tail->next = other.m_Head;
		other.m_Head->prev = m_Tail;
		m_Tail = other.m_Tail;
	}

	other.m_Head = nullptr;
	other.m_Tail = nullptr;

	sort();

	return *this;
}

template<typename Type>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::remove(const Type& target)
{
	return removeIf([&target](Type value) { return target == value; });
}

template<typename Type>
template<typename UnaryPredicate>
inline DoublyLinkedList<Type>& DoublyLinkedList<Type>::removeIf(UnaryPredicate predicate)
{
	if (isEmpty())
		return *this;

	Node* prevNode = nullptr;
	Node* currNode = m_Head;
	Node* nextNode = m_Head->next;

	while (currNode)
	{
		if (predicate(currNode->data))
		{
			if (currNode == m_Head)
				m_Head = m_Head->next;

			if (currNode == m_Tail)
				m_Tail = m_Tail->prev;

			if (prevNode)
				prevNode->next = nextNode;

			if (nextNode)
				nextNode->prev = prevNode;

			delete currNode;
		}

		currNode = nextNode;

		if (currNode)
		{
			prevNode = currNode->prev;
			nextNode = currNode->next;
		}
	}

	return*this;
}

template<typename Type>
inline void DoublyLinkedList<Type>::copy(const DoublyLinkedList& other)
{
	if (other.isEmpty())
		return;

	Node* otherNode = other.m_Head;
	m_Head = new Node(otherNode->data);

	Node* currNode = m_Head;

	while (otherNode->next)
	{
		otherNode = otherNode->next;
		currNode->next = new Node(otherNode->data, currNode);
		currNode = currNode->next;
	}

	m_Tail = currNode;
}

template<typename Type>
inline DoublyLinkedList<Type>::ConstIterator::ConstIterator(Node* ptr)
	: m_Ptr(ptr)
{
}

template<typename Type>
inline typename DoublyLinkedList<Type>::ConstIterator& DoublyLinkedList<Type>::ConstIterator::operator++()
{
	m_Ptr = m_Ptr->next;
	return *this;
}

template<typename Type>
inline typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::ConstIterator::operator++(int)
{
	ConstIterator old = ConstIterator(*this);
	++(*this);
	return old;
}

template<typename Type>
inline typename DoublyLinkedList<Type>::ConstIterator& DoublyLinkedList<Type>::ConstIterator::operator--()
{
	m_Ptr = m_Ptr->prev;
	return *this;
}

template<typename Type>
inline typename DoublyLinkedList<Type>::ConstIterator DoublyLinkedList<Type>::ConstIterator::operator--(int)
{
	ConstIterator old = ConstIterator(*this);
	--(*this);
	return old;
}

template<typename Type>
inline bool DoublyLinkedList<Type>::ConstIterator::operator==(ConstIterator other) const
{
	return m_Ptr == other.m_Ptr;
}

template<typename Type>
inline bool DoublyLinkedList<Type>::ConstIterator::operator!=(ConstIterator other) const
{
	return !(*this == other);
}

template<typename Type>
inline const Type& DoublyLinkedList<Type>::ConstIterator::operator*() const
{
	return m_Ptr->data;
}

template<typename Type>
inline const Type* DoublyLinkedList<Type>::ConstIterator::operator->() const
{
	return &m_Ptr->data;
}

template<typename Type>
inline DoublyLinkedList<Type>::Iterator::Iterator(Node* ptr)
	: ConstIterator(ptr)
{
}

template<typename Type>
inline Type& DoublyLinkedList<Type>::Iterator::operator*()
{
	return ConstIterator::m_Ptr->data;
}

template<typename Type>
inline Type* DoublyLinkedList<Type>::Iterator::operator->()
{
	return &ConstIterator::m_Ptr->data;
}

template<typename Type>
inline bool operator==(const DoublyLinkedList<Type>& lhs, const DoublyLinkedList<Type>& rhs)
{
	auto lhsIt = lhs.begin();
	auto rhsIt = rhs.begin();

	while (lhsIt != lhs.end() && rhsIt != rhs.end())
	{
		if (*(lhsIt++) != *(rhsIt++))
			return false;
	}

	if (lhsIt != lhs.end() || rhsIt != rhs.end())
		return false;

	return true;
}

template<typename Type>
inline bool operator!=(const DoublyLinkedList<Type>& lhs, const DoublyLinkedList<Type>& rhs)
{
	return !(lhs == rhs);
}