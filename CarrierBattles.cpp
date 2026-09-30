// CarrierBattles.cpp : This file contains the 'main' function. Program execution begins and ends there.

//student number 101545977


using namespace std;
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility> 

constexpr int HIT_THRESHOLD = 50;   // a roll of 50-100 out of 100 is a hit
constexpr int REPAIR_PERCENT = 5;   // repair 5% of max structural strength

class Fighter {
private:
	string name;
	int damage;
	int structStrength;
	int maxStructStrength;

public:
	Fighter(const string& name, int maxStructStrength, int damage) {
		this->name = name;
		this->damage = damage;
		this->maxStructStrength = maxStructStrength;
		this->structStrength = maxStructStrength;

	}


	void reduceStructure(int amount) {
		structStrength -= amount;
		if (structStrength < 0) {
			structStrength = 0;
		}

	}

	void repair(int amount) {
		structStrength += amount;
		if (structStrength > maxStructStrength) {
			structStrength = maxStructStrength;
		}
	}

	bool isDestroyed() const {
		if (structStrength <= 0) {
			return true;
		}

		else {
			return false;
		}
	}


	string getName() const {
		return name;
	}

	int getDamage() const {
		return damage;
	}

	int getStructStrength() const {
		return structStrength;
	}

	int getMaxStructStrength() const {
		return maxStructStrength;
	}


	string getInfo() const {
		ostringstream oss;
		oss << "Name: " << name << "\n";
		oss << "Structural Strength: " << structStrength << "/" << maxStructStrength << "\n";
		oss << "Damage: " << damage << "\n";
		return oss.str();
	}
};






class Carrier {
private: 
	string name; 
	Fighter** bayList; 
	int maxBays; 
	int numFighters; 
public:


	Carrier(const string& name, int maxBays) {
		this->name = name; 
		this->maxBays = maxBays; 
		bayList = new Fighter* [maxBays](); 
		this->numFighters = 0; 
	}

	~Carrier() {

		for (int i = 0; i < numFighters; i++) {
			delete bayList[i];
		

		}
		delete[] bayList; 

		bayList = nullptr; 
	}


	bool loadFighter(Fighter* fighter) {
		if (numFighters < maxBays) {
			bayList[numFighters] = fighter; 
			numFighters++; 
			return true; 
		}
		return false; 
	}

	Fighter* launchNextFighter() {

		if (numFighters == 0) {
			return nullptr; 
		}
		if (numFighters > 0) {

			Fighter* removedFighter = bayList[0]; 
			
			for (int i = 1; i < numFighters; i++) {
				bayList[i - 1] = bayList[i];
			}
			numFighters--; 
			return removedFighter;
		}
	}
	
	void repairAllFighters() {
		for (int i = 0; i < numFighters; i++) {
			Fighter* currentFighter = bayList[i];
			int maxStrength = currentFighter->getMaxStructStrength(); 
			int amountToIncreaseBy = maxStrength * REPAIR_PERCENT / 100;
			currentFighter->repair(amountToIncreaseBy); 
		}
	}




	void insertionSortByStrength() {
		
		// sort the array by structStrength
		Fighter* temp; int prev;
		for (int start = 1; start < numFighters; start++) {
			prev = start - 1; 
			temp = bayList[start]; 
			
			while (prev >= 0 && bayList[prev]->getStructStrength() < temp->getStructStrength()) {
				bayList[prev + 1] = bayList[prev]; 
				prev--; 
			}
			bayList[prev + 1] = temp; 
		}

	}






	void mergeSortByName() {
		
	}


	void mergeSortWorker(int lower, int upper) {
		int mid; 
		if (lower < upper) {
			mid = (lower + upper) / 2;
			mergeSortWorker(lower, mid); 
			mergeSortWorker(mid + 1, upper); 
		}
	}


	

};





int main()
{
	std::cout << "Hello World!\n"; 
}


