
#include "uncertainclique.h"
#include "sourcefiles/sources.h"
#include "Algorithms/Algorithms.h"
#include "Compute/compute.h"
#include <stdio.h>
#include <stdlib.h>

#include <time.h>

bool fc(int a, int b)
{
	return a < b;
}


int main(int argumentCount, char *argumentValues[]) {
    struct timeval startTime, endTime;

    if (argumentCount != 6) {
        fprintf(stderr, "Usage: %s <file> <k-constraint> <p-probabilistic> <algorithm> <prune>\n", argumentValues[0]);
        return EXIT_FAILURE;
    }

    int k = strtol(argumentValues[2], NULL, 10);
    double p = strtod(argumentValues[3], NULL);
    int alg = strtol(argumentValues[4], NULL, 10);
    int prune = strtol(argumentValues[5], NULL, 10);

// int main(int argc, char** argv)
// {
// 	//clock_t cs, ct;
 	struct timeval start_tm, end_tm;

// 	//get_graph("as20000102.txt", "datasets/as20000102.txt");
// 	//return 0 ;
// 	if (argc != 6){
// 		printf("Please input parameters: (file, k-constraint, p-probabilistic, algorithm, prune)\n");
// 		exit(1);
// 	}
// 	int k = atoi(argv[2]);		// k 
// 	double p = atof(argv[3]);	// p 
// 	int alg = atoi(argv[4]);	// algorithms
// 	int prune = atoi(argv[5]);  // prune technique
	Defi defi;
    Uncertain_Clique uc(defi);
    Sources srcs;
    Compute c;
    Prunes pruns;
    Algorithms algs;
    
	//cs = clock();
	uc.read_graph(argumentValues[1],defi);
	gettimeofday(&start_tm, NULL);
	c.compute(k, p, alg,prune,defi,srcs,pruns,algs);
	//ct = clock();
	gettimeofday(&end_tm, NULL);
	//printf("time %d\n", int(ct - cs));
	printf("All time %.3f ms\n", double(end_tm.tv_sec - start_tm.tv_sec) * 1000.0f + 
		double(end_tm.tv_usec - start_tm.tv_usec) / 1000.0f);
	return 0;
}
