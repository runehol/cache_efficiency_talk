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


BENCHMARK(benchmark_sum_inner_to_outer)->Args({4, 1000}); // 16 KB -> L1
BENCHMARK(benchmark_sum_inner_to_outer)->Args({100, 1000}); // 400 KB -> L2
BENCHMARK(benchmark_sum_inner_to_outer)->Args({1000, 1000}); // 4000 KB -> DRAM
























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

BENCHMARK(benchmark_sum_outer_to_inner)->Args({4, 1000}); // 16 KB -> L1
BENCHMARK(benchmark_sum_outer_to_inner)->Args({100, 1000}); // 400 KB -> L2
BENCHMARK(benchmark_sum_outer_to_inner)->Args({1000, 1000}); // 4000 KB -> DRAM























BENCHMARK(benchmark_sum_outer_to_inner)->Args({4, 1024}); // 16 KB -> L1
BENCHMARK(benchmark_sum_outer_to_inner)->Args({100, 1024}); // 400 KB -> L2
BENCHMARK(benchmark_sum_outer_to_inner)->Args({1000, 1024}); // 3000 KB -> DRAM



































static size_t round_down_to_pow2(size_t v)
{
    while(v & (v-1))
    {
        v &= v-1;
    }
    return v;
}

static float sum_random(const Matrix2D &tens)
{
    float sum = 0;
    size_t mask = round_down_to_pow2(tens.data.size()) - 1;
    for(size_t i = 0; i < tens.data.size(); ++i)
    {
        size_t idx = (i*13 + i*7919)&mask; // jump around randomly in the buffer
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

BENCHMARK(benchmark_sum_random)->Args({4, 1000}); // 16 KB -> L1
BENCHMARK(benchmark_sum_random)->Args({100, 1000}); // 400 KB -> L2
BENCHMARK(benchmark_sum_random)->Args({1000, 1000}); // 4000 KB -> DRAM
