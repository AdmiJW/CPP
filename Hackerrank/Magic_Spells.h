#pragma once

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


class Spell {
	string scrollName;
public:
	Spell() : scrollName("") {}
	Spell(string name) : scrollName(name) {}
	virtual ~Spell() {}
	string revealScrollName() {
		return scrollName;
	}
};

class Fireball : public Spell {
	int power;
public:
	Fireball(int power) : Spell(), power(power) {}
	void revealFirepower() {
		cout << "Fireball: " << power << endl;
	}
};


class Frostbite : public Spell {
	int power;
public:
	Frostbite(int power) : Spell(), power(power) {}
	int revealFrostpower() {
		cout << "Frostbite: " << power << endl;
	}
};


class Thunderstorm : public Spell {
	int power;
public:
	Thunderstorm(int power) : Spell(), power(power) {}
	void revealThunderpower() {
		cout << "Thunderstorm: " << power << endl;
	}
};


class Waterbolt : public Spell {
	int power;
public:
	Waterbolt(int power) : Spell(), power(power) {}
	int revealWaterpower() {
		cout << "Waterbolt: " << power << endl;
	}
};


class SpellJournal {
public:
	static string journal;
	static string read() {
		return journal;
	}
};
string SpellJournal::journal = "";



void counterSpell(Spell* spell) {
	Fireball* fire = dynamic_cast<Fireball*>(spell);
	Waterbolt* water = dynamic_cast<Waterbolt*>(spell);
	Thunderstorm* thund = dynamic_cast<Thunderstorm*>(spell);
	Frostbite* frost = dynamic_cast<Frostbite*>(spell);
	if (fire) {
		fire->revealFirepower();
	}
	else if (water) {
		water->revealWaterpower();
	}
	else if (thund) {
		thund->revealThunderpower();
	}
	else if (frost) {
		frost->revealFrostpower();
	}
	else {
		cout << longestCommonSubsq(spell->revealScrollName()) << endl;
	}
}


int longestCommonSubsq(string name) {
	string journal = SpellJournal::journal;
	int nlen = name.length();
	int jlen = journal.length();
	
	cout << nlen << " " << jlen << endl;

	//	ALLOCATING DYNAMIC ARRAY
	int** dp = new int*[ nlen + 1 ];
	for (int i = 0; i <= nlen; i++) {
		dp[i] = new int[jlen + 1]{};	// USE THE {} TO INITIALIZE THEM ARRAY TO 0
	}

	//	DYNAMIC PROGRAMMING: LONGEST COMMON SUBSEQUENCE(LCS)
	for (int i = 0; i < nlen; i++) {
		for (int j = 0; j < jlen; j++) {
			if (name[i] == journal[j]) {
				dp[i + 1][j + 1] = dp[i][j] + 1;
			}
			else {
				dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
			}
		}
	}

	int res = dp[nlen][jlen];

	cout << res << endl;

	//	DEALLOCATING DYNAMIC ARRAY
	for (int i = 0; i < nlen; i++) {
		delete[] dp[i];
	}
	delete[] dp;

}



class Wizard {
public:
	Spell* cast() {
		Spell* spell;
		string spellname; cin >> spellname;
		int power; cin >> power;

		if (spellname == "fire")
			spell = new Fireball(power);
		else if (spellname == "frost")
			spell = new Frostbite(power);
		else if (spellname == "water")
			spell = new Waterbolt(power);
		else if (spellname == "thunder")
			spell = new Thunderstorm(power);
		else {
			spell = new Spell(spellname);
			cin >> SpellJournal::journal;
		}
		return spell;
	}
};