#pragma once
#ifndef COMPUTE_H
#define COMPUTE_H


#define GENERAL_CLIQUE 1
#define CORE_ALG 2
#define EFF_CLIQUE 3
#define MAXIMUM_CLIQUE 4
#define ORIGINAL_MAXIMUM_CLQ 5
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <chrono>

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../defination.h"
#include "../Prunes/prunes.h"

#include "../Algorithms/Algorithms.h"

class Compute{
    public:
        //void read_graph(const char *str, Defi &defi);
        void init_parameters(int prunes, Defi &defi);
        void compute(int k, double p, int alg, int prunes, Defi &defi, Sources &sources, Prunes &pruns, Algorithms &algs);
};


class Timer {
public:
    void start() {
        start_time = std::chrono::system_clock::now();
    }

    void stop() {
        end_time = std::chrono::system_clock::now();
    }

    double elapsedMilliseconds() const {
        std::chrono::duration<double, std::milli> duration = end_time - start_time;
        return duration.count();
    }

    std::chrono::system_clock::time_point startTime() const {
        return start_time;
    }
    std::chrono::system_clock::time_point endTime() const {
        return end_time;
    }


private:
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
};

#endif