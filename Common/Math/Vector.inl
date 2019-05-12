#include <cstring>

namespace Math
{

template<typename T, unsigned int N>
inline Vector<T, N>::Vector()
{
    m_values.fill(0);
}

template<typename T, unsigned int N>
inline Vector<T, N>::Vector(const Vector <T, N>& vector)
{
    m_values = vector.m_values;
}

template<typename T, unsigned int N>
template<typename U>
inline Vector<T, N>::Vector(const Vector <U, N>& vector)
{
    ::std::copy(vector.m_values.begin(), vector.m_values.end(), m_values.begin());
}

template<typename T, unsigned int N>
template<unsigned int M>
inline Vector<T, N>::Vector(const Vector <T, M>& vector)
{
    for (int i = 0; i < M, i < N; ++i)
        m_values[i] = vector.m_values[i];
    for (int j = N; j < M; ++j)
        m_values[j] = 0;
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline Vector<T, N>::Vector(const Vector <U, M>& vector)
{
    for (int i = 0; i < M, i < N; ++i)
        m_values[i] = static_cast<T>(vector.m_values[i]);
    for (int j = N; j < M; ++j)
        m_values[j] = 0;
};

template<typename T, unsigned int N>
template<typename ... Values>
Vector<T, N>::Vector(Values... values)
        :m_values{static_cast<T>(values)...}
{
    static_assert(sizeof...(Values) == N, "Invalid number of constructor arguments");
}

template<typename T, unsigned int N>
template<unsigned int M>
inline typename::std::enable_if<M >= 1, T>::type Vector<T, N>::x() const { return m_values[0]; }

template<typename T, unsigned int N>
template<unsigned int M>
inline typename::std::enable_if<M >= 1, void>::type Vector<T, N>::setX(T x) { m_values[0] = x; }

template<typename T, unsigned int N>
template<unsigned int M>
inline typename::std::enable_if<M >= 2, T>::type Vector<T, N>::y() const { return m_values[1]; }

template<typename T, unsigned int N>
template<unsigned int M>
inline typename::std::enable_if<M >= 2, void>::type Vector<T, N>::setY(T y) { m_values[1] = y; }

template<typename T, unsigned int N>
template<unsigned int M>
inline typename::std::enable_if<M >= 3, T>::type Vector<T, N>::z() const { return m_values[2]; }

template<typename T, unsigned int N>
template<unsigned int M>
inline typename::std::enable_if<M >= 3, void>::type Vector<T, N>::setZ(T z) { m_values[2] = z; }

template<typename T, unsigned int N>
template<unsigned int M>
inline typename::std::enable_if<M >= 4, T>::type Vector<T, N>::w() const { return m_values[3]; }

template<typename T, unsigned int N>
template<unsigned int M>
inline typename::std::enable_if<M >= 4, void>::type Vector<T, N>::setW(T w) { m_values[3] = w; }

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M == 2 && std::is_floating_point<U>::value, U>::type Vector<T, N>::getLengthSqr() const
{
	return x()*x() + y()*y();
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M == 2 && std::is_floating_point<U>::value, U>::type Vector<T, N>::getLength() const
{
	return sqrt(getLengthSqr());
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M == 2 && std::is_floating_point<U>::value, void>::type Vector<T, N>::rotate(U radians)
{
	U cos = ::std::cos(radians);
	U sin = ::std::sin(radians);

	U x = m_values[0] * cos - m_values[1] * sin;
	U y = m_values[0] * sin + m_values[1] * cos;

	m_values[0] = x;
	m_values[1] = y;
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M >= 2, Vector<U, M>>::type Vector<T, N>::getI()
{
	Vector<U, M> i;
	i.setX(1);
	return i;
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M >= 2, Vector<U, M>>::type Vector<T, N>::getJ()
{
	Vector<U, M> j;
	j.setY(1);
	return j;
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M >= 3, Vector<U, M>>::type Vector<T, N>::getK()
{
	Vector<U, M> k;
	k.setZ(1);
	return k;
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M == 2, Vector<U, M>>::type Vector<T, N>::getPerpendicular(const Vector<U, M>& vector)
{
	return Vector<U, M>(-vector.y(), vector.x());
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M == 2, U>::type Vector<T, N>::dot(const Vector<U, M>& a, const Vector<U, M>& b)
{
	return (a.x() * b.x()) + (a.y() * b.y());
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M == 2, U>::type Vector<T, N>::cross(const Vector<U, M>& a, const Vector<U, M>& b)
{
	return a.x() * b.y() - a.y() * b.x();
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M == 2, Vector<U, M>>::type Vector<T, N>::cross(const Vector<U, M>& a, U scalar)
{
	return Vector<U, M>(scalar * a.y(), -scalar * a.x());
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M == 2, Vector<U, M>>::type Vector<T, N>::cross(U scalar, const Vector<U, M>& a)
{
	return Vector<U, M>(-scalar * a.y(), scalar * a.x());
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M == 2, bool>::type Vector<T, N>::overlap(const Vector<U, M>& a, const Vector<U, M>& b)
{
	if ((a.x() <= b.x()) && (b.x() <= a.y()))
		return true;
	if ((b.x() <= a.x()) && (a.x() <= b.y()))
		return true;
	return false;
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M == 2, double>::type Vector<T, N>::distance(const Vector<U, M>& p1, const Vector<U, M>& p2)
{
	return sqrt(((p1.x() - p2.x()) * (p1.x() - p2.x())) + ((p1.y() - p2.y()) * (p1.y() - p2.y())));
}

template<typename T, unsigned int N>
template<typename U, unsigned int M>
inline typename::std::enable_if<M == 2, Vector<U, M>>::type Vector<T, N>::getNormalized(const Vector<U, M>& vector)
{
	U lenght = vector.getLength();
	return Vector<U, M>(vector.x() / lenght, vector.y() / lenght);
}

template<typename T, unsigned int N>
T& Vector<T, N>::operator[](::std::size_t index)
{
    return m_values[index];
}

template<typename T, unsigned int N>
const T& Vector<T, N>::operator[](::std::size_t index) const
{
    return m_values[index];
}

template<typename T, unsigned int N>
inline Vector<T, N> operator-(const Vector<T, N>& left)
{
    Vector<T, N> vector;
    for (int i = 0; i < N; ++i)
        vector.m_values[i] = -left.m_values[i];
    return vector;
}

template<typename T, unsigned int N>
inline Vector<T, N>& operator+=(Vector<T, N>& left, const Vector<T, N>& right)
{
    for (int i = 0; i < N; ++i)
        left.m_values[i] += right.m_values[i];
    return left;
}

template<typename T, unsigned int N>
inline Vector<T, N>& operator-=(Vector<T, N>& left, const Vector<T, N>& right)
{
    for (int i = 0; i < N; ++i)
        left.m_values[i] -= right.m_values[i];
    return left;
}

template<typename T, unsigned int N>
inline Vector<T, N> operator+(const Vector<T, N>& left, const Vector<T, N>& right)
{
    Vector<T, N> vector;
    for (int i = 0; i < N; ++i)
        vector.m_values[i] = left.m_values[i] + right.m_values[i];
    return vector;
}

template<typename T, unsigned int N>
inline Vector<T, N> operator-(const Vector<T, N>& left, const Vector<T, N>& right)
{
    Vector<T, N> vector;
    for (int i = 0; i < N; ++i)
        vector.m_values[i] = left.m_values[i] - right.m_values[i];
    return vector;
}

template<typename T, unsigned int N>
inline Vector<T, N> operator*(const Vector<T, N>& left, T right)
{
    Vector<T, N> vector;
    for (int i = 0; i < N; ++i)
        vector.m_values[i] = left.m_values[i] * right;
    return vector;
}

template<typename T, unsigned int N>
inline Vector<T, N> operator*(T left, const Vector<T, N>& right)
{
    Vector<T, N> vector;
    for (int i = 0; i < N; ++i)
        vector.m_values[i] = right.m_values[i] * left;
    return vector;
}

template<typename T, unsigned int N>
inline Vector<T, N>& operator*=(Vector<T, N>& left, T right)
{
    for (int i = 0; i < N; ++i)
        left.m_values[i] *= right;
    return left;
}

template<typename T, unsigned int N>
inline Vector<T, N> operator/(const Vector<T, N>& left, T right)
{
    Vector<T, N> vector;
    for (int i = 0; i < N; ++i)
        vector.m_values[i] = left.m_values[i] / right;
    return vector;
}

template<typename T, unsigned int N>
inline Vector<T, N>& operator/=(Vector<T, N>& left, T right)
{
    for (int i = 0; i < N; ++i)
        left.m_values[i] /= right;
    return left;
}

template<typename T, unsigned int N>
inline bool operator==(const Vector<T, N>& left, const Vector<T, N>& right)
{
    for (int i = 0; i < N; ++i)
        if (left.m_values[i] != right.m_values[i])
            return false;
    return true;
}

template<typename T, unsigned int N>
inline bool operator!=(const Vector<T, N>& left, const Vector<T, N>& right)
{
    return !(left == right);
}

} // namespace Math
