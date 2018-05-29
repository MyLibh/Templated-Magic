#include <iostream>
#include "Simplify.hpp"

using namespace Simplification;

using X0 = Node<Variable<'x', 0>>;
constexpr X0 x0;
constexpr Node<Number<2>> _2;

int main()
{
	std::ios_base::sync_with_stdio(false);

	using formula = decltype((x0 + Sin(x0)));

	using der = Simplify<formula>;

	std::cout << formula::dump() << std::endl 
		<< der::res::template der<'x', 0>::dump() << std::endl;
	
	system("pause");
	return 0;
}