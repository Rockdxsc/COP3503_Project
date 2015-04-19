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
    
     Goblin(){

        int sLevel;     // Stores the Randomized Goblin's Level
        int sHealth;    // Stores the Calculated Health
        int sLevelMax;  // Max Level Range
        int sLevelMin;  // Min Level Range

        // Random Seed
        srand (time(NULL));

        // Generate Random Level Between 2 and 11
        sLevel = 2 + (rand() % (int)(10 - 1 + 1));

        // Random Health Based on Level
        sLevelMax = sLevel * 10;
        sLevelMin = (sLevel * 10) - 10;
        sHealth = sLevelMin + (rand() % (int)(sLevelMax - sLevelMin + 1));

        // Generate Goblin Level and Health
        goblinLevel = sLevel;
        goblinHealth = sHealth;

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

     Orc(){

        int sLevel;     // Stores the Randomized Orc's Level
        int sHealth;    // Stores the Calculated Health
        int sLevelMax;  // Max Level Range
        int sLevelMin;  // Min Level Range

        // Random Seed
        srand (time(NULL));

        // Generate Random Level Between 3 and 12
        sLevel = 3 + (rand() % (int)(10 - 1 + 1));

        // Random Health Based on Level
        sLevelMax = sLevel * 10;
        sLevelMin = (sLevel * 10) - 10;
        sHealth = sLevelMin + (rand() % (int)(sLevelMax - sLevelMin + 1));

        // Generate Orc Level and Health
        orcLevel = sLevel;
        orcHealth = sHealth;

    }

    // Deal Damage to Orc's Health
    void dealDamage(int damageDealt){
        spiderHealth = spiderHealth - damageDealt;
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
