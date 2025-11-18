Am eliminat cuvântul cheie override. Codul va funcționa exact la fel, deoarece C++ detectează automat că rescrii metodele virtuale dacă semnătura (numele și parametrii) este identică.
Iată codul modificat:
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class ExceptieSalariu : public runtime_error {
public:
    ExceptieSalariu(const char* mesaj) : runtime_error(mesaj) {}
};

class Angajat {
protected:
    const int id;
    string nume;
    float salariuBaza;

public:
    static const float Salariu_Minim;

    Angajat() : id(0), nume("Anonim"), salariuBaza(3300) {}

    Angajat(int idA, string numeA, float salariuA) : id(idA), nume(numeA), salariuBaza(salariuA) {
        if (salariuBaza < Salariu_Minim) {
            throw ExceptieSalariu("Eroare: Salariul este sub minimul pe economie!");
        }
    }

    virtual void Descriere() {
        cout << endl << "--- Fisa Angajat ---";
        cout << endl << "ID: " << this->id;
        cout << endl << "Nume: " << this->nume;
        cout << endl << "Salariu Baza: " << this->salariuBaza << " RON";
    }

    virtual ~Angajat() {
        cout << endl << "-> Destructor Angajat";
    }

    virtual float CalculeazaVenitTotal() = 0;
};

const float Angajat::Salariu_Minim = 3300.0f;

class Manager : public Angajat {
private:
    float bonusPerformanta;

public:
    Manager() : Angajat(), bonusPerformanta(0) {}

    Manager(int id, string nume, float salariu, float bonus) 
        : Angajat(id, nume, salariu), bonusPerformanta(bonus) {}

    void Descriere() {
        cout << endl << ">>> MANAGER: " << this->nume;
        cout << endl << "ID Intern: " << this->id;
        cout << endl << "Salariu Negociat: " << this->salariuBaza;
        cout << endl << "Bonus Performanta: " << this->bonusPerformanta << "%";
        cout << endl << "Venit TOTAL: " << this->CalculeazaVenitTotal() << " RON";
    }

    float CalculeazaVenitTotal() {
        return this->salariuBaza + (this->salariuBaza * (this->bonusPerformanta / 100.0f));
    }

    ~Manager() {
        cout << endl << "-> Destructor Manager";
    }
};

class IConvertorValutar {
public:
    virtual float ConversieRonInEuro(float sumaRon) = 0;
    virtual float ConversieRonInUsd(float sumaRon) = 0;
    
    virtual ~IConvertorValutar() {}
};

class BancaBala : public IConvertorValutar {
private:
    const float Curs_Euro = 4.97f;
    const float Curs_USD = 4.60f;

public:
    float ConversieRonInEuro(float sumaRon) {
        return sumaRon / Curs_Euro;
    }

    float ConversieRonInUsd(float sumaRon) {
        return sumaRon / Curs_USD;
    }
};

void main() {

    try {
        Manager stagiar(99, "Ionut", 1500, 0);
    }
    catch (exception& e) {
        cout << "EROARE PRINSA: " << e.what() << endl;
    }

    cout << endl << "---------------------------------" << endl;

    Angajat* Echipa[3];

    try {
        Echipa[0] = new Manager(1, "Andrei Popescu", 6000, 15);
        Echipa[1] = new Manager(2, "Elena Ionescu", 8000, 20);
        Echipa[2] = new Manager(3, "Mihai Radu", 5000, 10);
    }
    catch (...) {
        cout << "Eroare la alocarea memoriei.";
        return;
    }

    for (int i = 0; i < 3; i++) {
        Echipa[i]->Descriere();
        cout << endl;
    }

    cout << endl << "---------------------------------" << endl;

    IConvertorValutar* banca = new BancaBala();
    
    float venitElena = Echipa[1]->CalculeazaVenitTotal();
    cout << "Venitul Elenei in RON: " << venitElena << endl;
    cout << "Venitul Elenei in EURO: " << banca->ConversieRonInEuro(venitElena) << endl;

    cout << endl << "--- Stergere Obiecte ---";
    for (int i = 0; i < 3; i++) {
        delete Echipa[i];
    }
    delete banca;
}

Dacă mai ai nevoie de explicații despre cum funcționează virtual fără override sau despre moștenirea protected, spune-mi!
