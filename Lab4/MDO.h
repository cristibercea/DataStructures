#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;
#define NIL (-1) ///cheie Nula
#define CST (-2) ///Cheie STearsa

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
	friend class IteratorMDO;
    private:
    /* aici e reprezentarea */
    struct chei{
        TCheie cheie;
        vector<TValoare> valori; ///valorile asociate cheii
    };
    chei* TD; ///tabela de dispersie
    Relatie rel;
    int m; ///capacitate
    int n; ///numarul de valori din mdo

    ///functiile de dispersie
    [[nodiscard]] int d1(TCheie c) const;
    [[nodiscard]] int d2(TCheie c) const;
    [[nodiscard]] int d(TCheie c, int i) const;

    void redimensionare();
    int genereazaNrPrim();
    bool prim(int x);
    public:

	// constructorul implicit al MultiDictionarului Ordonat
	explicit MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	[[nodiscard]] vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	[[nodiscard]] int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	[[nodiscard]] bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	[[nodiscard]] IteratorMDO iterator() const;

    // se goleste mdo
    void goleste();

	// destructorul 	
	~MDO();

};
