#pragma once

#include "LO.h"

class Iterator{
	friend class LO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	explicit Iterator(const LO& lo);

	//contine o referinta catre containerul pe care il itereaza
	const LO& lo;

	/* aici e reprezentarea  specifica a iteratorului */
    LO::nod* curent;
public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

        //muta iteratorul in container cu o pozitie in spate
        // arunca exceptie daca iteratorul nu e valid si il re-pune
        void anterior();

		//verifica daca iteratorul e valid (indica un element al containerului)
		[[nodiscard]] bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		[[nodiscard]] TElement element() const;
};


