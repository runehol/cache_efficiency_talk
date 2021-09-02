#include <benchmark/benchmark.h>

#include <vector>
#include <list>
#include <set>
#include <cstdlib>



template<typename Container>
auto sum(const Container &vec)
{
    auto acc = *vec.begin();
    for(auto elm: vec)
    {
        acc += elm;
    }
    return acc;
}


template<typename Container> Container make_container(size_t sz)
{
    Container c;
    for(size_t i = 0; i < sz; ++i)
    {
        c.push_back(std::rand());
    }
    return c;
}

template<> std::set<float> make_container(size_t sz)
{
    std::set<float> c;
    for(size_t i = 0; i < sz; ++i)
    {
        c.insert(std::rand());
    }
    return c;
}

template<typename Container>
static void sum_container(benchmark::State& state)
{
    Container container = make_container<Container>(100000);

    size_t n_iters = 0;
    for (auto _: state)
    {
        float result = sum(container);
        benchmark::DoNotOptimize(result);
        ++n_iters;
    }
    state.SetBytesProcessed(n_iters * container.size()*sizeof(*container.begin()));
}

BENCHMARK_TEMPLATE(sum_container, std::vector<float>);
BENCHMARK_TEMPLATE(sum_container, std::list<float>);
BENCHMARK_TEMPLATE(sum_container, std::set<float>);
