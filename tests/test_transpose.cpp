#include <gtest/gtest.h>
#include "transpose.h"


void fill_tensor(Tensor3D &tens)
{
    for(size_t i = 0; i < tens.data.size(); ++i)
    {
        tens.data[i] = i;
    }
}


TEST(Transpose, transpose_simple)
{
    Tensor3D src(5, 4, 7);

    fill_tensor(src);

    Tensor3D dest(src.shape[0], src.shape[2], src.shape[1]);

    transpose_simple(dest, src);

    for(size_t k = 0; k < dest.shape[0]; ++k)
    {
        for(size_t j = 0; j < dest.shape[1]; ++j)
        {
            for(size_t i = 0; i < dest.shape[2]; ++i)
            {
                EXPECT_EQ(
                    dest.data[k*dest.strides[0] + j*dest.strides[1] + i*dest.strides[2]],
                     src.data[k* src.strides[0] + i* src.strides[1] + j* src.strides[2]]);
            }
        }
    }
}


TEST(Transpose, transpose_blocked)
{
    Tensor3D src(5, 4, 7);

    fill_tensor(src);

    Tensor3D dest(src.shape[0], src.shape[2], src.shape[1]);

    transpose_blocked(dest, src);

    for(size_t k = 0; k < dest.shape[0]; ++k)
    {
        for(size_t j = 0; j < dest.shape[1]; ++j)
        {
            for(size_t i = 0; i < dest.shape[2]; ++i)
            {
                EXPECT_EQ(
                    dest.data[k*dest.strides[0] + j*dest.strides[1] + i*dest.strides[2]],
                     src.data[k* src.strides[0] + i* src.strides[1] + j* src.strides[2]]);
            }
        }
    }
}
