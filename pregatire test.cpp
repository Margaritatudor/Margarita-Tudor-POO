#include <iostream>
#include <string>

using namespace std;
#pragma warning (disable: 4996)

enum Departament { IT = 10, HR = 5, FINANCIAR = 7, MARKETING = 8 };




class Angajat {

	const int idAngajat;
	string nume;
	float salariuBaza;
	int nrLuniVechime;
	float* istoricSalarii;
	static int contorAngajati;
	Departament departament;

public:
	Angajat() :idAngajat(++contorAngajati) {


		this->nume = "Necunoscut";
		this->salariuBaza = 0;
		this->nrLuniVechime = 0;
		this->istoricSalarii = nullptr;
		this->departament = IT;

	}

	Angajat(string nume, float salariuBaza, int nrLuniVechime, float* istoricSalarii, Departament departament) :idAngajat(++contorAngajati) {

		this->nume = nume;
		this->salariuBaza = salariuBaza;
		this->nrLuniVechime = nrLuniVechime;
		this->istoricSalarii = new float[this->nrLuniVechime];
		if (istoricSalarii != nullptr)
		{
			for (int i = 0; i < this->nrLuniVechime; i++)
				this->istoricSalarii[i] = istoricSalarii[i];
		}


		this->departament = departament;
		delete[] istoricSalarii;
	}


	Angajat(const Angajat& copie) :idAngajat(++contorAngajati) {

		this->nume = copie.nume;
		this->salariuBaza = copie.salariuBaza;
		this->nrLuniVechime = copie.nrLuniVechime;
		this->istoricSalarii = new float[copie.nrLuniVechime];
		if (copie.istoricSalarii != nullptr)
		{
			for (int i = 0; i < copie.nrLuniVechime; i++)
				this->istoricSalarii[i] = copie.istoricSalarii[i];
		}
		this->departament = copie.departament;
		delete[] this->istoricSalarii;
	}

	Angajat operator=(const Angajat& copie) : idAngajat(++contorAngajati) {
		this->nume = copie.nume;
		this->salariuBaza = copie.salariuBaza;
		this->nrLuniVechime = copie.nrLuniVechime;
		if (this->istoricSalarii != nullptr)
		{
			delete[] this->istoricSalarii;
			istoricSalarii = nullptr;
		}
		this->istoricSalarii = new float[copie.nrLuniVechime];
		if (copie.istoricSalarii != nullptr)
		{
			for (int i = 0; i < copie.nrLuniVechime; i++)
				this->istoricSalarii[i] = copie.istoricSalarii[i];
		}
		else this->istoricSalarii = nullptr;
		this->departament = copie.departament;
		delete[] istoricSalarii;
		return *this;
	
	
	}

	void afisareAngajat() {
 		
		cout << endl << "Angajatul" <<idAngajat<<" " << this->nume << " Are salariul de baza : " << this->salariuBaza << ", luni vechime : " << this->nrLuniVechime<<" ";
		cout << "Avand in fiecare luna salariul: ";
		if (this->istoricSalarii != nullptr)
			for (int i = 0; i < this->nrLuniVechime; i++)
				cout << istoricSalarii[i] << ", ";
		cout << "Si lucreaza la departamentul: " << this->departament;
		
	
	}
	
	float* getistoricSalarii() {
	
		float* copieIstoric = new float[this->nrLuniVechime];
		for (int i = 0; i < this->nrLuniVechime; i++)
			copieIstoric[i] = this->istoricSalarii[i];
		return copieIstoric;
	}

	void setNrLuniVechime(int nrLuniVechimeNou) {
		if (nrLuniVechime > 0)
		{
			this->nrLuniVechime = nrLuniVechimeNou;
		}
		else {
			//throw exception();
			//throw 404;
			throw "Valoare negativa";
		}
	}

	void setIstoricSalarii(float* istoricNou, int nrLuniNou) {
	
		setNrLuniVechime(nrLuniNou);
		if (this->istoricSalarii != nullptr)
		{
			delete[] this->istoricSalarii;
			this->istoricSalarii = nullptr;
		}
		this->istoricSalarii = new float[nrLuniNou];
		for (int i = 0; i < nrLuniNou; i++)
		{
			this->istoricSalarii[i] = istoricNou[i];

		}
		delete[] istoricNou;
	}

	
	
	~Angajat() {
		if (this->istoricSalarii != nullptr)
		{
			delete[] istoricSalarii;
			istoricSalarii = nullptr;
		}
	
	}




};
int Angajat::contorAngajati = 0;

void main() {
	Angajat a1;

	a1.afisareAngajat();
	float* istoricSalarii = new float[3] {3, 4, 5};
	Angajat* a2 = new Angajat("Ion", 400, 3, istoricSalarii, IT);
	a2->afisareAngajat();
	Angajat* a3= new Angajat;
	a3 = a2;
	a3->afisareAngajat();




}








