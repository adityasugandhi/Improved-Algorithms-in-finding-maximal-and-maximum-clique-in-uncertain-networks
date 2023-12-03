#pragma once
#ifndef ALGORITHMS
#define ALGORITHMS

#include <cstring>
#include "../sourcefiles/sources.h"
#include "../defination.h"
#include <utility>

class Algorithms {
public:
    void general_enumerate(int *R, double q, pairs *I, int I_size, pairs *C, int C_size, Defi &defi, Sources &sources);
    void general_algorithm_of_cliques(Defi &defi, Sources &sources);
    void Max_Pclq(Defi &defi, Sources &sources);
    void general_max_enumerate(int *R, double q, pairs *I, int I_size, pairs *C, int C_size, Defi &defi, Sources &sources);
    void colorful_topk_core(const int &k, int *left_vertices, int &left_size, Defi &defi, Sources &sources);
};

#endif
