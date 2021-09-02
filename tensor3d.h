#ifndef TENSOR3D_H
#define TENSOR3D_H

#include <vector>
#include <array>
#include <cstddef>
#include <cstdlib>

struct Tensor3D
{
    Tensor3D(size_t a, size_t b, size_t c)
        : data(a*b*c),
          shape{a, b, c},
          strides{b*c, c, 1}
    {
        for(size_t i = 0; i < data.size(); ++i)
        {
            data[i] = std::rand();
        }
    }

    float operator()(size_t k, size_t j, size_t i) const
    {
        return data[strides[0]*k + strides[1]*j + i];
    }

    float &operator()(size_t k, size_t j, size_t i)
    {
        return data[strides[0]*k + strides[1]*j + i];
    }

    std::vector<float> data;
    std::array<size_t, 3> shape;
    std::array<size_t, 3> strides;
};



#endif
