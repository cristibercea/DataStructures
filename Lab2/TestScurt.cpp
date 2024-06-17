#include <cassert>
#include <exception>
#include "LO.h"
#include "Iterator.h"

using namespace std;

bool relatie1(TElement cheie1, TElement cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	LO lo = LO(relatie1);
	assert(lo.dim() == 0);
	assert(lo.vida());
    lo.adauga(1);
    assert(lo.dim() == 1);
    assert(!lo.vida());
    Iterator itCauta = lo.cauta(1);
    assert(itCauta.valid());
    assert(itCauta.element() == 1);
    itCauta.urmator();
    assert(!itCauta.valid());
    itCauta.prim();
    assert(itCauta.valid());
    Iterator itPrim = lo.prim();
    assert(itPrim.valid());
    assert(itPrim.element() == 1);
    assert(lo.sterge(itCauta) == 1);
    assert(lo.dim() == 0);
    assert(lo.vida());

    //test iterator anterior
    for(int i=1;i<=10;i++)
        lo.adauga(i);
    assert(lo.dim() == 10);
    Iterator it = lo.prim();
    for(int i=1;i<=7;i++) {
        it.urmator();
        assert(it.valid());
    }
    for(int i=1;i<=9;i++)
        try{
            it.anterior();
        } catch (exception &e){}
    assert(!it.valid());
}

