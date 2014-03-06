#include <memory>
#include <iostream>

#pragma once

using namespace std;

class String final {
	shared_ptr<char> m_string;
	size_t m_len;
	size_t m_start;

	void copyChar(const char* source, char* dest, size_t len) const;

public:
	String();
	String(const String& s);
	String(const char* s);
	~String();

	char charAt(size_t index) const;
	int compareTo(const String& s) const;
	String concat(char c) const;
	String concat(const String& s) const;
	size_t length() const;
	String substring(size_t beg, size_t end) const; 
	unique_ptr<char[]> toCString() const;
	
	bool operator==(const String& s) const { return compareTo(s) == 0; }
	
	friend ostream& operator<<(ostream& os, const String& s) {
		const size_t end = s.m_start + s.m_len;
		const char* const sc = s.m_string.get();
		for (size_t i = s.m_start; i < end; i++)
			os << sc[i];
		return os;
	}
	
	static String valueOf(int i);
};