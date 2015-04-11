#ifndef _TEXTGAME_MAINHEADER_H_
#define _TEXTGAME_MAINHEADER_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "enemyClass.h"
#include "playerClass.h"

#define GRID_DIMENSION 20
#endif //_TEXTGAME_MAINHEADER_H_

using namespace std;

// Generate Integer Level Map
vector< vector<int> > generateIntMap(vector<string> itemsList, int numEnemies){

    // Random Seed
    srand (time(NULL));

    // Numeric Item Vector
    vector<int> itemIntList;
    vector< vector<int> > masterVector;

    // Error Checking
    if(itemsList.size() + numEnemies > (GRID_DIMENSION * GRID_DIMENSION)){

        cout << "Too Many Items on Map!" << endl;
        exit(1);

    }

    // Iterate Through List and Assign a Number to Each Item
    for(int counter = 1; (counter - 1) < itemsList.size(); counter++){

        // Append the Item Number to the 'itemIntList' Vector
        itemIntList.push_back(counter);

    }

    // Initialize 2D int Matrix to Map Items
    int mapOverlay[GRID_DIMENSION][GRID_DIMENSION] = {0};

    // Add Door (111) to Map
    int doorLocation = (int)(GRID_DIMENSION/2);
    mapOverlay[doorLocation][0] = 111;

    // Add Player (999) to Map
    int playerLocation = (int)(GRID_DIMENSION/2);
    mapOverlay[playerLocation][(GRID_DIMENSION - 1)] = 999;

    // While There are Still Items in 'itemIntList'
    while(itemIntList.size() > 0){

        // Generate Two Random Seeds for Each Matrix Dimension
        int random1 = rand() % GRID_DIMENSION;
        int random2 = rand() % GRID_DIMENSION;

        // Generate a New Random if Both Digits are the Same
        while(random1 == random2){
            random2 = rand() % GRID_DIMENSION;
        }

        // If Map Position is Empty, Fill it With an Item
        if(mapOverlay[random1][random2] == 0){
            mapOverlay[random1][random2] = itemIntList.back();
            itemIntList.pop_back();
        }

    }

    // While There are Still Enemies to Place
    while(numEnemies > 0){

        // Generate Two Random Seeds for Each Matrix Dimension
        int randomE1 = rand() % GRID_DIMENSION;
        int randomE2 = rand() % GRID_DIMENSION;

        // Generate a New Random if Both Digits are the Same
        while(randomE1 == randomE2){
            randomE2 = rand() % GRID_DIMENSION;
        }

        // If Map Position is Empty, Fill it With an Enemy
        if(mapOverlay[randomE1][randomE2] == 0){
            mapOverlay[randomE1][randomE2] = 666;
            numEnemies = numEnemies - 1;
        }

    }

    // Stores the Temporary Vector to Push into the Master Vector
    vector<int> tempVector;

    // Iterator of the mapOverlay
    for(int i = 0; i < GRID_DIMENSION; i++){

        for(int j = 0; j < GRID_DIMENSION; j++){

            // Push Contents into the Temp Vector
            tempVector.push_back(mapOverlay[i][j]);

        }

        // Push the Temp Vector into the Master Vector and then Clear the Temp Vector
        masterVector.push_back(tempVector);
        tempVector.clear();

    }

    // Returns the Master Vector
    return masterVector;

}

// Generate Player Level Map
vector< vector<string> > generatePlayerMap(vector< vector<int> > intMap){

    vector< vector<string> > masterPlayerMap;
    vector<string> tempArray;

    for(int i = 0; i < intMap.size(); i++){
        for(int j = 0; j < intMap.size(); j++){

            int element = intMap.at(i).at(j);
            string converted;

            if(element == 666 || element == 0){
                converted = ".";
            }

            else if(element == 111){
                converted = "D";
            }

            else if(element == 999){
                converted = "P";
            }

            else{
                converted = "I";
            }

            tempArray.push_back(converted);

        }

        masterPlayerMap.push_back(tempArray);
        tempArray.clear();

    }

    return masterPlayerMap;

}

// Converts String to Uppercase
void stringToUpper(string &s){
    for(unsigned int l = 0; l < s.length(); l++){
        s[l] = toupper(s[l]);
    }
}

// Outputs the Integer Map
void printIntMap(vector< vector<int> > inputVector){

    // Get Vector Size
    int inputSize = inputVector.size();

    // Print Every Element of Vector
    for(int i = 0; i < inputSize; i++){
        for(int j = 0; j < inputSize; j++){
            cout << setw(5) << inputVector.at(i).at(j);
        }
        cout << endl;
    }

    // Print Blank Line
    cout << endl;

}

// Outputs the Map that the Player Sees
void printPlayerMap(vector< vector<string> > inputVector){

    // Get Vector Size
    int inputSize = inputVector.size();

    // Print Every Element of Vector
    for(int i = 0; i < inputSize; i++){
        for(int j = 0; j < inputSize; j++){
            cout << setw(5) << inputVector.at(i).at(j);
        }
        cout << endl;
    }

    // Print Blank Line
    cout << endl;

}

// Returns a Vector Containing the Players Current X,Y Position
vector<int> getPlayerPosition(vector< vector<string> >& playerMap){

    vector<int> playerPositionVector;

    for(int i = 0; i < playerMap.size(); i++){

        for(int j = 0; j < playerMap.size(); j++){

            if(playerMap.at(i).at(j) == "P"){

                playerPositionVector.push_back(j);
                playerPositionVector.push_back(i);
                return playerPositionVector;

            }

        }

    }

    return playerPositionVector;

}

// Movement Function
void movePlayer(string direction, vector< vector<int> >& intMap, vector< vector<string> >& playerMap){

    // Get the Player's Coordinates
    vector<int> playerPosition = getPlayerPosition(playerMap);

    // Stores the Maximum Dimension of the Player Map
    int maxSize = playerMap.size() - 1;

    // Stores Current Position Data
    int currentYPosition = playerPosition.at(1);
    int currentXPosition = playerPosition.at(0);

    // Direction Control
    if(direction == "NORTH"){

        int futureYPosition = playerPosition.at(1) - 1;

        if(futureYPosition <= maxSize && futureYPosition >= 0){

            // Mark Old Space as Walked On
            if(intMap.at(currentYPosition).at(currentXPosition) != 111) {
                intMap.at(currentYPosition).at(currentXPosition) = 0;
                playerMap.at(currentYPosition).at(currentXPosition) = "*";
            }

            // Mark New Player Position
            playerMap.at(futureYPosition).at(currentXPosition) = "P";

            // Check for Items/Events
            if(intMap.at(futureYPosition).at(currentXPosition) != 0){

                int interactionStatus = intMap.at(futureYPosition).at(currentXPosition);

                /* If Enemy, Start Battle */
                if(interactionStatus == 666){
                    Spider spider1;
                    int eLevel = spider1.returnLevel();
                    int eHealth = spider1.returnHealth();
                    cout << "YOU HAVE ENCOUNTERED A SPIDER OF LEVEL " << eLevel << " AND HEALTH " << eHealth << endl;
                }

                /* If Item/Puzzle, Announce/Pickup Item */
                if(interactionStatus <= 100){
                    int ElementNumber = intMap.at(futureYPosition).at(currentXPosition);
                    cout << "YOU HAVE ENCOUNTERED ITEM " << ElementNumber << endl;
                }

                // After Interaction is Completed Mark the Player Position
                intMap.at(futureYPosition).at(currentXPosition) = 999;

            }

            else{

                intMap.at(futureYPosition).at(currentXPosition) = 999;

            }

        }

        else{

            cout << "Cannot Move Further North!" << endl;

        }

    }

    if(direction == "SOUTH"){

        int futureYPosition = playerPosition.at(1) + 1;

        if(futureYPosition <= maxSize && futureYPosition >= 0){

            // Mark Old Space as Walked On
            if(intMap.at(currentYPosition).at(currentXPosition) != 111) {
                intMap.at(currentYPosition).at(currentXPosition) = 0;
                playerMap.at(currentYPosition).at(currentXPosition) = "*";
            }

            // Mark New Player Position
            playerMap.at(futureYPosition).at(currentXPosition) = "P";

            // Check for Items/Events
            if(intMap.at(futureYPosition).at(currentXPosition) != 0){

                int interactionStatus = intMap.at(futureYPosition).at(currentXPosition);

                /* If Enemy, Start Battle */
                if(interactionStatus == 666){
                    Spider spider1;
                    int eLevel = spider1.returnLevel();
                    int eHealth = spider1.returnHealth();
                    cout << "YOU HAVE ENCOUNTERED A SPIDER OF LEVEL " << eLevel << " AND HEALTH " << eHealth << endl;
                }

                /* If Item/Puzzle, Announce/Pickup Item */
                if(interactionStatus <= 100){
                    int ElementNumber = intMap.at(futureYPosition).at(currentXPosition);
                    cout << "YOU HAVE ENCOUNTERED ITEM " << ElementNumber << endl;
                }

                // After Interaction is Completed Mark the Player Position
                intMap.at(futureYPosition).at(currentXPosition) = 999;

            }

            else{

                intMap.at(futureYPosition).at(currentXPosition) = 999;

            }

        }

        else{

            cout << "Cannot Move Further South!" << endl;

        }

    }

    if(direction == "WEST"){

        int futureXPosition = playerPosition.at(0) - 1;

        if(futureXPosition <= maxSize && futureXPosition >= 0){

            // Mark Old Space as Walked On
            if(intMap.at(currentYPosition).at(currentXPosition) != 111) {
                intMap.at(currentYPosition).at(currentXPosition) = 0;
                playerMap.at(currentYPosition).at(currentXPosition) = "*";
            }

            // Mark New Player Position
            playerMap.at(currentYPosition).at(futureXPosition) = "P";

            // Check for Items/Events
            if(intMap.at(currentYPosition).at(futureXPosition) != 0){

                int interactionStatus = intMap.at(currentYPosition).at(futureXPosition);

                /* If Enemy, Start Battle */
                if(interactionStatus == 666){
                    Spider spider1;
                    int eLevel = spider1.returnLevel();
                    int eHealth = spider1.returnHealth();
                    cout << "YOU HAVE ENCOUNTERED A SPIDER OF LEVEL " << eLevel << " AND HEALTH " << eHealth << endl;
                }

                /* If Item/Puzzle, Announce/Pickup Item */
                if(interactionStatus <= 100){
                    int ElementNumber = intMap.at(currentYPosition).at(futureXPosition);
                    cout << "YOU HAVE ENCOUNTERED ITEM " << ElementNumber << endl;
                }

                // After Interaction is Completed Mark the Player Position
                intMap.at(currentYPosition).at(futureXPosition) = 999;

            }

            else{

                intMap.at(currentYPosition).at(futureXPosition) = 999;

            }

        }

        else{

            cout << "Cannot Move Further West!" << endl;

        }

    }

    if(direction == "EAST"){

        int futureXPosition = playerPosition.at(0) + 1;

        if(futureXPosition <= maxSize && futureXPosition >= 0){

            // Mark Old Space as Walked On
            if(intMap.at(currentYPosition).at(currentXPosition) != 111) {
                intMap.at(currentYPosition).at(currentXPosition) = 0;
                playerMap.at(currentYPosition).at(currentXPosition) = "*";
            }

            // Mark New Player Position
            playerMap.at(currentYPosition).at(futureXPosition) = "P";

            // Check for Items/Events
            if(intMap.at(currentYPosition).at(futureXPosition) != 0){

                int interactionStatus = intMap.at(currentYPosition).at(futureXPosition);

                /* If Enemy, Start Battle */
                if(interactionStatus == 666){
                    Spider spider1;
                    int eLevel = spider1.returnLevel();
                    int eHealth = spider1.returnHealth();
                    cout << "YOU HAVE ENCOUNTERED A SPIDER OF LEVEL " << eLevel << " AND HEALTH " << eHealth << endl;
                }

                /* If Item/Puzzle, Announce/Pickup Item */
                if(interactionStatus <= 100){
                    int ElementNumber = intMap.at(currentYPosition).at(futureXPosition);
                    cout << "YOU HAVE ENCOUNTERED ITEM " << ElementNumber << endl;
                }

                // After Interaction is Completed Mark the Player Position
                intMap.at(currentYPosition).at(futureXPosition) = 999;

            }

            else{

                intMap.at(currentYPosition).at(futureXPosition) = 999;

            }

        }

        else{

            cout << "Cannot Move Further East!" << endl;

        }

    }

}
