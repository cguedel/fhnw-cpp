#pragma once
#include <iostream>

#include "Expr.h"
#include "Plus.h"
#include "Minus.h"
#include "Multiply.h"
#include "Scalar.h"

using namespace std;

template<typename T> struct Array
{
	T* m_data;
	size_t m_size;

	Array(T* data, size_t size) : m_data(data), m_size(size) { }
	~Array() { }

	T operator[] (size_t i)
	{
		return m_data[i];
	}

	// assignment operator for array (operator) array expressions
	template <typename Left, typename Operator, typename Right> void operator=(Expr<Left, Operator, Right, T> expr) 
	{
		for (size_t i = 0; i < m_size; ++i) 
		{
			m_data[i] = expr[i];
		}
	}

	// address operator to support the ** scalar product operator 
	Array<T>* operator* ()
	{
		return this;
	}

	void print() const
	{
		size_t i = 0;
		cout << "[";

		if (i < m_size) cout << m_data[i++];
		while (i < m_size) cout << ", " << m_data[i++];

		cout << "]" << endl;
	}
};

template <typename Left, typename T> Expr<Left, Plus<T>, Array<T>, T> operator+(Left a, Array<T> b)
{
	return Expr<Left, Plus<T>, Array<T>, T>(a, b);
}

template <typename Left, typename T> Expr<Left, Minus<T>, Array<T>, T> operator-(Left a, Array<T> b)
{
	return Expr<Left, Minus<T>, Array<T>, T>(a, b);
}

template <typename Left, typename T> Expr<Scalar<T>, Multiply<T>, Array<T>, T> operator*(Left a, Array<T> b)
{
	return Expr<Scalar<T>, Multiply<T>, Array<T>, T>(Scalar<T>(a), b);
}

template <typename Left, typename T> T operator*(Left a, Array<T>* b)
{
	T result = 0;
	Expr<Left, Multiply<T>, Array<T>, T> product(a, *b);

	for (size_t i = 0; i < a.m_size; ++i)
	{
		result += product[i];
	}

	return result;
}