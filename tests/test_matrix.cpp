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


#define MULT_LOCAL_16

#ifdef MULT_LOCAL_DEF
float MultLocal(const float * const m1, const float * const m2, const int width)
{
  float result = 0.0f;
  const int vectorSize = 1;
  for(int i = 0; i < width/vectorSize; i=i+vectorSize)
    {
      float result1 = m1[i] * m2[i];
      result += result1;
    }
  return result;
}
#endif


#ifdef MULT_LOCAL_2
float MultLocal(const float * const m1, const float * const m2, const int width)
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
#endif


#ifdef MULT_LOCAL_4
float MultLocal(const float * const m1, const float * const m2, const int width)
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
#endif


#ifdef MULT_LOCAL_8
float MultLocal(const float * const m1, const float * const m2, const int width)
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
#endif


#ifdef MULT_LOCAL_16
float MultLocal(const float * const m1, const float * const m2, const int width)
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
#endif

#ifdef MULT_LOCAL_32
float MultLocal(const float * const m1, const float * const m2, const int width)
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
#endif



class Matrix
{
public:
	Matrix(int width, int height): width(width), height(height)
	{
		values.resize(static_cast<unsigned long>(height) * static_cast<unsigned long>(width));
	}

	void Prefill()
	{
		for (auto& v : values)
		{
			v = static_cast<float>(rand());
		}

	}

	Matrix Transpose() const
	{
		Matrix m(height, width);
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				m.values[j*width+i] = values[i*width+j];
			}
		}
		return m;
	}

	Matrix Mult(const Matrix& m2) const
	{
		if(width == m2.height)
		{
			Matrix newMatrix(m2.width, height);
			for (int y = 0; y < newMatrix.height; y++)
			{
				for (int x = 0; x < newMatrix.width; x++)
				{
					float newValue = 0.0f;

					for(int i = 0; i < width;i++)
					{
						newValue += values[y*width+i] * m2.values[i*m2.width+x];
					}
							//

					newMatrix.values[x*newMatrix.width+y] = newValue;
				}
			}
			return newMatrix;
		}
		else
		{
			return Matrix(0, 0);
		}
	}


  Matrix MultOptimize(const Matrix& m2T) const
  {

    const int localWidth = width;
    if (localWidth == m2T.width)
      {
        Matrix newMatrix(m2T.width, height);
        const int newWidth = newMatrix.width;
        const int newHeight = newMatrix.height;
        for (int y = 0; y < newHeight; y++)
          {
            for (int x = 0; x < newWidth; x++)
              {
                const int xOrigin = x*m2T.width;
                const int yOrigin = y*width;
                float newValue = MultLocal(&values[yOrigin], &m2T.values[xOrigin], localWidth);
                newMatrix.values[x*newWidth+y] = newValue;
              }
          }
        return newMatrix;
      }
    else
      {
        return Matrix(0, 0);
      }
  }

private:
	int width = 0;
	int height = 0;
	std::vector<float> values;
};


static void BM_MatrixMult(benchmark::State& state)
{
	for (auto _ : state)
	{
		state.PauseTiming();
		Matrix m1(state.range(0), state.range(1));
		m1.Prefill();
		Matrix m2(state.range(1), state.range(0));
		m2.Prefill();
		state.ResumeTiming();

		benchmark::DoNotOptimize(m1.Mult(m2));
	}
}
BENCHMARK(BM_MatrixMult)->Args ({64,64})->Args({128,128})->Args({256,256})->Args({512,512})->Args({1024, 1024});


static void BM_MatrixMultOptimize(benchmark::State& state) {
	
	for (auto _ : state)
	{
		state.PauseTiming();
		Matrix m1(state.range(0), state.range(1));
		m1.Prefill();
		Matrix m2(state.range(1), state.range(0));
		m2.Prefill();
		state.ResumeTiming();

		const Matrix m2T = m2.Transpose ();
		benchmark::DoNotOptimize(m1.MultOptimize(m2T));
	}
}
BENCHMARK(BM_MatrixMultOptimize)->Args ({64,64})->Args({128,128})->Args({256,256})->Args({512,512})->Args({1024, 1024});

BENCHMARK_MAIN();

