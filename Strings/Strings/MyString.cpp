#include "MyString.h"
#include <iostream>

using namespace std;

void String::copyChar(const char* source, char* dest, size_t start, size_t len) const
{
	for (size_t i = 0; i < len; ++i)
		dest[start + i] = source[i];
}

void String::storeDigits(char* store, size_t pos, int number)
{
	if (number >= 10)
		storeDigits(store, pos - 1, number / 10);

	store[--pos] = (number % 10) + 48;
}

String::String()
{
	m_len = 0;
	m_start = 0;
}

String::String(const String& s)
{
	std::cout << "Copy constructor called for string " << s << std::endl;

	m_string = s.m_string;
	m_start = s.m_start;
	m_len = s.m_len;
}

String::String(String&& s)
{
	std::cout << "Move constructor called for string " << s << std::endl;

	m_string = s.m_string;
	s.m_string = nullptr;

	m_len = s.m_len;
	s.m_len = 0;

	m_start = s.m_start;
	s.m_start = 0;
}

String::String(const char* s)
{
	m_len = 0;
	m_start = 0;

	while (s[m_len] != '\0') ++m_len;

	if (m_len > 0)
	{
		m_string = shared_ptr<char>(unique_ptr<char[]>(new char[m_len]));
		copyChar(s, m_string.get(), 0, m_len);
	}
}

String::~String()
{
}

char String::charAt(size_t index) const
{
	if (index >= m_len)
		throw new exception("Invalid index");

	return m_string.get()[m_start + index];
}

int String::compareTo(const String& s) const
{
	size_t pos1 = m_start;
	size_t pos2 = s.m_start;

	while (pos1 < length())
	{
		if (pos2 >= s.length()) return 1;
		if (s.charAt(pos2) > charAt(pos1)) return -1;
		if (charAt(pos1) > s.charAt(pos2)) return 1;

		++pos1;
		++pos2;
	}

	if (pos2 < s.length()) return -1;
	return 0;
}

size_t String::length() const {
	return m_len;
}

String String::substring(size_t beg, size_t end) const
{
	if (beg >= m_len || end <= beg)
	{
		return String();
	}

	String substr = String(*this);
	substr.m_start = beg;
	substr.m_len = end - 1;

	return substr;
}

String String::concat(char c) const
{
	String newStr = String(*this);
	newStr.m_len++;

	newStr.m_string = shared_ptr<char>(unique_ptr<char[]>(new char[newStr.m_len]));
	copyChar(m_string.get(), newStr.m_string.get(), 0, m_len);
	newStr.m_string.get()[newStr.m_len - 1] = c;

	return newStr;
}

String String::concat(const String& s) const
{
	String newStr = String(*this);
	newStr.m_len += s.length();
	newStr.m_string = shared_ptr<char>(unique_ptr<char[]>(new char[newStr.m_len]));
	copyChar(m_string.get(), newStr.m_string.get(), 0, m_len);
	copyChar(s.m_string.get(), newStr.m_string.get(), m_len, s.m_len);

	return newStr;
}

unique_ptr<char[]> String::toCString() const {
	unique_ptr<char[]> r = unique_ptr<char[]>(new char[m_len + 1]);
	const char * const tc = m_string.get();

	for (size_t i = 0; i < m_len; ++i)
		r[i] = tc[m_start + i];

	r[m_len] = '\0';
	return move(r);
}

String String::valueOf(int i)
{
	// count digits
	size_t digits = i < 0 ? 1 : 0;
	int number = i;

	do { number /= 10; digits++; } while (number != 0);

	// allocate char array
	char* str = new char[digits + 1];
	str[digits] = '\0';

	if (i < 0)
	{
		str[0] = '-';
		i = i * -1;
	}

	storeDigits(str, digits, i);
	String digitStr = String(str);

	delete[] str;

	return digitStr;
}