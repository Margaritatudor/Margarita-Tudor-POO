#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// 1. Exceptie
class ExceptieForma : public runtime_error {
public:
    ExceptieForma(const char* mesaj) : runtime_error(mesaj) {}
};

// 2. Clasa Abstracta
class Forma {
protected:
    // TEMA: Atribut protected, accesibil in 'Patrat'
    float latura;
    string nume;

public:
    static const float Latura_Minima;

    Forma(string n, float l) : nume(n), latura(l) {
        if (latura < Latura_Minima) {
            throw ExceptieForma("Latura este prea mica!");
        }
    }

    // Metoda virtuala
    virtual void Afisare() {
        cout << endl << "Forma: " << this->nume;
        cout << endl << "Latura: " << this->latura;
    }

    // Metoda pur virtuala (Abstracta)
    virtual float Arie() = 0;

    // Destructor virtual
    virtual ~Forma() {
        cout << endl << "~Destructor Forma";
    }
};

const float Forma::Latura_Minima = 1.0f;

// 3. Clasa Derivata
class Patrat : public Forma {
public:
    Patrat(float l) : Forma("Patrat", l) {}

    // Nu folosim override
    void Afisare() {
        // Accesam direct atributele protected din parinte
        cout << endl << "[ " << this->nume << " ]";
        cout << endl << "Latura: " << this->latura;
        cout << endl << "Arie: " << this->Arie();
    }

    float Arie() {
        return this->latura * this->latura;
    }

    ~Patrat() { }
};

// 4. Interfata
class IMatematica {
public:
    virtual float Perimetru(float latura) = 0;
    virtual ~IMatematica() {}
};

class Calculator : public IMatematica {
public:
    float Perimetru(float latura) {
        return latura * 4;
    }
};

void main() {
    // Testare Exceptie
    try {
        Patrat pGresit(0.5);
    }
    catch (exception& e) {
        cout << "Eroare: " << e.what() << endl;
    }

    // Polimorfism
    Forma* forme[2];
    forme[0] = new Patrat(2);
    forme[1] = new Patrat(5);

    for (int i = 0; i < 2; i++) {
        forme[i]->Afisare();
        cout << endl;
    }

    // Testare Interfata
    Calculator* calc = new Calculator();
    cout << endl << "Perimetru patrat (latura 5): " << calc->Perimetru(5);

    // Curatare
    for (int i = 0; i < 2; i++) delete forme[i];
    delete calc;
}
