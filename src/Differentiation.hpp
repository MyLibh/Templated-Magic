#pragma once

//====================================================================================================================================
//!
//!	\file   Differentiation.hpp
//!
//! \brief	
//!
//====================================================================================================================================

#ifndef __cplusplus
#error
#error  Must use C++ to compile.
#error
#endif /* __cplusplus */

#include "Functions.hpp"

typedef long long llong_t;

//====================================================================================================================================
//!
//! \brief	Essence of number
//!
//====================================================================================================================================

template<llong_t>
struct Number;

//====================================================================================================================================
//!
//! \brief	Essence of variable
//!
//====================================================================================================================================

template<char NAME, int INDEX>
struct Variable;

#pragma region Node

template<typename NodeType, typename... Args>
struct Node;

#pragma region Additional structures for checking the state of Node

//====================================================================================================================================
//!
//! \brief	Checks is number in Node
//!
//====================================================================================================================================

template<typename T>
struct IsNodeNumber : std::false_type { };

template<llong_t N>
struct IsNodeNumber<Node<Number<N>>> : std::true_type { };

//====================================================================================================================================
//!
//! \brief	Checks is binary function in Node
//!
//====================================================================================================================================

template<typename T>
struct IsNodeBinary : std::false_type { };

template<BinaryFunction BF, typename Left, typename Right>
struct IsNodeBinary<Node<Wrap4BF<BF>, Left, Right>> : std::true_type { };

#pragma endregion

#pragma region Node specialization for number

//====================================================================================================================================
//!
//! \brief	Node specialization for number NUMBER
//!
//====================================================================================================================================

template<llong_t N>
struct Node<Number<N>>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for number
	//!
	//====================================================================================================================================

	template<char NAME, int INDEX>
	using der = Node<Number<0>>;

	//====================================================================================================================================
	//!
	//! \brief	Default constructor
	//!
	//====================================================================================================================================

	constexpr Node() = default;

	//====================================================================================================================================
	//!
	//! \brief	 Dumps Node to the string
	//!
	//! \return  String with number N
	//!
	//! \throw   std::bad_alloc
	//!
	//====================================================================================================================================

	static std::string dump() { return std::to_string(N); }

	//====================================================================================================================================
	//!
	//! \brief	 Converts Node to the TeX
	//!
	//! \return  String with number N
	//!
	//! \throw   std::bad_alloc
	//!
	//====================================================================================================================================

	static std::string convert2TeX() { return std::to_string(N); }

	//====================================================================================================================================
	//!
	//! \brief	 Calculates the node
	//!
	//! \return  Number N
	//!
	//====================================================================================================================================

	template<typename Vector>
	static typename Vector::value_type calc(const Vector&) noexcept { return N; }
};

#pragma endregion

#pragma region Node specialization for unary functions

//====================================================================================================================================
//!
//! \brief	Node specialization for unary functions
//!
//====================================================================================================================================

template<UnaryFunction UF, typename... Args>
struct Node<Wrap4UF<UF>, Node<Args...>>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for unary function
	//!
	//====================================================================================================================================

	template<char NAME, int INDEX>
	using der = Node<Wrap4BF<BinaryFunction::MUL>, typename Wrap4UF<UF>::template der<Node<Args...>>, typename Node<Args...>::template der<NAME, INDEX>>;

	//====================================================================================================================================
	//!
	//! \brief	 Dumps Node to the string
	//!
	//! \return  String with unary function(with her argument)
	//!
	//! \throw   std::bad_alloc
	//!
	//====================================================================================================================================

	static std::string dump() { return (GetFunctionName(UF) + "(" + Node<Args...>::dump() + ")"); }

	//====================================================================================================================================
	//!
	//! \brief	 Converts Node to the TeX
	//!
	//! \return  String with unary function(with her argument)
	//!
	//! \throw   std::bad_alloc
	//!
	//====================================================================================================================================

	static std::string convert2TeX() { return ("$" + GetFunctionName(UF) + "(" + Node<Args...>::dump() + ")$");
	}

	//====================================================================================================================================
	//!
	//! \brief	 Calculates the node
	//!
	//! \return  Unary function result
	//!
	//! \throw   std:invalid_argument, std::bad_alloc
	//!
	//====================================================================================================================================

	template<typename Vector>
	static typename Vector::value_type calc(const Vector &rValues)
	{
		const auto child = Node<Args...>::calc(rValues);

		return CalcUnary(Wrap4UF<UF>, child);
	}
};

#pragma endregion

#pragma region Node specialization for binary functions

//====================================================================================================================================
//!
//! \brief	Node specialization for binary functions
//!
//====================================================================================================================================

template<BinaryFunction BF, typename... LeftArgs, typename... RightArgs>
struct Node<Wrap4BF<BF>, Node<LeftArgs...>, Node<RightArgs...>>
{
	using Left = Node<LeftArgs...>;
	using Right = Node<RightArgs...>;

	//====================================================================================================================================
	//!
	//! \brief	Derivative for binary function
	//!
	//====================================================================================================================================

	template<char NAME, int INDEX>
	using der = typename Wrap4BF<BF>::template der<NAME, INDEX, Left, Right>;

	//====================================================================================================================================
	//!
	//! \brief	 Dumps Node to the string
	//!
	//! \return  String with binary function(with her arguments)
	//!
	//! \throw   std::bad_alloc
	//!
	//====================================================================================================================================

	static std::string dump() 
	{
		auto left  = Left::dump();
		auto right = Right::dump();

		if (IsNodeBinary<Node<LeftArgs...>>::value)
			left = "(" + left + ")";

		if (IsNodeBinary<Node<RightArgs...>>::value)
			right = "(" + right + ")";

		const auto &rFuncName = GetFunctionName(BF);

		return (left + " " + rFuncName + " " + right); // (rFuncName + "(" + left + ", " + right + ")"));
	}

	//====================================================================================================================================
	//!
	//! \brief	 Calculates the node
	//!
	//! \return  Binary function result
	//!
	//! \throw   std::overflow_error, std::invalid_argument, std::bad_alloc
	//!
	//====================================================================================================================================

	template<typename Vector>
	static typename Vector::value_type calc(const Vector &rValues)
	{
		const auto left  = Node<LeftArgs...>::calc(rValues);
		const auto right = Node<RightArgs...>::calc(rValues);

		return CalcBinary(Wrap4BF<BF> { }, left, right);
	}
};  

#pragma endregion

#pragma region Node specialization for Variable

//====================================================================================================================================
//!
//! \brief	Node specialization for Varible with name NAME and index INDEX
//!
//====================================================================================================================================

template<char NAME, int INDEX>
struct Node<Variable<NAME, INDEX>>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for variable
	//!
	//====================================================================================================================================

	template<char Name, int Index>
	using der = std::conditional_t<Name == NAME && Index == INDEX, Node<Number<1>>, Node<Number<0>>>;

	//====================================================================================================================================
	//!
	//! \brief	Default constructor
	//!
	//====================================================================================================================================

	constexpr Node() { }

	//====================================================================================================================================
	//!
	//! \brief	 Dumps Node to the string
	//!
	//! \return  String with variable(NAME_INDEX)
	//!
	//! \throw   std::bad_alloc
	//!
	//====================================================================================================================================

	static std::string dump()
	{
		return (std::string{ NAME, '_' } + std::to_string(INDEX));
	}

	//====================================================================================================================================
	//!
	//! \brief	 Calculates the node
	//!
	//! \return  Zero-node
	//!
	//====================================================================================================================================

	template<typename Vector>
	static typename Vector::value_type calc(const Vector &rValues) noexcept { return rValues(Node{ }); }
};

#pragma endregion

#pragma endregion

#pragma region Derivative of variable

template<typename Node, typename Var>
struct VarDerivative;

template<typename Expr, char NAME, int INDEX>
struct VarDerivative<Expr, Node<Variable<NAME, INDEX>>>
{
	using res = typename Expr::template der<NAME, INDEX>;
};

template<typename Node, typename Var>
using VarDerivativeResult = typename VarDerivative<Node, std::decay_t<Var>>::res;

#pragma endregion

template<typename Var, typename Expr, typename Formula, typename Enable = void>
struct ApplyDependency
{
	using res = Formula;
};

template<typename Var, typename Expr, UnaryFunction UF, typename Child>
struct ApplyDependency<Var, Expr, Node<Wrap4UF<UF>, Child>, std::enable_if_t<!std::is_same<Var, Node<Wrap4UF<UF>, Child>>::value>>
{
	using res = Node<Wrap4UF<UF>, typename ApplyDependency<std::decay_t<Var>, std::decay_t<Expr>, Child>::res>;
};

template<typename Var, typename Expr, BinaryFunction BF, typename Left, typename Right>
struct ApplyDependency<Var, Expr, Node<Wrap4BF<BF>, Left, Right>, std::enable_if_t<!std::is_same<Var, Node<Wrap4BF<BF>, Left, Right>>::value>>
{
	using res = Node<Wrap4BF<BF>, 
		typename ApplyDependency<std::decay_t<Var>, std::decay_t<Expr>, Left>::res, 
		typename ApplyDependency<std::decay_t<Var>, std::decay_t<Expr>, Right>::res>;
};

template<typename Var, typename Expr>
struct ApplyDependency<Var, Expr, Var>
{
	using res = Expr;
};

#pragma region Standart derivatives

#pragma region Unary function derivatives

template<>
struct Wrap4UF<UnaryFunction::SIN>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for SIN
	//!
	//====================================================================================================================================

	template<typename Child>
	using der = Node<WrapCos, Child>;
};

template<>
struct Wrap4UF<UnaryFunction::COS>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for COS
	//!
	//====================================================================================================================================

	template<typename Child>
	using der = Node<WrapNeg, Node<WrapSin>, Child>;
};

template<>
struct Wrap4UF<UnaryFunction::LG>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for LG
	//!
	//====================================================================================================================================

	template<typename Child>
	using der = Node<WrapDiv, Node<Number<1>>, Child>;
};

template<>
struct Wrap4UF<UnaryFunction::LN>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for LN
	//!
	//====================================================================================================================================

	template<typename Child>
	using der = Node<WrapDiv, Node<Number<1>>, Child>;
};

template<>
struct Wrap4UF<UnaryFunction::NEG>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for NEG
	//!
	//====================================================================================================================================

	template<typename>
	using der = Node<Number<-1>>;
};

#pragma endregion

#pragma region Binary function derivatives

template<>
struct Wrap4BF<BinaryFunction::ADD>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for ADD
	//!
	//====================================================================================================================================

	template<char NAME, int INDEX, typename Left, typename Right>
	using der = Node<WrapAdd, typename Left::template der<NAME, INDEX>, typename Right::template der<NAME, INDEX>>;
};

template<>
struct Wrap4BF<BinaryFunction::SUB>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for SUB
	//!
	//====================================================================================================================================

	template<char NAME, int INDEX, typename Left, typename Right>
	using der = Node<WrapSub, typename Left::template der<NAME, INDEX>, typename Right::template der<NAME, INDEX>>;
};

template<>
struct Wrap4BF<BinaryFunction::MUL>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for MUL
	//!
	//====================================================================================================================================

	template<char NAME, int INDEX, typename Left, typename Right>
	using der = 
		Node<WrapAdd,
		Node<WrapMul, typename Left::template der<NAME, INDEX>, Right>,
		Node<WrapMul, Left, typename Right::template der<NAME, INDEX>>>;
};

template<>
struct Wrap4BF<BinaryFunction::DIV>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for DIV
	//!
	//====================================================================================================================================

	template<char NAME, int INDEX, typename U, typename V>
	using der = 
		Node<WrapDiv,
		Node<WrapAdd,
		Node<WrapMul, typename U::template der<NAME, INDEX>, V>,
		Node<WrapNeg,
		Node<WrapMul, U, typename V::template der<NAME, INDEX>>>>,
		Node<WrapMul, V, V>>;
};

template<>
struct Wrap4BF<BinaryFunction::POW>
{
	//====================================================================================================================================
	//!
	//! \brief	Derivative for POW
	//!
	//====================================================================================================================================

	template<char NAME, int INDEX, typename U, typename V>
	using der = 
		Node<WrapMul,
		Node<WrapPow, U, V>, typename Node<WrapMul, V,
		Node<WrapLn, U>>::template der<NAME, INDEX>>;
};

#pragma endregion

#pragma endregion