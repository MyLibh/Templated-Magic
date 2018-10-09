#pragma once

#ifndef __LOGARITHM_HPP_INCLUDED__
#define __LOGARITHM_HPP_INCLUDED__

template <unsigned x>
struct Log2 
{ 
	static constexpr int value = 1 + Log2<x / 2>::value;
};

template <> 
struct Log2<1u> 
{ 
	static constexpr int value = 1;
};

#endif /* __LOGARITHM_HPP_INCLUDED__ */