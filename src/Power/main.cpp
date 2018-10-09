#include "Power.hpp"

#include <iostream> // std::cout

int main()
{
	std::cout << Power<5ll, 3u>::value;

	system("pause");
	return 0;
}