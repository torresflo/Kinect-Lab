#ifndef MATH_VECTOR_HPP
#define MATH_VECTOR_HPP

#include <type_traits>
#include <array>
#include <cmath>

namespace Math
{

template <typename T, unsigned int N>
class Vector
{
public:
    Vector(); //Null vector, all values to 0
    Vector(const Vector<T, N>& vector);

    template <typename U>
    Vector(const Vector<U, N>& vector);

    template <unsigned int M>
    Vector(const Vector<T, M>& vector);

    template <typename U, unsigned int M>
    Vector(const Vector<U, M>& vector);

    template<typename ... Values>
    Vector(Values... values);

    T& operator[](::std::size_t index);
    const T& operator[](::std::size_t index) const;

    template <unsigned int M = N>
	typename ::std::enable_if<M >= 1, T>::type x() const;

    template <unsigned int M = N>
	typename ::std::enable_if<M >= 1, void>::type setX(T x);

    template <unsigned int M = N>
	typename ::std::enable_if<M >= 2, T>::type y() const;

    template <unsigned int M = N>
	typename ::std::enable_if<M >= 2, void>::type setY(T y);

    template <unsigned int M = N>
	typename ::std::enable_if<M >= 3, T>::type z() const;

    template <unsigned int M = N>
	typename ::std::enable_if<M >= 3, void>::type setZ(T z);

    template <unsigned int M = N>
	typename ::std::enable_if<M >= 4, T>::type w() const;

    template <unsigned int M = N>
	typename ::std::enable_if<M >= 4, void>::type setW(T w);

    template <typename U = T, unsigned int M = N>
	typename ::std::enable_if<M == 2 && std::is_floating_point<U>::value, U>::type getLengthSqr() const;

    template <typename U = T, unsigned int M = N>
	typename ::std::enable_if<M == 2 && std::is_floating_point<U>::value, U>::type getLength() const;

    template <typename U = T, unsigned int M = N>
	typename ::std::enable_if<M == 2 && std::is_floating_point<U>::value, void>::type rotate(U radians);

    template <typename U = T, unsigned int M = N>
	static typename ::std::enable_if<M >= 2, Vector<U, M>>::type getI();

    template <typename U = T, unsigned int M = N>
	static typename ::std::enable_if<M >= 2, Vector<U, M>>::type getJ();

    template <typename U = T, unsigned int M = N>
	static typename ::std::enable_if<M >= 3, Vector<U, M>>::type getK();

    template <typename U = T, unsigned int M = N>
	static typename ::std::enable_if<M == 2, Vector<U, M>>::type getPerpendicular(const Vector<U, M>& vector);

    template <typename U = T, unsigned int M = N>
	static typename ::std::enable_if<M == 2, U>::type dot(const Vector<U, M>& a, const Vector<U, M>& b);

    template <typename U = T, unsigned int M = N>
	static typename ::std::enable_if<M == 2, U>::type cross(const Vector<U, M>& a, const Vector<U, M>& b);

    template <typename U = T, unsigned int M = N>
	static typename ::std::enable_if<M == 2, Vector<U, M>>::type cross(const Vector<U, M>& a, U scalar);

    template <typename U = T, unsigned int M = N>
	static typename ::std::enable_if<M == 2, Vector<U, M>>::type cross(U scalar, const Vector<U, M>& a);

    template <typename U = T, unsigned int M = N>
	static typename ::std::enable_if<M == 2, bool>::type overlap(const Vector<U, M>& a, const Vector<U, M>& b);

    template <typename U = T, unsigned int M = N>
	static typename ::std::enable_if<M == 2, double>::type distance(const Vector<U, M>& p1, const Vector<U, M>& p2);

    template <typename U = T, unsigned int M = N>
	static typename ::std::enable_if<M == 2, Vector<U, M>>::type getNormalized(const Vector<U, M>& vector);

public:
    std::array<T, N> m_values;
};

template <typename T, unsigned int N>
Vector<T, N> operator -(const Vector<T, N>& left);

template <typename T, unsigned int N>
Vector<T, N>& operator +=(Vector<T, N>& left, const Vector<T, N>& right);

template <typename T, unsigned int N>
Vector<T, N>& operator -=(Vector<T, N>& left, const Vector<T, N>& right);

template <typename T, unsigned int N>
Vector<T, N> operator +(const Vector<T, N>& left, const Vector<T, N>& right);

template <typename T, unsigned int N>
Vector<T, N> operator -(const Vector<T, N>& left, const Vector<T, N>& right);

template <typename T, unsigned int N>
Vector<T, N> operator *(const Vector<T, N>& left, T right);

template <typename T, unsigned int N>
Vector<T, N> operator *(T left, const Vector<T, N>& right);

template <typename T, unsigned int N>
Vector<T, N>& operator *=(Vector<T, N>& left, T right);

template <typename T, unsigned int N>
Vector<T, N> operator /(const Vector<T, N>& left, T right);

template <typename T, unsigned int N>
Vector<T, N>& operator /=(Vector<T, N>& left, T right);

template <typename T, unsigned int N>
bool operator ==(const Vector<T, N>& left, const Vector<T, N>& right);

template <typename T, unsigned int N>
bool operator !=(const Vector<T, N>& left, const Vector<T, N>& right);

typedef Vector<int, 2> Vector2i;
typedef Vector<float, 2> Vector2f;
typedef Vector<int, 3> Vector3i;
typedef Vector<float, 3> Vector3f;
typedef Vector<int, 4> Vector4i;
typedef Vector<float, 4> Vector4f;

} //namespace Math

#include <Common\Math\Vector.inl>

#endif //MATH_VECTOR_HPP