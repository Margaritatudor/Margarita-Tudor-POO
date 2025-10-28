#include<iostream>
#include<string>
#include<stdexcept>

using namespace std;

enum TipCombustibil { BENZINA = 1, MOTORINA = 2, ELECTRIC = 3, HIBRID = 4 };

class Masina {
private:
	const int id;
	string marca;
	float pret;
	TipCombustibil tipCombustibil;
	int nrOptiuni;
	int* coduriOptiuni;
	static int nrMasini;

public:
	Masina() : id(++nrMasini) {
		this->marca = "Necunoscuta";
		this->pret = 0;
		this->nrOptiuni = 0;
		this->coduriOptiuni = nullptr;
		this->tipCombustibil = BENZINA;
	}

	Masina(string marca, float pret, int nrOptiuni, int* coduriOptiuni, TipCombustibil tipCombustibil) : id(++nrMasini) {
		this->marca = marca;
		this->pret = pret;
		this->nrOptiuni = nrOptiuni;
		this->tipCombustibil = tipCombustibil;

		this->coduriOptiuni = new int[this->nrOptiuni];
		for (int i = 0; i < this->nrOptiuni; i++) {
			this->coduriOptiuni[i] = coduriOptiuni[i];
		}
	}

	Masina(const Masina& copie) : id(++nrMasini) {
		this->marca = copie.marca;
		this->pret = copie.pret;
		this->tipCombustibil = copie.tipCombustibil;
		this->nrOptiuni = copie.nrOptiuni;

		if (copie.coduriOptiuni != nullptr) {
			this->coduriOptiuni = new int[copie.nrOptiuni];
			for (int i = 0; i < copie.nrOptiuni; i++) {
				this->coduriOptiuni[i] = copie.coduriOptiuni[i];
			}
		}
		else {
			this->coduriOptiuni = nullptr;
		}
	}

	Masina& operator=(const Masina& copie) {
		if (this == &copie) {
			return *this;
		}

		this->marca = copie.marca;
		this->pret = copie.pret;
		this->tipCombustibil = copie.tipCombustibil;
		this->nrOptiuni = copie.nrOptiuni;

		if (this->coduriOptiuni != nullptr) {
			delete[] this->coduriOptiuni;
			this->coduriOptiuni = nullptr;
		}

		if (copie.coduriOptiuni != nullptr) {
			this->coduriOptiuni = new int[copie.nrOptiuni];
			for (int i = 0; i < copie.nrOptiuni; i++) {
				this->coduriOptiuni[i] = copie.coduriOptiuni[i];
			}
		}
		else {
			this->coduriOptiuni = nullptr;
		}
		return *this;
	}

	void afisareMasina() {
		cout << endl << "--- Detalii Masina ---";
		cout << endl << this->id << ". Masina marca " << this->marca << " costa " << this->pret << " Euro, are tipul de combustibil: ";
		switch (this->tipCombustibil) {
		case BENZINA: cout << "BENZINA"; break;
		case MOTORINA: cout << "MOTORINA"; break;
		case ELECTRIC: cout << "ELECTRIC"; break;
		case HIBRID: cout << "HIBRID"; break;
		}
		cout << " si are " << this->nrOptiuni << " optiuni extra cu codurile: ";
		if (this->coduriOptiuni != nullptr && this->nrOptiuni > 0) {
			for (int i = 0; i < this->nrOptiuni - 1; i++) {
				cout << this->coduriOptiuni[i] << ", ";
			}
			cout << this->coduriOptiuni[this->nrOptiuni - 1] << ".";
		}
		else {
			cout << "Niciuna.";
		}
		cout << endl;
	}

	int getNrOptiuni() const {
		return this->nrOptiuni;
	}

	void setNrOptiuni(int nrOptiuniNou) {
		if (nrOptiuniNou >= 0) {
			this->nrOptiuni = nrOptiuniNou;
		}
		else {
			throw out_of_range("Numarul de optiuni nu poate fi negativ!");
		}
	}

	int* getCoduriOptiuni() const {
		int* copieCoduri = new int[this->nrOptiuni];
		for (int i = 0; i < this->nrOptiuni; i++) {
			copieCoduri[i] = this->coduriOptiuni[i];
		}
		return copieCoduri;
	}

	void setCoduriOptiuni(int* coduriNoi, int nrOptiuniNou) {
		setNrOptiuni(nrOptiuniNou);

		if (this->coduriOptiuni != nullptr) {
			delete[] this->coduriOptiuni;
		}
		
		if (this->nrOptiuni >
