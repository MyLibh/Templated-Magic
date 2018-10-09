#pragma once

#ifndef __FIBONACCI_HPP_INCLUDED__
#define __FIBONACCI_HPP_INCLUDED__

template<size_t N>
struct Fibonacci
{
	static constexpr size_t value = Fibonacci<N - 1ull>::value + Fibonacci<N - 2ull>::value;
};

template<> 
struct Fibonacci<1ull>
{ 
	static constexpr size_t value = 1ull;
};

template<> 
struct Fibonacci<0ull> 
{
	static constexpr size_t value = 1ull;
};

#endif /* __FIBONACCI_HPP_INCLUDED__ */