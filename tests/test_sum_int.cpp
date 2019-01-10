//
// Created by efarhan on 1/10/19.
//

#include <benchmark/benchmark.h>

const int fromRange = 16;
const int toRange = 1<<25;
int sum(const size_t n)
{
  int sum = 0;
  for(int i = 1; i <= n ; i++)
    {
      sum += i;
    }
  return sum;
}

static void BM_Sum(benchmark::State& state) {
  for (auto _ : state)
    {
      benchmark::DoNotOptimize(sum(state.range (0)));
    }
}
BENCHMARK(BM_Sum)->Range(fromRange, toRange);

BENCHMARK_MAIN();