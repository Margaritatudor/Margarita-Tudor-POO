#include<iostream>
#include<string>

using namespace std;

enum Combustibil {BENZINA = 1, MOTORINA = 2, ELECTRIC = 3, HIBRID = 4};

class Automobil {
private:
	const int id;
	float pret;
	string marca;
	Combustibil tipCombustibil;
	int nrRevizii;
	int* costuriRevizii;
	static int nrAutomobile;

public:
	Automobil() :id(++nrAutomobile) {
		this->marca = "Necunoscuta";
		this->pret = 0.0f;
		this->nrRevizii = 0;
		this->costuriRevizii = nullptr;
		this->tipCombustibil = BENZINA;
	}

	Automobil(string marca, float pret, int nrRevizii, int* costuriRevizii, Combustibil tipCombustibil) :id(++nrAutomobile) {
		this->marca = marca;
		this->pret = pret;
		this->nrRevizii = nrRevizii;
		
		this->costuriRevizii = new int[this->nrRevizii];
		for (int i = 0; i < this->nrRevizii; i++) {
			this->costuriRevizii[i] = costuriRevizii[i];
		}
		
		this->tipCombustibil = tipCombustibil;

		delete[] costuriRevizii;
	}

	void afisareAutomobil() {
		cout << endl << "--- Automobilul #" << this->id << " ---";
		cout << endl << "Marca: " << this->marca << ", Pret: " << this->pret << " EUR";
		cout << endl << "Tip Combustibil: ";
		if (this->tipCombustibil == BENZINA) cout << "BENZINA";
		else if (this->tipCombustibil == MOTORINA) cout << "MOTORINA";
		else if (this->tipCombustibil == ELECTRIC) cout << "ELECTRIC";
		else if (this->tipCombustibil == HIBRID) cout << "HIBRID";
		
		cout << endl << "A avut " << this->nrRevizii << " revizii. Costuri (RON): ";
		if (this->costuriRevizii != nullptr) {
			for (int i = 0; i < this->nrRevizii; i++) {
				cout << this->costuriRevizii[i] << ((i < this->nrRevizii - 1) ? " RON, " : " RON.");
			}
		}
	}

	int getNrRevizii() {
		return this->nrRevizii;
	}

	void setNrRevizii(int nrNou) {
		if (nrNou >= 0)
		{
			this->nrRevizii = nrNou;
		}
		else {
			throw "Numar de revizii negativ invalid!";
		}
	}

	int* getCosturiRevizii() {
		if (this->costuriRevizii == nullptr || this->nrRevizii == 0) {
			return nullptr;
		}
		
		int* copieCosturi = new int[this->nrRevizii];
		for (int i = 0; i < this->nrRevizii; i++) {
			copieCosturi[i] = this->costuriRevizii[i];
		}

		return copieCosturi;
	}

	void setCosturiRevizii(int* costuriNoi, int nrReviziiNou) {
		try {
			setNrRevizii(nrReviziiNou);
		}
		catch (const char* mesaj) {
			throw 500;
		}

		if (this->costuriRevizii != nullptr) {
			delete[] this->costuriRevizii;
			this->costuriRevizii = nullptr;
		}
		
		if (this->nrRevizii > 0 && costuriNoi != nullptr) {
			this->costuriRevizii = new int[this->nrRevizii];
			for (int i = 0; i < this->nrRevizii; i++) {
				this->costuriRevizii[i] = costuriNoi[i];
			}
		} 

		if (costuriNoi != nullptr) {
		    delete[] costuriNoi;
		}
	}

	~Automobil() {
		if (this->costuriRevizii != nullptr) {
			delete[] this->costuriRevizii;
			this->costuriRevizii = nullptr;
		}
	}
};

int Automobil::nrAutomobile = 0;

void main() {
	Automobil masina1;
	masina1.afisareAutomobil();
	
	int* costuriT2 = new int[3] {850, 600, 1050};
	Automobil* masina2 = new Automobil("Dacia Spring", 18000.00f, 3, costuriT2, ELECTRIC);
	masina2->afisareAutomobil();

	cout << endl << "\n--- Testare SetNrRevizii cu Try-Catch ---";
	
	try {
		masina2->setNrRevizii(4);
		cout << endl << "SetNrRevizii reusit. Numar nou: " << masina2->getNrRevizii();
	}
	catch (const char* mesaj) {
		cout << endl << "Eroare (char*): " << mesaj;
	}
	catch (...) {
		cout << endl << "Eroare necunoscuta la setNrRevizii!";
	}
	
	try {
		masina2->setNrRevizii(-1);
	}
	catch (const char* mesaj) {
		cout << endl << "Eroare (char* prinsa): " << mesaj;
	}
	catch (int cod) {
		cout << endl << "Eroare (int prinsa): Cod " << cod;
	}
	catch (...) {
		cout << endl << "Eroare necunoscuta la setNrRevizii!";
	}

	cout << endl << "Nr revizii curent: " << masina2->getNrRevizii();
	
	cout << endl << "\n--- Testare SetCosturiRevizii ---";

	int* noiCosturi = new int[5] {400, 500, 600, 700, 800};
	try {
		masina2->setCosturiRevizii(noiCosturi, 5); 
		masina2->afisareAutomobil();
	}
	catch (int cod) {
		cout << endl << "Eroare (int prinsa in setCosturiRevizii): Cod " << cod;
	}
	catch (...) {
		cout << endl << "Eroare necunoscuta la setCosturiRevizii!";
	}

	int* costuriActuale = masina2->getCosturiRevizii();
	if (costuriActuale != nullptr) {
		cout << endl << "\nCosturi revizii (copie via get): ";
		for (int i = 0; i < masina2->getNrRevizii(); i++) {
			cout << costuriActuale[i] << " RON, ";
		}
	}

	delete[] costuriActuale; 
	
	cout << endl << "\n--- Apel Destructor ---";
	delete masina2;
}
