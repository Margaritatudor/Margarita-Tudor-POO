#include<iostream>
#include<string>

using namespace std;

class Calatorie {
private:
	float pret = 0;

public:
	Calatorie() {
	}

	Calatorie(float pret) {
		this->pret = pret;
	}

	float getPret() {
		return this->pret;
	}
	
	// Optional: Putem adauga operator << si pentru Calatorie pentru a simplifica afisarea
	friend ostream& operator<<(ostream& out, const Calatorie& c) {
		out << c.pret;
		return out;
	}
};

class Vacanta {
private:
	Calatorie* calatorii;
	int nrCalatorii;
	string destinatie;

public:
	Vacanta(string destinatie, int nrCalatorii, float* preturi) {
		this->nrCalatorii = nrCalatorii;
		this->destinatie = destinatie;
		this->calatorii = new Calatorie[nrCalatorii];
		for (int i = 0; i < nrCalatorii; i++) {
			this->calatorii[i] = Calatorie(preturi[i]);
		}
	}

	Calatorie& operator[](int index) {
		if (index >= 0 && index < this->nrCalatorii) {
			return this->calatorii[index];
		}
		else {
			throw "Index ul este in afara intervalului!";
		}
	}

	string getDestinatie() {
		return this->destinatie;
	}

	Vacanta(const Vacanta& v) {
		this->nrCalatorii = v.nrCalatorii;
		this->destinatie = v.destinatie;

		if (v.calatorii != nullptr) {
			this->calatorii = new Calatorie[v.nrCalatorii];
			for (int i = 0; i < this->nrCalatorii; i++) {
				this->calatorii[i] = v.calatorii[i];
			}
		}
		else {
			this->calatorii = nullptr;
		}
	}

	~Vacanta() {
		if (this->calatorii != nullptr) {
			delete[] this->calatorii;
		}
	}

	// ---------------------------------------------------------
	// IMPLEMENTAREA OPERATORULUI <<
	// ---------------------------------------------------------
	friend ostream& operator<<(ostream& out, const Vacanta& v) {
		out << "--- Detalii Vacanta ---" << endl;
		out << "Destinatie: " << v.destinatie << endl;
		out << "Numar calatorii: " << v.nrCalatorii << endl;
		out << "Preturi per calatorie: ";
		
		for (int i = 0; i < v.nrCalatorii; i++) {
			// Folosim getPret() deoarece este public in clasa Calatorie
			out << v.calatorii[i].getPret() << " EUR";
			if (i < v.nrCalatorii - 1) {
				out << ", ";
			}
		}
		out << endl << "-----------------------" << endl;
		return out;
	}
};

void main() {
	// Definim preturile separat pentru a evita memory leak (sau le stergem manual dupa)
	float preturiLondra[] = { 350, 140 };
	
	Vacanta vacanta("Londra", 2, preturiLondra);

	// Testam accesul prin index
	cout << "Test index: Pretul primei calatorii din " << vacanta.getDestinatie() << " este de " << vacanta[0].getPret() << " euro." << endl << endl;

	// Copiem vacanta (Copy Constructor)
	Vacanta vacanta2 = vacanta;
	
	// AFISAM OBIECTELE FOLOSIND OPERATORUL << IMPLEMENTAT
	cout << "Afisare vacanta 1:" << endl;
	cout << vacanta << endl;

	cout << "Afisare vacanta 2 (copie):" << endl;
	cout << vacanta2 << endl;
}
