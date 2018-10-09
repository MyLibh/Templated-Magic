#pragma once

#ifndef __POWER_HPP_INCLUDED__
#define __POWER_HPP_INCLUDED__

using ll_t = long long;

template <ll_t X, unsigned N>
struct Power
{
	static constexpr ll_t value = X * Power<X, N - 1>::value;
};

template <ll_t X>
struct Power<X, 0u>
{
	static constexpr ll_t value = 1ll;
};

#endif /* __POWER_HPP_INCLUDED__ */