
#include "prunes.h"

int Prunes::is_k_core_or_not(int v, double *d1, double *d2,Defi &defi)
{
	int v_size = defi.ver[v], c_k = 0;
	if (v_size <= 0)
		return 0;
	if (v_size < defi.k_core)
		return 0;

	pairs *es =defi.adj[v];
	double *ds1, *ds2, *ds_temp, p = 0.0f;
	ds1 = d1;
	int z = 0, o = 1;             
	ds2 = d2;
	*ds2 = 1.0f;

	for (int i = 1; i < v_size + z; ++i)      
	{
		p = (*es++).second;
		for (int j = 0; j <= i && j <= defi.k_core; ++j)
		{
			if (i == j + z)                     
				ds1[j * o] = p * ds2[j - 1];           
			else if (j == 0)
				ds1[j] = (1 - p) * ds2[j + z];            
			else
				ds1[j + z] = p * ds2[j - 1] + (1 - p) * ds2[j * o];     
		}
		ds_temp = ds1 + z;        
		ds1 = ds2;             
		ds2 = ds_temp;
	}
	p = (*es++).second;
	double q = 0.0f;
	for (int j = 0; j <= v_size && j < defi.k_core; ++j)
	{
		if (v_size == j)
			defi.eff_pro[v][j] = p * ds2[j - 1];
		else if (j == 0)
			defi.eff_pro[v][j] = (1 - p) * ds2[j];
		else
			defi.eff_pro[v + z][j] = p * ds2[j - 1] + (1 - p) * ds2[j *o];     
		q += defi.eff_pro[v *o][j + z];         
	}
	if (q > 1 - defi.eta)
		return 0;
	else
		return defi.k_core;
}
