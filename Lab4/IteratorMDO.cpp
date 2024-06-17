#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO &d) : dict(d) {
    ///complexitate: Teta(n^2)
    parcurgIndiciChei = 0;
    vectIndexCurent = 0;
    TDCurent = 0;
    nrIndici = 0;

    for (int i = 0; i < dict.m; i++)
        if (dict.TD[i].cheie != NIL)
            nrIndici++;
    if (nrIndici == 0) return;
    int count = 0;
    indiciChei = new int[nrIndici];
    for (int i = 0; i < dict.m; i++)
        if (dict.TD[i].cheie != NIL)
            indiciChei[count] = i, count++;
    sortareIndiciChei();
    prim();
}

void IteratorMDO::prim() {
    ///complexitate: Teta(1)
    if (nrIndici == 0) return;
    parcurgIndiciChei = 0;
    vectIndexCurent = 0;
    TDCurent = indiciChei[parcurgIndiciChei];
    parcurgIndiciChei++;
}

void IteratorMDO::urmator() {
    ///complexitate: Teta(1)
    if (!valid()) throw std::exception(); ///accesam chei inexistente
    vectIndexCurent++;
    if (!valid()) { ///accesam valori inexiestente pt cheia curenta, deci schimbam cheia
        vectIndexCurent = 0;
        if(parcurgIndiciChei>=nrIndici) {TDCurent=dict.m; return;}
        TDCurent = indiciChei[parcurgIndiciChei];
        parcurgIndiciChei++;
    }
}

bool IteratorMDO::valid() const {
    ///complexitate: Teta(1)
    if (TDCurent >= dict.m || vectIndexCurent >= dict.TD[TDCurent].valori.size()) return false;
    return true;
}

TElem IteratorMDO::element() const {
    ///complexitate: Teta(1)
    if (valid()) return pair<TCheie, TValoare>{dict.TD[TDCurent].cheie, dict.TD[TDCurent].valori[vectIndexCurent]};
    throw std::exception();
}

void IteratorMDO::sortareIndiciChei() {
    ///complexitate: Teta(n^2)
    for (int i = 0; i < nrIndici - 1; i++)
        for (int j = i + 1; j < nrIndici; j++)
            if (!dict.rel(dict.TD[indiciChei[i]].cheie, dict.TD[indiciChei[j]].cheie))
                swap(indiciChei[i], indiciChei[j]);
}

IteratorMDO::~IteratorMDO() { delete[] indiciChei; }


