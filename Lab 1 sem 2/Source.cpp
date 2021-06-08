#include <iostream>

using namespace std;

class NPC
{
private: 
	string Name;
	int hitPoints;
	int Damage; 
	int* Items[];
public:
	NPC(string name, int hp, int dam) {
		this->Name = Name;
		hitPoints = hp;
		Damage = dam;
		Items = new int[10];
	}
	
	string getName() { return Name; }
	int getHitPoints() { return hitPoints; }
	int getDamage() { return Damage; }

	void setName(string Name) {
		this->Name = Name;
	}
	void setDamage(int amt) {
		Damage = amt;
	}
	void sethitPoints(int amt) {
		hitPoints = amt;
	}

	void addItem(int loc, int value) {
		Items[loc] = value;
	}


};

int main()
{
	NPC np1("Dragon", 1500, 140);
	np1.addItem(1, 566);
	NPC np2("Soilder", 500, 50);
	NPC* np3 = new NPC("Kobold", 78, 15);

	cout << np1.getName();
	cout << np1.getHitPoints();
	cout << np1.getDamage();
	cout << np1.getItem(1);
	cout << "=================\n";
	cout << np2.getName();
	cout << np2.getHitPoints();
	cout << np2.getDamage();
	cout << "=================\n";
	cout << np3->getName();
	cout << np3->getHitPoints();
	cout << np3->getDamage();


	return 0;
}

