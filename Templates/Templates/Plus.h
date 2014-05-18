#pragma once

template <typename T> struct Plus
{
	static T apply(T left, T right)
	{
		return left + right;
	}
};