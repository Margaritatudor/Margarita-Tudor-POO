#include <iostream>
#include <string>

using namespace std;

class Carte {
private:
    string titlu;
    string autor;
    int nrPagini;
    float pret;

public:
    Carte() {
        this->titlu = "Necunoscut";
        this->autor = "Anonim";
        this->nrPagini = 0;
        this->pret = 0.0f;
    }

    Carte(string titlu, string autor, int nrPagini, float pret) {
        this->titlu = titlu;
        this->autor = autor;
        this->nrPagini = nrPagini;
        this->pret = pret;
    }

    friend ostream& operator<<(ostream& consola, const Carte& c) {
        consola << "Cartea '" << c.titlu << "' de " << c.autor;
        consola << " are " << c.nrPagini << " pagini si costa " << c.pret << " lei.";
        return consola;
    }

    Carte operator+(float valoareDeAdaugat) {
        Carte copie = *this; 
        copie.pret += valoareDeAdaugat;
        return copie;
    }

    bool operator>(const Carte& c) {
        return this->nrPagini > c.nrPagini;
    }
};

int main() {
    Carte c1("Amintiri din copilarie", "Ion Creanga", 200, 25.5);
    Carte c2("Morometii", "Marin Preda", 500, 45.0);

    cout << "--- Cartile initiale ---" << endl;
    cout << "Cartea 1: " << c1 << endl;
    cout << "Cartea 2: " << c2 << endl;

    cout << "\n--- Testare operator + (adaugare taxa) ---" << endl;
    Carte c3 = c1 + 10.0f; 
    
    cout << "Cartea 1 (original): " << c1 << endl;
    cout << "Cartea 3 (copie C1 + 10 lei): " << c3 << endl;

    cout << "\n--- Testare operator > (comparare pagini) ---" << endl;
    if (c2 > c1) { 
        cout << "Cartea 'Morometii' are mai multe pagini decat 'Amintiri din copilarie'." << endl;
    } else {
        cout << "Cartea 'Amintiri din copilarie' are mai multe pagini decat 'Morometii'." << endl;
    }

    return 0; 
}
