#pragma once

#ifndef __FACTORIAL_HPP_INCLUDED__
#define __FACTORIAL_HPP_INCLUDED__

template<size_t N>
struct Factorial 
{
	static constexpr size_t value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0ull> 
{
	static constexpr size_t value = 1ull;
};

#endif /* __FACTORIAL_HPP_INCLUDED__ */