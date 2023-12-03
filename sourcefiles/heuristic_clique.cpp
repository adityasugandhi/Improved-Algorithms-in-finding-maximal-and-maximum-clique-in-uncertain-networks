#include "sources.h"


int Sources::heuristic_clique(int *vertices, const int vt_size,Defi &defi)
{
	int max_clq = 0;
	int *visited = new int[defi.V+1]();
	int can_size = 0;
	for (int i = vt_size - 1; i >= 0; --i){
		int v = vertices[i];
		int d = defi.ver[v];
		int u, du, id, w, max_du = 0;
		int len = 1;
		can_size = d;
		if (d <= max_clq) continue;
		for (int j = 0; j < d; ++j){
			u = defi.adj[v][j].first;
			du = defi.ver[u];
			visited[u] = len;
			if (du > max_du){
				max_du = du;
				id = u;
			}
		}
		//printf("can size: %d\n", can_size);
		while (can_size > 0) {
			if (can_size + len <= max_clq) break;
			u = id;
			du = defi.ver[u];
			can_size = 0;
			max_du = 0;
			//printf("u=%d, d=%d, len=%d\n",u, du, len);
			for (int j = 0; j < du; ++j){
				w = defi.adj[u][j].first;
				if (visited[w] == len){
					visited[w] = len+1;
					int dw = defi.ver[w];
					if (dw > max_du){
						max_du = dw;
						id = w;
					}
					can_size++;
				}
			}
			//cout << "Iterator " << len << endl;
			//printf("can size: %d\n", can_size);
			len++;
			//if (len > 10)
			//	break;
		}
		for (int j = 0; j < d; ++j){
			w = defi.adj[v][j].first;
			du = defi.ver[w];
			visited[w] = 0;
		}
		max_clq = max(max_clq, len);
		//break;
	}
	return max_clq;
}