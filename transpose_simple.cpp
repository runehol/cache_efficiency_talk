#include "matrix2d.h"


void transpose_simple(Matrix2D &out, const Matrix2D &in)
{
    for(size_t j = 0; j < out.shape[0]; ++j)
    {
        for(size_t i = 0; i < out.shape[1]; ++i)
        {
            out.data[j*out.stride + i] = in.data[i*in.stride + j];
        }
    }

}
