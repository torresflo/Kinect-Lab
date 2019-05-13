#include <cassert>
#include <cstring>

#include <Common\Utils\MemoryHelper.hpp>

namespace Container
{
template<typename T, unsigned int N>
inline Array<T, N>::Array()
{
	m_NbElements = 0;
	m_Elements = nullptr;

	for (unsigned int i = 0; i < N; ++i)
	{
		m_Dimensions[i] = 0;
		m_SubArrayLengths[i] = 0;
	}
}

template<typename T, unsigned int N>
inline Array<T, N>::Array(const ArrayDimensions<N> dimensions)
{
	resize(dimensions);
}

template<typename T, unsigned int N>
inline Array<T, N>::Array(const ArrayDimensions<N> dimensions, T initValue)
{
	resize(dimensions, initValue);
}

template<typename T, unsigned int N>
inline Array<T, N>::Array(const Array<T, N>& copy)
{
	desallocateElements();
	m_NbElements = copy.m_NbElements;
	std::memcpy(m_Dimensions, copy.m_Dimensions, N * sizeof(size_t));
	std::memcpy(m_SubArrayLengths, copy.m_SubArrayLengths, N * sizeof(size_t));
	allocateElements(m_NbElements);
	std::memcpy(m_Elements, copy.m_Elements, m_NbElements * sizeof(T));
}

template<typename T, unsigned int N>
inline Array<T, N>::~Array()
{
	desallocateElements();
}

template<typename T, unsigned int N>
inline void Array<T, N>::resize(const ArrayDimensions<N>& dimensions, T initValue)
{
	resize(dimensions);
	initElements(initValue);
}

template<typename T, unsigned int N>
inline void Array<T, N>::resize(const ArrayDimensions<N>& dimensions)
{
	desallocateElements();

	//Calculate all the information you need to use the array
	m_NbElements = 1;
	for (unsigned int i = 0; i < N; ++i)
	{
		assert(dimensions[i] != 0);

		m_NbElements *= dimensions[i];
		m_Dimensions[i] = dimensions[i];
		m_SubArrayLengths[i] = 1;
		for (unsigned int k = N - 1; k > i; k--)
		{
			m_SubArrayLengths[i] *= dimensions[k];
		}
	}

	allocateElements(m_NbElements);
}

template<typename T, unsigned int N>
inline SubArray<T, N - 1> Array<T, N>::operator[](unsigned int index)
{
	assert(index < m_Dimensions[0]);
	return SubArray<T, N - 1>(&m_Elements[index * m_SubArrayLengths[0]], m_Dimensions+1, m_SubArrayLengths+1);
}

template<typename T, unsigned int N>
inline const SubArray<T, N - 1> Array<T, N>::operator[](unsigned int index) const
{
	assert(index < m_Dimensions[0]);
	return SubArray<T, N - 1>(&m_Elements[index * m_SubArrayLengths[0]], m_Dimensions + 1, m_SubArrayLengths + 1);
}

template<typename T, unsigned int N>
inline T * Array<T, N>::getData() const
{
	return m_Elements;
}

template<typename T, unsigned int N>
inline size_t Array<T, N>::getNbOfElements() const
{
	return m_NbElements;
}

template<typename T, unsigned int N>
inline unsigned int Array<T, N>::getNbOfDimensions() const
{
	return N;
}

template<typename T, unsigned int N>
inline size_t Array<T, N>::getDimension(unsigned int index) const
{
	assert(index < N);
	return m_Dimensions[index];
}

template<typename T, unsigned int N>
inline void Array<T, N>::allocateElements(size_t nbElements)
{
	m_Elements = new T[m_NbElements];
}

template<typename T, unsigned int N>
inline void Array<T, N>::initElements(T initValue)
{
	for (unsigned int i = 0; i < m_NbElements; ++i)
	{
		m_Elements[i] = initValue;
	}
}

template<typename T, unsigned int N>
inline void Array<T, N>::desallocateElements()
{
	SafeDeleteArray(m_Elements);
	m_NbElements = 0;

	for (unsigned int i = 0; i < N; ++i)
	{
		m_Dimensions[i] = 0;
		m_SubArrayLengths[i] = 0;
	}
}

}