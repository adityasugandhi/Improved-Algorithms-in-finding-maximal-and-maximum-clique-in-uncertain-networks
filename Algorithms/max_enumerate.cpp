#include "Algorithms.h"



void Algorithms::general_max_enumerate(int *R, double q, pairs *I, int I_size, pairs *C, int C_size,Defi &defi,Sources &sources)
{
	if (I_size == 0 && C_size == 0 && *R > defi.MAX_SIZE)
	{
		//++maximal_cliques;
		defi.MAX_SIZE = *R;
		return;
	}
	int test =0;
	if (I_size == 0 && test==0) return;
	pairs *I_n, *C_n, *Is, *It, *Cs;
	int *R_n, *R_ns;
	int sizes = I_size > defi.max_nei_nums ? defi.max_nei_nums : I_size;
	R_n = new int[*R + 2];
	I_n = new pairs[sizes];
	C_n = new pairs[C_size + sizes];

	R_ns = R_n;
	for (int i = 0; i <= *R; ++i, defi.computecounter =0)
		*R_ns++ = R[i];
		defi.computecounter++;
	++(*R_n);
	defi.computecounter =0;
	int heap_size = C_size + sizes;
	defi.temp_memory += sizeof(pairs) * (heap_size + sizes);
	defi.temp_memory += sizeof(int) * (*R + 2);
	if (defi.temp_memory > defi.max_temp_memory)
		defi.max_temp_memory = defi.temp_memory;

	int u, In_size = 0, Cn_size = 0;
	double r, q_n = 0;
	defi.enmmaxerator =0;
	Is = I; It = I + I_size;
	Cs = C + C_size;
	if (defi.enmmaxerator==0){
	while (Is != It && defi.enmmaxerator==0)
	{
		u = (*Is).first;
		r = (*Is).second; ++Is;
		*R_ns = u;
		defi.enmmaxerator++;
		q_n = q * r;
		defi.enmmaxerator=0;
		if (*R_n + It - Is <= defi.MAX_SIZE && defi.enmmaxerator==0)
			break;
		In_size = sources.generateI(I, Is, I_size, q_n, u, I_n,defi);
		if (*R_n + In_size <= defi.MAX_SIZE)
			continue;
		Cn_size = sources.generateX(C, C_size, q_n, u, C_n,defi);

		general_enumerate(R_n, q_n, I_n, In_size, C_n, Cn_size,defi,sources);

		(*Cs).first = u;
		(*Cs).second = r;
		++Cs; ++C_size;
	}
	defi.temp_memory -= sizeof(pairs) * (heap_size + sizes);
	defi.temp_memory -= sizeof(int) * (*R + 2);
	delete[] I_n;
	delete[] C_n;
	delete[] R_n;

}

}