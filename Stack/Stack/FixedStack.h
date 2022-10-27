#ifndef FIXED_STACK_H

#define FIXED_STACK_H

#include <initializer_list>
#include <stdexcept>

template <typename Type, size_t Size>
class FixedStack;

template <typename Type, size_t Size, typename Predicate>
inline bool compare(const FixedStack<Type, Size>& first, const FixedStack<Type, Size>& second, Predicate predicate);

template <typename Type, size_t Size>
class FixedStack
{
public:
	FixedStack();
	FixedStack(const FixedStack& other);
	FixedStack(FixedStack&& other);

	FixedStack& operator=(const FixedStack& other);
	FixedStack& operator=(FixedStack&& other);

	// ------- ELEMENT ACCESS -------

	const Type& top() const;

	// ------- CAPACITY -------
	
	bool empty() const;
	size_t size() const;

	// ------- MODIFIERS -------

	void pop();
	void push(const Type& element);
	void swap(FixedStack& other);

	template <typename Type, size_t Size, typename Predicate>
	friend bool compare<Type, Size>(const FixedStack<Type, Size>& first, const FixedStack<Type, Size>& second, Predicate predicate);


private:
	Type m_Data[Size] = {0};
	size_t m_UsedSpace;
};

#endif // !FIXED_STACK_H

template<typename Type, size_t Size>
inline FixedStack<Type, Size>::FixedStack()
	: m_UsedSpace(0)
{}

template<typename Type, size_t Size>
inline FixedStack<Type, Size>::FixedStack(const FixedStack& other)
{
	for (int i = 0; i < other.m_UsedSpace; i++)
	{
		m_Data[i] = other.m_Data[i];
	}

	m_UsedSpace = other.m_UsedSpace;
}

template<typename Type, size_t Size>
inline FixedStack<Type, Size>::FixedStack(FixedStack&& other)
{
	std::move(m_Data, other.m_Data);
	std::move(m_UsedSpace, other.m_UsedSpace);
}

template<typename Type, size_t Size>
inline FixedStack<Type, Size>& FixedStack<Type, Size>::operator=(const FixedStack& other)
{
	if (this != other)
	{
		for (int i = 0; i < other.m_UsedSpace; i++)
		{
			m_Data[i] = other.m_Data[i];
		}

		m_UsedSpace = other.m_UsedSpace;
	}

	return *this;
}

template<typename Type, size_t Size>
inline FixedStack<Type, Size>& FixedStack<Type, Size>::operator=(FixedStack&& other)
{
	std::move(m_Data, other.m_Data);
	std::move(m_UsedSpace, other.m_UsedSpace);
}

template<typename Type, size_t Size>
inline const Type& FixedStack<Type, Size>::top() const
{
	if (empty())
		throw std::out_of_range("The stack is empty!");

	return m_Data[m_UsedSpace - 1];
}

template<typename Type, size_t Size>
inline bool FixedStack<Type, Size>::empty() const
{
	return m_UsedSpace == 0;
}

template<typename Type, size_t Size>
inline size_t FixedStack<Type, Size>::size() const
{
	return m_UsedSpace;
}

template<typename Type, size_t Size>
inline void FixedStack<Type, Size>::pop()
{
	if (empty())
		throw std::out_of_range("The stack is empty!");

	m_UsedSpace--;
}

template<typename Type, size_t Size>
inline void FixedStack<Type, Size>::push(const Type& element)
{
	if (m_UsedSpace >= Size)
		throw std::overflow_error("Stack overflow exception!");

	m_Data[m_UsedSpace++] = element;
}

template<typename Type, size_t Size>
inline void FixedStack<Type, Size>::swap(FixedStack& other)
{
	int i = 0;
	Type temp;

	while (i != m_UsedSpace && i != other.m_UsedSpace)
	{
		temp = m_Data[i];
		m_Data[i] = other.m_Data[i];
		other.m_Data[i] = temp;

		++i;
	}
}

// ------- NON-MEMEBER FUNCTIONS -------

template<typename Type, size_t Size, typename Predicate>
inline bool compare(const FixedStack<Type, Size>& first, const FixedStack<Type, Size>& second, Predicate predicate)
{
	if (first.size() != second.size())
		return false;

	for (size_t i = 0; i < first.size(); i++)
	{
		if (!predicate(first.m_Data[i], second.m_Data[i]))
			return false;
	}

	return true;
}

template<typename Type, size_t Size>
inline bool operator==(const FixedStack<Type, Size>& first, const FixedStack<Type, Size>& second)
{
	return compare(first, second, [](const Type& firstEl, const Type& secondEl) { return firstEl == secondEl; });
}

template<typename Type, size_t Size>
inline bool operator!=(const FixedStack<Type, Size>& first, const FixedStack<Type, Size>& second)
{
	return !(first == second);
}

template<typename Type, size_t Size>
inline bool operator>(const FixedStack<Type, Size>& first, const FixedStack<Type, Size>& second)
{
	return compare(first, second, [](const Type& firstEl, const Type& secondEl) { return firstEl > secondEl; });
}

template<typename Type, size_t Size>
inline bool operator>=(const FixedStack<Type, Size>& first, const FixedStack<Type, Size>& second)
{
	return compare(first, second, [](const Type& firstEl, const Type& secondEl) { return firstEl >= secondEl; });
}

template<typename Type, size_t Size>
inline bool operator<(const FixedStack<Type, Size>& first, const FixedStack<Type, Size>& second)
{
	return !(first >= second);
}

template<typename Type, size_t Size>
inline bool operator<=(const FixedStack<Type, Size>& first, const FixedStack<Type, Size>& second)
{
	return !(first > second);
}
