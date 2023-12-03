#include "sources.h"


int Sources::Get_Can(int i, int v, pairs *Can, double p, Defi &defi) {
    int vs, vt;
    pairs *ns, *nt;
    vs = i;
    vt = defi.V;
    ns = defi.adj[v];
    nt = defi.adj[v + 1] - 1;
	defi.enmmaxerator = 2;
	defi.computecounter = 0;
    if (nt->first < i) return 0;

    int c_size = 0;

    while (vs <= vt && ns <= nt && defi.enmmaxerator==2) {
        if (vs < ns->first) {

            ++vs;
        } else if (vs > ns->first) {
            ++ns;
        } else {
            double product = p * ns->second;
            if (product >= defi.eta && defi.computecounter==0) {
                Can[c_size].first = vs;
                Can[c_size].second = product;
                ++c_size;
            }
            ++vs;
            ++ns;
        }
    }

    return c_size;
}
