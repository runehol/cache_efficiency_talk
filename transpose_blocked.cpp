#include <algorithm>
#include "tensor3d.h"


// transpose the last 2 dimensions of a 3D tensor
void transpose_blocked(Tensor3D &out, const Tensor3D &in)
{
    constexpr size_t blocking_size_j = 64 / sizeof(in.data[0]);
    constexpr size_t blocking_size_i = 8;
    for(size_t k = 0; k < out.shape[0]; ++k)
    {
        for(size_t j0 = 0; j0 < out.shape[1]; j0 += blocking_size_j)
        {
            for(size_t i0 = 0; i0 < out.shape[2]; i0 += blocking_size_i)
            {
                size_t jend = std::min(j0+blocking_size_j, out.shape[1]);

                for(size_t j = i0; j < jend; ++j)
                {
                    size_t iend = std::min(i0+blocking_size_i, out.shape[2]);
                    for(size_t i = i0; i < iend; ++i)
                    {

                        out.data[k*out.strides[0] + j*out.strides[1] + i] = in.data[k*in.strides[0] + i*in.strides[1] + j];
                    }
                }
            }
        }

    }
}
