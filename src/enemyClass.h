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

 class Goblin{

private:

    int goblinHealth;
    int goblinLevel;

public:

 Goblin(){

        int gLevel;     // Stores the Randomized Goblin's Level
        int gHealth;    // Stores the Calculated Health
        int gLevelMax;  // Max Level Range
        int gLevelMin;  // Min Level Range

        // Random Seed
        srand (time(NULL));

        // Generate Random Level Between 2 and 11
        gLevel = 2 + (rand() % (int)(10 - 1 + 1));

        // Random Health Based on Level
        gLevelMax = gLevel * 10;
        gLevelMin = (gLevel * 10) - 10;
        gHealth = gLevelMin + (rand() % (int)(gLevelMax - gLevelMin + 1));

        // Generate Goblin Level and Health
        goblinLevel = gLevel;
        goblinHealth = gHealth;

    }

    // Deal Damage to Goblin's Health
    void dealDamage(int damageDealt){
        goblinHealth = goblinHealth - damageDealt;
    }

    // Returns the goblin's Health
    int returnHealth(){
        return goblinHealth;
    }

    // Returns the goblin's Level
    int returnLevel(){
        return goblinLevel;
    }

    // Randomly Generated Attack Strength
    int attack(){

        // Generate Random Seed
        srand (time(NULL));

        int attackPower = (int)(goblinLevel/2) + (rand() % (int)((goblinLevel+2) - (goblinLevel/2) + 1));
        return attackPower;

    }
};


class Orc{

private:

    int orcHealth;
    int orcLevel;

public:

     Orc(){

        int oLevel;     // Stores the Randomized Orc's Level
        int oHealth;    // Stores the Calculated Health
        int oLevelMax;  // Max Level Range
        int oLevelMin;  // Min Level Range

        // Random Seed
        srand (time(NULL));

        // Generate Random Level Between 3 and 12
        oLevel = 3 + (rand() % (int)(10 - 1 + 1));

        // Random Health Based on Level
        oLevelMax = oLevel * 10;
        oLevelMin = (oLevel * 10) - 10;
        oHealth = oLevelMin + (rand() % (int)(oLevelMax - oLevelMin + 1));

        // Generate Orc Level and Health
        orcLevel = oLevel;
        orcHealth = oHealth;

    }

    // Deal Damage to Orc's Health
    void dealDamage(int damageDealt){
        orcHealth = orcHealth - damageDealt;
    }

    // Returns the Orc's Health
    int returnHealth(){
        return orcHealth;
    }

    // Returns the Orc's Level
    int returnLevel(){
        return orcLevel;
    }

    // Randomly Generated Attack Strength
    int attack(){

        // Generate Random Seed
        srand (time(NULL));

        int attackPower = (int)(orcLevel/2) + (rand() % (int)((orcLevel+2) - (orcLevel/2) + 1));
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
	
		Health = 1000;
		Level = 15;
	}

	// Deal Damage
	void dealDamage(int damageDealt){
		Health -= damageDealt;
	}

	// Returns Health
	int returnHealth(){
		return Health;
	}

	// Returns Level
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
