#include <gtest/gtest.h>
#include "transpose.h"


void fill_matrix(Matrix2D &tens)
{
    for(size_t i = 0; i < tens.data.size(); ++i)
    {
        tens.data[i] = i;
    }
}


TEST(Transpose, transpose_simple)
{
    Matrix2D src(4, 7);

    fill_matrix(src);

    Matrix2D dest(src.shape[1], src.shape[0]);

    transpose_simple(dest, src);

    for(size_t j = 0; j < dest.shape[0]; ++j)
    {
        for(size_t i = 0; i < dest.shape[1]; ++i)
        {
            EXPECT_EQ(
                dest.data[j*dest.stride + i],
                src.data[ i* src.stride + j]);
        }
    }
}


TEST(Transpose, transpose_blocked)
{
    Matrix2D src(4, 7);

    fill_matrix(src);

    Matrix2D dest(src.shape[1], src.shape[0]);

    transpose_blocked(dest, src);

    for(size_t j = 0; j < dest.shape[0]; ++j)
    {
        for(size_t i = 0; i < dest.shape[1]; ++i)
        {
            EXPECT_EQ(
                dest.data[j*dest.stride + i],
                src.data[ i* src.stride + j]);
        }
    }
}
