// CarrierBattles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//student number 101545977



#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility> 
#include <cctype>

using namespace std;

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


	const string& getName() const {
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

	Carrier(const Carrier&) = delete;
	Carrier& operator=(const Carrier&) = delete;


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

		

		Fighter* removedFighter = bayList[0]; 
			
		for (int i = 1; i < numFighters; i++) {
			bayList[i - 1] = bayList[i];
		}
		numFighters--; 
		bayList[numFighters] = nullptr;
		return removedFighter;
		
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
		mergeSortWorker(0,numFighters-1);
	}


	void mergeSortWorker(int lower, int upper) {
		int mid; 
		if (lower < upper) {
			mid = (lower + upper) / 2;
			mergeSortWorker(lower, mid); 
			mergeSortWorker(mid + 1, upper); 
			merge(lower, mid, upper); 
		}
	}

	void merge(int lo,int mid,int hi) {
		int i, j,  k; 
		int size = hi - lo + 1; 
		Fighter** temp = new Fighter*[size]; 
		i = lo; j = mid + 1; k = 0; 
		while (i <= mid && j <= hi) {
			string iName = bayList[i]->getName(); 
			string jName = bayList[j]->getName(); 
			if (iName < jName) {
				temp[k] = bayList[i]; 
				i++, k++; 
			}

			else {
				temp[k] = bayList[j]; 
				j++, k++;

			}
		}

		while (j <= hi) {
			temp[k] = bayList[j]; 
			j++, k++; 
		}

		while (i <= mid) {
			temp[k] = bayList[i];
			i++, k++; 
		}

		for (int x = 0; x < size; x++) {
			bayList[lo + x] = temp[x]; 
		}
		delete[] temp; 
	}

	bool hasFighters() const {
		if (numFighters > 0) {
			return true; 

		}
		return false; 
	}


	int getNumFighters() const {
		return numFighters; 
	}


	int getCapacity() const {
		return maxBays; 
	}

	const string& getName() const{
		return name; 
	}


	string getInfo() const {


		if (numFighters <= 0) {
			ostringstream oss2; 
			oss2 << "Name: " << name << "\n";
			oss2 << "Bays in use " << getNumFighters() << "\n";
			oss2 << "Max capacity: " << getCapacity() << "\n";
			oss2 << "No Fighters are loaded and ready to shoot" << "\n";
			return oss2.str(); 


		}



		ostringstream oss;
		oss << "Name: " << name << "\n";
		oss << " Bays in use: " << getNumFighters() <<"\n";
		oss << "Max capacity: " << getCapacity() << "\n";
		string mainString = "";
		for (int i = 0; i < getNumFighters(); i++) {
			string info = bayList[i]->getInfo() + "\n";
			mainString += info;
		}

		oss << "info for the carrier is:\n" << mainString; 
		return oss.str();
	}
};



void stripTrailingWhitespace(string& s) {
	while (!s.empty() && isspace(static_cast<unsigned char>(s.back()))) {
		s.pop_back();
	}
}


Carrier* readCarrier(istream& in) {
	string carrierName;
	getline(in >> std::ws, carrierName);
	stripTrailingWhitespace(carrierName);

	if (in.fail()) {
		return nullptr;
	}

	int maxBays, numFightersListed;
	in >> maxBays >> numFightersListed;

	if (in.fail()) {
		return nullptr;
	}

	Carrier* c = new Carrier(carrierName, maxBays);

	for (int i = 0; i < numFightersListed; i++) {
		string fighterName;

		getline(in >> std::ws, fighterName);
		stripTrailingWhitespace(fighterName);  // FIXED

		if (in.fail()) {
			delete c;
			return nullptr;
		}

		int strength, damage;
		in >> strength >> damage;

		if (in.fail()) {
			delete c;
			return nullptr;
		}

		Fighter* f = new Fighter(fighterName, strength, damage);

		if (!c->loadFighter(f)) {
			cout << "Warning: " << fighterName
				<< " could not be loaded\n";
			delete f;
		}
	}

	return c;
}

int rollDie(std::mt19937& rng, int sides)
{
	uniform_int_distribution<int> dist(1, sides);
	return dist(rng);
}


bool attack(Fighter& attacker, Fighter& defender, int round, std::mt19937& rng) {
	// Roll a die to determine if the attack hits
	int roll = rollDie(rng, 100);
	if (roll >= HIT_THRESHOLD) {
		int maxdamage = attacker.getDamage();
		int damageAmount = rollDie(rng, maxdamage);
		defender.reduceStructure(damageAmount);
		cout << "[R" << round << "] "
			<< attacker.getName() << " hits "
			<< defender.getName() << " for "
			<< damageAmount << " ("
			<< defender.getName() << ": "
			<< defender.getStructStrength() << "/"
			<< defender.getMaxStructStrength() << ")\n";
		
		return defender.isDestroyed();
	}

	else {
		cout << "[R" << round << "] " << attacker.getName() << " misses " << defender.getName() << "\n";
		return defender.isDestroyed();
	}

}

Fighter* duel(Fighter* f1, Fighter* f2, std::mt19937& rng) {
	int counter = 0;
	while (true) {
		counter++;
		int whoGoesFirst = rollDie(rng, 2);
		if (whoGoesFirst == 1) {
			if (attack(*f1, *f2, counter, rng)) {
				cout << "BOOOM! " << f2->getName() << " is destroyed!\n";
				return f1;
			}
			if (attack(*f2, *f1, counter, rng)) {
				cout << "BOOOM! " << f1->getName() << " is destroyed!\n";
				return f2;
			}
		}

		else if (whoGoesFirst == 2)		 {
			if (attack(*f2, *f1, counter, rng)) {
				cout << "BOOOM! " << f1->getName() << " is destroyed!\n";	
				return f2;
			}

			if (attack(*f1, *f2, counter, rng)) {
				cout << "BOOOM! " << f2->getName() << " is destroyed!\n";
				return f1;
			}		

		}
	}

}

void battle(Carrier& c1, Carrier& c2, std::mt19937& rng) {
	int duels = 0;
	while (c1.hasFighters() && c2.hasFighters()) {
		duels++;
		c1.insertionSortByStrength();
		c2.insertionSortByStrength();
		Fighter* f1 = c1.launchNextFighter();
		Fighter* f2 = c2.launchNextFighter();

		cout << "Duel " << duels << ": "
			<< f1->getName() << " (" << c1.getName() << ") vs "
			<< f2->getName() << " (" << c2.getName() << ")\n";

		Fighter* winner = duel(f1, f2, rng);

		if (winner == f1) {
			cout << f1->getName() << " returns to " << c1.getName()
				<< " with " << f1->getStructStrength() << "/"
				<< f1->getMaxStructStrength() << " structure.\n";
			c1.loadFighter(f1);
			delete f2;
		}
		else if (winner == f2) {
			cout << f2->getName() << " returns to " << c2.getName()
				<< " with " << f2->getStructStrength() << "/"
				<< f2->getMaxStructStrength() << " structure.\n";
			c2.loadFighter(f2);
			delete f1;
		}

		c1.repairAllFighters();
		c2.repairAllFighters();
	}

	if (c1.hasFighters()) {
		cout << "*** " << c1.getName() << " wins the battle after "
			<< duels << " duels with " << c1.getNumFighters()
			<< " fighter(s) remaining. ***\n";
	}
	else if (c2.hasFighters()) {
		cout << "*** " << c2.getName() << " wins the battle after "
			<< duels << " duels with " << c2.getNumFighters()
			<< " fighter(s) remaining. ***\n";
	}
}
	

int main()
{

	mt19937 rng(std::random_device{}()); // Initialize with random seed i think is what this does
	

	ifstream in("shipData_small.txt");
	if (!in) {
		cout << "Could not open file\n";
		return 1;
	}

	Carrier* c1 = readCarrier(in); // Read the first carrier from the file
	Carrier* c2 = readCarrier(in); // Read the second carrier from the file

	if (c1 == nullptr || c2 == nullptr) {
		cout << "Error reading carriers from file\n";
		delete c1;
		delete c2;
		return 1;
	}

	c1->mergeSortByName();
	c2->mergeSortByName();

	c1->getInfo(); 
	c2->getInfo();

	battle(*c1, *c2, rng);
	
	c1->getInfo();
	c2->getInfo();

	delete c1;
	delete c2;





}


