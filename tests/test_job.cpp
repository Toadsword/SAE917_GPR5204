//
// Created by efarhan on 22.12.18.
//

#include <cmath>

#include <job_system.h>
#include <misc.h>
#include <benchmark/benchmark.h>



static void BM_Transform(benchmark::State& state) {
    const int size = state.range (0);
    std::vector<float> m1;
    m1.resize (size);
    RandomFill (&m1[0], size);

    for (auto _ : state)
    {
        for(auto& v : m1)
        {
            v = sqrtf(powf(v, static_cast<float>(M_PI)));
        }
    }
}
BENCHMARK(BM_Transform)->Range(16, 8<<16)->UseRealTime();


static void BM_JobSystem(benchmark::State& state) {
    const int size = state.range (0);
    std::vector<float> m1;
    m1.resize (size);
    RandomFill (&m1[0], size);

    JobSystem jobSystem;
    for (auto _ : state)
    {
        Job<float> j
                {
            m1,[](float& number){
                number = sqrtf(powf(number, static_cast<float>(M_PI)));
            }
                };
        jobSystem.Schedule(j);
        j.WaitOnJob();

    }

}
BENCHMARK(BM_JobSystem)->Range(16, 8<<16)->UseRealTime();

static void BM_JobRangeSystem(benchmark::State& state) {
    const int size = state.range (0);
    std::vector<float> m1;
    m1.resize (size);
    RandomFill (&m1[0], size);

    JobSystem jobSystem;
    for (auto _ : state)
    {
        JobRange<float> j
        {
            m1,[](float* number, int start, int end)
            {
                for(int i = start; i < end;i++)
                {
                    number[i] = sqrtf(powf(number[i], static_cast<float>(M_PI)));
                }
            }
        };
        jobSystem.Schedule(j);
        j.WaitOnJob();

    }

}
BENCHMARK(BM_JobRangeSystem)->Range(16, 8<<16)->UseRealTime();


BENCHMARK_MAIN();

