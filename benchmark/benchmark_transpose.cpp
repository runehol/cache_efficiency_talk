#include <benchmark/benchmark.h>
#include "transpose.h"



static void transpose_simple(benchmark::State& state)
{
    Tensor3D src(state.range(0), state.range(1), state.range(2));
    Tensor3D dest(state.range(0), state.range(2), state.range(1));

    size_t n_iters = 0;
    for (auto _: state)
    {
        transpose_simple(dest, src);
        ++n_iters;
    }
    state.SetBytesProcessed(n_iters * src.data.size()*sizeof(src.data[0]));
}


BENCHMARK(transpose_simple)->Args({64, 64, 64});
BENCHMARK(transpose_simple)->Args({16, 200, 200});
BENCHMARK(transpose_simple)->Args({16, 1000, 1000});
BENCHMARK(transpose_simple)->Args({16, 256, 256});
BENCHMARK(transpose_simple)->Args({16, 1024, 1024});
BENCHMARK(transpose_simple)->Args({1024, 1024, 1024});




static void transpose_blocked(benchmark::State& state)
{
    Tensor3D src(state.range(0), state.range(1), state.range(2));
    Tensor3D dest(state.range(0), state.range(2), state.range(1));

    size_t n_iters = 0;
    for (auto _: state)
    {
        transpose_blocked(dest, src);
        ++n_iters;
    }
    state.SetBytesProcessed(n_iters * src.data.size()*sizeof(src.data[0]));
}


BENCHMARK(transpose_blocked)->Args({64, 64, 64});
BENCHMARK(transpose_blocked)->Args({16, 200, 200});
BENCHMARK(transpose_blocked)->Args({16, 1000, 1000});
BENCHMARK(transpose_blocked)->Args({16, 256, 256});
BENCHMARK(transpose_blocked)->Args({16, 1024, 1024});
BENCHMARK(transpose_blocked)->Args({1024, 1024, 1024});



// Run the benchmark
BENCHMARK_MAIN();
