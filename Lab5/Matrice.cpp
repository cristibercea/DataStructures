#include "Matrice.h"
#include <exception>
#include <climits>
using namespace std;


Matrice::Matrice(int m, int n) {
    ///complexitate: Teta(1)
    if (m <= 0 || n <= 0) throw std::exception();
    linii = m, coloane = n;
    radacina = nullptr;
}

int Matrice::nrLinii() const {
    ///complexitate: Teta(1)
    return linii;
}

int Matrice::nrColoane() const {
    ///complexitate: Teta(1)
    return coloane;
}

TElem Matrice::element(int i, int j) const {
    ///complexitate: CM - O(log(n)) - cautare in abc
    ///              CF - Teta(1) - elementul cautat e chiar radacina / abc vid
    ///              CD - O(n) - cautare in arbore binar degenerat
    if (i<0 || j<0 || i >= linii || j >= coloane) throw std::exception();
    if (radacina == nullptr) return NULL_TELEMENT;
    return cauta_nod(i, j, radacina);
}

TElem Matrice::modifica(int i, int j, TElem e) {
    ///complexitate: CM - O(log(n)) - abc
    ///              CF - Teta(1) - arbore vid
    ///              CD - O(n) -arbore binar degenerat
    if (i<0 || j<0 || i >= linii || j >= coloane) throw std::exception();
    if (radacina == nullptr) {
        radacina = creeazaNod(i, j, e);
        return NULL_TELEMENT;
    }
    return adauga_nod(i, j, e, radacina);
}

Matrice::~Matrice() {
    ///complexitate: CF - O(log(n)) -arbore binar
    ///              CD - O(n) -arbore binar degenerat
    distrug_rec(radacina);
}

Matrice::nod *Matrice::creeazaNod(int ii, int jj, TElem el) const {
    ///complexitate: Teta(1)
    nod *nou = new nod;
    nou->drept = nullptr;
    nou->stang = nullptr;
    nou->i = ii;
    nou->j = jj;
    nou->e = el;
    return nou;
}

void Matrice::distrug_rec(Matrice::nod *r) {
    ///complexitate: CF - O(log(n)) -arbore binar
    ///              CD - O(n) -arbore binar degenerat
    if (r != nullptr) {
        distrug_rec(r->stang);
        distrug_rec(r->drept);
        delete r;
    }
}

TElem Matrice::adauga_nod(int ii, int jj, TElem el, Matrice::nod *rad) {
    ///complexitate: CF - O(log(n)) -nodul p se pune undeva in interiorul abc
    ///              CD - O(n) -nodul p se pune in arbore binar degenerat
    while (true)
        if (ii == rad->i) {
            if (jj == rad->j) {
                TElem old = rad->e;
                if(el==0) rad->e = el; //in loc de asta trebuie sterge(rad)
                else rad->e = el;
                return old;
            } else if (jj < rad->j) {
                if (rad->stang == nullptr) {
                    rad->stang = creeazaNod(ii, jj, el);
                    return NULL_TELEMENT;
                } else {
                    rad = rad->stang;
                    continue;
                }
            } else {
                if (rad->drept == nullptr) {
                    rad->drept = creeazaNod(ii, jj, el);
                    return NULL_TELEMENT;
                } else {
                    rad = rad->drept;
                    continue;
                }
            }
        } else if (ii < rad->i) {
            if (rad->stang == nullptr) {
                rad->stang = creeazaNod(ii, jj, el);
                return NULL_TELEMENT;
            } else {
                rad = rad->stang;
                continue;
            }
        } else {
            if (rad->drept == nullptr) {
                rad->drept = creeazaNod(ii, jj, el);
                return NULL_TELEMENT;
            } else {
                rad = rad->drept;
                continue;
            }
        }
}

TElem Matrice::cauta_nod(int ii, int jj, Matrice::nod *rad) const {
    ///complexitate: CF - O(log(n)) - abc
    ///              CD - O(n) - arbore binar degenerat
    while (true)
        if (ii == rad->i) {
            if (jj == rad->j) return rad->e;
            else if (jj < rad->j) {
                if (rad->stang == nullptr) return NULL_TELEMENT;
                else {
                    rad = rad->stang;
                    continue;
                }
            } else {
                if (rad->drept == nullptr) return NULL_TELEMENT;
                else {
                    rad = rad->drept;
                    continue;
                }
            }
        } else if (ii < rad->i) {
            if (rad->stang == nullptr) return NULL_TELEMENT;
            else {
                rad = rad->stang;
                continue;
            }
        } else {
            if (rad->drept == nullptr) return NULL_TELEMENT;
            else {
                rad = rad->drept;
                continue;
            }
        }
}

int Matrice::difMaxMin() {
    ///complexitate: Teta(n^2) - rad=nullptr este caz rar
    if(radacina == nullptr) return 0;
    TElem min = INT_MAX, max = 0;
    for(int i=0;i<linii;i++)
        for(int j=0;j<coloane;j++){
            TElem el = element(i,j);
            if(el>max) max = el;
            if(el<min) min = el;
        }
    return max-min;
}
