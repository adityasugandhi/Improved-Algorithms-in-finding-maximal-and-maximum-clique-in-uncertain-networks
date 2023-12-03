#pragma once
#ifndef UNCERTAINCLIQUE
#define UNCERTAINCLIQUE

#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include "defination.h"
#include "Algorithms/Algorithms.h" 
#include "Prunes/prunes.h"
#include "sourcefiles/sources.h"
using namespace std;


#define pairs pair<int, double>

#define doube_deviation 10000000
#define precision 0.00000000001f

#define Stack stack<int *>
#define Stack_N stack<pairs *>


 // namespace std;
 class Uncertain_Clique
{
public:
	
	Uncertain_Clique(Defi &defi);
	~Uncertain_Clique();

	void read_graph(const char *str, Defi &defi);
	
	

	
};



#endif