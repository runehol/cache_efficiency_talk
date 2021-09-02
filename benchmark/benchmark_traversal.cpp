#include <benchmark/benchmark.h>

#include "matrix2d.h"


static float sum_inner_to_outer(const Matrix2D &tens)
{
    float sum = 0;
    for(size_t j = 0; j < tens.shape[0]; ++j)
    {
        for(size_t i = 0; i < tens.shape[1]; ++i)
        {
            sum += tens.data[j*tens.stride + i];
        }
    }
    return sum;
}

static void benchmark_sum_inner_to_outer(benchmark::State& state)
{
    Matrix2D src(state.range(0), state.range(1));

    size_t n_iters = 0;
    for (auto _: state)
    {
        auto sum = sum_inner_to_outer(src);
        benchmark::DoNotOptimize(sum);
        ++n_iters;
    }
    state.SetBytesProcessed(n_iters * src.data.size()*sizeof(src.data[0]));
}


BENCHMARK(benchmark_sum_inner_to_outer)->Args({16/4, 1000}); // 14 KB -> L1
BENCHMARK(benchmark_sum_inner_to_outer)->Args({72/4, 1000}); // 72 KB -> L2
BENCHMARK(benchmark_sum_inner_to_outer)->Args({3000/4, 1000}); // 3000 KB -> DRAM






static float sum_outer_to_inner(const Matrix2D &tens)
{
    float sum = 0;
    for(size_t i = 0; i < tens.shape[1]; ++i)
    {
        for(size_t j = 0; j < tens.shape[0]; ++j)
        {
            sum += tens.data[i + j*tens.stride];
        }
    }
    return sum;
}


static void benchmark_sum_outer_to_inner(benchmark::State& state)
{
    Matrix2D src(state.range(0), state.range(1));

    size_t n_iters = 0;
    for (auto _: state)
    {
        auto sum = sum_outer_to_inner(src);
        benchmark::DoNotOptimize(sum);
        ++n_iters;
    }
    state.SetBytesProcessed(n_iters * src.data.size()*sizeof(src.data[0]));
}

BENCHMARK(benchmark_sum_outer_to_inner)->Args({16/4, 1000}); // 14 KB -> L1
BENCHMARK(benchmark_sum_outer_to_inner)->Args({72/4, 1000}); // 72 KB -> L2
BENCHMARK(benchmark_sum_outer_to_inner)->Args({3000/4, 1000}); // 3000 KB -> DRAM

BENCHMARK(benchmark_sum_outer_to_inner)->Args({16/4, 1024}); // 14 KB -> L1
BENCHMARK(benchmark_sum_outer_to_inner)->Args({72/4, 1024}); // 72 KB -> L2
BENCHMARK(benchmark_sum_outer_to_inner)->Args({3000/4, 1024}); // 3000 KB -> DRAM




static float sum_random(const Matrix2D &tens)
{
    float sum = 0;
    for(size_t i = 0; i < tens.data.size(); ++i)
    {
        size_t idx = std::rand() % tens.data.size();
        sum += tens.data[idx];
    }
    return sum;
}


static void benchmark_sum_random(benchmark::State& state)
{
    Matrix2D src(state.range(0), state.range(1));

    size_t n_iters = 0;
    for (auto _: state)
    {
        auto sum = sum_random(src);
        benchmark::DoNotOptimize(sum);
        ++n_iters;
    }
    state.SetBytesProcessed(n_iters * src.data.size()*sizeof(src.data[0]));
}

BENCHMARK(benchmark_sum_random)->Args({16/4, 1000}); // 14 KB -> L1
BENCHMARK(benchmark_sum_random)->Args({72/4, 1000}); // 72 KB -> L2
BENCHMARK(benchmark_sum_random)->Args({3000/4, 1000}); // 3000 KB -> DRAM
