//
// Created by efarhan on 12/24/18.
//

#include <random>
#include <vector>
#include <misc.h>
#include <benchmark/benchmark.h>

void VectorAdd1(float* a, float* b, float* out, int size)
{
  for(int i = 0; i < size;i++)
    {
      out[i] = a[i]+b[i];
    }
}
void VectorAdd2(const float* a, const float* b, float* out, const int size)
{
  for(int i = 0; i < size;i++)
    {
      out[i] = a[i]+b[i];
    }
}
void VectorAdd3(const float* a, const float* b, float* __restrict out, const size_t size)
{
  for(int i = 0; i < size;i++)
    {
      out[i] = a[i]+b[i];
    }
}


static void BM_Add1(benchmark::State& state) {
  const int size = state.range (0);
  std::vector<float> m1;
  m1.resize (size);
  RandomFill (&m1[0], size);

  std::vector<float> m2;
  m2.resize ( size);
  RandomFill (&m2[0], size);

  std::vector<float> out;
  out.resize ( size);
  for (auto _ : state) {

      VectorAdd1(&m1[0],&m2[0],&out[0], size);
    }
}
BENCHMARK(BM_Add1)->Range(16, 8<<20);

static void BM_Add2(benchmark::State& state) {
  const int size = state.range (0);
  std::vector<float> m1;
  m1.resize (size);
  RandomFill (&m1[0], size);

  std::vector<float> m2;
  m2.resize ( size);
  RandomFill (&m2[0], size);

  std::vector<float> out;
  out.resize ( size);

  for (auto _ : state) {

      VectorAdd2(&m1[0],&m2[0],&out[0], size);
    }
}
BENCHMARK(BM_Add2)->Range(16, 8<<20);
static void BM_Add3(benchmark::State& state) {
  const int size = state.range (0);
  std::vector<float> m1;
  m1.resize (size);
  RandomFill (&m1[0], size);

  std::vector<float> m2;
  m2.resize ( size);
  RandomFill (&m2[0], size);


  std::vector<float> out;
  out.resize ( size);
  for (auto _ : state) {

      VectorAdd3(&m1[0],&m2[0],&out[0], size);
    }
}
BENCHMARK(BM_Add3)->Range(16, 8<<20);

BENCHMARK_MAIN ();