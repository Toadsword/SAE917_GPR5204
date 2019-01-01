/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <vector>
#include <numeric>
#include <iostream>
#include <functional>
#include "benchmark/benchmark.h"
#include <dot.h>
#include <misc.h>






static void BM_Mult(benchmark::State& state) {
  const int size = state.range (0);
  std::vector<float> m1;
  m1.resize (size);
  RandomFill (&m1[0], size);

  std::vector<float> m2;
  m2.resize ( size);
  RandomFill (&m2[0], size);

  for (auto _ : state) {

      benchmark::DoNotOptimize(MultLocal (&m1[0],&m2[0],size));
    }
}
BENCHMARK(BM_Mult)->Range(16, 8<<25);

static void BM_Mult2(benchmark::State& state) {
  const int size = state.range (0);
  std::vector<float> m1;
  m1.resize (size);
  RandomFill (&m1[0], size);

  std::vector<float> m2;
  m2.resize ( size);
  RandomFill (&m2[0], size);


  for (auto _ : state) {

      benchmark::DoNotOptimize(MultLocal2 (&m1[0],&m2[0],size));
    }
}
BENCHMARK(BM_Mult2)->Range(16, 8<<25);

static void BM_Mult4(benchmark::State& state) {
  const int size = state.range (0);
  std::vector<float> m1;
  m1.resize (size);
  RandomFill (&m1[0], size);

  std::vector<float> m2;
  m2.resize ( size);
  RandomFill (&m2[0], size);


  for (auto _ : state) {

      benchmark::DoNotOptimize(MultLocal4 (&m1[0], &m2[0], size));
    }
}
BENCHMARK(BM_Mult4)->Range(16, 8<<25);

static void BM_Mult8(benchmark::State& state) {
  const int size = state.range (0);
  std::vector<float> m1;
  m1.resize (size);
  RandomFill (&m1[0], size);

  std::vector<float> m2;
  m2.resize ( size);
  RandomFill (&m2[0], size);


  for (auto _ : state) {

      benchmark::DoNotOptimize(MultLocal8 (&m1[0],&m2[0],size));
    }
}
BENCHMARK(BM_Mult8)->Range(16, 8<<25);

static void BM_Mult16(benchmark::State& state) {
  const int size = state.range (0);
  std::vector<float> m1;
  m1.resize (size);
  RandomFill (&m1[0], size);

  std::vector<float> m2;
  m2.resize ( size);
  RandomFill (&m2[0], size);


  for (auto _ : state) {

      benchmark::DoNotOptimize(MultLocal16 (&m1[0],&m2[0],size));
    }
}
BENCHMARK(BM_Mult16)->Range(16, 8<<25);

static void BM_Mult32(benchmark::State& state) {
  const int size = state.range (0);
  std::vector<float> m1;
  m1.resize (size);
  RandomFill (&m1[0], size);

  std::vector<float> m2;
  m2.resize ( size);
  RandomFill (&m2[0], size);


  for (auto _ : state) {

      benchmark::DoNotOptimize(MultLocal32 (&m1[0],&m2[0],size));
    }
}
BENCHMARK(BM_Mult32)->Range(16, 8<<25);

BENCHMARK_MAIN ();