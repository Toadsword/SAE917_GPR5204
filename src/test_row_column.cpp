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
#include "benchmark/benchmark.h"


class Matrix
{
public:
	Matrix(int width, int height): width(width), height(height)
	{
		values.resize(height);
		for (auto& row : values)
		{
			row.resize(width);
		}
	}

	void Prefill()
	{
		for(auto& row : values)
		{
			for (auto& v : row)
			{
				v = static_cast<float>(rand());
			}
		}
	}

	Matrix Transpose()
	{
		Matrix m(height, width);
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				m.values[j][i] = values[i][j];
			}
		}
	}

	Matrix Mult(Matrix& m)
	{
		if(width == m.height)
		{
			Matrix newMatrix(m.width, height);
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < m.width; j++)
				{
					newMatrix.values[i][j] = values[i][j] * m.values[j][i];
				}
			}
			return newMatrix;
		}
		else
		{
			return Matrix(0, 0);
		}
	}

	Matrix MultOptimize(Matrix& m)
	{
		if (width == m.height)
		{
			Matrix newMatrix(m.width, height);
			Matrix otherTranspose = m.Transpose();
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < m.width; j++)
				{
					m.values[i][j] = values[i][j] * otherTranspose.values[i][j];
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
	int width;
	int height;

	std::vector<std::vector<float>> values;
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
BENCHMARK(BM_MatrixMult)->Ranges({ {16, 16}, {128, 256} });


static void BM_MatrixMultOptimize(benchmark::State& state) {
	
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
BENCHMARK(BM_MatrixMultOptimize)->Ranges({ {16, 16}, {128, 256} });

BENCHMARK_MAIN();

