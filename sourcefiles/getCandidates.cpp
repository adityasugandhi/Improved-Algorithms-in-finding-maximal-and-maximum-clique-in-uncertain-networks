#include "sources.h"


int Sources::Get_Can(int i, int v, pairs * Can, double p,Defi &defi)
{
	int vs, vt, c_size;
	pairs *ns, *nt;
	vs = i; vt = defi.V;
	ns = defi.adj[v];
	nt = defi.adj[v+1] - 1;
	if (nt->first < i) return 0;
	c_size = 0;
	while (vs <= vt && ns <= nt)
	{
		if (vs < ns->first)
			++vs;
		else if (vs > ns->first)
			++ns;
		else
		{
			if (p * ns->second >= defi.eta) {
				Can[c_size].first = vs;
				Can[c_size].second = p * ns->second;
				++c_size;
			}
			++vs; ++ns;
		}
	}
	return c_size;
}
