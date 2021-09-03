#include <benchmark/benchmark.h>
#include "matrix2d.h"

static void transpose_simple(Matrix2D &out, const Matrix2D &in)
{
    for(size_t j = 0; j < out.shape[0]; ++j)
    {
        for(size_t i = 0; i < out.shape[1]; ++i)
        {
            out.data[j*out.stride + i] = in.data[i*in.stride + j];
        }
    }
}


static void benchmark_transpose_simple(benchmark::State& state)
{
    Matrix2D src(state.range(0), state.range(1));
    Matrix2D dest(state.range(1), state.range(0));

    size_t n_iters = 0;
    for (auto _: state)
    {
        transpose_simple(dest, src);
        ++n_iters;
    }
    state.SetBytesProcessed(n_iters * src.data.size()*sizeof(src.data[0]));
}


BENCHMARK(benchmark_transpose_simple)->Args({40, 100});
BENCHMARK(benchmark_transpose_simple)->Args({100, 1000});
BENCHMARK(benchmark_transpose_simple)->Args({1000, 1000});
BENCHMARK(benchmark_transpose_simple)->Args({2000, 1000});
BENCHMARK(benchmark_transpose_simple)->Args({4000, 1000});




























static void transpose_blocked(Matrix2D &out, const Matrix2D &in)
{
    constexpr size_t blocking_size_j =  256; // 256*256* 4 = 256 KB. 2 buffers of these make for 512 KB, which fits into our L2 cache size
    constexpr size_t blocking_size_i =  256;
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


static void benchmark_transpose_blocked(benchmark::State& state)
{
    Matrix2D src(state.range(0), state.range(1));
    Matrix2D dest(state.range(1), state.range(0));

    size_t n_iters = 0;
    for (auto _: state)
    {
        transpose_blocked(dest, src);
        ++n_iters;
    }
    state.SetBytesProcessed(n_iters * src.data.size()*sizeof(src.data[0]));
}

BENCHMARK(benchmark_transpose_blocked)->Args({40, 100});
BENCHMARK(benchmark_transpose_blocked)->Args({100, 1000});
BENCHMARK(benchmark_transpose_blocked)->Args({1000, 1000});
BENCHMARK(benchmark_transpose_blocked)->Args({2000, 1000});
BENCHMARK(benchmark_transpose_blocked)->Args({4000, 1000});
