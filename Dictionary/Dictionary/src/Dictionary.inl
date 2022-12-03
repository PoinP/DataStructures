#include "Dictionary.h"

#include <stdexcept>

template<typename TKey, typename TValue>
inline Dictionary<TKey, TValue>::Dictionary()
	: m_Root(nullptr)
{
}

template<typename TKey, typename TValue>
inline Dictionary<TKey, TValue>::Dictionary(std::initializer_list<Pair> init)
	: Dictionary()
{
	for (Pair pair : init)
	{
		add(pair.key, pair.value);
	}
}

template<typename TKey, typename TValue>
inline Dictionary<TKey, TValue>::Dictionary(const Dictionary& other)
	: Dictionary()
{
	copy(m_Root, other.m_Root);
}

template<typename TKey, typename TValue>
inline Dictionary<TKey, TValue>::Dictionary(Dictionary&& other) noexcept
	: Dictionary()
{
	std::swap(m_Root, other.m_Root);
}

template<typename TKey, typename TValue>
inline Dictionary<TKey, TValue>::~Dictionary()
{
	deleteTree(m_Root);
}

template<typename TKey, typename TValue>
inline Dictionary<TKey, TValue>& Dictionary<TKey, TValue>::operator=(const Dictionary& other)
{
	if (this != &other)
	{
		clear();
		copy(m_Root, other.m_Root);
	}

	return *this;
}

template<typename TKey, typename TValue>
inline Dictionary<TKey, TValue>& Dictionary<TKey, TValue>::operator=(Dictionary&& other) noexcept
{
	std::swap(m_Root, other.m_Root);
	return *this;
}

template<typename TKey, typename TValue>
inline TValue& Dictionary<TKey, TValue>::at(const TKey& key)
{
	return const_cast<TValue&>(static_cast<const Dictionary<TKey, TValue>&>(*this).at(key));
}

template<typename TKey, typename TValue>
inline const TValue& Dictionary<TKey, TValue>::at(const TKey& key) const
{
	if (isEmpty())
		throw std::invalid_argument("The dictionary is empty!");

	const Node* foundValue = findKey(key);

	if (!foundValue)
		throw std::invalid_argument("No such key exists");

	return foundValue->data.value;
}

template<typename TKey, typename TValue>
inline TValue& Dictionary<TKey, TValue>::operator[](const TKey& key)
{
	return at(key);
}

template<typename TKey, typename TValue>
inline const TValue& Dictionary<TKey, TValue>::operator[](const TKey& key) const
{
	return at(key);
}

template<typename TKey, typename TValue>
inline typename Dictionary<TKey, TValue>::ConstIterator Dictionary<TKey, TValue>::begin() const
{
	if (!m_Root)
		return nullptr;

	Node* rootCopy = m_Root;

	while (rootCopy->left)
		rootCopy = rootCopy->left;

	return ConstIterator(rootCopy);
}

template<typename TKey, typename TValue>
inline typename Dictionary<TKey, TValue>::ConstIterator Dictionary<TKey, TValue>::end() const
{
	return ConstIterator(nullptr);
}

template<typename TKey, typename TValue>
inline bool Dictionary<TKey, TValue>::isEmpty() const
{
	return !m_Root;
}

template<typename TKey, typename TValue>
inline size_t Dictionary<TKey, TValue>::size() const
{
	return size(m_Root);
}

template<typename TKey, typename TValue>
inline void Dictionary<TKey, TValue>::clear()
{
	deleteTree(m_Root);
}

template<typename TKey, typename TValue>
inline void Dictionary<TKey, TValue>::add(const TKey& key, const TValue& value)
{
	if (!m_Root)
	{
		m_Root = new Node(Pair(key, value));
		return;
	}

	Node* treeIter = m_Root;

	while (treeIter)
	{
		if (key < treeIter->data.key)
		{
			if (treeIter->left)
			{
				treeIter = treeIter->left;
				continue;
			}

			treeIter->left = new Node(Pair(key, value), treeIter);
			return;
		}
		else
		{
			if (treeIter->right)
			{
				treeIter = treeIter->right;
				continue;
			}

			treeIter->right = new Node(Pair(key, value), treeIter);
			return;
		}
	}
}

template<typename TKey, typename TValue>
inline void Dictionary<TKey, TValue>::erase(const TKey& key)
{
	if (isEmpty())
		return;

	deleteKey(m_Root, key);
}

template<typename TKey, typename TValue>
inline void Dictionary<TKey, TValue>::erase(ConstIterator pos)
{
	erase(pos.getKey());
}

template<typename TKey, typename TValue>
inline void Dictionary<TKey, TValue>::erase(ConstIterator first, ConstIterator last)
{
	ConstIterator firstCopy = first;
	int diff = 0;

	while (firstCopy != last && firstCopy != end())
	{
		diff++;
		firstCopy++;
	}

	TKey* keys = new TKey[diff];

	for (int i = 0; i < diff; i++)
	{
		keys[i] = first.getKey();
		first++;
	}

	for (int i = 0; i < diff; i++)
	{
		erase(keys[i]);
	}

	delete[] keys;
}

template<typename TKey, typename TValue>
inline void Dictionary<TKey, TValue>::swap(Dictionary& other)
{
	Node* temp = m_Root;
	m_Root = other.m_Root;
	other.m_Root = temp;
}

template<typename TKey, typename TValue>
inline typename Dictionary<TKey, TValue>::ConstIterator Dictionary<TKey, TValue>::find(const TKey& key) const
{
	Node* treeIter = m_Root;

	while (treeIter)
	{
		if (treeIter->data.key == key)
			return ConstIterator(treeIter);

		if (treeIter->data.key > key)
			treeIter = treeIter->left;
		else
			treeIter = treeIter->right;
	}

	return end();
}

template<typename TKey, typename TValue>
inline bool Dictionary<TKey, TValue>::contains(const TKey& key) const
{
	return find(key) != end();
}

template<typename TKey, typename TValue>
inline void Dictionary<TKey, TValue>::copy(Node* root, Node* otherRoot)
{
	if (!otherRoot)
		return;

	if (!m_Root)
	{
		m_Root = new Node(otherRoot->data);
		root = m_Root;
	}

	if (otherRoot->left)
		root->left = new Node(otherRoot->left->data, root);

	if (otherRoot->right)
		root->right = new Node(otherRoot->right->data, root);

	copy(root->left, otherRoot->left);
	copy(root->right, otherRoot->right);
}

template<typename TKey, typename TValue>
inline void Dictionary<TKey, TValue>::deleteTree(Node*& root)
{
	if (!root)
		return;

	deleteTree(root->left);
	deleteTree(root->right);

	delete root;
	root = nullptr;
}

template<typename TKey, typename TValue>
inline std::size_t Dictionary<TKey, TValue>::size(Node* root) const
{
	if (!root)
		return 0;

	return 1 + size(root->left) + size(root->right);
}

template<typename TKey, typename TValue>
inline typename Dictionary<TKey, TValue>::Node* Dictionary<TKey, TValue>::findKey(const TKey& key)
{
	return static_cast<Node*>(const_cast<const Dictionary<int, int>&>(*this).findKey(key));
}

template<typename TKey, typename TValue>
inline typename const Dictionary<TKey, TValue>::Node* Dictionary<TKey, TValue>::findKey(const TKey& key) const
{
	Node* treeIter = m_Root;

	while (treeIter)
	{
		if (treeIter->data.key == key)
			return treeIter;

		if (treeIter->data.key > key)
			treeIter = treeIter->left;
		else
			treeIter = treeIter->right;
	}

	return nullptr;
}

template<typename TKey, typename TValue>
inline typename Dictionary<TKey, TValue>::Node* Dictionary<TKey, TValue>::deleteKey(Node* root, const TKey& key)
{
	if (!root)
		return nullptr;

	if (root->data.key > key)
	{
		root->left = deleteKey(root->left, key);
	}
	else if (root->data.key < key)
	{
		root->right = deleteKey(root->right, key);
	}
	else
	{
		if (!root->left && !root->right)
		{
			if (root == m_Root)
				m_Root = nullptr;

			delete root;
			return nullptr;
		}

		Node* temp;
		if (!root->left)
		{
			temp = root->right;
			temp->parent = root->parent;

			if (root == m_Root)
				m_Root = temp;

			delete root;
			return temp;
		}
		else if (!root->right)
		{
			temp = root->left;
			temp->parent = root->parent;

			if (root == m_Root)
				m_Root = temp;

			delete root;
			return temp;
		}
		else
		{
			temp = root->right;

			while (temp->left)
				temp = temp->left;

			root->data = temp->data;
			root->right = deleteKey(root->right, root->data.key);
		}
	}

	return root;
}

template<typename TKey, typename TValue>
inline Dictionary<TKey, TValue>::ConstIterator::ConstIterator(Node* iter)
	: m_Iter(iter)
{
}

template<typename TKey, typename TValue>
inline bool Dictionary<TKey, TValue>::ConstIterator::operator==(ConstIterator other) const
{
	return m_Iter == other.m_Iter;
}

template<typename TKey, typename TValue>
inline bool Dictionary<TKey, TValue>::ConstIterator::operator!=(ConstIterator other) const
{
	return !(*this == other);
}

template<typename TKey, typename TValue>
inline typename Dictionary<TKey, TValue>::ConstIterator& Dictionary<TKey, TValue>::ConstIterator::operator++()
{
	if (!m_Iter)
		return *this;

	Node* p;

	if (m_Iter->right)
	{
		m_Iter = m_Iter->right;

		while (m_Iter->left)
			m_Iter = m_Iter->left;
	}
	else
	{
		p = m_Iter->parent;

		while (p && p->left != m_Iter)
		{
			m_Iter = p;
			p = m_Iter->parent;
		}

		m_Iter = p;
	}

	return *this;
}

template<typename TKey, typename TValue>
inline typename Dictionary<TKey, TValue>::ConstIterator Dictionary<TKey, TValue>::ConstIterator::operator++(int)
{
	ConstIterator oldValue(*this);
	++(*this);
	return oldValue;
}

template<typename TKey, typename TValue>
inline const TValue& Dictionary<TKey, TValue>::ConstIterator::operator*() const
{
	return m_Iter->data.value;
}

template<typename TKey, typename TValue>
inline const TValue* Dictionary<TKey, TValue>::ConstIterator::operator->() const
{
	return &m_Iter->data.value;
}

template<typename TKey, typename TValue>
inline TKey& Dictionary<TKey, TValue>::ConstIterator::getKey() const
{
	return m_Iter->data.key;
}
