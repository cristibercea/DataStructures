#pragma once
typedef int TElem;
#define NULL_TELEMENT 0

class Matrice {

private:
    /* aici e reprezentarea */
    int linii, coloane;
    struct nod {
        int i, j;
        TElem e;
        nod *stang;
        nod *drept;
    };
    nod *radacina;

    /* utilitare */
    [[nodiscard]] nod *creeazaNod(int ii, int jj, TElem el) const;

    void distrug_rec(nod *r);

    TElem adauga_nod(int ii, int jj, TElem el, nod *rad);

    TElem cauta_nod(int ii, int jj, nod *rad) const;

public:
    //constructor
    //se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
    Matrice(int nrLinii, int nrColoane);

    //destructor
    ~Matrice();

    //returnare element de pe o linie si o coloana
    //se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
    //indicii se considera incepand de la 0
    TElem element(int i, int j) const;

    // returnare numar linii
    [[nodiscard]] int nrLinii() const;

    // returnare numar coloane
    [[nodiscard]] int nrColoane() const;

    // modificare element de pe o linie si o coloana si returnarea vechii valori
    // se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
    TElem modifica(int i, int j, TElem);

    // returneaza diferenta dintre elem max si elem min din matrice
    int difMaxMin();
};







