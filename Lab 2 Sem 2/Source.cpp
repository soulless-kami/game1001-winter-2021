#include <iostream>
#include <sstream>
using namespace std;

class Ship
{
private:
	string name;
	int structralPoints;
	int primaryDamage;
	int secondaryDamage;
public:
	Ship(string n, int sp, int pDam, int sDam) {
		name = n;
		structralPoints = sp;
		primaryDamage = pDam;
		secondaryDamage = sDam;

	}
	
	
	void takeDamage(int amount) {
		structralPoints -= amount;
	}
	int getPrimaryAttack() const {
		return primaryDamage;
	}
	int getSecondaryAttack() const {
		return secondaryDamage;
	}

	string getShipInfo() {
		stringstream s;
		s << "Ship Name: " << name << "/t Structural Points: " << structralPoints; s << "/t Primary Damage: " << primaryDamage << "/t Secondary Damage: " << secondaryDamage;
		return s.str();
	}


};

class Carrier
{
private:
	string name;
	int numShips;
	int maxShips;
	Ship** shipList;

public:
	Carrier(string name, int maxShips) {
		this->name = name;
		this->maxShips = maxShips;
		numShips = 0;
		shipList = new Ship* [maxShips];
	}

	bool addShip(string n, int sp, int pDam, int sDam) {
		if (numShips < maxShips) {
			Ship* newShip= new Ship(n, sp, pDam, sDam);
			shipList[numShips] = newShip;
			numShips++;
			return true;
		}
		return false;
	}

	Ship* launchShip(int pos) {
		if (pos >= numShips) {
			return NULL;
		}
		Ship* temp = shipList[pos];
		shipList[pos] = shipList[numShips - 1];
		numShips--;
		return temp;
	}

	string getCarrierInfo() {
		stringstream s;
		s << "Carrier Name: " << name << "\n";
		s << "Ships Carried: \n";
		for (int x = 0; x < numShips; x++) {
			s << shipList[x]->getShipInfo() << "\n";
		}
		return s.str();
	}
	
	
	int getNumShips() {
		return numShips;
	}
	string getName() {
		return name;
	}

};

int main()
{
	Carrier c1("StarDestroyer", 150);
	c1.addShip("X-wing", 350, 25, 180);
	c1.addShip("Y-wing", 900, 15, 450);
	c1.addShip("A-wing", 150, 25, 65);
	cout << c1.getCarrierInfo();
	
	
	return 0;


}