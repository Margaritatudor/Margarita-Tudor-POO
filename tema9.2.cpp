#include<iostream>
#include<string>

using namespace std;

class Vacanta {
protected:
	string destinatiePrincipala;
	float pretBaza;

public:
	Vacanta(string destinatie, float pret) : destinatiePrincipala(destinatie), pretBaza(pret) {
	}

	virtual ~Vacanta() {
	}

	virtual void afisare(ostream& out) const {
		out << "Destinatie: " << this->destinatiePrincipala << " | Pret baza: " << this->pretBaza << " EUR";
	}

	friend ostream& operator<<(ostream& out, const Vacanta& v) {
		v.afisare(out);
		return out;
	}
};

class Sejur : public Vacanta {
private:
	string numeHotel;
	int nrStele;

public:
	Sejur(string destinatie, float pret, string hotel, int stele)
		: Vacanta(destinatie, pret) {
		this->numeHotel = hotel;
		this->nrStele = stele;
	}

	void afisare(ostream& out) const override {
		Vacanta::afisare(out);
		out << " | Tip
