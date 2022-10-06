#ifndef VECTOR_H

#define VECTOR_H

#include <stdexcept>

// Too lazy to make a seperate .inl file lol

template <typename Type>
class Vector
{
public:
	Vector();
	Vector(const Type* data, const int& dataSize);
	Vector(const Vector& other);
	Vector(Vector&& other) noexcept;
	~Vector();

	Vector& operator= (const Vector& other);
	Vector& operator= (Vector&& other) noexcept;

	Type& operator[] (const int& index);
	const Type& operator[] (const int& index) const;

	Type& at(const int& index);
	const Type& at(const int& index) const;

	Type& back();
	Type& front();
	const Type& back() const;
	const Type& front() const;

	const Type* data() const;
	int size() const;
	int capacity() const;
	bool empty() const;

	void clear();
	void insert(const Type* data, const int& dataSize);
	void erase(int index);
	void erase(int first, int last);
	void pushBack(const Type& el);
	void popBack();

private:
	Type* m_Data;
	int m_Size;
	int m_Capacity;

	int calculateCapacity(const int& num);
	void resize(const int& newSize);

	void freeMemory();
	void copy(const Vector& other);
	void swap(Vector& other);
};

template<typename Type>
inline Vector<Type>::Vector()
{
	m_Size = 0;
	m_Capacity = 0;
	m_Data = nullptr;
}

template<typename Type>
inline Vector<Type>::Vector(const Type* data, const int& dataSize)
{
	if (dataSize <= 0)
		throw std::invalid_argument("The data's size can not be negative or zero!");

	m_Size = 0;
	m_Capacity = calculateCapacity(dataSize);
	m_Data = new Type[m_Capacity];

	insert(data, dataSize);
}

template<typename Type>
inline Vector<Type>::Vector(const Vector& other)
{
	copy(other);
}

template<typename Type>
inline Vector<Type>::Vector(Vector&& other) noexcept
	: Vector()
{
	swap(other);
}

template<typename Type>
inline Vector<Type>::~Vector()
{
	freeMemory();
}

template<typename Type>
inline Vector<Type>& Vector<Type>::operator=(const Vector& other)
{
	if (this != &other)
	{
		freeMemory();
		copy(other);
	}

	return *this;
}

template<typename Type>
inline Vector<Type>& Vector<Type>::operator=(Vector<Type>&& other) noexcept
{
	if (this != &other)
		swap(other);

	return *this;
}

template<typename Type>
inline Type& Vector<Type>::operator[](const int& index)
{
	return m_Data[index];
}

template<typename Type>
inline const Type& Vector<Type>::operator[](const int& index) const
{
	return m_Data[index];
}

template<typename Type>
inline Type& Vector<Type>::at(const int& index)
{
	if (index < 0 || index >= m_Size)
		throw std::out_of_range("Index out of range exception!");

	return m_Data[index];
}

template<typename Type>
inline const Type& Vector<Type>::at(const int& index) const
{
	if (index < 0 || index >= m_Size)
		throw std::out_of_range("Index out of range exception!");

	return m_Data[index];
}

template<typename Type>
inline Type& Vector<Type>::back()
{
	if (empty())
		throw std::exception("The vector is empty!");

	return m_Data[m_Size - 1];
}

template<typename Type>
inline Type& Vector<Type>::front()
{
	if (empty())
		throw std::exception("The vector is empty!");

	return m_Data[0];
}

template<typename Type>
inline const Type& Vector<Type>::back() const
{
	if (empty())
		throw std::exception("The vector is empty!");

	return m_Data[m_Size - 1];
}

template<typename Type>
inline const Type& Vector<Type>::front() const
{
	if (empty())
		throw std::exception("The vector is empty!");

	return m_Data[0];
}

template<typename Type>
inline const Type* Vector<Type>::data() const
{
	return m_Data;
}

template<typename Type>
inline int Vector<Type>::size() const
{
	return m_Size;
}

template<typename Type>
inline int Vector<Type>::capacity() const
{
	return m_Capacity;
}

template<typename Type>
inline bool Vector<Type>::empty() const
{
	return m_Size <= 0;
}

template<typename Type>
inline void Vector<Type>::clear()
{
	m_Size = 0;
	m_Capacity = 0;
	freeMemory();
	m_Data = nullptr;
}

template<typename Type>
inline void Vector<Type>::insert(const Type* data, const int& dataSize)
{
	for (int i = 0; i < dataSize; i++)
	{
		pushBack(data[i]);
	}
}

template<typename Type>
inline void Vector<Type>::erase(int index)
{
	// Check if this index exists
	at(index);

	for (int i = index + 1; i < m_Size; ++i)
	{
		m_Data[index++] = m_Data[i];
	}

	m_Size--;
}

template<typename Type>
inline void Vector<Type>::erase(int first, int last)
{
	if (first > last)
		throw std::invalid_argument("First can not be bigger than last!");

	if (first < 0)
		throw std::out_of_range("First index is out of range!");

	if (last > m_Size - 1)
		throw std::out_of_range("Last index is out of range!");

	int diff = last - first + 1;

	for (int i = last + 1; i <= m_Size; ++i)
	{
		m_Data[first++] = m_Data[i];
	}

	m_Size -= diff;
}

template<typename Type>
inline void Vector<Type>::pushBack(const Type& el)
{
	if (m_Size >= m_Capacity)
		resize(m_Capacity);

	m_Data[m_Size++] = el;
}

template<typename Type>
inline void Vector<Type>::popBack()
{
	m_Size--;
}

template<typename Type>
inline int Vector<Type>::calculateCapacity(const int& newSize)
{
	if (newSize <= 2)
		return 4;

	if (newSize <= 8)
		return 16;

	if (newSize <= 16)
		return 32;

	return ((newSize / 16) + 1) * 16;
}

template<typename Type>
inline void Vector<Type>::resize(const int& newSize)
{
	int newCapacity = calculateCapacity(newSize);
	Type* newData = new Type[newCapacity];

	int i;
	for (i = 0; i < m_Capacity && i < newCapacity; ++i)
	{
		newData[i] = m_Data[i];
	}

	delete[] m_Data;

	m_Data = newData;
	m_Capacity = newCapacity;
	m_Size = newCapacity < m_Size ? newCapacity : m_Size;
}

template<typename Type>
inline void Vector<Type>::freeMemory()
{
	delete[] m_Data;
}

template<typename Type>
inline void Vector<Type>::copy(const Vector& other)
{
	m_Size = other.m_Size;
	m_Capacity = other.m_Capacity;
	m_Data = new Type[m_Capacity];

	for (int i = 0; i < other.m_Size && i < m_Capacity; i++)
	{
		m_Data[i] = other.m_Data[i];
	}
}

template<typename Type>
inline void Vector<Type>::swap(Vector& other)
{
	std::swap(m_Size, other.m_Size);
	std::swap(m_Capacity, other.m_Capacity);
	std::swap(m_Data, other.m_Data);
}

#endif // !VECTOR_H