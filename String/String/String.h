#ifndef STRING_H

#define STRING_H

#include <iostream>

class String
{
public:
	String();
	String(const char* string);
	String(const char& symbol);
	String(const String& other);
	String(String&& other) noexcept;
	~String();

	String& operator= (const String& other);
	String& operator= (String&& other) noexcept;
	String& operator= (const char* string);
	String& operator= (const char& symbol);

	String& operator+= (const char* string);
	String& operator+= (const char& symbol);
	String& operator+= (const String& other);
	bool operator== (const char* string);
	bool operator== (const char& symbol);
	bool operator== (const String& other);
	bool operator!= (const char* string);
	bool operator!= (const char& symbol);
	bool operator!= (const String& other);

	char& operator[] (const int& index);
	const char& operator[] (const int& index) const;

	char& at(const int& index);
	const char& at(const int& index) const;

	char& back();
	char& front();
	const char& back() const;
	const char& front() const;

	const char* c_str() const;
	int size() const;
	int length() const;
	int capacity() const;
	bool empty() const;

	String& append(const char* string);
	String& append(const char& symbol);
	String& append(const String& other);

	void clear();
	void pushBack(const char& symbol);

private:
	char* m_Str;
	int m_Size;
	int m_Capacity;

	int stringLength(const char* str);
	char* stringCopy(char* dest, const char* source);
	char* stringCopy(char* dest, const char* source, const int& size);
	bool compareStrings(const char* lhs, const char* rhs);

	int calculateCapacity(const int& num);

	void resize(const int& newSize);

	void freeMemory();
	void copy(const String& other);
	void swap(String& other);

	friend std::istream& operator>>(std::istream& in, String& str);
};

std::istream& getLine(std::istream& in, String& str, const char& delimiter = '\n');
std::ostream& operator<< (std::ostream& out, const String& str);
String operator+ (const String& lhs, const String& rhs);
String operator+ (const String& lhs, const char* rhs);
String operator+ (String&& lhs, const char* rhs);
String operator+ (const char* lhs, const String& rhs);
String operator+ (const char* lhs, String&& rhs);
void swapStrings(String& str1, String& str2);

#endif