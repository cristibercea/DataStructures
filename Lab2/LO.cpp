#include "Iterator.h"
#include "LO.h"
#include <exception>
using namespace std;

LO::LO(Relatie r) {
    ///complexitate: Teta(1)
    tail= head= nullptr;
    rel=r;
    nr_elemente=0;
}

// returnare dimensiune
int LO::dim() const {
    ///complexitate: Teta(1)
    if(nr_elemente>0) return nr_elemente;
	return 0;
}

// verifica daca LO e vida
bool LO::vida() const {
    ///complexitate: Teta(1)
    if(nr_elemente>0) return false;
	return true;
}

// prima pozitie din LO
Iterator LO::prim() const {
    ///complexitate: Teta(1)
	return Iterator{*this};
}

// returnare element de pe pozitia curenta
//arunca exceptie daca poz nu e valid
TElement LO::element(Iterator poz) {
    ///complexitate: Teta(1)
	if(poz.valid()) return poz.element();
    throw std::exception();
}

//sterge element de pe o pozitie poz si returneaza elementul sters
//dupa stergere poz e pozitionat pe elementul de dupa cel sters
//arunca exceptie daca poz nu e valid
TElement LO::sterge(Iterator& poz) {
	///complexitate: Teta(1)
    if(!poz.valid()) throw std::exception();
    nr_elemente--;
    TElement temp = poz.element();
    if(head==tail) { delete head; head = tail = nullptr; poz.curent = nullptr;}
    else {
        if (poz.curent == head) {///stergere de la inceput
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
            poz.curent = head;
        } else {
            if (poz.curent == tail) {///adaugare la final
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
                poz.curent = nullptr;
            } else {///adaugare in interior, inserare inaintea unui element
                nod* temp_nod=poz.curent->next;
                (poz.curent->prev)->next = poz.curent->next;
                (poz.curent->next)->prev = poz.curent->prev;
                delete poz.curent;
                poz.curent = temp_nod;
            }
        }
    }
    return temp;
}


// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
Iterator LO::cauta(TElement e) const{
    ///complexitate: O(n)
    Iterator it(*this);
    while (it.valid() && it.element()!=e) it.urmator();
    return it;
}

// adaugare element in LO
void LO::adauga(TElement e) {
    ///complexitate: O(n)
    nr_elemente++;
    nod* nou = creeazaNod();
    nou->info = e;
    if(head == nullptr) head=tail=nou;
    else{
        if(rel(e,head->info)){///adaugare la inceput
            head->prev=nou;
            nou->next=head;
            head = nou;
        }
        else{
            if(rel(tail->info,e)){///adaugare la final
                tail->next=nou;
                nou->prev=tail;
                tail = nou;
            }
            else{///adaugare in interior, inserare inaintea unui element
                nod* curent = head->next;
                while(curent != head && !rel(e, curent->info)) curent = curent->next;
                (curent->prev)->next=nou;
                nou->prev=curent->prev;
                nou->next=curent;
                curent->prev=nou;
            }
        }
    }
}

//destructor
LO::~LO() {
	///complexitate: Teta(n)
    nod* lista = head;
    while(lista != nullptr){
        nod* aux = lista->next;
        delete lista;
        lista = aux;
    }
}

LO::nod* LO::creeazaNod() {
    ///complexitate: Teta(1)
    nod* p = new nod;
    p->info = NULL_TELEMENT;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}
