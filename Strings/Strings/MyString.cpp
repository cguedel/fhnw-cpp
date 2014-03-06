#include "MyString.h"
#include <iostream>

using namespace std;

void String::copyChar(const char* source, char* dest, size_t len) const
{
	for (size_t i = 0; i < len; ++i)
		dest[i] = source[i];
}

String::String()
{
	std::cout << "String created" << std::endl;
}

String::String(const String& s)
{
	m_string = s.m_string;
	m_start = s.m_start;
	m_len = s.m_len;
}

String::String(const char* s)
{
	while (s[m_len] != '\0') ++m_len;
	m_string = make_shared<char>(unique_ptr<char[]>(new char[m_len]));

	copyChar(s, m_string.get(), m_len);
}

String::~String()
{
	
}

char String::charAt(size_t index) const
{
	if (index < 0 || index >= m_len)
		throw new exception("Invalid index");

	return m_string.get()[m_start + index];
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

	newStr.m_string = make_shared<char>(unique_ptr<char[]>(new char[newStr.m_len]));
	copyChar(m_string.get(), newStr.m_string.get(), m_len);
	newStr.m_string.get()[newStr.m_len - 1] = c;

	return newStr;
}

String String::concat(const String& s) const 
{
	return NULL;
}

unique_ptr<char[]> String::toCString() const {
	unique_ptr<char[]> r = unique_ptr<char[]>(new char[m_len + 1]); const char * const tc = m_string.get();
	for (size_t i = 0; i < m_len; ++i) r[i] = tc[m_start + i];
	r[m_len] = '\0';
	return move(r);
}