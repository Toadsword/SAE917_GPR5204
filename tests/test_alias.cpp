//
// Created by efarhan on 1/16/19.
//

/*
MIT License

Copyright (c) 2019 SAE Institute Switzerland AG

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

#include<cmath>
#include "benchmark/benchmark.h"

const int fromRange = 1 << 2;
const int toRange = 1 << 20;

struct MyIntArray1
{
    int* basePtr;
    int count;

    void SetToValue(int val)
    {
      for(int i = 0; i<count; i++)
        {
          basePtr[i] = val;
        }
    }
};
struct MyIntArray2
{
    int* basePtr;
    size_t count;

    void SetToValue(int val)
    {
      for(int i = 0; i<count; i++)
        {
          basePtr[i] = val;
        }
    }
};
struct MyIntArray3
{
    int* basePtr;
    size_t count;

    void SetToValue(int val)
    {
      int localCount = count;
      for(int i = 0; i<localCount; i++)
        {
          basePtr[i] = val;
        }
    }
};

static void BM_Array1(benchmark::State& state) {

  MyIntArray1 intArray;
  intArray.count = state.range (0);
  intArray.basePtr = new int[intArray.count];
  for (auto _ : state) {
      state.PauseTiming ();
      const int newValue = rand();
      state.ResumeTiming ();
      intArray.SetToValue (newValue);

      benchmark::DoNotOptimize (intArray);
    }
    delete[] (intArray.basePtr);
}
BENCHMARK(BM_Array1)->Range(fromRange, toRange);


static void BM_Array2(benchmark::State& state) {

  MyIntArray2 intArray;
  intArray.count = state.range (0);
  intArray.basePtr = new int[intArray.count];
  for (auto _ : state) {
      state.PauseTiming ();
      const int newValue = rand();
      state.ResumeTiming ();
      intArray.SetToValue (newValue);
      benchmark::DoNotOptimize (intArray);
    }
  delete[] (intArray.basePtr);
}
BENCHMARK(BM_Array2)->Range(fromRange, toRange);

static void BM_Array3(benchmark::State& state) {

  MyIntArray3 intArray;
  intArray.count = state.range (0);
  intArray.basePtr = new int[intArray.count];
  for (auto _ : state) {
      state.PauseTiming ();
      const int newValue = rand();
      state.ResumeTiming ();
      intArray.SetToValue (newValue);
      benchmark::DoNotOptimize (intArray);
    }
  delete[] (intArray.basePtr);
}
BENCHMARK(BM_Array3)->Range(fromRange, toRange);

BENCHMARK_MAIN();