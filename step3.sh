#!/bin/sh
ninja -C build-release/ all && build-release/benchmark/benchmark_cache_efficiency_talk --benchmark_filter=benchmark_sum_outer.*
