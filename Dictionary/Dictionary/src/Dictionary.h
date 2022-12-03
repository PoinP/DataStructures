#ifndef DICTIONARY_H

#define DICTIONARY_H

#include <initializer_list>

template <typename TKey, typename TValue>
class Dictionary
{
	struct Pair;
	struct Node;
	class ConstIterator;

public:
	using key_type			= TKey;
	using mapped_type		= TValue;
	using value_type		= Pair;
	using size_type			= std::size_t;
	using reference			= mapped_type&;
	using const_reference	= const mapped_type&;
	using pointer			= mapped_type*;
	using const_pointer		= const mapped_type*;
	using iterator			= ConstIterator;
	using const_iterator	= ConstIterator;

public:
	Dictionary();
	Dictionary(std::initializer_list<Pair> init);
	Dictionary(const Dictionary& other);
	Dictionary(Dictionary&& other) noexcept;
	~Dictionary();
	
	Dictionary& operator= (const Dictionary& other);
	Dictionary& operator= (Dictionary&& other) noexcept;

	// ----------- ELEMENT ACCESS ----------- //
	TValue& at(const TKey& key);
	const TValue& at(const TKey& key) const;

	TValue& operator[](const TKey& key);
 	const TValue& operator[](const TKey& key) const;

	// ----------- ITERATORS ----------- //
	ConstIterator begin() const;
	ConstIterator end() const;

	// ----------- CAPACITY ----------- //
	bool isEmpty() const;
	size_t size() const;

	// ----------- MODIFIERS ----------- //
	void clear();
	void add(const TKey& key, const TValue& value);
	void erase(const TKey& key);
	void erase(ConstIterator pos);
	void erase(ConstIterator first, ConstIterator last);
	void swap(Dictionary& other);

	// ----------- LOOKUP ----------- //
	ConstIterator find(const TKey& key) const;
	bool contains(const TKey& key) const;

private:
	Node* m_Root;

	void copy(Node* root, Node* otherRoot);
	void deleteTree(Node*& root);
	std::size_t size(Node* root) const;
	
	Node* findKey(const TKey& key);
	const Node* findKey(const TKey& key) const;

	Node* deleteKey(Node* root, const TKey& key);

public:
	class ConstIterator
	{
		friend class Dictionary;
	public:
		using iterator_category		= std::forward_iterator_tag;
		using value_type			= typename Dictionary::value_type;
		using pointer				= typename Dictionary::const_pointer*;
		using reference				= const value_type&;

	public:
		ConstIterator(Node* iter = nullptr);

		bool operator== (ConstIterator other) const;
		bool operator!= (ConstIterator other) const;

		ConstIterator& operator++();
		ConstIterator operator++(int);

		const TValue& operator*() const;
		const TValue* operator->() const;

	private:
		Node* m_Iter;

		TKey& getKey() const;
	};

	struct Pair
	{
		Pair(const TKey& key, const TValue& value)
			: key(key), value(value)
		{}

		TKey key;
		TValue value;
	};

private:

	struct Node
	{
		Node(const Pair& data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
			: data(data), parent(parent), left(left), right(right)
		{}

		Pair data;
		Node* parent;
		Node* left;
		Node* right;
	};
};

#include "Dictionary.inl";

#endif // !DICTIONARY_H