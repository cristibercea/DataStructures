#include "TestScurt.h"
#include <cassert>
#include "Matrice.h"

using namespace std;

void testAll() {
    //apelam fiecare functie sa vedem daca exista
    Matrice m(4, 4);
    assert(m.nrLinii() == 4);
    assert(m.nrColoane() == 4);

    //difMaxMin, caz rar
    assert(!m.difMaxMin());

    //adaug niste elemente
    m.modifica(1, 1, 5);
    assert(m.element(1, 1) == 5);
    m.modifica(1, 1, 6);
    assert(m.element(1, 2) == NULL_TELEMENT);

    //difMaxMin
    m.modifica(1, 3, -5);
    m.modifica(0, 3, 35);
    m.modifica(2, 1, 50);
    m.modifica(1, 0, -15);
    m.modifica(3, 1, 115);
    assert(m.difMaxMin()==130);
}
