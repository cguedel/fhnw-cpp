#include "MyString.h"
#include <iostream>

using namespace std;

String::String()
{
	std::cout << "String created" << std::endl;
}

String::String(const String& s)
{
	m_string = s.m_string;
}

String::String(const char* s)
{
	std::cout << "String created" << std::endl;

	while (s[m_len] != '\0') ++m_len;
	m_string = make_shared<char>(unique_ptr<char[]>(new char[m_len]));

	std::cout << "length is " << m_len << std::endl;
}

String::~String()
{
	std::cout << "String destroyed" << std::endl;
}

char String::charAt(size_t index) const
{
	if (index < m_start || index >= m_len)
		throw new exception("Invalid index");

	return 'a';
}