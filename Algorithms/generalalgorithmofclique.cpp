#include "Algorithms.h"



void Algorithms::general_algorithm_of_cliques(Defi &defi,Sources &sources )
{
	pairs * I, *C, *Is;
	I = new pairs[defi.V + 2];
	C = new pairs[defi.V + 2];
	//memset(I, 0, sizeof(pairs) * (defi.V + 1));
	memset(C, 0, sizeof(pairs) * (defi.V + 2));
	defi.max_memory += sizeof(pairs) * (defi.V + 2) * 2;
	defi.temp_memory = 0;

	Is = I;
	for (int i = 0; i <= defi.V; ++i)
	{
		(*Is).first = i;
		(*Is).second = 1.0f;
		++Is;
	}
	int R[1] = { 0 };
	if (defi.algorithm == 1)
		general_enumerate(R, 1.0f, I, defi.V + 1, C, 0,defi,sources);
	else if (defi.algorithm == 6)
		general_max_enumerate(R, 1.0f, I, defi.V + 1, C, 0,defi,sources);
	delete[] I;
	delete[] C;
	//defi.max_memory += max_temp_memory;
	//max_temp_memory = 0;
	defi.temp_memory = 0;
	if (defi.algorithm == 1){
		cout << "Maximal cliques\t" << defi.maximal_cliques << endl;
		cout << "Maximum clique\t" << defi.MAX_SIZE << endl;
		//cout << "max_temp_memory "<< max_temp_memory /1024 <<endl;
	}
	defi.max_temp_memory = 0;
}
