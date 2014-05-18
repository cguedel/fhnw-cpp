#pragma once

template <typename T> struct Minus
{
	static T apply(T left, T right)
	{
		return left - right;
	}
};