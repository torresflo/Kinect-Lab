#include <cassert>

namespace Container
{

template<typename T, unsigned int N>
inline SubArray<T, N>::SubArray(T * elements, const size_t * dimensions, const size_t * subArrayLengths)
	:m_Elements(elements), m_Dimensions(dimensions), m_SubArrayLengths(subArrayLengths)
{}

template<typename T, unsigned int N>
inline SubArray<T, N - 1> SubArray<T, N>::operator[](unsigned int index)
{
	assert(index < m_Dimensions[0]);
	return SubArray<T, N - 1>(&m_Elements[index + m_SubArrayLengths[0]], m_Dimensions + 1, m_SubArrayLengths +1);
}

template<typename T, unsigned int N>
inline const SubArray<T, N - 1> SubArray<T, N>::operator[](unsigned int index) const
{
	assert(index < m_Dimensions[0]);
	return SubArray<T, N - 1>(&m_Elements[index + m_SubArrayLengths[0]], m_Dimensions + 1, m_SubArrayLengths + 1);
}

template<typename T>
inline SubArray<T, 1>::SubArray(T * elements, const size_t * dimensions, const size_t * subArrayLengths)
	:m_Elements(elements), m_Dimensions(dimensions)
{}

template<typename T>
inline T & SubArray<T, 1>::operator[](unsigned int index)
{
	assert(index < m_Dimensions[0]);
	return m_Elements[index];
}

template<typename T>
inline const T & SubArray<T, 1>::operator[](unsigned int index) const
{
	assert(index < m_Dimensions[0]);
	return m_Elements[index];
}

}