#include <benchmark/benchmark.h>
#include "transpose.h"



static void transpose_simple(benchmark::State& state)
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


BENCHMARK(transpose_simple)->Args({40, 100});
BENCHMARK(transpose_simple)->Args({100, 1000});
BENCHMARK(transpose_simple)->Args({1000, 1000});




static void transpose_blocked(benchmark::State& state)
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

BENCHMARK(transpose_blocked)->Args({40, 100});
BENCHMARK(transpose_blocked)->Args({100, 1000});
BENCHMARK(transpose_blocked)->Args({1000, 1000});
