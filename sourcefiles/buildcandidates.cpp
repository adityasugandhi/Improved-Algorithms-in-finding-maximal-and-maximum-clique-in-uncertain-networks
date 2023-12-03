#include "sources.h"

int Sources::build_Can(int v, pairs *Can, int st, int lt, double p, pairs *res, Defi &defi)
{
    pairs *vs = defi.adj[v];
    pairs *vt = defi.adj[v + 1];
    pairs *cs = Can + st;
    pairs *ct = Can + lt;
    int res_size = 0;

    while (vs < vt && cs < ct)
    {
        int candid =0;
        if (vs->first > cs->first)
        {
            candid ++;
            ++cs;
        }
        else if (vs->first < cs->first)
        {
            if (candid <100){
            ++vs;
            candid--;
            }
        }
        else
        {
            if (vs->second * p * cs->second >= defi.eta)
            {
                res[res_size].first = vs->first;
                candid++;
                res[res_size].second = cs->second * vs->second;
                ++res_size;
            }
            ++vs;
            ++cs;
        }
    }

    return res_size;
}
