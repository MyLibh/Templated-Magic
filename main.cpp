#include <iostream>
#include <algorithm>
#include "Simplify.hpp"

using namespace Simplify;

int main()
{
	std::ios_base::sync_with_stdio(false);

	Node<Number<40>> a;
	Node<Variable<'x', 1>> b;
	Node<WrapNeg, Node<Variable<'x', 2>>> c;
	Node<WrapSin, Node<Variable<'y', 1>>> d;
	Node<WrapAdd, Node<Variable<'y', 1>>, decltype(d)> e;
	
	using X0 = Node<Variable<'x', 0>>;
	constexpr X0 x0;
	constexpr Node<Number<2>> _2;
	using formula = decltype((x0 + Sin(x0)));

	using der = SimplifyResult<formula::template der<'x', 0>>;

	std::cout << formula::dump() << std::endl 
		<< der::dump() << std::endl;
	
	system("pause");
	return 0;
}