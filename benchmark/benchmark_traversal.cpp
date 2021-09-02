#include <benchmark/benchmark.h>

#include "tensor3d.h"


static float sum_inner_to_outer(const Tensor3D &tens)
{
    float sum = 0;
    for(size_t k = 0; k < tens.shape[0]; ++k)
    {
        for(size_t j = 0; j < tens.shape[1]; ++j)
        {
            for(size_t i = 0; i < tens.shape[2]; ++i)
            {
                sum += tens.data[k*tens.strides[0] + j*tens.strides[1] + i];
            }
        }
    }
    return sum;
}

static void benchmark_sum_inner_to_outer(benchmark::State& state)
{
    Tensor3D src(state.range(0), state.range(1), state.range(2));

    size_t n_iters = 0;
    for (auto _: state)
    {
        auto sum = sum_inner_to_outer(src);
        benchmark::DoNotOptimize(sum);
        ++n_iters;
    }
    state.SetBytesProcessed(n_iters * src.data.size()*sizeof(src.data[0]));
}


BENCHMARK(benchmark_sum_inner_to_outer)->Args({16/4, 10, 100}); // 14 KB -> L1
BENCHMARK(benchmark_sum_inner_to_outer)->Args({72/4, 10, 100}); // 72 KB -> L2
BENCHMARK(benchmark_sum_inner_to_outer)->Args({3000/4, 10, 100}); // 3000 KB -> DRAM






static float sum_outer_to_inner(const Tensor3D &tens)
{
    float sum = 0;
    for(size_t i = 0; i < tens.shape[2]; ++i)
    {
        for(size_t j = 0; j < tens.shape[1]; ++j)
        {
            for(size_t k = 0; k < tens.shape[0]; ++k)
            {
                sum += tens.data[k*tens.strides[0] + j*tens.strides[1] + i];
            }
        }
    }
    return sum;
}


static void benchmark_sum_outer_to_inner(benchmark::State& state)
{
    Tensor3D src(state.range(0), state.range(1), state.range(2));

    size_t n_iters = 0;
    for (auto _: state)
    {
        auto sum = sum_outer_to_inner(src);
        benchmark::DoNotOptimize(sum);
        ++n_iters;
    }
    state.SetBytesProcessed(n_iters * src.data.size()*sizeof(src.data[0]));
}

BENCHMARK(benchmark_sum_outer_to_inner)->Args({16/4, 10, 100}); // 14 KB -> L1
BENCHMARK(benchmark_sum_outer_to_inner)->Args({72/4, 10, 100}); // 72 KB -> L2
BENCHMARK(benchmark_sum_outer_to_inner)->Args({3000/4, 10, 100}); // 3000 KB -> DRAM

BENCHMARK(benchmark_sum_outer_to_inner)->Args({72/4, 1, 1024}); // 14 KB -> L1
