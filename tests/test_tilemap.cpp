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
//BENCHMARK(BM_LoadTilemapNaive)->Range(fromRange, toRange);

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
//BENCHMARK(BM_LoadTilemap)->Range(fromRange, toRange);



unsigned getTileAtNaive(std::vector<std::vector<unsigned>>& tiles, const int n, const int m)
{
	return tiles[n][m];
}

static void BM_GetTileAtNaive(benchmark::State& state) {
	std::vector<std::vector<unsigned>> tiles = std::vector<std::vector<unsigned>>{ 10000 , std::vector<unsigned>(10000) };
	for (auto _ : state)
	{
		benchmark::DoNotOptimize(getTileAtNaive(tiles, state.range(0) / 2, state.range(0) / 2));
	}
}
BENCHMARK(BM_GetTileAtNaive)->Range(fromRange, toRange);

unsigned getTileAtOpti(std::vector<unsigned>& tiles, const size_t tilemapSizeY, const int n, const int m)
{
	return tiles.at(n * tilemapSizeY + m);
}

static void BM_GetTileAtOpti(benchmark::State& state) {
	std::vector<unsigned> tiles = std::vector<unsigned>(10000 * 1000, 0);
	for (auto _ : state)
	{
		benchmark::DoNotOptimize(getTileAtOpti(tiles, state.range(0), state.range(0) / 2, state.range(0) / 2));
	}
}
BENCHMARK(BM_GetTileAtOpti)->Range(fromRange, toRange);

BENCHMARK_MAIN();

