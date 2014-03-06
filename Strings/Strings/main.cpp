#include "MyString.h"
#include <iostream>

using namespace std;

int main() {
	String s0;
	String s1("");
	String s2("abcdef");

	/*String s00(s0);
	String s11(s1);
	String s22(s2);*/

	//String s3 = s2.substring(1, 2);
	//std::cout << s2.length() << std::endl;
	//std::cout << s3.length() << std::endl;

	{
		auto up = s2.toCString();
		std::cout << up.get() << std::endl;

		std::cout << s2 << std::endl;

		std::cout << s2.substring(0, 3) << std::endl;

		std::cout << s2.concat('a') << std::endl;
	}

	std::cin.get();
}