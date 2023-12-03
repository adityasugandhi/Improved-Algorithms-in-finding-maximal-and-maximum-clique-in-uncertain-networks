
#include "prunes.h"


int Prunes::DPcore(int * PV,Defi &defi)
{
	defi.temp_memory = 0;
	queue<int> Q;
	double *d1, *d2 , q, p = 0.0f;
	d1 = new double[defi.k_core + 1];
	d2 = new double[defi.k_core + 1];
	int double_size = sizeof(double);
	defi.temp_memory += double_size * (defi.k_core + 1) * 2;

	for (int i = 0, k; i <= defi.V; ++i)
	{
		//cout << "ver " << i << endl;
		k = is_k_core_or_not(i, d1, d2,defi);
		if (k == 0)
			Q.emplace(i);
		PV[i] = k;
		/*if (i > 10)
		return 0;*/
	}
	delete[] d1;
	delete[] d2;

	int u = 0, v = 0, counts = 0;
	pairs *s, *t;
	while (!Q.empty())
	{
		u = Q.front(); Q.pop();
		s = defi.adj[u];
		t = defi.adj[u + 1];
		while (s < t)
		{
			v = (*s).first;
			if (PV[v] != 0)
			{
				p = (*s).second;
				defi.eff_pro[v][0] /= (1.0f - p);
				q = defi.eff_pro[v][0];
				for (int j = 1; j < defi.k_core; ++j)
				{
					defi.eff_pro[v][j] = (defi.eff_pro[v][j] - p * defi.eff_pro[v][j - 1]) / (1.0f - p);
					q += defi.eff_pro[v][j];
				}
				if (q > 1 - defi.eta)
				{
					Q.emplace(v);
					PV[v] = 0;
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
			*x++ = i;
	}
	cout << "Prune1: the left nodes " << defi.V + 1 - counts << endl;
	
	if (defi.max_temp_memory < defi.temp_memory)
		defi.max_temp_memory = defi.temp_memory;
	return defi.V + 1 - counts;
};
