#include "String.h"

#include <stdexcept>

String::String()
{
	m_Size = 0;
	m_Capacity = 2;
	m_Str = new char[m_Capacity];
	m_Str[0] = '\0';
}

String::String(const char* string)
{
	m_Size = stringLength(string);
	m_Capacity = calculateCapacity(m_Size);
	m_Str = new char[m_Capacity];
	stringCopy(m_Str, string);
}

String::String(const char& symbol)
{
	m_Size = 1;
	m_Capacity = 4;
	m_Str = new char[m_Capacity];
	m_Str[0] = symbol;
	m_Str[1] = '\0';
}

String::String(const String& other)
{
	copy(other);
}

String::String(String&& other) noexcept
	: String()
{
	swap(other);
}

String::~String()
{
	freeMemory();
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		freeMemory();
		copy(other);
	}

	return *this;
}

String& String::operator=(String&& other) noexcept
{
	if (this != &other)
		swap(other);

	return *this;
}

String& String::operator=(const char* string)
{
	freeMemory();

	m_Size = stringLength(string);

	if (m_Size == 0)
		m_Capacity = 2;
	else
		m_Capacity = calculateCapacity(m_Size);

	m_Str = new char[m_Capacity];
	stringCopy(m_Str, string);

	return *this;
}

String& String::operator=(const char& symbol)
{
	freeMemory();

	m_Size = 1;
	m_Capacity = 4;
	m_Str = new char[m_Capacity];
	m_Str[0] = symbol;
	m_Str[1] = '\0';

	return *this;
}

String& String::operator+=(const char* string)
{
	return this->append(string);
}

String& String::operator+=(const char& symbol)
{
	return this->append(symbol);
}

String& String::operator+=(const String& other)
{
	return this->append(other);
}

bool String::operator==(const char* string)
{
	return compareStrings(m_Str, string);
}

bool String::operator==(const char& symbol)
{
	if (m_Size > 0)
		return m_Str[0] == symbol;

	return false;
}

bool String::operator==(const String& other)
{
	return *this == other.m_Str;
}

bool String::operator!=(const char* string)
{
	return !(*this == string);
}

bool String::operator!=(const char& symbol)
{
	return !(*this == symbol);
}

bool String::operator!=(const String& other)
{
	return !(*this == other);
}

char& String::operator[](const int& index)
{
	return m_Str[index];
}

const char& String::operator[](const int& index) const
{
	return m_Str[index];
}

char& String::at(const int& index)
{
	if (index < 0 || index >= m_Size)
		throw std::out_of_range("Index out of range exception!");

	return m_Str[index];
}

const char& String::at(const int& index) const
{
	if (index < 0 || index >= m_Size)
		throw std::out_of_range("Index out of range exception!");

	return m_Str[index];
}

char& String::back()
{
	if (m_Size == 0)
		throw std::invalid_argument("The string is empty!");

	return m_Str[m_Size - 1];
}

char& String::front()
{
	if (m_Size == 0)
		throw std::invalid_argument("The string is empty!");

	return m_Str[0];
}

const char& String::back() const
{
	if (m_Size == 0)
		throw std::invalid_argument("The string is empty!");

	return m_Str[m_Size - 1];
}

const char& String::front() const
{
	if (m_Size == 0)
		throw std::invalid_argument("The string is empty!");

	return m_Str[0];
}

const char* String::c_str() const
{
	return m_Str;
}

int String::size() const
{
	return m_Size;
}

int String::length() const
{
	return m_Size;
}

int String::capacity() const
{
	return m_Capacity;
}

bool String::empty() const
{
	return m_Size == 0;
}

String& String::append(const char* string)
{
	for (int i = 0; string[i] != '\0'; ++i)
	{
		pushBack(string[i]);
	}

	return *this;
}

String& String::append(const char& symbol)
{
	pushBack(symbol);

	return *this;
}

String& String::append(const String& other)
{
	append(other.m_Str);

	return *this;
}

void String::clear()
{
	*this = String();
}

void String::pushBack(const char& symbol)
{
	if (m_Size + 1 >= m_Capacity)
		resize(m_Capacity);

	m_Str[m_Size++] = symbol;
	m_Str[m_Size] = '\0';
}

int String::stringLength(const char* str)
{
	int i;
	for (i = 0; str[i] != '\0'; ++i);

	return i;
}

char* String::stringCopy(char* dest, const char* source)
{
	int i;
	for (i = 0; source[i] != '\0'; i++)
	{
		dest[i] = source[i];
	}

	dest[i] = source[i];

	return dest;
}

char* String::stringCopy(char* dest, const char* source, const int& size)
{
	int i;
	for (i = 0; source[i] != '\0' && i < size; i++)
	{
		dest[i] = source[i];
	}

	dest[i] = '\0';

	return dest;
}

bool String::compareStrings(const char* lhs, const char* rhs)
{
	int i;
	for (i = 0; lhs[i] != '\0' && rhs[i] != '\0'; ++i)
	{
		if (rhs[i] != lhs[i])
			return false;
	}

	return rhs[i] == lhs[i];
}

int String::calculateCapacity(const int& newSize)
{
	if (newSize <= 2)
		return 4;

	if (newSize <= 8)
		return 16;

	if (newSize <= 16)
		return 32;

	return ((newSize / 16) + 1) * 16;
}

void String::resize(const int& newSize)
{
	int newCapacity = calculateCapacity(newSize);
	char* newStr = new char[newCapacity];

	int i;
	for (i = 0; m_Str[i] != '\0' && i < newCapacity - 1; ++i)
	{
		newStr[i] = m_Str[i];
	}

	newStr[i] = '\0';

	delete[] m_Str;

	m_Str = newStr;
	m_Capacity = newCapacity;
	m_Size = stringLength(newStr);
}

void String::freeMemory()
{
	delete[] m_Str;
}

void String::copy(const String& other)
{
	m_Size = other.m_Size;
	m_Capacity = other.m_Capacity;
	m_Str = new char[m_Capacity];
	stringCopy(m_Str, other.m_Str);
}

void String::swap(String& other)
{
	std::swap(m_Size, other.m_Size);
	std::swap(m_Capacity, other.m_Capacity);
	std::swap(m_Str, other.m_Str);
}




std::ostream& operator<<(std::ostream& out, const String& str)
{
	return out << str.c_str();
}

std::istream& operator>>(std::istream& in, String& str)
{
	str = String();
	char c;

	do
	{
		c = in.get();
		if (c != '\n' && c != ' ')
			str.pushBack(c);
		else
			break;
	} while (true);

	return in;
}

std::istream& getLine(std::istream& in, String& str, const char& delimiter)
{
	str = String();
	char c;

	do
	{
		c = in.get();
		if (c == delimiter)
			break;

		str.pushBack(c);
	} while (true);

	return in;
}

String operator+(const String& lhs, const String& rhs)
{
	String newStr = lhs;
	return newStr.append(rhs);
}

String operator+(const String& lhs, const char* rhs)
{
	String newStr = lhs;
	return newStr.append(rhs);
}

String operator+(String&& lhs, const char* rhs)
{
	String newStr = lhs;
	return newStr.append(rhs);
}

String operator+(const char* lhs, const String& rhs)
{
	String newStr = lhs;
	return newStr.append(rhs);
}

String operator+(const char* lhs, String&& rhs)
{
	String newStr = lhs;
	return newStr.append(rhs);
}

void swapStrings(String& str1, String& str2)
{
	String temp = str1;
	str1 = str2;
	str2 = temp;
}
