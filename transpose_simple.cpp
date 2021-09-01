#include "tensor3d.h"


// transpose the last 2 dimensions of a 3D tensor
void transpose_simple(Tensor3D &out, const Tensor3D &in)
{
    for(size_t k = 0; k < out.shape[0]; ++k)
    {
        for(size_t j = 0; j < out.shape[1]; ++j)
        {
            for(size_t i = 0; i < out.shape[2]; ++i)
            {
                out.data[k*out.strides[0] + j*out.strides[1] + i] = in.data[k*in.strides[0] + i*in.strides[1] + j];
            }
        }

    }
}
