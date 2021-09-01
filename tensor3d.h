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

    std::vector<int16_t> data;
    std::array<size_t, 3> shape;
    std::array<size_t, 3> strides;
};



#endif
