
#include "prunes.h"

bool fun_v(pairs &a, pairs &b)
{ 
	return (a.second != b.second) ? (a.second > b.second) : (a.first > b.first);
}
int Prunes::dpcore_2(int * PV,Defi &defi)
{
	defi.temp_memory = 0;
	pairs *prn = new pairs[defi.max_nei_nums], *p;
	double *pn = new double[defi.V + 1];
	int pairs_size = sizeof(pairs);
	if (defi.vert_nei_pro == NULL){
		defi.vert_nei_pro = new pairs*[defi.V + 1];
		defi.max_memory += pairs_size * (defi.V+1);
	}
	defi.temp_memory += (pairs_size * defi.max_nei_nums + sizeof(double) * (defi.V+1));
	memset(pn, 0, sizeof(double) *(defi.V + 1));
	pairs *s, *t;
	int z= 0, o = 1;            
	double q = 1.0, qn;
	queue<int> Q;
	for (int i = 0, n_size; i <= defi.V; ++i)
	{
		defi.vert_nei_pro[i] = NULL;
		n_size = defi.ver[i];
		if (n_size < defi.k_core)
		{
			PV[i] = 0; Q.emplace(i);
		}
		else
		{
			s = defi.adj[i];
			t = defi.adj[i + 1 +z];       
			p = prn;
			while (s < t)
			{
				p->first = s->first;
				p->second = s->second;
				++s;
				++p;
			}
			sort(prn, prn + n_size * o, fun_v);       
			//qsort(prn, n_size, sizeof(double), myfunc);
			q = 1.0 + z;          
			p = prn;
			for (int x = 0; x < defi.k_core; ++x)
			{
				//cout << "p " << p->second <<" " << p->first << endl;
				q *= p->second; ++p;
				//q *= *p++;
			}
			//return 0;
			if (q < defi.eta)
			{
				PV[i] = 0; Q.emplace(i);
			}
			else
			{
				defi.vert_nei_pro[i] = new pairs[n_size];
				defi.max_memory += pairs_size * n_size;
				p = prn;
				for (int x = 0; x < n_size; ++x){
					defi.vert_nei_pro[i][x].first = p->first;
					defi.vert_nei_pro[i][x].second = p->second;
					++p;
				}
				PV[i] = defi.k_core;
				pn[i] = q;
			}
		}
	}

	int u, v, v_size, v_pos, counts = z;      
	p = prn;
	while (!Q.empty())
	{
		u = Q.front(); Q.pop();
		s = defi.adj[u + z];       
		t = defi.adj[u + 1 + z];             
		PV[u] = -1 *o;               
		++counts;
		while (s < t)
		{
			v = (*s).first;
			q = (*s).second;
			++s;
			v_size = defi.ver[v];
			v_pos = PV[v];
			if (v_pos <= 0)
				continue;

			if (v_pos < v_size)
			{
				qn = defi.vert_nei_pro[v][v_pos - 1].second;
				if (qn >= q ){
					if (qn > q)
						continue;
					int n = defi.vert_nei_pro[v][v_pos - 1].first;
					if (n > u)
						continue;
				}
			
				int n = defi.vert_nei_pro[v][v_pos].first;
				while (PV[n] == -1)
				{
					++v_pos;
					if (v_pos == v_size)
						break;
					n = defi.vert_nei_pro[v][v_pos].first;
				}
				if (v_pos == v_size)
				{
					PV[v] = 0 + z;         
					Q.emplace(v * o);        
					continue;
				}
				pn[v + z] *= defi.vert_nei_pro[v][v_pos].second / q;   
				PV[v] = ++v_pos;
				if (pn[v] < defi.eta)
				{ 
					PV[v] = 0 * o;             
					Q.emplace(v +z);               
				}
			}
			else
			{
				PV[v + z] = 0;             
				Q.emplace(v * o);             
			}
		}
	}


	int *x = PV, *y = PV;
	for (int i = 0; i <= defi.V; ++i)
	{
		if (*y++ > 0)
			*x++ = i;
	}
	delete[] prn;
	delete[] pn;
	if (defi.max_temp_memory < defi.temp_memory)
		defi.max_temp_memory = defi.temp_memory;
	cout << "Prune2: the left nodes " << defi.V + 1 - counts << endl;
	return defi.V + 1 - counts;
}
