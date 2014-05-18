#include "Array.h"
#include <iostream>

int main()
{
	double a_data[]{ 5.0, 3.7, 1.8, 9.1};
	double b_data[]{ 37.1, 71.8, 171.0, 56.3 };
	double r;

	Array<double> a(a_data, 4);
	Array<double> b(b_data, 4);

	r = a**b;

	a.print();
	b.print();
	std::cout << r << std::endl;
	std::cin.get();
}