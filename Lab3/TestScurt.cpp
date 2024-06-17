#include <cassert>
#include <exception>

#include "TestScurt.h"
#include "LI.h"
#include "IteratorLI.h"




void testAll() {
    LI lista = LI();
    assert(lista.vida());
    lista.adaugaSfarsit(1);
    assert(lista.dim() == 1);
    lista.adauga(0,2);
    assert(lista.dim() == 2);
    IteratorLI it = lista.iterator();
    assert(it.valid());
    it.urmator();
    assert(it.element() == 1);
    it.prim();
    assert(it.element() == 2);
    assert(lista.cauta(1) == 1);
    assert(lista.modifica(1,3) == 1);
    assert(lista.element(1) == 3);
    assert(lista.sterge(0) == 2);
    assert(lista.dim() == 1);

    //sterge tot
    LI lista1 = LI();
    LI lista2 = LI();
    for (int i = 0; i < 10; i ++){
        lista1.adaugaSfarsit(i);
        lista2.adaugaSfarsit(i+1);
    }
    assert(lista1.eliminaToate(lista2) == 9);
    assert(lista1.dim() == 1);
    lista1.sterge(0);
    try{
        lista1.eliminaToate(lista2);
        assert(false);
    }catch (std::exception&){}
}
