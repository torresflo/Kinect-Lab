#ifndef CONTAINER_SUBARRAY_HPP
#define CONTAINER_SUBARRAY_HPP

namespace Container
{

template <typename T, unsigned int N>
class Array;

template <typename T, unsigned int N>
class SubArray
{
public:
	SubArray<T, N>(T* elements, const size_t* dimensions, const size_t* subArrayLengths);

	SubArray<T, N - 1> operator[] (unsigned int index);
	const SubArray<T, N - 1> operator[] (unsigned int index) const;

private:
	const size_t* const m_Dimensions;
	const size_t* const m_SubArrayLengths;
	T* m_Elements;

	friend Array<T, N + 1>;
	friend SubArray<T, N + 1>;
};

template <typename T>
class SubArray<T, 1>
{
public:
	SubArray(T* elements, const size_t* dimensions, const size_t* subArrayLengths);

	T& operator[] (unsigned int index);
	const T& operator[] (unsigned int index) const;

private:
	const size_t* const m_Dimensions;
	T* m_Elements;

	friend Array<T, 2>;
	friend SubArray<T, 2>;
};

}

#include <Common\Container\SubArray.inl>

#endif //CONTAINER_SUBARRAY_HPP