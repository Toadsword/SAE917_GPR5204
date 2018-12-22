//
// Created by efarhan on 22.12.18.
//

#include <iostream>
#include <job_system.h>
#include <thread>



JobSystem::JobSystem()
{
    tp.resize(std::thread::hardware_concurrency()-1);
}

