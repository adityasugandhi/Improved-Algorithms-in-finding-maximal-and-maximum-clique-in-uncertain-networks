#include "sources.h"

int myfunc(const void *a, const void *b)
{
	return int((*(double *)b - *(double *)a) * doube_deviation);
}
bool myfunc1(double &a, double &b)
{
	return a > b;
}

int Sources::count_colors(pairs *Can, int c_size, int *color_class,Defi &defi)
{
	if (c_size <= 0)
		return 0;
	int i, c, u, nums;
	i = 0; nums = 0;
	for (; i < c_size; ++i)
	{
		u = Can[i].first;
		c = defi.colors[u];
		if (color_class[c] == 0)
			++nums;
		++color_class[c];
	}
	return nums;
}

int Sources::provide_degrees(pairs * Can, int c_size, double q,Defi &defi)
{
	if (c_size <= 0)
		return 0;
	int derta = 0;
	memset(defi.max_clr_p, 0, sizeof(double) * (defi.coloring_nums));

	pairs *s, *t;
	s = Can;
	t = Can + c_size;
	int v, c, max_c;
	double p;
	max_c = 0;
	while (s < t)
	{
		v = (*s).first;
		c = defi.colors[v];
		p = (*s).second;
		if (defi.max_clr_p[c] < p)
			defi.max_clr_p[c] = p;
		if (max_c < c)
			max_c = c;
		++s;
	}
	sort(defi.max_clr_p, defi.max_clr_p + max_c + 1, myfunc1);
	p = q;
	for (int i = 0; i <= max_c; ++i)
	{
		p *= defi.max_clr_p[i];
		if (p < defi.eta)
			break;
		++derta;
	}
	return derta;
}

int Sources::require_degrees(int *R, double pr,int color_nums,int set_NO, int max_v,Defi &defi)
{
	int r_size = *R;
	if (r_size <= 0)
		return color_nums;
	double p = 1.0f;
	memset(defi.max_clr_p, 0, sizeof(double) * (color_nums));
	pairs *s, *t;
	int min = color_nums, max_c = -1;
	for (int i = 1, u, v, c, add_in; i <= r_size; ++i)
	{
		u = R[i];
		max_c = -1;
		s = defi.adj[u];
		t = defi.adj[u + 1];
		while (s < t)
		{
			v = (*s).first;
			if (v > max_v)
				break;
			if (defi.sub_set[v] == set_NO)
			{
				p = (*s).second;
				c = defi.colors[v];
				if (defi.max_clr_p[c] < p)
					defi.max_clr_p[c] = p;
				if (c > max_c)
					max_c = c;
			}
			++s;
		}
		++max_c;
		sort(defi.max_clr_p, defi.max_clr_p + (max_c), myfunc1);
		p = pr;
		add_in = max_c;
		for (int j = 0; j < max_c; ++j)
		{
			p *= defi.max_clr_p[j];
			if (p < defi.eta)
			{
				add_in = j;
				break;
			}
		}
		if (min > add_in)
			min = add_in;
		memset(defi.max_clr_p, 0, sizeof(double) * (max_c));
	}
	return min;
}

int Sources::probability_of_vR(double pr, pairs * Can, int size, int color_nums,Defi &defi)
{
	if (size <= 0)
		return 0;
	int u, c, max_c = -1;
	int check = -1;
	double p;
	memset(defi.max_clr_p, 0, sizeof(double) * (color_nums));
	if (check ==-1){
		pairs *s, *t;

		s = Can;
		t = Can + size;
		while ( s < t)
	{
		u = (*s).first;
		p = (*s).second;
		c = defi.colors[u];
		if (max_c < c)
			max_c = c;
		if (c >= color_nums || c < 0)
			cout << c << endl;
		++s;

		if (defi.max_clr_p[c] < p)
			defi.max_clr_p[c] = p;
	}
	
	}
	
	sort(defi.max_clr_p,defi. max_clr_p + (++max_c), myfunc1);
	int theta = max_c + 1;
	p = pr;
	for (int i = 0; i < max_c; ++i)
	{
		pr *= defi.max_clr_p[i];
		if (pr < defi.eta)
		{
			theta = i + 1;
			break;
		}
	}
	return theta;
}
