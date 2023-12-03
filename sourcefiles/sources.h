#pragma once
#ifndef SOURCES_H
#define SOURCES_H
#define pairs_sources pair<int, double>
#include <cstring>

#include "../defination.h"


 

class Sources {
public:
    void free_Dynamic_pointers(Defi &defi);
    void search(pairs *Can, int c_size, int *R, int r_size, double p, bool &found, Defi &defi);
    void vertices_sort(int *vertices, const int vt_size, Defi &defi);
    int build_Can(int v, pairs * Can, int st,int lt, double p, pairs * res,Defi &defi);
    int Get_Can(int i, int v, pairs * Can, double p,Defi &defi);
    int generateI(pairs * I, pairs * Is, int I_size, double q_n, int u, pairs * In,Defi &defi);
    int generateX(pairs * C, int C_size, double q_n, int u, pairs * Cn,Defi &defi);
    int color_vertices(Defi &defi);
    int color_verticeses(pairs * Can, int c_size, int set_NO,Defi &defi);
    int heuristic_clique(int *vertices, const int vt_size,Defi &defi);
    int count_colors(pairs *Can, int c_size, int *color_class,Defi &defi);
    int require_degrees(int *R, double pr,int color_nums,int set_NO, int max_v,Defi &defi);
    int provide_degrees(pairs * Can, int c_size, double q,Defi &defi);
    int probability_of_vR(double pr, pairs * Can, int size, int color_nums,Defi &defi);
    void maximun_clique(int *R, double q, pairs *I, int I_size, pairs *C, int C_size, Defi &defi, Sources &sources);
   
};
extern int myfunc(const void *a,const void *b);
extern bool myfunc1(double &a, double &b);
#endif // SOURCES_H
