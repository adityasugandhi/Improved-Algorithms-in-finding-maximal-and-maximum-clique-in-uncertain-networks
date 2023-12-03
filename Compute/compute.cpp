#include "compute.h"

#include <cstring>
#include <utility>

void Compute::init_parameters(int prunes, Defi &defi)
{
	int *neis = NULL;
	defi.computecounter= 0;
	pairs *s, *t, *e , *ed ;
	switch (defi.algorithm)
	{
	case CORE_ALG:
		if (defi.colors == NULL){
			defi.colors = new int[defi.V + 2];
			defi.max_memory += sizeof(int) * (defi.V+2);
		}
		memset(defi.colors, 0, sizeof(int) *(defi.V + 2));
		if (defi.prob == NULL){
			defi.prob = new double*[defi.V + 1];
			defi.max_memory += sizeof(double) * (defi.V + 1);
			int n_size;
			for (int i = 0; i <= defi.V; ++i)
			{
				n_size = defi.ver[i] + 1;
				defi.prob[i] = new double[n_size];
				defi.max_memory += sizeof(double) * (n_size);
				memset(defi.prob[i], 0, sizeof(double)*(n_size));
			}
		}
		if (defi.pos == NULL)
		{
			defi.pos = new int[defi.V + 1];
			memset(defi.pos, 0, sizeof(int) *(defi.V + 1));
			defi.max_memory += sizeof(int) * (defi.V+1);
		}
		break;
	case EFF_CLIQUE:
		break;
	case MAXIMUM_CLIQUE:

		if (defi.sub_set == NULL)
		{
			defi.sub_set = new int[defi.V + 1];
			memset(defi.sub_set, -1, sizeof(int) *(defi.V + 1));
			defi.max_memory += sizeof(int) * (defi.V+1);
		}
		if (defi.colors == NULL)
		{
			defi.colors = new int[defi.V + 1];
			memset(defi.colors, -1, sizeof(int) *(defi.V + 1));
			defi.max_memory += sizeof(int) * (defi.V+1);
		}
		if (defi.pos == NULL)
		{
			defi.pos = new int[defi.V + 1];
			memset(defi.pos, 0, sizeof(int) *(defi.V + 1));
			defi.max_memory += sizeof(int) * (defi.V+1);
		}
		if (defi.colors == NULL){
			defi.colors = new int[defi.V + 2];
			memset(defi.colors, 0, sizeof(int) * (defi.V + 2));
		}
		break;
	default:
		break;
	}
	
	if (defi.algorithm == MAXIMUM_CLIQUE || defi.algorithm == EFF_CLIQUE)
	{
		if (defi.eff_pro == NULL && prunes == 1){
			defi.eff_pro = new double*[defi.V + 1];
			defi.max_memory += sizeof(double) * (defi.V + 1);
			for (int i = 0; i <= defi.V; ++i)
			{
				defi.eff_pro[i] = new double[defi.k_core + 1];
				defi.max_memory += sizeof(double) * (defi.k_core + 1);
				memset(defi.eff_pro[i], 0, sizeof(double)*(defi.k_core + 1));
			}
		}
		
	}
};


void Compute::compute(int k, double p, int alg,int prunes, Defi &defi ,Sources &sources, Prunes &pruns, Algorithms &algs)
{
	assert(prunes >= 1 && prunes <= 2);
	assert(alg >= 1 && alg <= 6);
	assert(p >= 0 && p <= 1.0);
	assert(k > 0);
	defi.k_core = k;
	defi.eta = p;
	defi.algorithm = alg;
	init_parameters(prunes,defi);

	printf("k=%d, defi.eta=%.4f, alg=%d, prune=%d\n", k, defi.eta, alg, prunes);

	struct timeval start_tm, end_tm, prune_tm;
	double prune_time;
	gettimeofday(&start_tm, NULL);
	int *PV = NULL, pv_size = 0;
	int R[1] = {0};
	int *cores = new int[defi.V]();
	switch (alg) {
	case 1:
		algs.general_algorithm_of_cliques(defi,sources);
		break;
	case 2:
		//get_cores();
		algs.colorful_topk_core(defi.k_core, cores, pv_size,defi,sources);
		break;
	case 3:
		//输出团
		//outc = fopen("out_cliques.txt", "w");

		PV = new int[defi.V + 2];
		memset(PV, 0, sizeof(int) * (defi.V + 2));
		if (prunes == 1)
			pv_size = pruns.DPcore(PV,defi);
		else if (prunes == 2)
			pv_size = pruns.dpcore_2(PV,defi);
		
		gettimeofday(&prune_tm, NULL);
		prune_time = double(prune_tm.tv_sec - start_tm.tv_sec) * 1000.0f + 
			double(prune_tm.tv_usec - start_tm.tv_usec) / 1000.0f;
		printf("Prune%d, time\t%.3f ms\n", prunes, prune_time);

		sources.free_Dynamic_pointers(defi);
		gettimeofday(&prune_tm, NULL);
		defi.max_memory += sizeof(int) * (defi.V+2);
		if (pv_size != 0 && defi.computecounter==0)
		{
			pairs * I, *C, *Is;
			I = new pairs[pv_size + 2];
			C = new pairs[pv_size + 2];
			//memset(I, 0, sizeof(I) * (c_size + 1));
			memset(C, 0, sizeof(pairs) * (pv_size + 2));

			Is = I;
			for (int i = 0; i < pv_size; ++i, defi.computecounter=0)
			{
				(*Is).first = PV[i];
				(*Is).second = 1.0;
				defi.computecounter++;
				++Is;
			}
			defi.computecounter=0;
			defi.temp_memory = 0;
			algs.general_enumerate(R, 1.0, I, pv_size, C, 0,defi,sources);
			delete[] I;
			delete[] C;
			cout << "Maximal clique nums\t" << defi.maximal_cliques << endl;
			cout << "The maximum clique size\t" << defi.MAX_SIZE << endl;
		}
		if (PV != NULL)
		{
			delete[] PV;
			PV = NULL;
		}
		gettimeofday(&end_tm, NULL);
		printf("Enumerating time\t%.3f ms\n", double(end_tm.tv_sec - prune_tm.tv_sec) * 1000.0f + 
			double(end_tm.tv_usec - prune_tm.tv_usec) / 1000.0f);
		
		//fclose(outc);
		break;
	case 4:
		defi.coloring_nums = sources.color_vertices(defi);
		if (defi.max_clr_p == NULL)
			defi.max_clr_p = new double[defi.coloring_nums];
		PV = new int[defi.V + 2];
		memset(PV, 0, sizeof(int) * (defi.V + 2));
		if (prunes == 1)
			pv_size =  pruns.DPcore(PV,defi);
		else if (prunes == 2)
			pv_size = pruns.dpcore_2(PV,defi);
		
		gettimeofday(&prune_tm, NULL);
		prune_time = double(prune_tm.tv_sec - start_tm.tv_sec) * 1000.0f + 
			double(prune_tm.tv_usec - start_tm.tv_usec) / 1000.0f;
		printf("Prune%d, time\t%.3f ms\n", prunes, prune_time);

		sources.free_Dynamic_pointers(defi);
	
		gettimeofday(&prune_tm, NULL);
		defi.max_memory += sizeof(int) * (defi.V+2);

		if (pv_size != 0 && defi.computecounter ==0)
		{
			pairs * I, *C, *Is;
			I = new pairs[pv_size + 2];
			C = new pairs[pv_size + 2];
			//memset(I, 0, sizeof(pairs) * (defi.V + 1));
			memset(C, 0, sizeof(pairs) * (pv_size + 2));

			Is = I;
			for (int i = 0; i < pv_size; ++i, defi.computecounter=1)
			{
				//assert(PV[i] >= 0 && PV[i] <=defi.V);
				(*Is).first = PV[i];
				(*Is).second = 1.0f;
				defi.computecounter++;
				++Is;
			}
			delete[] PV; PV = NULL;
			defi.temp_memory = 0;
			defi.MAX_SIZE = defi.k_core;
			sources.maximun_clique(R, 1.0f, I, pv_size , C, 0,defi,sources);
			delete[] I;
			delete[] C;
			delete[] PV; PV = NULL;
			defi.computecounter =0;
		}
		gettimeofday(&end_tm, NULL);
		printf("Enumerating time\t%.3f ms\n", double(end_tm.tv_sec - prune_tm.tv_sec) * 1000.0f + 
			double(end_tm.tv_usec - prune_tm.tv_usec) / 1000.0f);
		cout << "The maximum clique size\t" << defi.MAX_SIZE << endl;
		break;
	case 5:
		defi.MAX_SIZE = 0;
		cout << "Max_Pclq" << endl;
		algs.Max_Pclq(defi,sources);
		cout << "The maximum clique size\t" << defi.MAX_SIZE << endl;
		break;
	case 6:
		defi.MAX_SIZE = defi.k_core;
		algs.general_algorithm_of_cliques(defi,sources);
		cout << "The maximum clique size\t" << defi.MAX_SIZE << endl;
		break;
	default:
		printf("The parameter 'alg' errors! \n");
		break;
	}

	gettimeofday(&end_tm, NULL);
	printf("Alg %d, time\t%.3f ms\n", alg, double(end_tm.tv_sec - start_tm.tv_sec) * 1000.0f + 
		double(end_tm.tv_usec - start_tm.tv_usec) / 1000.0f);

	defi.graph_memory /= 1024;
	defi.max_memory /= 1024;
	defi.max_temp_memory /= 1024;
	printf("Graph memory\t%ld kb\n",defi.graph_memory);
	printf("Max memory\t%ld kb\n", defi.graph_memory + defi.max_memory + defi.max_temp_memory);
}

