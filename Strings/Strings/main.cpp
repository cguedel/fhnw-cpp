#include "MyString.h"
#include <iostream>

using namespace std;

int main() {
	String s0;
	String s1("");
	String s2("abc");
	
	/*String s00(s0);
	String s11(s1);
	String s22(s2);*/

	std::cout << s2.charAt(0) << std::endl;
	std::cout << s2.charAt(1) << std::endl;
	std::cout << s2.charAt(2) << std::endl;
	std::cout << s2.charAt(0) << std::endl;

	std::cin.get();
}