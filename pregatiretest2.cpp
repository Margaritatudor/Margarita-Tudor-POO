#include <iostream>
#include <string>

using namespace std;
#pragma warning (disable: 4996)

class courier {
private:
	string courierName;
	int noShipments;
	int* distancePerShipment;
	int maxDistance;
	string companyName;

public:
	courier() {
		this->courierName = "Curier necunoscut";
		this->noShipments = 0;
		this->distancePerShipment = nullptr;
		this->maxDistance = 0;
		this->companyName = "";


	}

	int getmaxDistance() {
		return this->maxDistance;

	}

	void setMaxdistance(int newmaxdistance) {
		if (newmaxdistance > 0 && maxDistance < 500)
			this->maxDistance = newmaxdistance;

	}

	courier(string companyName, int maxDistance) {
		this->courierName = "Curier necunoscut";
		this->noShipments = 0;
		this->distancePerShipment = nullptr;
		this->maxDistance = maxDistance;
		this->companyName = companyName;

	}
	courier(string courierName, int noShipments, int* distancePerShipment, int maxDistance, string companyName) {
		this->courierName = courierName;
		this->noShipments = noShipments;
		this->distancePerShipment = new int[this->noShipments];
		if (distancePerShipment != nullptr)
		{
			for (int i = 0; i < this->noShipments; i++)
				this->distancePerShipment[i] = distancePerShipment[i];

		}

		this->maxDistance = maxDistance;
		this->companyName = companyName;
		delete[] distancePerShipment;
	}

	void afisarecourier() {

		cout << endl << " Numele curierului: " << this->courierName << " care are " << this->noShipments << " colete livrate " << " Cu distantele de: ";
		if(this->distancePerShipment!=nullptr)
		for (int i = 0; i < this->noShipments; i++)
			cout << distancePerShipment[i] << " km ";
	}
	~courier() {
		if (distancePerShipment != nullptr)
		{
			delete[] distancePerShipment;
			distancePerShipment = nullptr;
		}
	}


}

void main() {
	courier c1;
	c1.afisarecourier();

}
