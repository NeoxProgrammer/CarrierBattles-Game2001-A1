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


class Carrier {
private: 
	string name; 
	Fighter** baylist; 
	int maxBays; 
	int numFighters; 

	

	

};


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



int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
