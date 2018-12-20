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


float MultLocal(const float * const m1, const float * const m2, const int width)
{
  float result = 0.0f;
  for(int i = 0; i < width; i++)
  {
    result += m1[i] * m2[i];
  }
  return result;
}
float MultLocal2(const float * const m1, const float * const m2, const int width)
{
  float result = 0.0f;
  const int vectorSize = 2;
  for(int i = 0; i < width/vectorSize; i=i+vectorSize)
    {
      float result1 = m1[i] * m2[i];
      float result2 = m1[i+1] * m2[i+1];
      result += result1+result2;
    }
  const int start = (width/vectorSize)*vectorSize;
  for(int i = start; i<width;i++)
    {
      result += m1[i]*m2[i];
    }
  return result;
}
float MultLocal4 (const float *const m1, const float *const m2, const int width)
{
  float result = 0.0f;
  const int vectorSize = 4;
  for(int i = 0; i < width/vectorSize; i=i+vectorSize)
    {
      float result1 = m1[i] * m2[i];
      float result2 = m1[i+1] * m2[i+1];
      float result3 = m1[i+2] * m2[i+2];
      float result4 = m1[i+3] * m2[i+3];
      result += result1+result2+result3+result4;
    }
  const int start = (width/vectorSize)*vectorSize;
  for(int i = start; i<width;i++)
    {
      result += m1[i]*m2[i];
    }
  return result;
}
float MultLocal8(const float * const m1, const float * const m2, const int width)
{
  float result = 0.0f;
  const int vectorSize = 8;
  for(int i = 0; i < width/vectorSize; i=i+vectorSize)
    {
      float result1 = m1[i] * m2[i];
      float result2 = m1[i+1] * m2[i+1];
      float result3 = m1[i+2] * m2[i+2];
      float result4 = m1[i+3] * m2[i+3];
      float result5 = m1[i+4] * m2[i+4];
      float result6 = m1[i+5] * m2[i+5];
      float result7 = m1[i+6] * m2[i+6];
      float result8 = m1[i+7] * m2[i+7];
      result += result1+result2+result3+result4+result5+result6+result7+result8;
    }
  const int start = (width/vectorSize)*vectorSize;
  for(int i = start; i<width;i++)
    {
      result += m1[i]*m2[i];
    }
  return result;
}
float MultLocal16(const float * const m1, const float * const m2, const int width)
{
  float result = 0.0f;
  const int vectorSize = 16;
  for(int i = 0; i < width/vectorSize; i=i+vectorSize)
    {
      float result1 = m1[i] * m2[i];
      float result2 = m1[i+1] * m2[i+1];
      float result3 = m1[i+2] * m2[i+2];
      float result4 = m1[i+3] * m2[i+3];
      float result5 = m1[i+4] * m2[i+4];
      float result6 = m1[i+5] * m2[i+5];
      float result7 = m1[i+6] * m2[i+6];
      float result8 = m1[i+7] * m2[i+7];
      float result9 = m1[i+8] * m2[i+8];
      float result10 = m1[i+9] * m2[i+9];
      float result11 = m1[i+10] * m2[i+10];
      float result12 = m1[i+11] * m2[i+11];
      float result13 = m1[i+12] * m2[i+12];
      float result14 = m1[i+13] * m2[i+13];
      float result15 = m1[i+14] * m2[i+14];
      float result16 = m1[i+15] * m2[i+15];
      result += result1+result2+result3+result4+result5+result6+result7+result8+result9+result10+result11+result12+result13+result14+result15+result16;
    }
  const int start = (width/vectorSize)*vectorSize;
  for(int i = start; i<width;i++)
    {
      result += m1[i]*m2[i];
    }
  return result;
}
float MultLocal32(const float * const m1, const float * const m2, const int width)
{
  float result = 0.0f;
  const int vectorSize = 16;
  for (int i = 0; i < width / vectorSize; i = i + vectorSize)
    {
      float result1 = m1[i] * m2[i];
      float result2 = m1[i + 1] * m2[i + 1];
      float result3 = m1[i + 2] * m2[i + 2];
      float result4 = m1[i + 3] * m2[i + 3];
      float result5 = m1[i + 4] * m2[i + 4];
      float result6 = m1[i + 5] * m2[i + 5];
      float result7 = m1[i + 6] * m2[i + 6];
      float result8 = m1[i + 7] * m2[i + 7];
      float result9 = m1[i + 8] * m2[i + 8];
      float result10 = m1[i + 9] * m2[i + 9];
      float result11 = m1[i + 10] * m2[i + 10];
      float result12 = m1[i + 11] * m2[i + 11];
      float result13 = m1[i + 12] * m2[i + 12];
      float result14 = m1[i + 13] * m2[i + 13];
      float result15 = m1[i + 14] * m2[i + 14];
      float result16 = m1[i + 15] * m2[i + 15];
      float result17 = m1[i + 16] * m2[i + 16];
      float result18 = m1[i + 17] * m2[i + 17];
      float result19 = m1[i + 18] * m2[i + 18];
      float result20 = m1[i + 19] * m2[i + 19];
      float result21 = m1[i + 20] * m2[i + 20];
      float result22 = m1[i + 21] * m2[i + 21];
      float result23 = m1[i + 22] * m2[i + 22];
      float result24 = m1[i + 23] * m2[i + 23];
      float result25 = m1[i + 24] * m2[i + 24];
      float result26 = m1[i + 25] * m2[i + 25];
      float result27 = m1[i + 26] * m2[i + 26];
      float result28 = m1[i + 27] * m2[i + 27];
      float result29 = m1[i + 28] * m2[i + 28];
      float result30 = m1[i + 29] * m2[i + 29];
      float result31 = m1[i + 30] * m2[i + 30];
      float result32 = m1[i + 31] * m2[i + 31];
      result += result1 + result2 + result3 + result4 + result5 + result6 + result7 + result8 + result9 +
                result10 + result11 + result12 + result13 + result14 + result15 + result16 + result17 + result18
                + result19 +
                result20 + result21 + result22 + result23 + result24 + result25 + result26 + result27 + result28
                + result29 +
                result30 + result31 + result32;
    }
  const int start = (width / vectorSize) * vectorSize;
  for (int i = start; i < width; i++)
    {
      result += m1[i] * m2[i];
    }
  return result;
}

void RandomFill(float* m, const int size)
{
  for(int i = 0; i<size; i++)
  {
    m[i] = static_cast<float>(rand());
  }
}

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