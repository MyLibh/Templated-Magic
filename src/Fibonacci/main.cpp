#include "Fibonacci.hpp"

#include <iostream> // std::cout

int main()
{
	std::cout << Fibonacci<5ull>::value;

	system("pause");
	return 0;
}