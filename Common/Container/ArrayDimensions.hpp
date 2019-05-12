#ifndef CONTAINER_ARRAYDIMENSIONS_HPP
#define CONTAINER_ARRAYDIMENSIONS_HPP

#include <Common\Math\Scalar.hpp>

namespace Container
{

template<unsigned int N>
using ArrayDimensions = Math::Scalar<size_t, N>;

}

#endif //CONTAINER_ARRAYDIMENSIONS_HPP