#pragma once

template <typename T> struct Multiply
{
	static T apply(T left, T right)
	{
		return left * right;
	}
};