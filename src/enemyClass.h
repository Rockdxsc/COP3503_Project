#ifndef _TEXTGAME_ENEMYCLASS_H_
#define _TEXTGAME_ENEMYCLASS_H_

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#endif //_TEXTGAME_ENEMYCLASS_H_

using namespace std;

class Spider{

private:

    int spiderHealth;
    int spiderLevel;

public:

    // Default Constructor
    Spider(){

        int sLevel;     // Stores the Randomized Spider's Level
        int sHealth;    // Stores the Calculated Health
        int sLevelMax;  // Max Level Range
        int sLevelMin;  // Min Level Range

        // Random Seed
        srand (time(NULL));

        // Generate Random Level Between 1 and 10
        sLevel = 1 + (rand() % (int)(10 - 1 + 1));

        // Random Health Based on Level
        sLevelMax = sLevel * 10;
        sLevelMin = (sLevel * 10) - 10;
        sHealth = sLevelMin + (rand() % (int)(sLevelMax - sLevelMin + 1));

        // Generate Spider Level and Health
        spiderLevel = sLevel;
        spiderHealth = sHealth;

    }

    // Deal Damage to Spider's Health
    void dealDamage(int damageDealt){
        spiderHealth = spiderHealth - damageDealt;
    }

    // Returns the Spider's Health
    int returnHealth(){
        return spiderHealth;
    }

    // Returns the Spider's Level
    int returnLevel(){
        return spiderLevel;
    }

    // Randomly Generated Attack Strength
    int attack(){

        // Generate Random Seed
        srand (time(NULL));

        int attackPower = (int)(spiderLevel/2) + (rand() % (int)((spiderLevel+2) - (spiderLevel/2) + 1));
        return attackPower;

    }

};

class Boss{

private:

	int Health;
	int Level;

public:

	// Default Constructor
	Boss(){
	
		srand(time(NULL));
		Health = 1000000;

	}

	// Deal Damage to Spider's Health
	void dealDamage(int damageDealt){
		Health -= damageDealt;
	}

	// Returns the Spider's Health
	int returnHealth(){
		return Health;
	}

	// Returns the Spider's Level
	int returnLevel(){
		return Level;
	}

	// Randomly Generated Attack Strength
	int attack(){

		// Generate Random Seed
		srand(time(NULL));

		int attackPower = 4 + (int)(rand() % 3);
		return attackPower;

	}

};
