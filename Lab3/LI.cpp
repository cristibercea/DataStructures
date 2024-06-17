#include <exception>
#include "LI.h"
#include "IteratorLI.h"

LI::LI() {
    ///complexitate: Teta(capacitate)
    primLiber = -1;
    capacitate = 7;
    nr_elem = 0;
    urm = new int[capacitate];
    elemente = new TElem[capacitate];
    initSpatiuLiber();
    prim = -1;
}

int LI::dim() const {
    ///complexitate: Teta(1)
    if (nr_elem != 0) return nr_elem;
    return 0;
}

bool LI::vida() const {
    ///complexitate: Teta(1)
    if (dim() != 0) return false;
    return true;
}

TElem LI::element(int i) const {
    ///complexitate: Teta(n)
    if (i <= -1 || i >= nr_elem) throw std::exception();
    int aux = prim, c = 0;
    while (c != i) {
        c++;
        aux = urm[aux];
    }
    return elemente[aux];
}

TElem LI::modifica(int i, TElem e) {
    ///complexitate: Teta(n)
    TElem el;
    try { el = element(i); }
    catch (std::exception &) { throw std::exception(); }
    int aux = prim, c = 0;
    while (c != i) {
        c++;
        aux = urm[aux];
    }
    elemente[aux] = e;
    return el;
}

void LI::adaugaSfarsit(TElem e) {
    ///complexitate: Teta(n)
    nr_elem++;
    int nou = creeazaNod(e);
    if (prim == -1) { //caz: lista vida
        prim = nou;
        return;
    }
    //caz: lista nevida
    int ultim = prim;
    while (urm[ultim] != -1) ultim = urm[ultim];
    urm[ultim] = nou;
}

void LI::adauga(int i, TElem e) {
    ///complexitate: O(n)
    if (i <= -1 || i > nr_elem) throw std::exception();
    int nou = creeazaNod(e);
    if (prim == -1) { //caz: lista vida
        prim = nou;
        nr_elem++;
        return;
    }
    //caz: lista nevida
    if (i == nr_elem) { //adaugare la final
        int ultim = prim;
        while (urm[ultim] != -1) ultim = urm[ultim];
        urm[ultim] = nou;
    } else if (i == 0) { //adaugare la inceput
        urm[nou] = prim;
        prim = nou;
    } else {  //adaugare pe o pozitie mijlocie
        int aux = prim, c = 0, prev;
        while (c != i) {
            c++;
            prev = aux;
            aux = urm[aux];
        }
        urm[prev] = nou;
        urm[nou] = aux;
    }
    nr_elem++;
}

TElem LI::sterge(int i) {
    ///complexitate: O(n)
    if (i <= -1 || i >= nr_elem) throw std::exception();
    TElem el;
    if (i == 0) { //stergerea primului element
        el = elemente[prim];
        int next = urm[prim];
        dealoca(prim);
        prim = next;
    } else if (i == nr_elem - 1) { //stergerea ultimului element
        int ultim = prim, prev;
        while (urm[ultim] != -1) {
            prev = ultim;
            ultim = urm[ultim];
        }
        el = elemente[ultim];
        urm[prev] = -1;
        dealoca(ultim);
    } else { //stergerea unui element de pe pozitie mijlocie
        int aux = prim, c = 0, prev;
        while (c != i) {
            c++;
            prev = aux;
            aux = urm[aux];
        }
        el = elemente[aux];
        urm[prev] = urm[aux];
        dealoca(aux);
    }
    nr_elem--;
    return el;
}

int LI::cauta(TElem e) const {
    ///complexitate: O(n)
    int aux = prim, c = 0;
    while (aux != -1) {
        if (elemente[aux] == e) return c;
        aux = urm[aux];
        c++;
    }
    return -1;
}

IteratorLI LI::iterator() const {
    ///complexitate: Teta(1)
    return IteratorLI(*this);
}

LI::~LI() {
    ///complexitate: Teta(1)
    delete[] elemente;
    delete[] urm;
    prim = -1;
    primLiber = nr_elem = 0;
    capacitate = 7;
}

void LI::initSpatiuLiber() {
    ///complexitate: Teta(n)
    for (int i = 0; i < capacitate - 1; i++) urm[i] = i + 1;
    urm[capacitate - 1] = -1;
    primLiber = 0;
}

void LI::aloca(int &poz) {
    ///complexitate: Teta(1)
    poz = primLiber;
    primLiber = urm[primLiber];
}

void LI::dealoca(int &poz) {
    ///complexitate: Teta(1)
    urm[poz] = primLiber;
    primLiber = poz;
}

int LI::creeazaNod(const TElem &e) {
    ///complexitate: Teta(1) amortizat (redimensionarea e un caz rar)
    int i;
    if (primLiber == -1) redimensionare();
    aloca(i);
    elemente[i] = e;
    urm[i] = -1;
    return i;
}

void LI::redimensionare() {
    ///complexitate: Teta(n)
    auto elemente_nou = new TElem[capacitate * 2];
    int *urm_nou = new int[capacitate * 2];
    //copiere date
    for (int i = 0; i < capacitate; i++) {
        elemente_nou[i] = elemente[i];
        urm_nou[i] = urm[i];
    }
    //initializare spatiu liber nou
    for (int i = capacitate; i < capacitate * 2 - 1; i++) urm_nou[i] = i + 1;
    urm_nou[capacitate * 2 - 1] = -1;
    primLiber = capacitate;
    //redimensionarea listelor din container
    capacitate *= 2;
    delete[] elemente;
    delete[] urm;
    elemente = elemente_nou;
    urm = urm_nou;
}

int LI::eliminaToate(LI &l){
    ///complexitate: O(n^2)
    int nr_sterse = 0;
    if(vida() || l.vida()) throw std::exception();
    else{
        auto it1 = IteratorLI(l);
        it1.prim();
        while(it1.valid()){
            int j=prim;
            int poz=0;
            while(poz<nr_elem){
                auto aux= urm[j];
                if(it1.element() == element(poz)){
                    sterge(poz);
                    nr_sterse++;
                }
                j = aux;
                poz++;
            }
            if(nr_elem==0) return nr_sterse;
            it1.urmator();
        }
        return nr_sterse;
    }
}