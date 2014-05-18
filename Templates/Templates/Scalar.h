#pragma once
template<typename T> struct Scalar
{
	T m_value;

	Scalar(T value) : m_value(value) { }

	T operator[](size_t i)
	{
		return m_value;
	}
};