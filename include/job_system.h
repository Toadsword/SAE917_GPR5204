//
// Created by efarhan on 22.12.18.
//

#ifndef GPR5204_JOB_SYSTEM_H
#define GPR5204_JOB_SYSTEM_H

#include <vector>
#include <ctpl_stl.h>
#include <thread>

class JobSystem;

template<class TData>
struct Job
{
    Job() = default;
    Job(const Job&) = delete;
    std::vector<TData>& data;
    std::function<void(TData&)> function;

    void WaitOnJob();
    std::vector<std::future<void>> futures;
};

template<class TData>
void Job<TData>::WaitOnJob() {

    for(auto& f : futures)
    {
        f.wait();
    }
}
template<class TData>
struct JobRange
{
    JobRange() = default;
    JobRange(const JobRange&) = delete;
    std::vector<TData>& data;
    std::function<void(TData*,int,int)> function;

    void WaitOnJob();
    std::vector<std::future<void>> futures;
};

template<class TData>
void JobRange<TData>::WaitOnJob() {
    for(auto& f : futures)
    {
        f.wait();
    }
}

class JobSystem
{
public:
    JobSystem();
    template <class TData>
    void Schedule(Job<TData>& job)
    {
        int tpSize = tp.size();
        for(int i = 0; i < tp.size();i++)
        {
            std::function<void(TData&)>  func = job.function;
            std::vector<TData>& data = job.data;
            auto future = tp.push([&func, &data, tpSize, i](int){
                int length = data.size()/tpSize;
                int start = length*i;
                int end = length*(i+1);
                for(int j = start; j < end || j<data.size();j++)
                {
                    func(data[j]);
                }
            });
            job.futures.push_back(std::move(future));
        }
    }

    template <class TData>
    void Schedule(JobRange<TData>& job)
    {
        int tpSize = tp.size();
        for(int i = 0; i < tp.size();i++)
        {
            std::function<void(TData*, int, int)>  func = job.function;
            std::vector<TData>& data = job.data;
            auto future = tp.push([&func, &data, tpSize, i](int){
                int length = data.size()/tpSize;
                int start = length*i;
                int end = i == tpSize-1?data.size():length*(i+1);
                func(&data[0], start, end);

            });
            job.futures.push_back(std::move(future));
        }
    }
private:
    ctpl::thread_pool tp;
};


#endif //GPR5204_JOB_SYSTEM_H
