#pragma once

#include "Differentiation.hpp"

namespace Simplification
{

#pragma region Simplification

	template<typename T, typename Enable = void>
	struct Simplify
	{
		using res = T;
	};

	template<typename T>
	using SimplifyPrime = Simplify<T>;

	//====================================================================================================================================
	//!
	//! \brief	Simplification not to write ::res
	//!
	//====================================================================================================================================

	template<typename T>
	using SimplifyResult = typename Simplify<T>::res;

	template<typename Other>
	using NotANum = std::enable_if_t<!IsNodeNumber<Other>::value>;

	//====================================================================================================================================
	//!
	//! \brief	Simplification 'x * 1' to 'x'
	//!
	//====================================================================================================================================

	template<typename Other>
	struct Simplify<Node<Wrap4BF<BinaryFunction::MUL>, Other, Node<Number<1>>>, NotANum<Other>>
	{
		using res = SimplifyResult<Other>;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification '1 * x' to 'x'
	//!
	//====================================================================================================================================

	template<typename Other>
	struct Simplify<Node<Wrap4BF<BinaryFunction::MUL>, Node<Number<1>>, Other>, NotANum<Other>>
	{
		using res = SimplifyResult<Other>;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification 'x * 0' to '0'
	//!
	//====================================================================================================================================

	template<typename Other>
	struct Simplify<Node<Wrap4BF<BinaryFunction::MUL>, Other, Node<Number<0>>>, NotANum<Other>>
	{
		using Result_t = Node<Number<0>>;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification '0 * x' to '0'
	//!
	//====================================================================================================================================

	template<typename Other>
	struct Simplify<Node<Wrap4BF<BinaryFunction::MUL>, Node<Number<0>>, Other>, NotANum<Other>>
	{
		using res = Node<Number<0>>;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification 'const * const' to 'const'
	//!
	//====================================================================================================================================

	template<llong_t N, llong_t M>
	struct Simplify<Node<Wrap4BF<BinaryFunction::MUL>, Node<Number<N>>, Node<Number<M>>>>
	{
		using res = Node<Number<N * M>>;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification 'x * (-1)' to '(-x)'
	//!
	//====================================================================================================================================

	template<typename Other>
	struct Simplify<Node<Wrap4BF<BinaryFunction::MUL>, Other, Node<Number<-1>>>, NotANum<Other>>
	{
		using res = Node<WrapNeg, Other>;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification '(-1) * x' to '(-x)'
	//!
	//====================================================================================================================================

	template<typename Other>
	struct Simplify<Node<Wrap4BF<BinaryFunction::MUL>, Node<Number<-1>>, Other>, NotANum<Other>>
	{
		using res = Node<WrapNeg, Other>;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification '0 / x' to '0'
	//!
	//====================================================================================================================================

	template<typename Other>
	struct Simplify<Node<WrapDiv, Node<Number<0>>, Other>>
	{
		using res = Node<Number<0>>;
	};

	/*
	//====================================================================================================================================
	//!
	//! \brief	Simplification 'const + const' to 'const'
	//!
	//====================================================================================================================================

	template<llong_t N, llong_t M>
	struct Simplify<Node<Add, Node<Number<N>>, Node<Number<M>>>>
	{
		using res = Node<Number<N + M>>;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification 'const / const' to 'const'
	//!
	//====================================================================================================================================

	template<llong_t N, llong_t M>
	struct Simplify<Node<Div, Node<Number<N>>, Node<Number<M>>>>
	{
		static_assert(!M, "M must not be zero");

		using res = Node<Number<N / M>>;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification 'const - const' to 'const'
	//!
	//====================================================================================================================================

	template<llong_t N, llong_t M>
	struct Simplify<Node<Sub, Node<Number<N>>, Node<Number<M>>>>
	{
		using res = Node<Number<N - M>>;
	};
	*/

	//====================================================================================================================================
	//!
	//! \brief	Simplification 'x + 0' to 'x'
	//!
	//====================================================================================================================================

	template<typename Other>
	struct Simplify<Node<WrapAdd, Other, Node<Number<0>>>>
	{
		using res = Other;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification '0 + x' to 'x'
	//!
	//====================================================================================================================================

	template<typename Other>
	struct Simplify<Node<WrapAdd, Node<Number<0>>, Other>>
	{
		using res = Other;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification '(-const)' to '-const'
	//!
	//====================================================================================================================================

	template<llong_t N>
	struct Simplify<Node<WrapNeg, Node<Number<N>>>>
	{
		using res = Node<Number<-N>>;
	};

	//====================================================================================================================================
	//!
	//! \brief	Simplification of unary function argument
	//!
	//====================================================================================================================================

	template<UnaryFunction UF, typename Child>
	struct Simplify<Node<Wrap4UF<UF>, Child>>
	{
		using res = Node<Wrap4UF<UF>, SimplifyResult<Child>>;
	};

#pragma endregion
	
#pragma region Operators

	template<llong_t N>
	Node<Number<N>> Num{ };

	template<char NAME, int INDEX = 0>
	constexpr Node<Variable<NAME, INDEX>> Var{ };

	template<typename T1, typename T2>
	Node<WrapAdd, std::decay_t<T1>, std::decay_t<T2>> operator+(T1, T2);

	template<typename T1, typename T2>
	Node<WrapMul, std::decay_t<T1>, std::decay_t<T2>> operator*(T1, T2);

	template<typename T1, typename T2>
	Node<WrapDiv, std::decay_t<T1>, std::decay_t<T2>> operator/(T1, T2);

	template<typename T1, typename T2>
	Node<WrapAdd, std::decay_t<T1>, Node<WrapNeg, std::decay_t<T2>>> operator-(T1, T2);

	template<typename T>
	Node<WrapNeg, std::decay_t<T>> operator-(T);

	template<typename T>
	Node<WrapSin, std::decay_t<T>> Sin(T);

	template<typename T>
	Node<WrapCos, std::decay_t<T>> Cos(T);

	template<typename T>
	Node<WrapLn, std::decay_t<T>> Ln(T);

	template<typename T>
	Node<WrapPow, std::decay_t<T>, Node<WrapDiv, Node<Number<1>>, Node<Number<2>>>> Sqrt(T);

	template<typename T>
	Node<WrapPow, std::decay_t<T>, std::decay_t<T>> operator^ (T, Node<Number<2>>);

#pragma endregion

} // namespace Simplification

