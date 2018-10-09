#include "Factorial.hpp" 

#include <iostream> // std::cout

int main() 
{
	std::cout << Factorial<5ull>::value;

	system("pause");
	return 0;
}