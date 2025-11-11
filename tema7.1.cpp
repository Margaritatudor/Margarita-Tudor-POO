#include <iostream>
#include <string>

using namespace std;

class Masina {
private:
    string marca;
    string model;
    int anFabricatie;
    float pret;

public:
    Masina() {
        this->marca = "N/A";
        this->model = "N/A";
        this->anFabricatie = 0;
        this->pret = 0.0f;
    }

    Masina(string marca, string model, int an, float pret) {
        this->marca = marca;
        this->model = model;
        this->anFabricatie = an;
        this->pret = pret;
    }

    friend ostream& operator<<(ostream& os, const Masina& m) {
        os << "Masina: " << m.marca << " " << m.model;
        os << " (An: " << m.anFabricatie << ", Pret: " << m.pret << " EUR)";
        return os;
    }

    friend istream& operator>>(istream& is, Masina& m) {
        cout << "Introduceti marca (fara spatii): ";
        is >> m.marca;
        cout << "Introduceti modelul (fara sp
