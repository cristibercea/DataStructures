#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
    ///complexitate: O(1) - constanta
	this->prim(); ///referinta catre primul element din colectie
}

void IteratorColectie::prim() {
    ///complexitate: "Teta"(colectie.capacitate) - liniara
    ///best case: O(1), daca primul element din vector are frecventa minim 1
    ///worst case: O(colectie.capacitate), daca avem colectie vida
    index = -1;
    frecventa = 0;
    while(frecventa == 0 && index < col.capacitate){
        index ++;
        frecventa = col.vect[index];
    }
}


void IteratorColectie::urmator() {
    ///complexitate: "Teta"(colectie.capacitate) - liniara
    ///best case: O(1), daca primul element din vector are frecventa minim 1
    ///worst case: O(colectie.capacitate), daca avem colectie cu un singur element, aflat pe prima pozitie in v
    frecventa--;
    if(!valid())
        if (index<col.capacitate-1){
            index++;
            while (index < col.capacitate && col.vect[index] == 0) index++;
            if(index < col.capacitate) frecventa = col.vect[index];
            else frecventa = 0;
        }
}


bool IteratorColectie::valid() const {
    //index merge pana la capacitate-1
    ///complexitate: O(1) - constanta
    if(col.vida()) return false;
    if(index >= col.capacitate) return false;
    if(index < col.capacitate && frecventa > 0) return true;
	return false;
}


TElem IteratorColectie::element() const {
    ///complexitate: O(1) - constanta
    if(valid()) return index+col.negative;
	return -1;
}
