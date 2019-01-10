//
// Created by efarhan on 1/10/19.
//

#include <vector>
#include <list>
#include <benchmark/benchmark.h>

const int fromRange = 16;
const int toRange = 1 << 20;

float sum_vector(std::vector<float*>& f)
{
  float sum = 0.0f;
  for(auto* f_ptr : f)
    {
      sum += (*f_ptr);
    }
    return sum;
}

float sum_list(std::list<float*>& f)
{
  float sum = 0.0f;
  for(auto* f_ptr : f)
    {
      sum += (*f_ptr);
    }
  return sum;
}

float sum(const float* f, const int N)
{
  float sum = 0.0f;
  for(int i = 0; i<N;i++)
    {
      sum += f[i];
    }
  return sum;
}

static void BM_SumList(benchmark::State& state) {

  std::list<float*> f;
  for(int i = 0 ; i<state.range (0);i++)
    {
      f.push_back(new float);
    }
  for (auto _ : state) {

      benchmark::DoNotOptimize(sum_list (f));
    }
  for(auto* ptr : f)
    {

      delete(ptr);
    }
}
BENCHMARK(BM_SumList)->Range(fromRange, toRange);

static void BM_SumVector(benchmark::State& state) {

  std::vector<float*> f;
  for(int i = 0 ; i<state.range (0);i++)
    {
      f.push_back(new float);
    }

  for (auto _ : state) {

      benchmark::DoNotOptimize(sum_vector (f));
    }
    for(int i = 0; i< f.size();i++)
      {
        delete(f[i]);
      }
}
BENCHMARK(BM_SumVector)->Range(fromRange, toRange);

static void BM_SumVectorValue(benchmark::State& state) {

  std::vector<float> f;
  f.resize(state.range (0));
  for (auto _ : state) {

      benchmark::DoNotOptimize(sum(&f[0], f.size()));
    }
}
BENCHMARK(BM_SumVectorValue)->Range(fromRange, toRange);

BENCHMARK_MAIN ();