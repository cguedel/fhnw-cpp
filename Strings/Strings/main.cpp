#include "MyString.h"
#include <iostream>

using namespace std;

int main() {

	std::cout << "Move constructor tests" << std::endl;

	String integer1 = String("123");
	String integer2 = String("-123");
	cout << integer1.toInt() << endl;
	cout << integer2.toInt() << endl;

	std::cin.get();
}