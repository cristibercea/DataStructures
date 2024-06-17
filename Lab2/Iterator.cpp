#include "Iterator.h"
#include "LO.h"
#include <exception>

Iterator::Iterator(const LO& lo) : lo(lo){
    ///complexitate: Teta(1)
    curent = lo.head;
}

void Iterator::prim(){
    ///complexitate: Teta(1)
    curent = lo.head;
}

void Iterator::urmator(){
    ///complexitate: Teta(1)
    if(!valid()) throw std::exception();
    curent=curent->next;
}

void Iterator::anterior(){
    ///complexitate: Teta(1)
    if(!valid()) throw std::exception();
    curent=curent->prev;
}

bool Iterator::valid() const{
    ///complexitate: Teta(1)
    if(curent != nullptr) return true;
	return false;
}

TElement Iterator::element() const{
    ///complexitate: Teta(1)
    if(!valid()) throw std::exception();
    return curent->info;
}


