#pragma once

typedef int TElem;
class IteratorLI;

class LI {
private:
    friend class IteratorLI;

    /* aici e reprezentarea */
    int nr_elem, capacitate, prim,primLiber;
    TElem * elemente;
    int * urm;

    /*utilitare*/
    void initSpatiuLiber();
    void redimensionare();
    void aloca(int& poz);
    void dealoca(int& poz);
    int creeazaNod(const TElem& e);
public:
 		// constructor implicit
		LI ();
		
		// returnare dimensiune
		[[nodiscard]] int dim() const;

		// verifica daca lista e vida
		[[nodiscard]] bool vida() const;

		// returnare element
		//arunca exceptie daca i nu e valid
		TElem element(int i) const;

		// modifica element de pe pozitia i si returneaza vechea valoare
		//arunca exceptie daca i nu e valid
		TElem modifica(int i, TElem e);

		// adaugare element la sfarsit
		void adaugaSfarsit(TElem e);

		// adaugare element pe o pozitie i 
		//arunca exceptie daca i nu e valid
		void adauga(int i, TElem e);

		// sterge element de pe o pozitie i si returneaza elementul sters
		//arunca exceptie daca i nu e valid
		TElem sterge(int i);

		// cauta element si returneaza prima pozitie pe care apare (sau -1)
		[[nodiscard]] int cauta(TElem e) const;

		// returnare iterator
		[[nodiscard]] IteratorLI iterator() const;

        // sterge toate elementele din TAD
        int eliminaToate(LI &l);

		//destructor
		~LI();

};
