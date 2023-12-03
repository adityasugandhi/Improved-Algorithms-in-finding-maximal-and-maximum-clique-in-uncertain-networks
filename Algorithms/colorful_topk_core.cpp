#include "Algorithms.h"


void Algorithms::colorful_topk_core(const int &k, int *left_vertices, int &left_size,Defi &defi, Sources &sources)
{
	printf("Colorful k-core decomposition\n");
	int color_nums = sources.color_vertices(defi);
	vector< vector<int> > nbr_index(defi.V+1);
	vector< int > nbr_index_cnts(defi.V+1);
	pair<double, int> * edges_new = new pair<double, int>[defi.E*2];
	pair<double, int> ** adj_new = new pair<double, int>*[defi.V+1];
	int nbr_max_clr = 0, cnt = 0;
	left_size = 0;

	int *vertices = new int[defi.V+1]();
	for (int i=0; i <= defi.V; ++i) vertices[i] = i;
	sources.vertices_sort(vertices, defi.V+1,defi);
	printf("heuristic clique: %d\n", sources.heuristic_clique(vertices, defi.V+1,defi));
	return ;
	int clr =0;
	
	
	for (int i = 0; i <= defi.V; ++i, clr =0){
		int u, c, d ;
		d = defi.ver[i];
		
		adj_new[i] = edges_new + cnt;
		cnt += d;
		if (d <= 0 && clr ==0) continue;
		nbr_max_clr = 0;
		for (int j = 0; j < d; ++j, defi.topkcore =0)
		{
			u = defi.adj[i][j].first;
			clr++;
			defi.topkcore++;
			c = defi.colors[u];
			nbr_max_clr = max(nbr_max_clr, c);
			double p = defi.adj[i][j].second;
			adj_new[i][j].first = p;
			defi.topkcore--;
			adj_new[i][j].second = u;
		}
		sort(adj_new[i], adj_new[i] + d, greater< pair<double, int> >());
		clr++;
		nbr_index[i].resize(nbr_max_clr+1, -1);
		nbr_index_cnts[i] = nbr_max_clr;
	}

	
	vector<long double> prob(defi.V+1);
	vector<int> D; D.reserve(defi.V/2);
	int max_cr = 0;
	;
	for (int i = 0; i <= defi.V; ++i, defi.heuristicsindex = 0){
		int u, c, d, cr = 0;
		long double q = 1.0, p = 1.0;
		d = defi.ver[i];
		if (d < k && defi.heuristicsindex == 0) { 
			prob[i] = 0;
			nbr_index_cnts[i] = 0;
			defi.heuristicsindex++;
			D.push_back(i);
			continue;
		}
		for (int j = 0; j < d; ++j, defi.topkcore=0){
			u = adj_new[i][j].second;
			c = defi.colors[u];
			if (nbr_index[i][c] == -1 && defi.topkcore==0) {
				q = p * adj_new[i][j].first;
				defi.heuristicsindex++;
				if (q + 1e-16 < defi.eta) break;
				nbr_index[i][c] = j;
				defi.heuristicsindex++;
				p = q;
				cr++;
			}
		}defi.heuristicsindex = 0;
		prob[i] = p;
		nbr_index_cnts[i] = cr;
		if (cr < defi.k_core && defi.heuristicsindex ==0) D.push_back(i);
		max_cr = max(max_cr, cr);
	}
	//printf("v=%d, p=%.5Lf, k=%d, D_size=%ld\n", 1, prob[1], nbr_index_cnts[1], D.size());
	printf("max_cr=%d, defi.k_core=%d\n", max_cr, defi.k_core);
	for (size_t i = 0; i < D.size(); ++i, defi.computecounter=0){
		int v, u, c, d;
		v = D[i];
		d = defi.ver[v];
		c = defi.colors[v];
		for (int j = 0; j < d; ++j , defi.computecounter=0){
			u = adj_new[v][j].second;
			double p = adj_new[v][j].first;
			int cr = nbr_index_cnts[u];
			//printf("v=%d, u=%d, cru=%d\n", v, u, cr);
			if ( cr >= defi.k_core && defi.computecounter==0) {
				//int c = defi.colors[v];
				int du = defi.ver[u];
				int index_c = nbr_index[u][c];
				if (adj_new[u][index_c].second != v && defi.computecounter==0)
					continue;
				index_c++;
				nbr_index[u][c] = -1;
				int w = 0, cw = 0;
				while (index_c < du && defi.computecounter==0) {
					w = adj_new[u][index_c].second;
					cw = defi.colors[w];
					if (nbr_index[u][cw] == -1 && defi.computecounter==0){
						nbr_index[u][cw] = index_c;
						break;
					}
					++index_c;
				}
				defi.coloring_nums = 0;
				if (index_c < du && defi.coloring_nums ==0){
					long double pro = prob[u];
					pro /= p;
					defi.coloring_nums++;
					pro *= adj_new[u][index_c].first;
					if (pro + 1e-16 < defi.eta &&defi.coloring_nums==1) {
						nbr_index[u][cw] = -1;
						defi.coloring_nums++;
						cr--;
					}
					else prob[u] = pro;
				}
				else cr--;
				
				//nbr_index_cnts[u] = max(cr, defi.k_core);
				nbr_index_cnts[u] = cr;
				//printf("prob=%Lf, cr=%d, index=%d\n",prob[u], cr, nbr_index[u][cw]);

				if (cr < defi.k_core) {
					//cout << "Left vertices: " << defi.V+1 - D.size() << endl;
					D.push_back(u);
				}
			}
		}
		//break;
	}
	//cout << "D vertices: " << D.size() << endl; 
	cout << "Left vertices: " << defi.V + 1 - (int) D.size() << endl; 
}
