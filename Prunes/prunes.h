#pragma once
#ifndef PRUNES
#define PRUNES

#include "../uncertainclique.h"
#include "../defination.h"
#include <cstring>

using namespace std;
#define pairs pair<int, double>


class Prunes{
	public:
		int DPcore(int *C,Defi &defi);
		//int core_prune1(int *C);
		int is_k_core_or_not(int v, double *d1, double *d2,Defi &defi);
		// enhanced prune
		//int core_prune2(int *C);
		int dpcore_2(int *C,Defi &defi);
};
extern bool fun_v(pairs &a, pairs &b);

#endif
