#include <algorithm>
#include "matrix2d.h"


void transpose_blocked(Matrix2D &out, const Matrix2D &in)
{
    constexpr size_t blocking_size_j =  8;
    constexpr size_t blocking_size_i = 32;
    for(size_t j0 = 0; j0 < out.shape[0]; j0 += blocking_size_j)
    {
        size_t jend = std::min(j0+blocking_size_j, out.shape[0]);
        for(size_t i0 = 0; i0 < out.shape[1]; i0 += blocking_size_i)
        {
            size_t iend = std::min(i0+blocking_size_i, out.shape[1]);

            for(size_t j = j0; j < jend; ++j)
            {
                for(size_t i = i0; i < iend; ++i)
                {

                    out.data[j*out.stride + i] = in.data[i*in.stride + j];
                }
            }
        }
    }
}
