#include "MyString.h"
#include <iostream>

using namespace std;

void String::storeDigits(char* store, size_t pos, int number)
{
	if (number >= 10)
		storeDigits(store, pos - 1, number / 10);

	store[--pos] = (number % 10) + '0';
}

String::String() : m_len(0), m_start(0)
{
}

String::String(const String& s) : m_string(s.m_string), m_start(s.m_start), m_len(s.m_len)
{
}

String::String(String&& s) : m_string(s.m_string), m_len(s.m_len), m_start(s.m_start)
{
	s.m_string = nullptr;
	s.m_len = 0;
	s.m_start = 0;
}

String::String(const char* s) : m_len(0), m_start(0)
{
	while (s[m_len] != '\0') ++m_len;

	if (m_len > 0)
	{
		m_string = shared_ptr<char>(unique_ptr<char[]>(new char[m_len]));
		memcpy(m_string.get(), s, m_len);
	}
}

String::~String()
{
}

char String::charAt(size_t index) const
{
	if (index >= m_len)
		throw exception("Invalid index");

	return m_string.get()[m_start + index];
}

int String::compareTo(const String& s) const 
{
	size_t len = (m_len <= s.m_len ? m_len : s.m_len);
	for (size_t i = 0; i < len; i++) {
		if (charAt(i) < s.charAt(i))
			return -1;
		if (charAt(i) > s.charAt(i))
			return 1;
	}

	if (m_len > s.m_len) return 1;
	if (s.m_len > m_len) return -1;

	return 0;
}

size_t String::length() const 
{
	return m_len;
}

String String::substring(size_t beg, size_t end) const 
{
	if (beg >= m_len || end <= beg) return String();

	size_t newend = end > m_len ? m_len : end;

	String newStr = String();
	newStr.m_string = m_string;
	newStr.m_start = m_start + beg;
	newStr.m_len = newend - beg;
	return newStr;
}

String String::concat(char c) const
{
	String newStr = String(*this);
	newStr.m_len++;

	newStr.m_string = shared_ptr<char>(unique_ptr<char[]>(new char[newStr.m_len]));
	memcpy(newStr.m_string.get(), m_string.get(), m_len);
	newStr.m_string.get()[newStr.m_len - 1] = c;

	return newStr;
}

String String::concat(const String& s) const
{
	String newStr = String(*this);
	newStr.m_len += s.length();
	newStr.m_string = shared_ptr<char>(unique_ptr<char[]>(new char[newStr.m_len]));
	memcpy(newStr.m_string.get(), m_string.get(), m_len);
	memcpy(newStr.m_string.get() + m_len, s.m_string.get(), s.m_len);

	return newStr;
}

unique_ptr<char[]> String::toCString() const 
{
	unique_ptr<char[]> r = unique_ptr<char[]>(new char[m_len + 1]);
	const char * const tc = m_string.get();
	memcpy(r.get(), tc + m_start, m_len);
	r[m_len] = '\0';
	return move(r);
}

int String::toInt() const 
{
	// assume we have a maximum number of digits that is equal
	// to the string length, as we can't read from the back of the
	// string.
	int* digits = new int[length()];

	int sign = 1;
	size_t currentDigit = 0;
	bool numberStarted = false;

	for (size_t i = 0; i < m_len; ++i)
	{
		char current = m_string.get()[i];
		if (current == '-')
		{
			if (sign < 0 || numberStarted) throw std::exception("Unexpected double sign");
			sign = -1;
		}
		else if (current == ' ')
		{
			if (numberStarted) break;
		}
		else if (current < '0' || current > '9')
		{
			throw std::exception("Unexpected character in integer");
		} 
		else 
		{
			if (!numberStarted) numberStarted = true;
			digits[currentDigit] = current - '0';
			++currentDigit;
		}
	}

	int integer = 0;
	int power = 1;
	for (int i = currentDigit - 1; i >= 0; --i)
	{
		integer += digits[i] * power;
		power *= 10;
	}

	delete[] digits;
	return integer * sign;
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
		i *= -1;
	}

	storeDigits(str, digits, i);
	String digitStr = String(str);

	delete[] str;

	return digitStr;
}