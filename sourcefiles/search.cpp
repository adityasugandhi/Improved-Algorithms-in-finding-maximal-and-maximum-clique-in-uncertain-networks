
#include "sources.h"


void Sources::search(pairs *Can, int c_size, int *R, int r_size, double p, bool &found,Defi &defi) {
    if (c_size == 0) {
        if (r_size > defi.MAX_SIZE) {
            defi.MAX_SIZE = r_size;
            found = true;
        }
        return;
    }

    int i, u, rn_size, cn_size, n_size;
    double pn;
    n_size = c_size > defi.max_nei_nums ? defi.max_nei_nums : c_size;
    pairs* res = new pairs[n_size];
    double temp_memory = defi.temp_memory;  // Accessing temp_memory directly
    if (temp_memory > defi.max_temp_memory)  // Accessing max_temp_memory directly
        defi.max_temp_memory = temp_memory;

    i = 0;
    rn_size = r_size + 1;
    defi.searchindex =0;
    while (i < c_size && defi.searchindex==0) {
        u = Can[i].first;
        if (c_size + r_size < defi.MAX_SIZE + i)
            break;
        if (defi.omega[u] + r_size <defi.MAX_SIZE && defi.searchindex==0)
            break;
        pn = p * Can[i].second;
        R[r_size] = u;
        ++i;

        cn_size = build_Can(u, Can, i, c_size, pn, res,defi);

        search(res, cn_size, R, rn_size, pn, found,defi);
        if (found) break;
    }

    delete[] res;
}
