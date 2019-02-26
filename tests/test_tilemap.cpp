//
// Created by efarhan on 1/10/19.
//

#include <benchmark/benchmark.h>

const int fromRange = 4;
const int toRange = 1 << 11;
std::vector<std::vector<unsigned>> initTilemapNaive(const size_t n)
{
	std::vector<std::vector<unsigned>> tiles = std::vector<std::vector<unsigned>>{
		static_cast<unsigned>(n),
		std::vector<unsigned>(static_cast<unsigned>(n))
	};

	for (unsigned indexX = 0; indexX < n; indexX++)
	{
		for (unsigned indexY = 0; indexY < n; indexY++)
		{
			tiles[indexX][indexY] = 0;						
		}
	}

	return tiles;
}

static void BM_LoadTilemapNaive(benchmark::State& state) {
	for (auto _ : state)
	{
		benchmark::DoNotOptimize(initTilemapNaive(state.range(0)));
	}
}
BENCHMARK(BM_LoadTilemapNaive)->Range(fromRange, toRange);

std::vector<unsigned> initTilemapOpti(const size_t n)
{
	std::vector<unsigned> tiles = std::vector<unsigned>(n*n, 0);

	return tiles;
}

static void BM_LoadTilemap(benchmark::State& state) {
	for (auto _ : state)
	{
		benchmark::DoNotOptimize(initTilemapOpti(state.range(0)));
	}
}
BENCHMARK(BM_LoadTilemap)->Range(fromRange, toRange);

BENCHMARK_MAIN();