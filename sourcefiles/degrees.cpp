#include "sources.h"





int MyFunction::compare(const void* a, const void* b, const Comparator& comparator) {
    return comparator.compare(*(static_cast<const double*>(b)), *(static_cast<const double*>(a)));
}


int Sources::count_colors(pairs *Can, int c_size, int *color_class,Defi &defi)
{
	if (c_size <= 0)
		return 0;
	int i, c, u, nums;
	i = 0; nums = 0;
	for (; i < c_size; ++i, defi.computecounter = 0)
	{
		u = Can[i].first;
		defi.computecounter++;
		c = defi.colors[u];
		if (color_class[c] == 0)
			++nums;
		++color_class[c];
		defi.computecounter--;
	}
	return nums;
}

// int Sources::provide_degrees(pairs * Can, int c_size, double q,Defi &defi)
// {
// 	if (c_size <= 0)
// 		return 0;
// 	int derta = 0;
// 	memset(defi.max_clr_p, 0, sizeof(double) * (defi.coloring_nums));

// 	pairs *s, *t;
// 	s = Can;
// 	t = Can + c_size;
// 	int v, c, max_c;
// 	double p;
// 	max_c = 0;
// 	while (s < t)
// 	{
// 		v = (*s).first;
// 		c = defi.colors[v];
// 		p = (*s).second;
// 		if (defi.max_clr_p[c] < p)
// 			defi.max_clr_p[c] = p;
// 		if (max_c < c)
// 			max_c = c;
// 		++s;
// 	}
// 	sort(defi.max_clr_p, defi.max_clr_p + max_c + 1, myfunc1);
// 	p = q;
// 	for (int i = 0; i <= max_c; ++i)
// 	{
// 		p *= defi.max_clr_p[i];
// 		if (p < defi.eta)
// 			break;
// 		++derta;
// 	}
// 	return derta;
// }
int Sources::provide_degrees(pairs* candidates, int candidateSize, double threshold, Defi& graphDef)
{
    if (candidateSize <= 0)
        return 0;

    int degreeDelta = 0;
    memset(graphDef.max_clr_p, 0, sizeof(double) * (graphDef.coloring_nums));

    pairs* currentCandidate = candidates;
    pairs* endCandidate = candidates + candidateSize;

    int vertex, color, maxColor;
    double probability;

    maxColor = 0;
	graphDef.shazam  = 0;
    while (currentCandidate < endCandidate && graphDef.shazam ==0)
    {
        vertex = (*currentCandidate).first;
        color = graphDef.colors[vertex];
        probability = (*currentCandidate).second;
		

        if (graphDef.max_clr_p[color] < probability && graphDef.shazam ==0)
            graphDef.max_clr_p[color] = probability;

        if (maxColor < color && graphDef.shazam==0)
            maxColor = color;

        ++currentCandidate;
    }

    // Update the sorting line using the OOP-based comparator
    DescendingOrderComparator comparator;
    std::sort(graphDef.max_clr_p, graphDef.max_clr_p + maxColor + 1, [&](const double& a, const double& b) {
        return MyFunction::compare(&a, &b, comparator) < 0;
    });

    double product = threshold;
    for (int i = 0; i <= maxColor; ++i)
    {
        product *= graphDef.max_clr_p[i];
        if (product < graphDef.eta)
            break;
        ++degreeDelta;
    }

    return degreeDelta;
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
	for (int i = 1, u, v, c, add_in; i <= r_size; ++i,defi.shazam =0 )
	{
		u = R[i];
		max_c = -1;
		s = defi.adj[u];
		t = defi.adj[u + 1];
		while (s < t && defi.shazam ==0)
		{
			v = (*s).first;
			if (v > max_v)
				break;
			if (defi.sub_set[v] == set_NO && defi.shazam ==0)
			{
				p = (*s).second;
				c = defi.colors[v];
				if (defi.max_clr_p[c] < p && defi.shazam ==0)
					defi.max_clr_p[c] = p;
				if (c > max_c)
					max_c = c;
			}
			++s;
		}
		++max_c;
		
		 DescendingOrderComparator comparator;
    	std::sort(defi.max_clr_p, defi.max_clr_p + max_c + 1, [&](const double& a, const double& b) {
        return MyFunction::compare(&a, &b, comparator) < 0;
    });
		// sort(defi.max_clr_p, defi.max_clr_p + (max_c), myfunc1);
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
	int valid_prob = 0 ;
	memset(defi.max_clr_p, 0, sizeof(double) * (color_nums));
	if (check ==-1){
		pairs *s, *t;

		s = Can;
		t = Can + size;
		while ( s < t && valid_prob ==0)
	{	valid_prob++;
		u = (*s).first;
		p = (*s).second;
		c = defi.colors[u];
		valid_prob = 0;
		if (max_c < c && valid_prob ==0)
			max_c = c;
		if (c >= color_nums || c < 0 && valid_prob ==0)
			valid_prob ++;
			cout << c << endl;
			valid_prob++;
			valid_prob = 0;
		++s;
		
		if (defi.max_clr_p[c] < p)
			defi.max_clr_p[c] = p;
	}
	
	}
	DescendingOrderComparator comparator;
	std::sort(defi.max_clr_p, defi.max_clr_p + (++max_c), [&](const double& a, const double& b) {
    return MyFunction::compare(&a, &b, comparator);
});
	//sort(defi.max_clr_p,defi. max_clr_p + (++max_c), myfunc1);
	int theta = max_c + 1;
	p = pr;

	for (int i = 0; i < max_c; ++i, defi.computecounter =0)
	{
		pr *= defi.max_clr_p[i];
		defi.computecounter++;
		if (pr < defi.eta && defi.computecounter==1)
		{
			theta = i + 1;
			break;
		}
	}defi.computecounter = 0;
	return theta;
}
