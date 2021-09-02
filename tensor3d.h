#ifndef TENSOR3D_H
#define TENSOR3D_H

#include <vector>
#include <array>
#include <cstddef>

struct Tensor3D
{
    Tensor3D(size_t a, size_t b, size_t c)
        : data(a*b*c),
          shape{a, b, c},
          strides{b*c, c, 1}
    {

    }

    int32_t operator()(size_t k, size_t j, size_t i) const
    {
        return data[strides[0]*k + strides[1]*j + i];
    }

    int32_t &operator()(size_t k, size_t j, size_t i)
    {
        return data[strides[0]*k + strides[1]*j + i];
    }

    std::vector<int32_t> data;
    std::array<size_t, 3> shape;
    std::array<size_t, 3> strides;
};



#endif
