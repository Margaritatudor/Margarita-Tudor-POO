#include<iostream>
#include<string>

using namespace std;

enum OS_Tip {ANDROID = 10, IOS = 12, ALTELE = 5};

class Telefon {
private:
	const int id;
	float pret;
	string model;
	OS_Tip osTip;
	int nrAplicatii;
	int* dimensiuniAplicatii;
	static int nrTelefoane;

public:
	Telefon() :id(++nrTelefoane) {
		this->model = "Model necunoscut";
		this->pret = 0.0f;
		this->nrAplicatii = 0;
		this->dimensiuniAplicatii = nullptr;
		this->osTip = ANDROID;
	}

	Telefon(string model, float pret, int nrAplicatii, int* dimensiuniAplicatii, OS_Tip osTip) :id(++nrTelefoane) {
		this->model = model;
		this->pret = pret;
		this->nrAplicatii = nrAplicatii;
		
		this->dimensiuniAplicatii = new int[this->nrAplicatii];
		for (int i = 0; i < this->nrAplicatii; i++) {
			this->dimensiuniAplicatii[i] = dimensiuniAplicatii[i];
		}
		
		this->osTip = osTip;

		delete[] dimensiuniAplicatii;
	}

	void afisareTelefon() {
		cout << endl << "--- Telefonul #" << this->id << " ---";
		cout << endl << "Model: " << this->model << ", Pret: " << this->pret << " lei";
		cout << endl << "Sistem de operare: ";
		if (this->osTip == ANDROID) cout << "ANDROID";
		else if (this->osTip == IOS) cout << "IOS";
		else if (this->osTip == ALTELE) cout << "ALTELE";
		
		cout << endl << "Contine " << this->nrAplicatii << " aplicatii. Dimensiuni (MB): ";
		if (this->dimensiuniAplicatii != nullptr) {
			for (int i = 0; i < this->nrAplicatii; i++) {
				cout << this->dimensiuniAplicatii[i] << ((i < this->nrAplicatii - 1) ? ", " : ".");
			}
		}
	}

	int getNrAplicatii() {
		return this->nrAplicatii;
	}

	void setNrAplicatii(int nrNou) {
		if (nrNou >= 0)
		{
			this->nrAplicatii = nrNou;
		}
		else {
			throw "Numar de aplicatii negativ invalid!";
		}
	}

	int* getDimensiuniAplicatii() {
		if (this->dimensiuniAplicatii == nullptr || this->nrAplicatii == 0) {
			return nullptr;
		}
		
		int* copieDimensiuni = new int[this->nrAplicatii];
		for (int i = 0; i < this->nrAplicatii; i++) {
			copieDimensiuni[i] = this->dimensiuniAplicatii[i];
		}

		return copieDimensiuni;
	}

	void setDimensiuniAplicatii(int* dimensiuniNoi, int nrAplicatiiNou) {
		try {
			setNrAplicatii(nrAplicatiiNou);
		}
		catch (const char* mesaj) {
			throw 400;
		}

		if (this->dimensiuniAplicatii != nullptr) {
			delete[] this->dimensiuniAplicatii;
		}
		
		if (this->nrAplicatii > 0 && dimensiuniNoi != nullptr) {
			this->dimensiuniAplicatii = new int[this->nrAplicatii];
			for (int i = 0; i < this->nrAplicatii; i++) {
				this->dimensiuniAplicatii[i] = dimensiuniNoi[i];
			}
		} else {
			this->dimensiuniAplicatii = nullptr;
		}

		if (dimensiuniNoi != nullptr) {
		    delete[] dimensiuniNoi;
		}
	}

	~Telefon() {
		if (this->dimensiuniAplicatii != nullptr) {
			delete[] this->dimensiuniAplicatii;
			this->dimensiuniAplicatii = nullptr;
		}
	}
};

int Telefon::nrTelefoane = 0;

void main() {
	Telefon telefon1;
	telefon1.afisareTelefon();
	
	int* dimsT2 = new int[2] {50, 120};
	Telefon* telefon2 = new Telefon("iPhone 15", 4500.50f, 2, dimsT2, IOS);
	telefon2->afisareTelefon();

	cout << endl << "\n--- Testare SetNrAplicatii cu Try-Catch ---";
	
	try {
		telefon2->setNrAplicatii(5);
		cout << endl << "SetNrAplicatii reusit. Numar nou: " << telefon2->getNrAplicatii();
	}
	catch (const char* mesaj) {
		cout << endl << "Eroare (char*): " << mesaj;
	}
	catch (...) {
		cout << endl << "Eroare necunoscuta la setNrAplicatii!";
	}
	
	try {
		telefon2->setNrAplicatii(-3);
	}
	catch (const char* mesaj) {
		cout << endl << "Eroare (char* prinsa): " << mesaj;
	}
	catch (int cod) {
		cout << endl << "Eroare (int prinsa): Cod " << cod;
	}
	catch (...) {
		cout << endl << "Eroare necunoscuta la setNrAplicatii!";
	}

	cout << endl << "Nr aplicatii curent: " << telefon2->getNrAplicatii();
	
	cout << endl << "\n--- Testare SetDimensiuniAplicatii ---";

	int* noiDimensiuni = new int[4] {10, 20, 30, 40};
	try {
		telefon2->setDimensiuniAplicatii(noiDimensiuni, 4); 
		telefon2->afisareTelefon();
	}
	catch (int cod) {
		cout << endl << "Eroare (int prinsa in setDimensiuniAplicatii): Cod " << cod;
	}
	catch (...) {
		cout << endl << "Eroare necunoscuta la setDimensiuniAplicatii!";
	}

	int* dimensiuniActuale = telefon2->getDimensiuniAplicatii();
	if (dimensiuniActuale != nullptr) {
		cout << endl << "\nDimensiuni (copie via get): ";
		for (int i = 0; i < telefon2->getNrAplicatii(); i++) {
			cout << dimensiuniActuale[i] << " MB, ";
		}
	}

	delete[] dimensiuniActuale; 
	
	cout << endl << "\n--- Apel Destructor ---";
	delete telefon2;
}
