#include<iostream>
#include<string>
#include<stdexcept>

using namespace std;

enum Specializare { INFORMATICA = 1, AUTOMATICA = 2, CIBERNETICA = 3 };

class Student {
private:
	const int codMatricol;
	string nume;
	float medieAdmitere;
	Specializare specializare;
	int nrNote;
	int* note;
	static int nrStudenti;

public:
	Student() : codMatricol(++nrStudenti) {
		this->nume = "Anonim";
		this->medieAdmitere = 0.0f;
		this->nrNote = 0;
		this->note = nullptr;
		this->specializare = INFORMATICA;
	}

	Student(string nume, float medieAdmitere, int nrNote, int* noteElev, Specializare specializare) : codMatricol(++nrStudenti) {
		this->nume = nume;
		this->medieAdmitere = medieAdmitere;
		this->nrNote = nrNote;
		this->specializare = specializare;

		this->note = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++) {
			this->note[i] = noteElev[i];
		}
	}

	Student(const Student& copie) : codMatricol(++nrStudenti) {
		this->nume = copie.nume;
		this->medieAdmitere = copie.medieAdmitere;
		this->specializare = copie.specializare;
		this->nrNote = copie.nrNote;

		if (copie.note != nullptr) {
			this->note = new int[copie.nrNote];
			for (int i = 0; i < copie.nrNote; i++) {
				this->note[i] = copie.note[i];
			}
		}
		else {
			this->note = nullptr;
		}
	}

	Student& operator=(const Student& copie) {
		if (this == &copie) {
			return *this;
		}

		this->nume = copie.nume;
		this->medieAdmitere = copie.medieAdmitere;
		this->specializare = copie.specializare;
		this->nrNote = copie.nrNote;

		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
		}

		if (copie.note != nullptr) {
			this->note = new int[copie.nrNote];
			for (int i = 0; i < copie.nrNote; i++) {
				this->note[i] = copie.note[i];
			}
		}
		else {
			this->note = nullptr;
		}
		return *this;
	}

	void afisareStudent() const {
		cout << "\n--- Detalii Student ---";
		cout << "\nCod Matricol: " << this->codMatricol;
		cout << ", Nume: " << this->nume;
		cout << ", Medie Admitere: " << this->medieAdmitere;
		cout << ", Specializare: ";
		switch (this->specializare) {
		case INFORMATICA: cout << "INFORMATICA"; break;
		case AUTOMATICA: cout << "AUTOMATICA"; break;
		case CIBERNETICA: cout << "CIBERNETICA"; break;
		}
		cout << ", Nr. Note: " << this->nrNote;
		cout << ", Note: ";
		if (this->note != nullptr && this->nrNote > 0) {
			for (int i = 0; i < this->nrNote; i++) {
				cout << this->note[i] << (i < this->nrNote - 1 ? ", " : "");
			}
		}
		else {
			cout << "Nicio nota inregistrata.";
		}
		cout << endl;
	}
	
	int getNrNote() const {
		return this->nrNote;
	}

	void setNrNote(int nrNoteNou) {
		if (nrNoteNou >= 0) {
			this->nrNote = nrNoteNou;
		}
		else {
			throw out_of_range("Numarul de note nu poate fi negativ!");
		}
	}

	int* getNote() const {
		int* copieNote = new int[this->nrNote];
		for (int i = 0; i < this->nrNote; i++) {
			copieNote[i] = this->note[i];
		}
		return copieNote;
	}

	void setNote(int* noteNoi, int nrNoteNou) {
		setNrNote(nrNoteNou);

		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
		}
		
		if (this->nrNote > 0 && noteNoi != nullptr) {
			this->note = new int[this->nrNote];
			for (int i = 0; i < this->nrNote; i++) {
				this->note[i] = noteNoi[i];
			}
		}
		else {
			this->note = nullptr;
		}
	}

	~Student() {
		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
		}
	}

	void operator+=(int notaNoua) {
		if (notaNoua < 1 || notaNoua > 10) return;

		int* noteNoi = new int[this->nrNote + 1];
		for (int i = 0; i < this->nrNote; i++) {
			noteNoi[i] = this->note[i];
		}
		noteNoi[this->nrNote] = notaNoua;

		if (this->note != nullptr) {
			delete[] this->note;
		}

		this->note = noteNoi;
		this->nrNote++;
	}

	bool operator>(const Student& s) const {
		return this->medieAdmitere > s.medieAdmitere;
	}
};

int Student::nrStudenti = 0;

void main() {
	Student ion;
	ion.afisareStudent();

	int* noteMaria = new int[3] {9, 10, 8};
	Student* maria = new Student("Maria Popescu", 9.80f, 3, noteMaria, CIBERNETICA);
	maria->afisareStudent();
	delete[] noteMaria; 

	Student andrei(*maria);
	andrei.afisareStudent();

	ion = *maria;
	cout << "\n--- Dupa atribuire (ion = maria) ---";
	ion.afisareStudent();

	ion += 7;
	cout << "\n--- Dupa adaugare nota (ion += 7) ---";
	ion.afisareStudent();

	cout << "\n--- Comparare Medii Admitere ---";
	if (andrei > ion) {
		cout << "\n Studentul Andrei are media de admitere mai mare!";
	}
	else {
		cout << "\n Studentul Ion are media de admitere mai mare sau egala!";
	}

	delete maria;
}
