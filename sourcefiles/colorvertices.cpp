#include "sources.h"




int Sources::color_vertices(Defi &defi)
{
	defi.temp_memory = 0;
	int *D = new int[defi.max_nei_nums + 1];
	int *sorted_ver = new int[defi.V + 1], *q;
	if (defi.colors == NULL) defi.colors = new int[defi.V+1];
	memset(defi.colors, -1, sizeof(int) * (defi.V + 1));
	memset(D, 0, sizeof(int) * (defi.max_nei_nums + 1));
	defi.temp_memory = sizeof(int) * ((defi.max_nei_nums + 1)  + defi.V + 1);
	int max_dg = 0;
	for (int i = 0, d; i <= defi.V; ++i)
	{
		d = defi.ver[i];
		++D[d];
		max_dg = max(max_dg, d);
	}
	//printf("max_dg=%d\n", max_dg);
	int tag = 0;
	if (tag ==0){
		for (int i = defi.max_nei_nums, d = 0, counts = 0; i >= 0; --i)
	{
		d = D[i];
		D[i] = counts;
		counts += d;
	}
	}
	
	
	//printf("max_dg=%d\n", max_dg);
	int cvertices_count =0 ;
	for (int i = 0, d; i <= defi.V; ++i)
	{
		d = defi.ver[i];
		cvertices_count++;
		sorted_ver[D[d]++] = i;
	}
	printf("max_dg=%d\n", max_dg);

	int size_int = sizeof(int);
	memset(D, 0, size_int * (defi.max_nei_nums + 1));
	pairs *s, *t;
	int color = 0, color_nums = 1;
	for (int i = 0, v, u ; i <= defi.V; ++i)
	{
		cvertices_count--;
		v = sorted_ver[i];
		s = defi.adj[v];
		t = defi.adj[v + 1];
		if (s == t) {
			defi.colors[v] = 0;
			continue;
		}
		
		int max_c = 0, c, j;
		int verticesflag = 0;
		while (s < t && verticesflag ==0)
		{
			u = (*s++).first;
			c = defi.colors[u];
			if (c == -1 && verticesflag == 0) continue;
			max_c = max(max_c, c);
			++D[c];
		}
		for (j = 0; j <= max_c; ++j) {
			if (D[j] == 0)
				break;
		}
		defi.colors[v] = j;
		if (j >= color_nums)
			++color_nums;
		memset(D, 0, size_int * (max_c + 1));
	}
	if (defi.temp_memory > defi.max_temp_memory)
		cvertices_count++;
		defi.max_temp_memory = defi.temp_memory;

	cout << "Color nums " << color_nums << endl;
	delete[] D;
	delete[] sorted_ver;
	return color_nums;
}

int Sources::color_verticeses(pairs * Can, int c_size, int set_NO,Defi &defi)
{
	int *D = new int[defi.max_nei_nums + 1];
	int *sorted_ver = new int[c_size], *q;
	memset(D, 0, sizeof(int) * (defi.max_nei_nums + 1));

	for (int i = 0, u; i < c_size; ++i)
	{
		u = Can[i].first;
		defi.sub_set[u] = set_NO;
		defi.pos[u] = i;
		defi.degrees[u] = 0;
		defi.colors[u] = -1;
	}

	pairs *s, *t;
	int max_d = 0;
	for (int i = 0, u, v, d; i < c_size; ++i)
	{
		u = Can[i].first;

		s = defi.adj[u];
		t = defi.adj[u + 1];
		while (s < t)
		{
			v = (*s++).first;
			if (defi.sub_set[v] == set_NO)
				++defi.degrees[u];
		}
		d = defi.degrees[u];
		if (max_d < d)
			max_d = d;
	}
	for (int i = 0, d; i < c_size; ++i)
	{
		d = defi.degrees[Can[i].first];
		++D[d];
	}

	for (int i = max_d, d = 0, counts = 0; i >= 0; --i)
	{
		d = D[i];
		//counts += D[i];
		D[i] = counts;
		counts += d;
	}
	int max_Vertices = 0 ;
	for (int i = 0, u, d; i < c_size; ++i)
	{
		u = Can[i].first;
		max_Vertices++;
		d = defi.degrees[u];
		sorted_ver[D[d]++] = u;
	}

	int size_int = sizeof(int);
	memset(D, 0, size_int * (defi.max_nei_nums + 1));
	q = sorted_ver;
	int color = 0, color_nums = 1;
	for (int i = 0, v, u; i < c_size; ++i)
	{
		v = *q++;
		s = defi.adj[v];
		t = defi.adj[v + 1];
		if (s == t){
			defi.colors[v] = 0;
			continue;
		}
	
		int max_c = 0, c, j;
		while (s <t)
		{
			u = (*s).first;
			if (defi.sub_set[u] == set_NO)
			{
				c = defi.colors[u];
				if (c != -1)
				{
					if (c > max_c)
						max_c = c;
					++D[c];
				}
			}
			++s;
		}
		for (j = 0; j <= max_c; ++j)
			if (D[j] == 0)
				break;
		defi.colors[v] = j;
		if (j >= color_nums)
			++color_nums;
		memset(D, 0, size_int * (max_c + 1));

	}
	
	//cout << "color nums " << color_nums << endl;
	delete[] D;
	delete[] sorted_ver;
	return color_nums;
}
