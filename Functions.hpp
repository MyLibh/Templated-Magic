#pragma once

#include <cmath>       // std::sin, std::cos, std::log10, std::log
#include <cassert>     // assert
#include <type_traits> // std::is_arithmetic_v
#include <string>  

#pragma region Unary Function

//====================================================================================================================================
//!
//! \brief	Enumeration of unary functions
//!
//====================================================================================================================================

enum class UnaryFunction
{
	SIN,
	COS,
	LG,
	LN,
	NEG
};

//====================================================================================================================================
//!
//! \brief	 Returns name of the function
//!
//! \param   uf  Unary function
//!
//! \return  Name of unary function or "undefined"
//!
//! \throw   std::bad_alloc
//!
//====================================================================================================================================

inline std::string GetFunctionName(UnaryFunction uf) 
{
	switch (uf)
	{
	case UnaryFunction::SIN:
		return std::string("sin");
	case UnaryFunction::COS:
		return std::string("cos");
	case UnaryFunction::LG:
		return std::string("lg");
	case UnaryFunction::LN:
		return std::string("ln");
	case UnaryFunction::NEG:
		return std::string("-");
	default:
		return std::string("undefined");
	}
}

//====================================================================================================================================
//!
//! \brief	 Calculates unary function
//!
//! \param   uf     Unary function
//! \param   value  Argument of the unary function
//!
//! \return  Result of unary function
//!
//! \throw   std::invalid_argument, std::bad_alloc
//!
//====================================================================================================================================

template<typename T>
T CalcUnary(UnaryFunction uf, T value)
{
	static_assert(std::is_arithmetic_v<T>, "Type T must be arithmetic");

	switch (uf)
	{
	case UnaryFunction::SIN:
		return std::sin(value);
	case UnaryFunction::COS:
		return std::cos(value);
	case UnaryFunction::LG:
		return std::log10(value);
	case UnaryFunction::LN:
		return std::log(value);
	case UnaryFunction::NEG:
		return (-value);
	default:
		throw std::invalid_argument("Undefined unary function\n");
	}
}

#pragma region Wrapper for unary functions

template<UnaryFunction>
struct Wrap4UF;

using WrapSin = Wrap4UF<UnaryFunction::SIN>;
using WrapCos = Wrap4UF<UnaryFunction::COS>;
using WrapLg  = Wrap4UF<UnaryFunction::LG>;
using WrapLn  = Wrap4UF<UnaryFunction::LN>;
using WrapNeg = Wrap4UF<UnaryFunction::NEG>;

#pragma endregion

#pragma endregion

#pragma region Binary functions

//====================================================================================================================================
//!
//! \brief	Enumeration of binary functions
//!
//====================================================================================================================================

enum class BinaryFunction
{
	ADD,
	SUB,
	MUL,
	DIV,
	POW
};

//====================================================================================================================================
//!
//! \brief	 Returns name of the function
//!
//! \param   bf  Binary function
//!
//! \return  Name of binary function or "undefined"
//!
//! \throw   std::bad_alloc
//!
//====================================================================================================================================

inline std::string GetFunctionName(BinaryFunction bf) 
{
	switch (bf)
	{
	case BinaryFunction::ADD:
		return std::string("+");
	case BinaryFunction::SUB:
		return std::string("-");
	case BinaryFunction::MUL:
		return std::string("*");
	case BinaryFunction::DIV:
		return std::string("/");
	case BinaryFunction::POW:
		return std::string("^");
	default:
		return std::string("undefined");
	}
}

//====================================================================================================================================
//!
//! \brief	 Calculates bianry function
//!
//! \param   bf     Binary function
//! \param   left   Left argument
//! \param   right  Right argument
//!
//! \return  Name of binary function or "undefined"
//!
//! \throw   std::invalid_argument, std::bad_alloc
//!
//====================================================================================================================================

template<typename T>
T CalcBinary(BinaryFunction uf, T left, T right)
{
	static_assert(std::is_arithmetic_v<T>, "Type T must be arithmetic");

	switch (uf)
	{
	case BinaryFunction::ADD:
		return (left + right);
	case BinaryFunction::SUB:
		return (left - right);
	case BinaryFunction::DIV:
	{
		if (!right)
			throw std::overflow_error("Division by zero");

		return (left / right); 
	}
	case BinaryFunction::MUL:
		return (left * right);
	case BinaryFunction::POW:
		return std::pow(left, right);
	default:
		throw std::invalid_argument("Undefined unary function\n");
	}
}

#pragma region Wrapper for binary functions

template<BinaryFunction>
struct Wrap4BF;

using WrapAdd = Wrap4BF<BinaryFunction::ADD>;
using WrapSub = Wrap4BF<BinaryFunction::SUB>;
using WrapMul = Wrap4BF<BinaryFunction::MUL>;
using WrapDiv = Wrap4BF<BinaryFunction::DIV>;
using WrapPow = Wrap4BF<BinaryFunction::POW>;

#pragma endregion

#pragma endregion