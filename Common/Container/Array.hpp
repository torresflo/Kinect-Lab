#ifndef CONTAINER_ARRAY_HPP
#define CONTAINER_ARRAY_HPP

#include <array>

#include <Common\Container\ArrayDimensions.hpp>
#include <Common\Container\SubArray.hpp>

namespace Container
{

template <typename T, unsigned int N>
class Array
{
public:
	Array<T, N>();
	Array<T, N>(const ArrayDimensions<N> dimensions);
	Array<T, N>(const ArrayDimensions<N> dimensions, T initValue);
	Array<T, N>(const Array<T, N>& copy);
	~Array<T, N>();

	void resize(const ArrayDimensions<N>& dimensions, T initValue);
	void resize(const ArrayDimensions<N>& dimensions);

	SubArray<T, N - 1> operator[] (unsigned int index);
	const SubArray<T, N - 1> operator[] (unsigned int index) const;

	T* getData() const;

	size_t getNbOfElements() const;
	unsigned int getNbOfDimensions() const;
	size_t getDimension(unsigned int index) const;

private:
	T* m_Elements; //Pointer to all the actual elements
	size_t m_NbElements; //Total number of array elements
	size_t m_Dimensions[N]; //Sizes of the N dimensions
	size_t m_SubArrayLengths[N]; //Dimensions of subarrays

	void allocateElements(size_t nbElements);
	void initElements(T initValue);
	void desallocateElements();
};

template <typename T>
class Array<T, 0>
{
};

template <typename T>
class Array<T, 1>
{
};

template <typename T>
using Array2D = Array<T, 2>;

template <typename T>
using Array3D = Array<T, 3>;

template <typename T>
using Array4D = Array<T, 4>;

}

#include <Common\Container\Array.inl>

#endif //CONTAINER_ARRAY_HPP