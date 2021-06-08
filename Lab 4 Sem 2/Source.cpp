#include <iostream>
#include <sstream>
#include <time.h>
#include <cstdlib>

using namespace std;

class CombatNPC
{
	string name;
	int maxHp;
	int strength;
	int presentHp;
	int intelligence;
	int baseDamage;

public:
	CombatNPC(string name, int maxHp, int str, int intel, int, int baseDam)
	{
		this->name = name;
		this->maxHp = maxHp;
		presentHp = maxHp;
		intelligence = intel;
		baseDamage = baseDam;
	}

	string getName()const { return name; }
	int getStrength()const { return strength; }
	int getIntelligence()const { return intelligence; }
	int getMaxHp()const { return maxHp; }
	int getPresentHp()const { return presentHp; }

	int getAttackValue()
	{
		return baseDamage;
	}

	void gettakeDamage(int amt)
	{
		presentHp -= amt;
		if (presentHp < 0) {
			presentHp = 0;
		}
	}

	string toString()
	{
		stringstream s;
		s << "Name: " << name << "\n";
		s << "Max Hp: " << maxHp << "\n";
		s << "Present Hp: " << presentHp << "\n";
		s << "Strength: " << strength << "\n";
		s << "Intelligence: " << intelligence << "\n";
		return s.str();
	}
};