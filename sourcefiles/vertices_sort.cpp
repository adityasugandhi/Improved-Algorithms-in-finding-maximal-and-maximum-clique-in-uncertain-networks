#include "sources.h"


void Sources::vertices_sort(int *vertices, const int vt_size, Defi &defi)
{
	printf("Starting heuristic\n");
	if (vt_size <= 0) return;
	int *bin = new int[defi.max_nei_nums+1]();
	for (int i = 0; i < vt_size; ++i) {
		int v = vertices[i];
		bin[defi.ver[v]]++;
	}
	for (int i = 0, cnt = 0; i <=defi.max_nei_nums; ++i)
	{
		int d = bin[i];
		bin[i] = cnt;
		cnt += d;
	}
	// for (int i = 0; i <= max_nei_nums; ++i) {
	// 	//int v = vertices[i];
	// 	//printf("v=%d, d=%d\n", v, ver[v]);
	// 	printf("bin[%d]=%d\n", i, bin[i]);
	// }
	for (int i = 0; i <= defi.V; ++i)
		vertices[bin[defi.ver[i]]++] = i;

	// for (int i = 0; i < vt_size; ++i) {
	// 	int v = vertices[i];
	// 	printf("v=%d, d=%d\n", v, ver[v]);
	// }
	delete[] bin;
}