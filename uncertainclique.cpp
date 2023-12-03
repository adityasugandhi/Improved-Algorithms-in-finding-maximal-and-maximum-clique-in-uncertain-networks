#include "uncertainclique.h"



Uncertain_Clique::Uncertain_Clique(Defi &defi)
{
	defi.V = 0; defi.E = 0;
	defi.algorithm = 0;

	defi.k_core = 0;
	defi.eta = 0;

	defi.graph_memory = 0;
	defi.max_memory = 0;
	defi.temp_memory = 0;
	defi.max_temp_memory = 0;

	defi.max_nei_nums = 0;
	defi.maximal_cliques = 0;
	defi.MAX_SIZE = 0;
	defi.coloring_nums = 0;

	defi.edges = NULL;
	defi.ver = NULL;
	defi.degrees = NULL;
	defi.adj = NULL;

	defi.prob = NULL;
	defi.eff_pro = NULL;
	defi.vert_nei_pro = NULL;

	defi.colors = NULL;
	defi.pos = NULL;
	defi.sub_set = NULL;

	defi.max_clr_p = NULL;
	defi.omega = NULL;

	defi.outc = NULL;
}
Uncertain_Clique::~Uncertain_Clique()
{
	printf("destruction\n");
}

void Uncertain_Clique::read_graph(const char *str, Defi &defi) {
    FILE *in = fopen(str, "r");

    if (in == NULL) {
        printf("No such the input file\n");
        exit(1);
    }

    printf("InFile: %s\n", str);

    if (fscanf(in, "%d %d", &defi.V, &defi.E) != 2)
        exit(1);

    assert(defi.V > 0);
    assert(defi.E > 0);

    int x, y, counts = 0;
    double p;

    defi.ver = new int[defi.V + 2];
    memset(defi.ver, 0, sizeof(int) * (defi.V + 2));

    defi.E = 0;

    while (fscanf(in, "%d %d %lf", &x, &y, &p) == 3) {
        assert(x <= defi.V && x >= 0);
        assert(y <= defi.V && y >= 0);
        assert(p > 0 && p <= 1);

        if (x >= y) continue;

        ++defi.ver[x];
        ++defi.ver[y];
        ++defi.E;

        if (feof(in)) break;
    }

    fclose(in);

    defi.graph_memory += (sizeof(pairs)) * defi.E * 2;
    defi.graph_memory += sizeof(int) * (defi.V + 1);

    counts = 0;

    if (defi.edges == nullptr) defi.edges = new pair<int, double>[defi.E * 2 + 1];
    if (defi.adj == nullptr) defi.adj = new pairs*[defi.V + 2];

    memset(defi.edges, 0, sizeof(pairs) * (defi.E * 2 + 1));

    for (int i = 0; i <= defi.V; ++i) {
        int d = defi.ver[i];
        defi.adj[i] = defi.edges + counts;
        counts += d;
        defi.ver[i] = 0;
        defi.max_nei_nums = std::max(defi.max_nei_nums, d);
    }

    defi.adj[defi.V + 1] = defi.adj[defi.V] + defi.ver[defi.V];

    in = fopen(str, "r");

    if (fscanf(in, "%d %d", &defi.V, &counts) != 2) exit(1);

    while (fscanf(in, "%d %d %lf", &x, &y, &p) == 3) {
        if (x >= y) continue;
        int id = defi.ver[x]++;
        defi.adj[x][id].first = y;
        defi.adj[x][id].second = p;

        id = defi.ver[y]++;
        defi.adj[y][id].first = x;
        defi.adj[y][id].second = p;

        if (feof(in)) break;
    }

    fclose(in);

    for (int i = 1; i <= defi.V; ++i) {
        assert(defi.ver[i] >= 0 && defi.ver[i] <= 2 * defi.E);
    }

    printf("V=%d, E=%d, max_deg=%d\n", defi.V, defi.E, defi.max_nei_nums);
}

// void Uncertain_Clique::init_parameters(int prunes, Defi &defi) {
//     int *neis = nullptr;
//     pairs *s, *t, *e, *ed;

//     switch (defi.algorithm) {
//         case CORE_ALG:
//             if (defi.degrees == nullptr) {
//                 defi.degrees = new int[defi.V + 2];
//                 defi.max_memory += sizeof(int) * (defi.V + 2);
//             }

//             memset(defi.degrees, 0, sizeof(int) * (defi.V + 2));

//             if (defi.prob == nullptr) {
//                 defi.prob = new double*[defi.V + 1];
//                 defi.max_memory += sizeof(double) * (defi.V + 1);

//                 int n_size;
//                 for (int i = 0; i <= defi.V; ++i) {
//                     n_size = defi.ver[i] + 1;
//                     defi.prob[i] = new double[n_size];
//                     defi.max_memory += sizeof(double) * (n_size);
//                     memset(defi.prob[i], 0, sizeof(double) * (n_size));
//                 }
//             }

//             if (defi.pos == nullptr) {
//                 defi.pos = new int[defi.V + 1];
//                 memset(defi.pos, 0, sizeof(int) * (defi.V + 1));
//                 defi.max_memory += sizeof(int) * (defi.V + 1);
//             }
//             break;

//         case EFF_CLIQUE:
//             break;

//         case MAXIMUM_CLIQUE:
//             if (defi.sub_set == nullptr) {
//                 defi.sub_set = new int[defi.V + 1];
//                 memset(defi.sub_set, -1, sizeof(int) * (defi.V + 1));
//                 defi.max_memory += sizeof(int) * (defi.V + 1);
//             }

//             if (defi.colors == nullptr) {
//                 defi.colors = new int[defi.V + 1];
//                 memset(defi.colors, -1, sizeof(int) * (defi.V + 1));
//                 defi.max_memory += sizeof(int) * (defi.V + 1);
//             }

//             if (defi.pos == nullptr) {
//                 defi.pos = new int[defi.V + 1];
//                 memset(defi.pos, 0, sizeof(int) * (defi.V + 1));
//                 defi.max_memory += sizeof(int) * (defi.V + 1);
//             }

//             if (defi.degrees == nullptr) {
//                 defi.degrees = new int[defi.V + 2];
//                 memset(defi.degrees, 0, sizeof(int) * (defi.V + 2));
//             }
//             break;

//         default:
//             break;
//     }

//     if (defi.algorithm == MAXIMUM_CLIQUE || defi.algorithm == EFF_CLIQUE) {
//         if (defi.eff_pro == nullptr && prunes == 1) {
//             defi.eff_pro = new double*[defi.V + 1];
//             defi.max_memory += sizeof(double) * (defi.V + 1);

//             for (int i = 0; i <= defi.V; ++i) {
//                 defi.eff_pro[i] = new double[defi.k_core + 1];
//                 defi.max_memory += sizeof(double) * (defi.k_core + 1);
//                 memset(defi.eff_pro[i], 0, sizeof(double) * (defi.k_core + 1));
//             }
//         }
//     }
// }

// void Uncertain_Clique::compute(int k, double p, int alg, int prunes, Defi &defi, Sources &sources, Prunes &pruns, Algorithms &algs) {
// 	sources.compute(k, p, alg, prunes, defi, sources, pruns, algs);
// }
