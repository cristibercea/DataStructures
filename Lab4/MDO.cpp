#include "IteratorMDO.h"
#include "MDO.h"
#include <vector>
#include <exception>

using namespace std;

MDO::MDO(Relatie r) : rel{r} {
    ///complexitate: Teta(1)
    m = 13;
    n = 0;
    TD = new chei[m];
    for (int i = 0; i < m; i++) TD[i].cheie = NIL;
}


void MDO::adauga(TCheie c, TValoare v) {
    ///complexitate CD: O(n) - cheia exista si se afla in coliziune cu alte n chei
    ///complexitate CM: Teta(1) - amortizat (redimensionarea e caz rar)
    ///complexitate CF: Teta(1) - cheia: deja exista/ nu exista, dar nu sunt coliziuni
    n++;
    int i = 0;
    bool gasit = false;
    do {
        int j = d(c, i);
        if (TD[j].cheie == c) {
            TD[j].valori.push_back(v);
            gasit = true;
        } else {
            if (TD[j].cheie == NIL || TD[j].cheie == CST) {
                TD[j].cheie = c;
                TD[j].valori.push_back(v);
                gasit = true;
            } else i++;
        }
    } while (!gasit && i != m);
    if (i == m) {
        redimensionare();///redimensionare+redispersare

        do { ///adaugam noua cheie
            int j = d(c, i);
            if (TD[j].cheie == NIL) {
                TD[j].cheie = c;
                TD[j].valori.push_back(v);
                gasit = true;
            } else i++;
        } while (!gasit);
    }
}

vector<TValoare> MDO::cauta(TCheie c) const {
    ///complexitate CD: O(n) - nu gasim cheia
    ///complexitate CM: Teta(1)
    ///complexitate CF: Teta(1) - cheia e chiar prima din succesiune
    if(c>m||c<0) return vector<TValoare>{};
    int i = 0, j;
    do {
        j = d(c, i);
        if (TD[j].cheie == c) return TD[j].valori;
        else i++;
    } while (i != m && TD[j].cheie != NIL);
    return vector<TValoare>{};
}

bool MDO::sterge(TCheie c, TValoare v) {
    ///complexitate CD: O(n) - stergem un element din vector sau nu gasim cheia
    ///complexitate CM: Teta(1)
    ///complexitate CF: Teta(1) - stergem cheia - caz cu probabilitate redusa
    int i = 0, j;
    bool gasit = false;
    do {
        j = d(c, i);
        if (TD[j].cheie == c) {
            int poz;
            for (int k = 0; k < TD[j].valori.size(); k++) if (TD[j].valori[k] == v) poz = k, gasit = true;
            if (!gasit) return false;
            n--;
            if (TD[j].valori.size() > 1) { ///stergem doar o valoare
                for (int k = poz + 1; k < TD[j].valori.size(); k++)
                    TD[j].valori[k - 1] = TD[j].valori[k];
                TD[j].valori.pop_back();
            } else { ///stergem si valoarea si cheia
                TD[j].valori.clear();
                TD[j].cheie = CST;
            }
        } else i++;
    } while (i != m && TD[j].cheie != NIL && !gasit);
    return gasit;
}

int MDO::dim() const {
    ///complexitate: Teta(1)
    return n;
}

bool MDO::vid() const {
    ///complexitate: Teta(1)
    if (n != 0) return false;
    return true;
}

IteratorMDO MDO::iterator() const {
    ///complexitate: Teta(1)
    return IteratorMDO{*this};
}

MDO::~MDO() {
    ///complexitate: Teta(1)
    n = 0;
    m = 13;
    rel = nullptr;
    delete[] TD;
}

int MDO::d1(TCheie c) const {
    ///complexitate: Teta(1)
    return c % m;
}

int MDO::d2(TCheie c) const {
    ///complexitate: Teta(1)
    return 1 + c % (m - 2);
}

int MDO::d(TCheie c, int i) const {
    ///complexitate: Teta(1)
    return (d1(c) + i * d2(c)) % m;
}

void MDO::redimensionare() {
    ///complexitate: O(n^2)

    ///redimensionare
    int maux = m;
    m = genereazaNrPrim();
    chei *TDaux = new chei[maux];
    for(int i=0;i<maux;i++) TDaux[i]=TD[i];
    delete[] TD;
    TD = new chei[m];
    for (int i = 0; i < m; i++) TD[i].cheie = NIL;

    ///redispersare
    for (int k = 0; k < maux; k++) {
        int i = 0;
        bool gasit = false;
        do {
            int j = d(TDaux[k].cheie, i);
            if (TD[j].cheie == NIL) {
                TD[j].cheie = TDaux[k].cheie;
                TD[j].valori = TDaux[k].valori;
                gasit = true;
            } else i++;
        } while (!gasit);
    }
    delete[] TDaux;
}

int MDO::genereazaNrPrim() {
    ///complexitate: O(n)
    int nr = m*2 + 7;
    while (!prim(nr)) nr += 2;
    return nr;
}

bool MDO::prim(int x) { //n - impar si mai mare decat 11
    ///complexitate: O(n)
    for (int d = 3; d * d <= x; d += 2) if (x % d == 0) return false;
    return true;
}

void MDO::goleste() {
    ///complexitate: Teta(n)
    ///caz rar: mdo = vid (Teta(1))
    if(vid()) throw std::exception();
    for(int i=0;i<m;i++)
        if(TD[i].cheie!=NIL && TD[i].cheie!=CST) {
            n-=(int) TD[i].valori.size();
            TD[i].valori.clear();
            TD[i].cheie = NIL;
        }
}