#pragma once

// expression with two vectors (arrays) on each side
template <typename Left, typename Operator, typename Right, typename T> struct Expr
{
	Left m_left;
	Right m_right;

	Expr(Left l, Right r) : m_left(l), m_right(r) { }
	
	T operator[] (size_t i)
	{ 
		return Operator::apply(m_left[i], m_right[i]);
	}
};