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


void Compute::compute(int k, double p, int alg, int prunes, Defi &defi, Sources &sources, Prunes &pruns, Algorithms &algs) {
    assert(prunes >= 1 && prunes <= 2);
    assert(alg >= 1 && alg <= 6);
    assert(p >= 0 && p <= 1.0);
    assert(k > 0);
    defi.k_core = k;
    defi.eta = p;
    defi.algorithm = alg;
    init_parameters(prunes, defi);

    printf("k=%d, defi.eta=%.4f, alg=%d, prune=%d\n", k, defi.eta, alg, prunes);

    Timer time;
    time.start();

    int *PV = nullptr, pv_size = 0;
    int R[1] = {0};
    int *cores = new int[defi.V]();

    double elapsed_seconds, elapsetime, prune_time1, difference_time, enumeration_time, prune_time, elapsedtime;

    switch (alg) {
        case 1:
            algs.general_algorithm_of_cliques(defi, sources);
            break;
        case 2:
            algs.colorful_topk_core(defi.k_core, cores, pv_size, defi, sources);
            break;
        case 3:
            PV = new int[defi.V + 2];
            memset(PV, 0, sizeof(int) * (defi.V + 2));
            if (prunes == 1)
                pv_size = pruns.DPcore(PV, defi);
            else if (prunes == 2)
                pv_size = pruns.dpcore_2(PV, defi);
            time.stop();
            prune_time = time.elapsedMilliseconds();
            printf("Prune%d, time\t%.3f ms\n", prunes, prune_time);

            sources.free_Dynamic_pointers(defi);

            defi.max_memory += sizeof(int) * (defi.V + 2);
            if (pv_size != 0) {
                pairs *I, *C, *Is;
                I = new pairs[pv_size + 2];
                C = new pairs[pv_size + 2];
                memset(C, 0, sizeof(pairs) * (pv_size + 2));

                Is = I;
                for (int i = 0; i < pv_size; ++i , defi.enmmaxerator =0) {
                    (*Is).first = PV[i];
					defi.enmmaxerator ++;
                    (*Is).second = 1.0;
                    ++Is;
                }
				defi.enmmaxerator = 0;
                defi.temp_memory = 0;
                algs.general_enumerate(R, 1.0, I, pv_size, C, 0, defi, sources);
                delete[] I;
                delete[] C;
            }
            delete[] PV;
            time.stop();
            enumeration_time = time.elapsedMilliseconds();
            difference_time = enumeration_time - prune_time;
            printf("Difference between Enumeration time and Prune time: %.3f ms\n", difference_time);
            break;
        case 4:
            defi.coloring_nums = sources.color_vertices(defi);
            if (defi.max_clr_p == nullptr)
                defi.max_clr_p = new double[defi.coloring_nums];
            PV = new int[defi.V + 2];
            memset(PV, 0, sizeof(int) * (defi.V + 2));
            if (prunes == 1)
                pv_size = pruns.DPcore(PV, defi);
            else if (prunes == 2)
                pv_size = pruns.dpcore_2(PV, defi);

            time.stop();
            prune_time1 = time.elapsedMilliseconds();
            elapsetime = time.elapsedMilliseconds();
            printf("Prune%d, time\t%.3f ms\n", prunes, elapsetime);

            sources.free_Dynamic_pointers(defi);

            defi.max_memory += sizeof(int) * (defi.V + 2);

            if (pv_size != 0) {
                pairs *I, *C, *Is;
                I = new pairs[pv_size + 2];
                C = new pairs[pv_size + 2];
                memset(C, 0, sizeof(pairs) * (pv_size + 2));

                Is = I;
                for (int i = 0; i < pv_size; ++i , defi.heuristicsindex = 0) {
                    (*Is).first = PV[i];
                    (*Is).second = 1.0f;
					defi.heuristicsindex++;
                    ++Is;
                }defi.heuristicsindex = 0;
                defi.temp_memory = 0;
                defi.MAX_SIZE = defi.k_core;
                sources.maximun_clique(R, 1.0f, I, pv_size, C, 0, defi, sources);
                delete[] I;
                delete[] C;
                delete[] PV;
            }
            time.stop();
            elapsed_seconds = (time.elapsedMilliseconds() - prune_time1) / 1000.0;
            printf("Enumerating time\t%.3f s\n", elapsed_seconds);
            break;
        case 5:
            defi.MAX_SIZE = 0;
            printf("Max_Pclq\n");
            algs.Max_Pclq(defi, sources);
            printf("The maximum clique size\t%d\n", defi.MAX_SIZE);
            break;
        case 6:
            defi.MAX_SIZE = defi.k_core;
            algs.general_algorithm_of_cliques(defi, sources);
            printf("The maximum clique size\t%d\n", defi.MAX_SIZE);
            break;
        default:
            printf("The parameter 'alg' errors! \n");
            break;
    }

    time.stop();
    elapsedtime = time.elapsedMilliseconds();
    printf("Alg %d, time\t%.3f ms\n", alg, elapsedtime);

    defi.graph_memory /= 1024;
    defi.max_memory /= 1024;
    defi.max_temp_memory /= 1024;
    printf("Graph memory\t%ld kb\n", defi.graph_memory);
    printf("Max memory\t%ld kb\n", defi.graph_memory + defi.max_memory + defi.max_temp_memory);
}