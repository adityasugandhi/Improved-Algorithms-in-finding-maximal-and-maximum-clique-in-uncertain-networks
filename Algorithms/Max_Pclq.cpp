#include "Algorithms.h"


void Algorithms::Max_Pclq(Defi &defi,Sources &sources)
{
	//Order();
	int c_size;
	bool found = false;
	int *R = new int[defi.max_nei_nums];
	memset(R, 0, sizeof(int) * defi.max_nei_nums);
	if (defi.omega == NULL)
		defi.omega = new int[defi.V + 1];
	memset(defi.omega, 0, sizeof(int) * (defi.V + 1));
	double p = 1.0f;
	pairs * Can = new pairs[defi.max_nei_nums];
	defi.max_memory = 0;
	defi.max_temp_memory = 0;
	defi.max_memory += (sizeof(pairs) * (defi.max_nei_nums) * 2 + sizeof(int) * (defi.V+1));
	for (int i = defi.V; i >= 0; --i)
	{
		found = false;
		c_size = sources.Get_Can(i, i, Can, 1.0,defi);
		*R = i;
		defi.temp_memory = 0;
		//cout << "Max_Pclq " << i << endl;
		sources.search(Can, c_size, R, 1, p ,found,defi);
		defi.omega[i] = defi.MAX_SIZE;
	}
	delete[] Can;
	delete[] R;
}
