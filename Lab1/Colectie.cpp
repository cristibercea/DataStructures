#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>

using namespace std;


Colectie::Colectie() {
    ///complexitate: O(this->capacitate) - liniara
    this->vect = new TElem [100]; ///vector dinamic cu 100 de elem
    this->capacitate = 10;
    this->pozitive = 9;
    this->negative = 0;
    this->nr_elemente = 0;
    for(int i=0;i<this->capacitate; i++) this->vect[i]=0;
}


void Colectie::adauga(TElem elem) {
    ///complexitate: O(1) - constanta (complexitate amortizata)
    this->resize(elem);
    this->vect[elem-negative]++;
    this->nr_elemente++;
}


void Colectie::adaugaNElemente(TElem elem, int n){
    ///complexitate: O(n) - liniara
    for(int count=1;count<=n;count++)
        adauga(elem);
}


bool Colectie::sterge(TElem elem) {
    ///complexitate: O(1) - constanta
    if(elem>this->pozitive || elem<this->negative) return false;
    if(this->vect[elem-negative]!=0) {
        this->vect[elem-negative]--;
        this->nr_elemente--;
        return true;
    }
	return false;
}


bool Colectie::cauta(TElem elem) const {
    ///complexitate: O(1) - constanta
    if(elem>this->pozitive || elem<this->negative) return false;
	if(this->vect[elem-negative]==0) return false;
	return true;
}


int Colectie::nrAparitii(TElem elem) const {
    ///complexitate: O(1) - constanta
    if(elem>this->pozitive || elem<this->negative) return 0;
    return this->vect[elem-negative];
}


int Colectie::dim() const {
    ///complexitate: O(1) - constanta
    if(this->nr_elemente > 0) return this->nr_elemente;
	return 0;
}


bool Colectie::vida() const {
    ///complexitate: O(1) - constanta
	if(this->nr_elemente > 0) return false;
	return true;
}


IteratorColectie Colectie::iterator() const {
    ///complexitate: O(1) - constanta
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
    ///complexitate: O(1) - constanta
    delete[] this->vect;
}


void Colectie::resize(TElem elem){
    ///complexitate: O(colectie.capacitate) - liniara
    if(elem < this->negative) {
        this->capacitate = this->pozitive - elem + 1;
        TElem *vect_nou = new TElem[this->capacitate];

        int i=0;
        for (int j = 0; j < this->capacitate; j++)
            if (j < this->capacitate - this->pozitive + this->negative - 1) vect_nou[j] = 0;
            else {
                vect_nou[j] = this->vect[i];
                i++;
            }

        this->negative = elem;
        delete[] this->vect;
        this->vect = vect_nou;
    }
    if(elem > this->pozitive) {
        this->capacitate = elem - this->negative + 1;
        TElem *vect_nou = new TElem[this->capacitate];

        int i=0;
        for (int j = 0; j < this->capacitate; j++)
            if (j <= this->pozitive + (-1)*this->negative) {
                vect_nou[j] = this->vect[i];
                i++;
            }
            else vect_nou[j] = 0;

        this->pozitive = elem;
        delete[] this->vect;
        this->vect = vect_nou;
    }
}
