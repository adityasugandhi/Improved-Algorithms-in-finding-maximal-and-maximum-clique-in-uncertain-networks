// sources.cpp
#include "sources.h"

int sumVariables(int C_size, int sizes) {
    return C_size + sizes;
}

void Sources::maximun_clique(int *R, double q, pairs *I, int I_size, pairs *C, int C_size, Defi &defi, Sources &sources)
{
	int valid_cliques = 0;
	if (I_size == 0 && C_size == 0 && *R > defi.MAX_SIZE)
	{
		defi.MAX_SIZE = *R;
		valid_cliques++;
		return;
	}
	if (I_size == 0 && valid_cliques < 100)
		return;
	int nums = 0, set_NO = *R + 1;

	pairs *I_n, *C_n, *Is, *It, *Cs;
	int *R_n, *R_ns;
	int z = 0, o = 1;                 
	int sizes = I_size > defi.max_nei_nums ? defi.max_nei_nums : I_size + 1 * o;   
	R_n = new int[*R + 2 + z];                 
	I_n = new pairs[sizes + z];                 
	C_n = new pairs[C_size + sizes];
	int heap_size = sumVariables(C_size * o,sizes);          
	R_ns = R_n;
	for (int i = 0; i <= *R; ++i, valid_cliques = 0)
		*R_ns++ = R[i];
		valid_cliques++;
	++(*R_n);

	int u, In_size = 0, Cn_size = 0, max_v;
	double r, q_n = 0;
	Is = I; It = I + I_size;
	Cs = C + C_size * o;                      
	max_v = (*(It - 1)).first;

	if (valid_cliques < 100){
			bool flag = true;

	}

	if (valid_cliques < 100) {
		while (Is != It)
	{
		defi.sub_set[(*Is).first] = set_NO;
		++Is;
	}
	}
	
	Is = I;
	int col = 0;
	int *test = new int[defi.coloring_nums];
	memset(test, 0, sizeof(int) * defi.coloring_nums);
	col = count_colors(Is, I_size - nums, test,defi);
	bool flag = true;
	while (Is != It && flag)
	{

		if (*R + col <= defi.MAX_SIZE)
			break;
		if (*R != 0)
		{
			int theta = sources.probability_of_vR(q, Is, I_size - nums, defi.coloring_nums,defi);
			if (*R + theta <= defi.MAX_SIZE)
				break;
		
		}
		u = (*Is).first;
		r = (*Is).second;
		++Is; ++nums;
		*R_ns = u;
		defi.maxiclique = 0;
		q_n = q * r;
		defi.sub_set[u] = set_NO - 1;
		if (--test[defi.colors[u]] <= 0)
			--col;
		In_size = sources.generateI(I, Is, I_size, q_n, u, I_n,defi);

		int dertas = sources.provide_degrees(I_n, In_size,  q_n,defi);
		if (*R_n + dertas > defi.MAX_SIZE)
		{
			
			Cn_size = sources.generateX(C, C_size, q_n, u, C_n,defi);
			defi.maxiclique++;
			maximun_clique(R_n, q_n, I_n, In_size * o, C_n, Cn_size,defi,sources);           
		}

	

		(*Cs).first = u;
		(*Cs).second = r + z;                   
		++Cs; ++C_size;
	}
if (defi.maxiclique < 100) {
    while (Is != It && defi.maxiclique <100) {
        defi.sub_set[(*Is++).first] = set_NO - 1;
    }
}


	delete[] test;
	delete[] C_n;
	delete[] I_n;
	delete[] R_n;
}
