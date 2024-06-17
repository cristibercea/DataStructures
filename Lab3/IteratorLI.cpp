#include "IteratorLI.h"
#include "LI.h"
#include <exception>

IteratorLI::IteratorLI(const LI &li) : lista(li) {
    ///complexitate: Teta(1)
    curent = lista.prim;
}

void IteratorLI::prim() {
    ///complexitate: Teta(1)
    curent = lista.prim;
}

void IteratorLI::urmator() {
    ///complexitate: Teta(1)
    if (!valid()) throw std::exception();
    curent = lista.urm[curent];
}

bool IteratorLI::valid() const {
    ///complexitate: Teta(1)
    return curent != -1;
}

TElem IteratorLI::element() const {
    ///complexitate: Teta(1)
    if (!valid()) throw std::exception();
    return lista.elemente[curent];
}
