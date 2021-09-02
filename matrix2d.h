#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <vector>
#include <array>
#include <cstddef>
#include <cstdlib>

struct Matrix2D
{
    Matrix2D(size_t m, size_t n)
        : data(m*n),
          shape{m, n},
          stride(n)
    {
        for(size_t i = 0; i < data.size(); ++i)
        {
            data[i] = std::rand();
        }
    }

    float operator()(size_t j, size_t i) const
    {
        return data[stride*j + i];
    }

    float &operator()(size_t j, size_t i)
    {
        return data[stride*j + i];
    }

    std::vector<float> data;
    std::array<size_t, 2> shape;
    size_t stride;
};



#endif
