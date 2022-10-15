#ifndef LINKED_LIST_H

#define LINKED_LIST_H

#include <initializer_list>

template<typename Type>
class LinkedList
{
private:
	struct Node
	{
		Type data;
		Node* next;

		Node(const Type& data, Node* next = nullptr) : data(data), next(next) {}
	};

public:
	class Iterator;
	class ConstIterator;

	LinkedList();
	explicit LinkedList(std::initializer_list<Type> initList);
	LinkedList(const LinkedList& other);
	LinkedList(LinkedList&& other) noexcept;
	~LinkedList();

	LinkedList& operator=(const LinkedList& other);
	LinkedList& operator=(LinkedList&& other) noexcept;

	LinkedList& assign(const Type* values, size_t count);
	template<typename InputIt>
	LinkedList& assign(InputIt begin, InputIt end);
	LinkedList& assign(std::initializer_list<Type> initList);


	// -------- MODIFIERS --------

	LinkedList& pushFront(const Type& data);
	LinkedList& pushBack(const Type& data);

	Type popFront();
	Type popBack(); // Note: It takes O(n) complexity to popBack an item!

	LinkedList& clear();

	LinkedList& insertAfter(ConstIterator pos, const Type& value);
	LinkedList& insertAfter(ConstIterator pos, const Type* values, size_t count);
	template<typename InputIt>
	LinkedList& insertAfter(ConstIterator pos, InputIt begin, InputIt end);
	LinkedList& insertAfter(ConstIterator pos, std::initializer_list<Type> initList);

	LinkedList& eraseAfter(ConstIterator pos);
	LinkedList& eraseAfter(ConstIterator first, ConstIterator last);

	LinkedList& swap(LinkedList& other);

	// -------- ELEMENT ACCESS --------

	Type& search(const Type& data);
	const Type& search(const Type& data) const;

	Type& front();
	const Type& front() const;

	Type& back();
	const Type& back() const;

	const Type& read(int nodeIndex) const;

	// -------- ITERATORS --------

	Iterator begin();
	ConstIterator begin() const;

	Iterator end();
	ConstIterator end() const;

	// -------- OPERATIONS --------

	LinkedList& merge(LinkedList& other); // Probably a slow af merge
	LinkedList& remove(const Type& target);
	template <typename Predicate>
	LinkedList& removeIf(Predicate predicate);
	LinkedList& reverse();
	LinkedList& sort(); // Sorts in ascending order

	// -------- CAPACITY --------

	int size() const; // Returns the size by traversing the list. O(n) time complexity
	bool empty() const;

private:
	Node* m_Head;
	Node* m_Tail;

	void copy(const LinkedList& other);
	void swap(Node*& firstNode, Node*& secondNode);
	void move(LinkedList&& other);
	void clearData();
	void throwIfNull(const Node* node) const;

public:
	class ConstIterator
	{
		friend LinkedList<Type>;

	public:
		ConstIterator(Node* ptr = nullptr);

		ConstIterator& operator++();   // Prefix ++
		ConstIterator operator++(int); // Postfix ++

		const Type& operator*() const;
		const Type* operator->() const;

		bool operator==(const ConstIterator& other) const;
		bool operator!=(const ConstIterator& other) const;

	protected:
		Node* m_Ptr;
	};

	class Iterator : public ConstIterator
	{
		friend LinkedList<Type>;

	public:
		Iterator(Node* ptr = nullptr);

		Type& operator*();
		Type* operator->();
	};
};

#include "LinkedList.inl"

#endif // !LINKED_LIST_H
