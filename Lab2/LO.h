#pragma once

class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT {-1}

class LO {
private:
	friend class Iterator;
private:
    typedef struct nod{
        TElement info;
        nod* prev;
        nod* next;
    }nod;

    Relatie rel;
    nod* head;
    nod* tail;
    int nr_elemente;

    static nod* creeazaNod();

public:
		// constructor
		explicit LO (Relatie r);

		// returnare dimensiune
		[[nodiscard]] int dim() const;

		// verifica daca LO e vida
		[[nodiscard]] bool vida() const;

		// prima pozitie din LO
		[[nodiscard]] Iterator prim() const;

		// returnare element de pe pozitia curenta
		//arunca exceptie daca poz nu e valid
		[[nodiscard]] static TElement element(Iterator poz) ;

		// adaugare element in LO a.i. sa se pastreze ordinea intre elemente
		void adauga(TElement e);

		// sterge element de pe o pozitie poz si returneaza elementul sters
		//dupa stergere poz e pozitionat pe elementul de dupa cel sters
		//arunca exceptie daca poz nu e valid
		TElement sterge(Iterator& poz);

		// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
		[[nodiscard]] Iterator cauta(TElement e) const;

		//destructor
		~LO();

};