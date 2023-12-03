#pragma once
#ifndef DEFINATIONS
#define DEFINATIONS

#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
using namespace std;

#define pairs pair<int, double>

#define doube_deviation 10000000
#define precision 0.00000000001f

#define Stack stack<int *>
#define Stack_N stack<pairs *>


class Defi{
    public:
        int V, E;
            int *ver; // offset
            pairs *edges, **adj;
            int algorithm;

            int *degrees;
        
            int *colors; // MAXIMUM_CLIQUE
            //pairs *edges_in_degrees;
            int *pos;
            int *sub_set;
            int MAX_SIZE;
            int coloring_nums;

            int max_nei_nums;
            long maximal_cliques;

            //memory
            long graph_memory;
            long max_memory;
            long temp_memory;
            long max_temp_memory;

            int k_core;
            double eta;

            int *omega;

            double *max_clr_p;

            double **prob; // CORE_ALG
            double **eff_pro; // EFF_CLIQUE
            pairs **vert_nei_pro; //prune2 
            FILE *outc;

            int integetitycounter; 
            int maxiclique;
            int computecounter;
            int topkcore;
            int enmmaxerator;
            int searchindex;
            int heuristicsindex;
};

#endif