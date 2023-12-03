#include "sources.h"


void Sources::free_Dynamic_pointers(Defi &defi) {
    // Free the dynamic memory allocated in Uncertain_Clique

    // Free prob array
    if (defi.prob != nullptr) {
        for (int i = 0; i <= defi.V; ++i) {
            if (defi.prob[i] != nullptr) {
                delete[] defi.prob[i];
                defi.prob[i] = nullptr;
            }
        }
        delete[] defi.prob;
        defi.prob = nullptr;
    }

    // Free eff_pro array
    if (defi.eff_pro != nullptr) {
        for (int i = 0; i <= defi.V; ++i) {
            if (defi.eff_pro[i] != nullptr)
                delete[] defi.eff_pro[i];
        }
        delete[] defi.eff_pro;
        defi.eff_pro = nullptr;
    }

    // Free vert_nei_pro array
    if (defi.vert_nei_pro != nullptr) {
        for (int i = 0; i <= defi.V; ++i) {
            if (defi.vert_nei_pro[i] != nullptr)
                delete[] defi.vert_nei_pro[i];
        }
        delete[] defi.vert_nei_pro;
        defi.vert_nei_pro = nullptr;
    }

    // Add more memory deallocation as needed for other dynamic members in Uncertain_Clique
}
