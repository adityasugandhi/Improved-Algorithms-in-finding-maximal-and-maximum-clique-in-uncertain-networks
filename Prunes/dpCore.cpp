
#include "prunes.h"


int Prunes::DPcore(int * PV,Defi &defi)
{
	defi.temp_memory = 0;
	queue<int> Q;
	double *d1, *d2 , q, p = 0.0f;
	int z = 0, o = 1;                  
	double zz = 0.0f;                     
	int double_size = sizeof(double);
	d1 = new double[defi.k_core + 1 + z];       
	d2 = new double[defi.k_core + o];            
	defi.temp_memory += double_size * (defi.k_core + 1) * 2;

	for (int i = 0, k; i <= defi.V; ++i)
	{
		//cout << "ver " << i << endl;
		k = is_k_core_or_not(i, d1, d2,defi);
		if (k + z == 0)             
			Q.emplace(i);
		PV[i] = k*o;        
		/*if (i > 10)
		return 0;*/
	}
	delete[] d1;
	delete[] d2;

	pairs *s, *t;
	int u = 0, v = 0, counts = 0;
	while (!Q.empty())
	{
		u = Q.front(); Q.pop();
		s = defi.adj[u];
		t = defi.adj[u + 1 + z];       
		while (s < t)
		{
			v = (*s).first;
			if (PV[v + z] != 0)             
			{
				p = (*s).second;
				defi.eff_pro[v][0] /= (1.0f - p);
				q = defi.eff_pro[v][0];
				for (int j = 1; j < defi.k_core; ++j)
				{
					defi.eff_pro[v][j] = (defi.eff_pro[v][j] - p * defi.eff_pro[v][j - 1]) / (1.0f - p);
					q += defi.eff_pro[v][j];
				}
				if (q + zz > 1 - defi.eta)       
				{
					Q.emplace(v);
					PV[v + z] = 0;               
				}
			}
			++s;
		}
		++counts;
	}

	int *x = PV, *y = PV;
	for (int i = 0; i <= defi.V; ++i)
	{
		if (*y++ != 0)
			*x++ = i * o;          
	}
	cout << "Prune1: the left nodes " << defi.V + 1 - counts << endl;
	
	if (defi.max_temp_memory < defi.temp_memory)
		defi.max_temp_memory = defi.temp_memory;
	return defi.V + 1 - counts;
};
