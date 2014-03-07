#include "MyString.h"
#include <iostream>

using namespace std;

int main() {
	String s0;
	String s1("");
	String s2("abc");
	String s3(s2);
	String s00(s0);
	String s11(s1);
	String s22(s2);

	std::cout << s2 << std::endl;

	std::cout << s2.compareTo("abcde") << std::endl;
	std::cout << s2.compareTo("abcdef") << std::endl;
	std::cout << s2.compareTo("abcdefg") << std::endl;
	std::cout << s2.concat('z') << std::endl;

	std::cout << s2.concat(String("xyz")) << std::endl;

	std::cout << String::valueOf(-1238929) << std::endl;

	std::cout << s3.compareTo(s2) << std::endl;
	std::cout << (s3 == s2) << std::endl;

	std::cout << (s2 + s3) << std::endl;

	std::cin.get();
}