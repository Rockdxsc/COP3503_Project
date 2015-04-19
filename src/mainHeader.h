#ifndef _TEXTGAME_MAINHEADER_H_
#define _TEXTGAME_MAINHEADER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include "enemyClass.h"
#include "playerClass.h"

#define GRID_DIMENSION 10
#define GRID_DIMENSION2 9               //added a seond grid dimension for floor 2
#endif //_TEXTGAME_MAINHEADER_H_

/* FUNCTION PROTOTYPES */
vector< vector<int> > generateIntMap(vector<string> itemsList, int numEnemies);
vector< vector<int> > generateIntMap2(vector<string> itemsList, int numEnemies);
vector< vector<string> > generatePlayerMap(vector< vector<int> > intMap);
vector<int> getPlayerPosition(vector< vector<string> >& playerMap);
void stringToUpper(string &s);
void inn(Player& mainPlayer);
void shop(Player& P);
void printIntMap(vector< vector<int> > inputVector);
void printPlayerMap(vector< vector<string> > inputVector);
void printItemMap(vector< vector<int> > inputVector);
void clearScreen();
void movePlayer(Player& gamePlayer, string direction, vector< vector<int> >& intMap, vector< vector<string> >& playerMap, vector<string> itemsList);
void enemyBattle(Player& mainPlayer, Spider& enemySpider);
void enemyBattle(Player& mainplayer, Goblin& enemyGoblin);
void enemyBattle(Player& mainplayer, Orc& enemyOrc);
void enemybossBattle(Player& mainPlayer, Boss& enemyBoss);
void playerUse(Player& player, string usingItem, vector< vector<int> > intMap);
void gameSave(vector< vector<int> > integerMap, vector < vector <int> > integerMap2, Player mainPlayer);
bool loadGame(vector< vector<int> >& integerMap, vector < vector<int> > &integerMap2, Player& mainPlayer);
bool checkFileExists(string file);
string printInventory(Player player);
int mapCheck();

// Game Floor Number
int gameFloor = 1;                   //added floor int to keep track of floor placement

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

    // Add Player (999) to Map
    int playerLocation = (int)(GRID_DIMENSION/2);
    mapOverlay[playerLocation][(GRID_DIMENSION - 1)] = 999;

    // Add Inn to the map
    int innLocation = playerLocation - 2;
    mapOverlay[innLocation][(GRID_DIMENSION - 1)] = 777;

    // Add Shop to the map
    int shopLocation = innLocation - 2;
    mapOverlay[shopLocation][(GRID_DIMENSION - 1)] = 778;

    //added "X" far a test floor change location
    int XLocation  = (int)(GRID_DIMENSION/2);
    mapOverlay[0][XLocation] = 888;

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
            int i = rand()%100;

            if (i >= 0 && i < 50){
                mapOverlay[randomE1][randomE2] = 666;
            }

            else if (i >= 50 && i < 80){
                mapOverlay[randomE1][randomE2] = 667;
            }

            else {
                mapOverlay[randomE1][randomE2] = 668;
            }

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


// Generate second Integer Level Map
vector< vector<int> > generateIntMap2(vector<string> itemsList, int numEnemies){

    // Random Seed
    srand (time(NULL));

    // Numeric Item Vector
    vector<int> itemIntList;
    vector< vector<int> > masterVector;

    // Error Checking
    if(itemsList.size() + numEnemies > (GRID_DIMENSION2 * GRID_DIMENSION2)){

        cout << "Too Many Items on Map!" << endl;
        exit(1);

    }

    // Iterate Through List and Assign a Number to Each Item
    for(int counter = 1; (counter - 1) < itemsList.size(); counter++){

        // Append the Item Number to the 'itemIntList' Vector
        itemIntList.push_back(counter);

    }

    // Initialize 2D int Matrix to Map Items
    int mapOverlay[GRID_DIMENSION2][GRID_DIMENSION2] = {0};

    // Add Door (111) to Map
    int doorLocation = (int)(GRID_DIMENSION2/2);
    mapOverlay[doorLocation][0] = 111;

    // Add Player (999) to Map
    int playerLocation = (int)(GRID_DIMENSION2/2);
    mapOverlay[playerLocation][(GRID_DIMENSION2 - 2)] = 999;

    // Add Boss to map
    mapOverlay[(int)(GRID_DIMENSION/2)][2] = 42069;

    //added a square to get back to "dungeon 1"
    int D1Location  = (int)(GRID_DIMENSION2/2);
    mapOverlay[D1Location][(GRID_DIMENSION2-1)] = 1000;

    // While There are Still Items in 'itemIntList'
    while(itemIntList.size() > 0){

        // Generate Two Random Seeds for Each Matrix Dimension
        int random1 = rand() % GRID_DIMENSION2;
        int random2 = rand() % GRID_DIMENSION2;

        // Generate a New Random if Both Digits are the Same
        while(random1 == random2){
            random2 = rand() % GRID_DIMENSION2;
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
        int randomE1 = rand() % GRID_DIMENSION2;
        int randomE2 = rand() % GRID_DIMENSION2;

        // Generate a New Random if Both Digits are the Same
        while(randomE1 == randomE2){
            randomE2 = rand() % GRID_DIMENSION2;
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
    for(int i = 0; i < GRID_DIMENSION2; i++){

        for(int j = 0; j < GRID_DIMENSION2; j++){

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

            else if(element == 888){    //element for floor 1 to floor 2 square
                converted = "X";
            }

            else if(element == 1000){  //element for floor 2 to floor 1 square
                converted = "D1";
            }

            else if (element == 42069){
                converted = "B";
            }

            else if (element == 777){
                converted = "I";
            }

            else if (element == 778){
                converted = "S";
            }

            else{
                converted = ".";
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

int mapCheck(){                //added function for checking current floor
    if (gameFloor == 1){
        return 1;
    }
    else{
        return 0;
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

// Clears Terminal
void clearScreen(){

    cout << string( 100, '\n' );

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
void movePlayer(Player& gamePlayer, string direction, vector< vector<int> >& intMap, vector< vector<string> >& playerMap, vector<string> itemsList){

    // Get the Player's Coordinates
    vector<int> playerPosition = getPlayerPosition(playerMap);

    // Stores the Maximum Dimension of the Player Map
    int maxSize = playerMap.size() - 1;

    // Stores Current Position Data
    int currentYPosition = playerPosition.at(1);
    int currentXPosition = playerPosition.at(0);

    // Direction Control
    if(direction == "NORTH" || direction == "N"){

        int futureYPosition = playerPosition.at(1) - 1;

        if(futureYPosition <= maxSize && futureYPosition >= 0 ){

            //checks if the square being moved onto is element "X" and marks the player as on floor 2 now
            if(playerMap.at(futureYPosition).at(currentXPosition) == "X"){
                gamePlayer.setCurrentFloor(2);
                gameFloor = 2;
            }

                //same but marks the player on floor 1 now
            else if(playerMap.at(futureYPosition).at(currentXPosition) == "D1"){
                gamePlayer.setCurrentFloor(1);
                gameFloor = 1;
            }

            else if(playerMap.at(futureYPosition).at(currentXPosition) != "D") {

                // Mark Old Space as Walked On
                if (intMap.at(currentYPosition).at(currentXPosition) != 111 && intMap.at(currentYPosition).at(currentXPosition) != 777 && intMap.at(currentYPosition).at(currentXPosition) != 778) {
                    intMap.at(currentYPosition).at(currentXPosition) = 0;
                    playerMap.at(currentYPosition).at(currentXPosition) = "*";
                }
		if (intMap.at(currentYPosition).at(currentXPosition) == 777){
			playerMap.at(currentYPosition).at(currentXPosition) = "I";
		}
		if (intMap.at(currentYPosition).at(currentXPosition) == 778){
			playerMap.at(currentYPosition).at(currentXPosition) = "S";
		}
                // Mark New Player Position
                playerMap.at(futureYPosition).at(currentXPosition) = "P";

                // Check for Items/Events
                if (intMap.at(futureYPosition).at(currentXPosition) != 0) {

                    int interactionStatus = intMap.at(futureYPosition).at(currentXPosition);

                    /* If Enemy, Start Battle */
                    if (interactionStatus == 666) {
                        Spider spider1;
                        enemyBattle(gamePlayer, spider1);
                    }

                    if (interactionStatus == 667) {
                        Goblin goblin1;
                        enemyBattle(gamePlayer, goblin1);
                    }

                    if (interactionStatus == 668) {
                        Orc orc1;
                        enemyBattle(gamePlayer, orc1);
                    }

                    //boss event
                    if (interactionStatus == 42069) {
                        Boss boss1;
                        enemybossBattle(gamePlayer, boss1);
                    }

                    //inn event
                    if (interactionStatus == 777) {
                        inn(gamePlayer);
                    }

                    //shop event
                    if (interactionStatus == 778) {
                        shop(gamePlayer);
                    }

                    /* If Item/Puzzle, Announce/Pickup Item */
                    if (interactionStatus <= 100) {
                        int ElementNumber = intMap.at(futureYPosition).at(currentXPosition);
                        cout << "You Have Found: " << itemsList.at(ElementNumber - 1) << endl;
                        gamePlayer.addToInventory(itemsList.at(ElementNumber - 1));
                    }

                    // After Interaction is Completed Mark the Player Position
                    intMap.at(futureYPosition).at(currentXPosition) = 999;

                }

                else {

                    intMap.at(futureYPosition).at(currentXPosition) = 999;

                }

            }

            else if(playerMap.at(futureYPosition).at(currentXPosition) == "D"){

                vector<string> pInventory = gamePlayer.returnInventory();

                if(find(pInventory.begin(), pInventory.end(), "KEY") != pInventory.end()){

                    cout << "You Have Successfully Completed the Game!" << endl;
                    remove("saveMapData.dat");
                    remove("savePlayerData.dat");
                    exit(1);

                }

                else{

                    cout << "The Door Won't Budge..." << endl;

                }

            }

        }

        else{

            cout << "Cannot Move Further North!" << endl;

        }

    }

    else if(direction == "SOUTH" || direction == "S"){

        int futureYPosition = playerPosition.at(1) + 1;

        if(futureYPosition <= maxSize && futureYPosition >=0){

            if(playerMap.at(futureYPosition).at(currentXPosition) == "X"){
                gamePlayer.setCurrentFloor(2);
                gameFloor = 2;
            }

            else if(playerMap.at(futureYPosition).at(currentXPosition) == "D1"){
                gamePlayer.setCurrentFloor(1);
                gameFloor = 1;
            }

            else  if(playerMap.at(futureYPosition).at(currentXPosition) != "D") {

                // Mark Old Space as Walked On
                if (intMap.at(currentYPosition).at(currentXPosition) != 111 && intMap.at(currentYPosition).at(currentXPosition) != 777 && intMap.at(currentYPosition).at(currentXPosition) != 778) {
                    intMap.at(currentYPosition).at(currentXPosition) = 0;
                    playerMap.at(currentYPosition).at(currentXPosition) = "*";
                }
		if (intMap.at(currentYPosition).at(currentXPosition) == 777){
			playerMap.at(currentYPosition).at(currentXPosition) = "I";
		}
		if (intMap.at(currentYPosition).at(currentXPosition) == 778){
			playerMap.at(currentYPosition).at(currentXPosition) = "S";
		}
                // Mark New Player Position
                playerMap.at(futureYPosition).at(currentXPosition) = "P";

                // Check for Items/Events
                if (intMap.at(futureYPosition).at(currentXPosition) != 0) {

                    int interactionStatus = intMap.at(futureYPosition).at(currentXPosition);

                    /* If Enemy, Start Battle */
                    if (interactionStatus == 666) {
                        Spider spider1;
                        enemyBattle(gamePlayer, spider1);
                    }

                    if (interactionStatus == 667) {
                        Goblin goblin1;
                        enemyBattle(gamePlayer, goblin1);
                    }

                    if (interactionStatus == 668) {
                        Orc orc1;
                        enemyBattle(gamePlayer, orc1);
                    }

                    //boss event
                    if (interactionStatus == 42069) {
                        Boss boss1;
                        enemybossBattle(gamePlayer, boss1);
                    }

                    //inn event
                    if (interactionStatus == 777) {
                        inn(gamePlayer);
                    }

                    //shop event
                    if (interactionStatus == 778) {
                        shop(gamePlayer);
                    }

                    /* If Item/Puzzle, Announce/Pickup Item */
                    if (interactionStatus <= 100) {
                        int ElementNumber = intMap.at(futureYPosition).at(currentXPosition);
                        cout << "You Have Found: " << itemsList.at(ElementNumber - 1) << endl;
                        gamePlayer.addToInventory(itemsList.at(ElementNumber - 1));
                    }

                    // After Interaction is Completed Mark the Player Position
                    intMap.at(futureYPosition).at(currentXPosition) = 999;

                }

                else {

                    intMap.at(futureYPosition).at(currentXPosition) = 999;

                }

            }

            else if(playerMap.at(futureYPosition).at(currentXPosition) == "D"){

                vector<string> pInventory = gamePlayer.returnInventory();

                if(find(pInventory.begin(), pInventory.end(), "KEY") != pInventory.end()){

                    cout << "You Have Successfully Completed the Game!" << endl;
                    remove("saveMapData.dat");
                    remove("savePlayerData.dat");
                    exit(1);

                }

                else{

                    cout << "The Door Won't Budge..." << endl;

                }

            }

        }

        else{

            cout << "Cannot Move Further South!" << endl;

        }

    }

    else if(direction == "WEST" || direction == "W"){

        int futureXPosition = playerPosition.at(0) - 1;

        if(futureXPosition <= maxSize && futureXPosition >= 0){

            if(playerMap.at(currentYPosition).at(futureXPosition) == "X"){
                gamePlayer.setCurrentFloor(2);
                gameFloor = 2;
            }

            else if(playerMap.at(currentYPosition).at(futureXPosition) == "D1"){
                gamePlayer.setCurrentFloor(1);
                gameFloor = 1;
            }


            else if(playerMap.at(currentYPosition).at(futureXPosition) != "D") {


                // Mark Old Space as Walked On
                if (intMap.at(currentYPosition).at(currentXPosition) != 111 && intMap.at(currentYPosition).at(currentXPosition) != 777 && intMap.at(currentYPosition).at(currentXPosition) != 778) {
                    intMap.at(currentYPosition).at(currentXPosition) = 0;
                    playerMap.at(currentYPosition).at(currentXPosition) = "*";
                }
		if (intMap.at(currentYPosition).at(currentXPosition) == 777){
			playerMap.at(currentYPosition).at(currentXPosition) = "I";
		}
		if (intMap.at(currentYPosition).at(currentXPosition) == 778){
			playerMap.at(currentYPosition).at(currentXPosition) = "S";
		}
                // Mark New Player Position
                playerMap.at(currentYPosition).at(futureXPosition) = "P";

                // Check for Items/Events
                if (intMap.at(currentYPosition).at(futureXPosition) != 0) {

                    int interactionStatus = intMap.at(currentYPosition).at(futureXPosition);

                    /* If Enemy, Start Battle */
                    if (interactionStatus == 666) {
                        Spider spider1;
                        enemyBattle(gamePlayer, spider1);
                    }

                    if (interactionStatus == 667) {
                        Goblin goblin1;
                        enemyBattle(gamePlayer, goblin1);
                    }

                    if (interactionStatus == 668) {
                        Orc orc1;
                        enemyBattle(gamePlayer, orc1);
                    }

                    //boss event
                    if (interactionStatus == 42069) {
                        Boss boss1;
                        enemybossBattle(gamePlayer, boss1);
                    }

                    //inn event
                    if (interactionStatus == 777) {
                        inn(gamePlayer);
                    }

                    //shop event
                    if (interactionStatus == 778) {
                        shop(gamePlayer);
                    }

                    /* If Item/Puzzle, Announce/Pickup Item */
                    if (interactionStatus <= 100) {
                        int ElementNumber = intMap.at(currentYPosition).at(futureXPosition);
                        cout << "You Have Found: " << itemsList.at(ElementNumber - 1) << endl;
                        gamePlayer.addToInventory(itemsList.at(ElementNumber - 1));
                    }

                    // After Interaction is Completed Mark the Player Position
                    intMap.at(currentYPosition).at(futureXPosition) = 999;

                }

                else {

                    intMap.at(currentYPosition).at(futureXPosition) = 999;

                }

            }

            else if(playerMap.at(currentYPosition).at(futureXPosition) == "D"){

                vector<string> pInventory = gamePlayer.returnInventory();

                if(find(pInventory.begin(), pInventory.end(), "KEY") != pInventory.end()){

                    cout << "You Have Successfully Completed the Game!" << endl;
                    remove("saveMapData.dat");
                    remove("savePlayerData.dat");
                    exit(1);

                }

                else{

                    cout << "The Door Won't Budge..." << endl;

                }

            }

        }

        else{

            cout << "Cannot Move Further West!" << endl;

        }

    }

    else if(direction == "EAST" || direction == "E"){

        int futureXPosition = playerPosition.at(0) + 1;

        if(futureXPosition <= maxSize && futureXPosition >= 0){

            if(playerMap.at(currentYPosition).at(futureXPosition) == "X"){
                gamePlayer.setCurrentFloor(2);
                gameFloor = 2;
            }

            else if(playerMap.at(currentYPosition).at(futureXPosition) == "D1"){
                gamePlayer.setCurrentFloor(1);
                gameFloor = 1;
            }

            else if(playerMap.at(currentYPosition).at(futureXPosition) != "D") {

                // Mark Old Space as Walked On
                if (intMap.at(currentYPosition).at(currentXPosition) != 111 && intMap.at(currentYPosition).at(currentXPosition) != 777 && intMap.at(currentYPosition).at(currentXPosition) != 778) {
                    intMap.at(currentYPosition).at(currentXPosition) = 0;
                    playerMap.at(currentYPosition).at(currentXPosition) = "*";
                }
		if (intMap.at(currentYPosition).at(currentXPosition) == 777){
			playerMap.at(currentYPosition).at(currentXPosition) = "I";
		}
		if (intMap.at(currentYPosition).at(currentXPosition) == 778){
			playerMap.at(currentYPosition).at(currentXPosition) = "S";
		}
                // Mark New Player Position
                playerMap.at(currentYPosition).at(futureXPosition) = "P";

                // Check for Items/Events
                if (intMap.at(currentYPosition).at(futureXPosition) != 0) {

                    int interactionStatus = intMap.at(currentYPosition).at(futureXPosition);

                    /* If Enemy, Start Battle */
                    if (interactionStatus == 666) {
                        Spider spider1;
                        enemyBattle(gamePlayer, spider1);
                    }

                    if (interactionStatus == 667) {
                        Goblin goblin1;
                        enemyBattle(gamePlayer, goblin1);
                    }

                    if (interactionStatus == 668) {
                        Orc orc1;
                        enemyBattle(gamePlayer, orc1);
                    }

                    //boss event
                    if (interactionStatus == 42069) {
                        Boss boss1;
                        enemybossBattle(gamePlayer, boss1);
                    }

                    //inn event
                    if (interactionStatus == 777) {
                        inn(gamePlayer);
                    }

                    //shop event
                    if (interactionStatus == 778) {
                        shop(gamePlayer);
                    }

                    /* If Item/Puzzle, Announce/Pickup Item */
                    if (interactionStatus <= 100) {
                        int ElementNumber = intMap.at(currentYPosition).at(futureXPosition);
                        cout << "You Have Found a: " << itemsList.at(ElementNumber - 1) << endl;
                        gamePlayer.addToInventory(itemsList.at(ElementNumber - 1));
                    }

                    // After Interaction is Completed Mark the Player Position
                    intMap.at(currentYPosition).at(futureXPosition) = 999;

                }

                else {

                    intMap.at(currentYPosition).at(futureXPosition) = 999;

                }

            }

            else if(playerMap.at(currentYPosition).at(futureXPosition) == "D"){

                vector<string> pInventory = gamePlayer.returnInventory();

                if(find(pInventory.begin(), pInventory.end(), "KEY") != pInventory.end()){

                    cout << "You Have Successfully Completed the Game!" << endl;
                    remove("saveMapData.dat");
                    remove("savePlayerData.dat");
                    exit(1);

                }

                else{

                    cout << "The Door Won't Budge..." << endl;

                }

            }

        }

        else{

            cout << "Cannot Move Further East!" << endl;

        }

    }

    else if(direction == "HELP"){

        cout << endl;
        cout << "Type \'NORTH\' to Move Your Character North" << endl;
        cout << "Type \'SOUTH\' to Move Your Character South" << endl;
        cout << "Type \'EAST\' to Move Your Character East" << endl;
        cout << "Type \'WEST\' to Move Your Character West" << endl;
        cout << endl;

    }

    else{

        cout << "UNKNOWN DIRECTION \'" << direction << "\' " << endl;

    }

}

void enemyBattle(Player& mainPlayer, Spider& enemySpider){

    int eLevel = enemySpider.returnLevel();
    string playerName = mainPlayer.getName();
    bool fleeFailure = true;
    vector<string> inventory = mainPlayer.returnInventory();

    cout << "You Have Encountered a Level " << eLevel << " Spider! Get Ready to Battle!" << endl;
    cout << endl;

    while((enemySpider.returnHealth() > 0 && mainPlayer.returnHealth() > 0) && fleeFailure){

        string userChoice;
        string userWeaponChoice;

        cout << endl;
        cout << "Player: " << playerName << endl;
        cout << "Health: " << mainPlayer.returnHealth() << endl;
        cout << "Inventory: " << printInventory(mainPlayer) << endl;
        cout << endl;
        cout << "Spider Level: " << enemySpider.returnLevel() << endl;
        cout << "Spider Health: " << enemySpider.returnHealth() << endl;
        cout << endl;
        cout << endl;

        cout << "Fight or Flee: ";
        cin >> userChoice;
        stringToUpper(userChoice);

        if(userChoice == "FIGHT"){

            cout << "What Would You like to Use: ";
            cin >> userWeaponChoice;
            stringToUpper(userWeaponChoice);
            clearScreen();

            // If the Weapon is in the Inventory or If the Item is a Fist
            if(find(inventory.begin(), inventory.end(), userWeaponChoice) != inventory.end() || userWeaponChoice == "FIST"){

                // If Attacked With a Fist Deal 5pts Damage
                if(userWeaponChoice == "FIST"){
                    cout << playerName << " Attacks!" << endl;
                    cout << playerName << " Deals 5pts in Damage!" << endl;
                    enemySpider.dealDamage(5);

                    cout << endl;

                    // Spider Attack Turn
                    if(enemySpider.returnHealth() > 0) {
                        int sAttackStrength = enemySpider.attack();
                        cout << "Spider Attacks!" << endl;
                        cout << "Spider Deals " << sAttackStrength << "pts in Damage!" << endl;
                        mainPlayer.takeDamage(sAttackStrength);
                    }

                }

                else if(userWeaponChoice == "SWORD"){
                    cout << playerName << " Attacks!" << endl;
                    cout << playerName << " Deals 20pts in Damage!" << endl;
                    enemySpider.dealDamage(20);

                    cout << endl;

                    // Spider Attack Turn if Spider Still Alive
                    if(enemySpider.returnHealth() > 0) {
                        int sAttackStrength = enemySpider.attack();
                        cout << "Spider Attacks!" << endl;
                        cout << "Spider Deals " << sAttackStrength << "pts in Damage!" << endl;
                        mainPlayer.takeDamage(sAttackStrength);
                    }

                }

                else{

                    cout << "Sorry, That Item Cannot Be Used Here!" << endl;

                }

            }

            else if(userWeaponChoice == "HELP"){

                clearScreen();

                cout << "Type \'FIST\' to Punch the Enemy (5pts Damage)" << endl;
                cout << "Type \'SWORD\' if You Have One in Your Inventory to Attack (20pts Damage)" << endl;
                cout << endl;
            }

            else{

                cout << "You Do Not Have That Item!" << endl;

            }

        }

            // If the User Chooses to Flee, Calculate if Flee was Successful
        else if(userChoice == "FLEE"){

            clearScreen();

            // Random Seed
            srand (time(NULL));

            // Generate Random Level Between 1 and 10
            int escapeChance = 1 + (rand() % (int)(10 - 1 + 1));

            if(escapeChance >= eLevel){
                cout << "You Managed to Escape Successfully!" << endl;
                fleeFailure = false;
            }

            else{
                cout << "You Try to Run, but the Spider Cuts You Off!" << endl;

                if(escapeChance > 5){
                    cout << "The Spider Chooses to Attack!" << endl;
                    int sAttackStrength = enemySpider.attack();
                    cout << "Spider Attacks!" << endl;
                    cout << "Spider Deals " << sAttackStrength << "pts in Damage!" << endl;
                    mainPlayer.takeDamage(sAttackStrength);
                }

                fleeFailure = true;
            }

        }

        else if(userChoice == "HELP"){

            clearScreen();

            cout << "Type \'FIGHT\' to Engage the Enemy" << endl;
            cout << "Type \'FLEE\' to Attempt to Run Away From the Enemy" << endl;
            cout << endl;
        }

        else{
            clearScreen();
            cout << "Sorry, That's Not an Option!" << endl;
        }

    }

    if(enemySpider.returnHealth() <= 0 && mainPlayer.returnHealth() > 0){

        cout << endl;
        cout << "Enemy Spider Defeated!" << endl;
        int goldDrop = enemySpider.returnLevel() * 5;
        cout <<"You got "<<goldDrop<<" gold."<< endl;
		mainPlayer.addGold(goldDrop);
        cout << endl;

    }

    else if(mainPlayer.returnHealth() > 0){
        //Nothing Happens
    }

    else{

        cout << endl;
        cout << "You Have Been Killed in Battle. GAME OVER." << endl;
        exit(1);

    }


}

void enemybossBattle(Player& mainPlayer, Boss& enemyBoss){

    int eLevel = enemyBoss.returnLevel();
    string playerName = mainPlayer.getName();
    bool fleeFailure = true;
    vector<string> inventory = mainPlayer.returnInventory();

    cout << "You Have Encountered a Level " << eLevel << " Hydra! Get Ready to Battle!" << endl;
    cout << endl;

    while ((enemyBoss.returnHealth() > 0 && mainPlayer.returnHealth() > 0) && fleeFailure){

        string userChoice;
        string userWeaponChoice;
        int extra = 0; //attacks will get stronger

        cout << endl;
        cout << "Player: " << playerName << endl;
        cout << "Health: " << mainPlayer.returnHealth() << endl;
        cout << "Inventory: " << printInventory(mainPlayer) << endl;
        cout << endl;
        cout << "Hydra Level: " << enemyBoss.returnLevel() << endl;
        cout << "Hydra Health: " << enemyBoss.returnHealth() << endl;
        cout << endl;
        cout << endl;

        cout << "Fight or Flee: ";
        cin >> userChoice;
        stringToUpper(userChoice);

        if (userChoice == "FIGHT"){

            cout << "What Would You like to Use: ";
            cin >> userWeaponChoice;
            stringToUpper(userWeaponChoice);
            clearScreen();


            if (find(inventory.begin(), inventory.end(), userWeaponChoice) != inventory.end() || userWeaponChoice == "FIST"){


                if (userWeaponChoice == "FIST"){
                    int damage = extra + 50;
                    extra += 30;
                    cout << playerName << " Attacks!" << endl;
                    cout << playerName << " Deals "<<damage<<"pts in Damage!" << endl;
                    enemyBoss.dealDamage(damage);

                    cout << endl;

                    if (enemyBoss.returnHealth() > 0) {
                        int sAttackStrength = enemyBoss.attack();
                        cout << "Hydra Attacks!" << endl;
                        cout << "Hydra Deals " << sAttackStrength << "pts in Damage!" << endl;
                        mainPlayer.takeDamage(sAttackStrength);
                    }

                }

                else if (userWeaponChoice == "SWORD"){
                    int damage = extra + 200;
                    extra += 30;
                    cout << playerName << " Attacks!" << endl;
                    cout << playerName << " Deals "<<damage<<"pts in Damage!" << endl;
                    enemyBoss.dealDamage(damage);

                    cout << endl;

                    if (enemyBoss.returnHealth() > 0) {
                        int sAttackStrength = enemyBoss.attack();
                        cout << "Hydra Attacks!" << endl;
                        cout << "Hydra Deals " << sAttackStrength << "pts in Damage!" << endl;
                        mainPlayer.takeDamage(sAttackStrength);
                    }

                }

                else{

                    cout << "Sorry, That Item Cannot Be Used Here!" << endl;

                }

            }

            else if (userWeaponChoice == "HELP"){

                clearScreen();

                cout << "Type \'FIST\' to Punch the Enemy (5pts Damage)" << endl;
                cout << "Type \'SWORD\' if You Have One in Your Inventory to Attack (20pts Damage)" << endl;
                cout << endl;
            }

            else{

                cout << "You Do Not Have That Item!" << endl;

            }

        }

            //User can always flee from the boss
        else if (userChoice == "FLEE"){

            clearScreen();
            fleeFailure = false;


        }

        else if (userChoice == "HELP"){

            clearScreen();

            cout << "Type \'FIGHT\' to Engage the Enemy" << endl;
            cout << "Type \'FLEE\' to Attempt to Run Away From the Enemy" << endl;
            cout << endl;
        }

        else{
            clearScreen();
            cout << "Sorry, That's Not an Option!" << endl;
        }

    }

    if (enemyBoss.returnHealth() <= 0 && mainPlayer.returnHealth() > 0){

        cout << endl;
        cout << "Boss Enemy Hydra Defeated!" << endl;
        cout << "You Have Found the Key" << endl;
        cout << endl;
        mainPlayer.addToInventory("KEY");

    }

    else if (mainPlayer.returnHealth() > 0){
        //Nothing Happens
    }

    else{

        cout << endl;
        cout << "You Have Been Killed in Battle. GAME OVER." << endl;
        exit(1);

    }


}

void inn(Player& mainPlayer){
    clearScreen();
    int exit = 0;
    string innchoice;

    while (exit == 0){
        cout << "Would you like to stay in the inn for the night for 10 gold? (Y/N)" << endl;
        cin >> innchoice;
        stringToUpper(innchoice);
        if (innchoice == "Y" || innchoice == "YES"){
            if (mainPlayer.getGold() >= 10){
                cout << "You rest in the inn for a night. Your health has been fully restored." << endl;
                cout << "Current gold: " << mainPlayer.getGold() << endl;
                mainPlayer.setHealth(100);
                mainPlayer.removeGold(10);
                exit = 1;
            }
            else{
                cout << "You do not have enough gold." << endl;
                cout << "Current gold: " << mainPlayer.getGold() << endl;
            }
        }
        else if (innchoice == "N" || innchoice == "NO"){
            exit = 1;
        }
        else{
            cout << "Statement not recognised" << endl;
        }
    }
}

void shop(Player& P){
    clearScreen();
    string c;
    cout << "You enter the shop." << endl;
    cout << "\nShop Inventory:\n\nSword - 50 gold\nHealing Soda - 15 gold" << endl;
    while (c != "EXIT"){
        cout << "What would you like to buy? Type 'exit' to exit the shop." << endl;
        cin >> c;
        stringToUpper(c);
        if (c == "SWORD" && P.getGold() >= 50){
            cout << "You bought a sword." << endl;
            P.addToInventory("SWORD");
            P.removeGold(50);

        }
        else if (c == "SWORD" && P.getGold() < 50){
            cout << "Not enough gold." << endl;
        }
        else if (c == "HEALING SODA" && P.getGold() >= 15){
            cout << "You bought a healing soda." << endl;
            P.addToInventory("HEALING SODA");
            P.removeGold(15);

        }
        else if (c == "HEALING SODA" && P.getGold() < 15){
            cout << "Not enough gold." << endl;
        }
        else{
            cout << "Statement not recognised." << endl;
        }
    }
}


string printInventory(Player player){

    vector<string> inventory = player.returnInventory();

    string inventoryList = "";

    if(inventory.size() == 0){
        return "EMPTY";
    }

    else {

        for (int i = 0; i < inventory.size(); i++) {

            inventoryList += inventory.at(i) + ", ";

        }

    }

    return inventoryList;

}

void playerUse(Player& player, string usingItem, vector< vector<int> > intMap){

    vector<string> inventory = player.returnInventory();

    if(find(inventory.begin(), inventory.end(), usingItem) != inventory.end()){

        if(usingItem == "HEALING SODA"){

            if(player.returnHealth() < 100) {

                player.removeFromInventory("HEALING SODA");

                cout << "HEALING..." << endl;

                int playerHealthBefore = player.returnHealth();
                int pointstoHeal = 1 + (rand() % (int) (30 - 1 + 1));
                player.healDamage(pointstoHeal);
                int playerHealthAfter = player.returnHealth();
                int playerHealthDifference = playerHealthAfter - playerHealthBefore;

                if (playerHealthAfter == 100) {
                    cout << "The Soda Has Returned You to Full Health! Quite Refreshing!" << endl;
                }

                else {
                    cout << "The Soda Has Healed You By " << playerHealthDifference << "pts!" << endl;
                }

            }

            else{

                cout << "You are Already at Full Health! No Need to Waste This..." << endl;

            }

        }

        else if(usingItem == "MAP"){

            cout << "You Look at the Map..." << endl;
            cout << endl;

            printItemMap(intMap);

        }

        else{

            cout << "Sorry, You Can't Use that Right Now..." << endl;

        }

    }

    else if(usingItem == "HELP"){
        cout << endl;
        cout << "Type \'HEALING SODA\' if You Have Some in Your Inventory to Use a Soda to Heal Some of Your Damage" << endl;
        cout << "Type \'MAP\' if You Have One in Your Inventory to View Where Items are on the Map" << endl;
        cout << endl;
    }

    else{

        cout << "Sorry, You Don't Seem to Have that Item..." << endl;

    }

}

void printItemMap(vector< vector<int> > inputVector){

    vector< vector<string> > masterPlayerMap;
    vector<string> tempArray;

    for(int i = 0; i < inputVector.size(); i++){
        for(int j = 0; j < inputVector.size(); j++){

            int element = inputVector.at(i).at(j);
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

            else if(element == 1000){
                converted = "D1";
            }

            else{
                converted = "I";
            }

            tempArray.push_back(converted);

        }

        masterPlayerMap.push_back(tempArray);
        tempArray.clear();

    }

    printPlayerMap(masterPlayerMap);

}

bool checkFileExists(string file){
    ifstream file_to_check (file.c_str());
    if(file_to_check.is_open())
        return true;
    return false;
    file_to_check.close();
}

void gameSave(vector< vector<int> > integerMap, vector < vector <int> > integerMap2, Player mainPlayer){   //added the second integermap to the parameters

    if (checkFileExists("saveMapData.dat")){

        string saveOverwrite;
        cout << "Are You Sure You Want to Save? This Will Overwrite the Old Save (yes/no): ";
        cin >> saveOverwrite;
        stringToUpper(saveOverwrite);

        if(saveOverwrite == "YES" || saveOverwrite == "NO") {

            if(saveOverwrite == "YES") {

                remove("saveMapData.dat");
                remove("saveMap2Data.dat");
                ofstream mapfile;
                mapfile.open("saveMapData.dat");

                // Get Vector Size
                int inputSize = integerMap.size();
                int inputSize2 = integerMap2.size();

                // Print Every Element of Vector
                for (int i = 0; i < inputSize; i++) {
                    for (int j = 0; j < inputSize; j++) {
                        mapfile << integerMap.at(i).at(j) << "\t";
                    }
                    mapfile << "\n";
                }

                mapfile.close();

                ofstream mapfile2;        //added same process for floor 2
                mapfile2.open("saveMap2Data.dat");

                for (int i = 0; i < inputSize2; i++) {
                    for (int j = 0; j < inputSize2; j++) {
                        mapfile2 << integerMap2.at(i).at(j) << "\t";
                    }
                    mapfile2 << "\n";
                }

                mapfile2.close();

                remove("savePlayerData.dat");
                ofstream playerFile;
                playerFile.close();
                playerFile.open("savePlayerData.dat");

                vector<string> inventory = mainPlayer.returnInventory();
                int inventorySize = inventory.size();

                playerFile << mainPlayer.getName() << "\n";
                playerFile << mainPlayer.returnHealth() << "\n";

                for(int i = 0; i < inventorySize; i++){

                    playerFile << inventory.at(i) << "\t";

                }

                playerFile << "\n";
                playerFile << mainPlayer.getGold() << "\n";
                playerFile.close();

                cout << "Game Successfully Saved!" << endl;

            }

            else{

                cout << "Game Not Saved" << endl;

            }

        }

        else{

            cout << "Invalid Command" << endl;
            gameSave(integerMap, integerMap2, mainPlayer);

        }

    }

    else{

        ofstream mapfile;
        mapfile.open("saveMapData.dat");

        // Get Vector Size
        int inputSize = integerMap.size();
        int inputSize2 = integerMap2.size();

        // Print Every Element of Vector
        for(int i = 0; i < inputSize; i++){
            for(int j = 0; j < inputSize; j++){
                mapfile << integerMap.at(i).at(j) << "\t";
            }
            mapfile << "\n";
        }

        mapfile.close();

        ofstream mapfile2;
        mapfile2.open("saveMap2Data.dat");

        for (int i = 0; i < inputSize2; i++) {
            for (int j = 0; j < inputSize2; j++) {
                mapfile2 << integerMap2.at(i).at(j) << "\t";
            }
            mapfile2 << "\n";
        }

        mapfile2.close();


        ofstream playerFile;
        playerFile.open("savePlayerData.dat");

        vector<string> inventory = mainPlayer.returnInventory();
        int inventorySize = inventory.size();

        playerFile << mainPlayer.getName() << "\n";
        playerFile << mainPlayer.returnHealth() << "\n";

        for(int i = 0; i < inventorySize; i++){

            playerFile << inventory.at(i) << "\t";

        }

        playerFile << "\n";
        playerFile << mainPlayer.getGold() << "\n";
        playerFile.close();

        cout << "Game Successfully Saved!" << endl;

    }

}

void enemyBattle(Player& mainPlayer, Goblin& enemyGoblin) {

    int eLevel = enemyGoblin.returnLevel();
    string playerName = mainPlayer.getName();
    bool fleeFailure = true;
    vector<string> inventory = mainPlayer.returnInventory();

    cout << "You Have Encountered a Level " << eLevel << " Goblin! Get Ready to Battle!" << endl;
    cout << endl;

    while ((enemyGoblin.returnHealth() > 0 && mainPlayer.returnHealth() > 0) && fleeFailure) {

        string userChoice;
        string userWeaponChoice;

        cout << endl;
        cout << "Player: " << playerName << endl;
        cout << "Health: " << mainPlayer.returnHealth() << endl;
        cout << "Inventory: " << printInventory(mainPlayer) << endl;
        cout << endl;
        cout << "Goblin Level: " << enemyGoblin.returnLevel() << endl;
        cout << "Goblin Health: " << enemyGoblin.returnHealth() << endl;
        cout << endl;
        cout << endl;

        cout << "Fight or Flee: ";
        cin >> userChoice;
        stringToUpper(userChoice);

        if (userChoice == "FIGHT") {

            cout << "What Would You like to Use: ";
            cin >> userWeaponChoice;
            stringToUpper(userWeaponChoice);
            clearScreen();

            // If the Weapon is in the Inventory or If the Item is a Fist
            if (find(inventory.begin(), inventory.end(), userWeaponChoice) != inventory.end() ||
                userWeaponChoice == "FIST") {

                // If Attacked With a Fist Deal 5pts Damage
                if (userWeaponChoice == "FIST") {
                    cout << playerName << " Attacks!" << endl;
                    cout << playerName << " Deals 5pts in Damage!" << endl;
                    enemyGoblin.dealDamage(5);

                    cout << endl;

                    // Goblin Attack Turn
                    if (enemyGoblin.returnHealth() > 0) {
                        int gAttackStrength = enemyGoblin.attack();
                        cout << "Goblin Attacks!" << endl;
                        cout << "Goblin Deals " << gAttackStrength << "pts in Damage!" << endl;
                        mainPlayer.takeDamage(gAttackStrength);
                    }

                }

                else if (userWeaponChoice == "SWORD") {
                    cout << playerName << " Attacks!" << endl;
                    cout << playerName << " Deals 20pts in Damage!" << endl;
                    enemyGoblin.dealDamage(20);

                    cout << endl;

                    // Goblin Attack Turn if Goblin Still Alive
                    if (enemyGoblin.returnHealth() > 0) {
                        int gAttackStrength = enemyGoblin.attack();
                        cout << "Goblin Attacks!" << endl;
                        cout << "Goblin Deals " << gAttackStrength << "pts in Damage!" << endl;
                        mainPlayer.takeDamage(gAttackStrength);
                    }

                }

                else {

                    cout << "Sorry, That Item Cannot Be Used Here!" << endl;

                }

            }

            else if (userWeaponChoice == "HELP") {

                clearScreen();

                cout << "Type \'FIST\' to Punch the Enemy (5pts Damage)" << endl;
                cout << "Type \'SWORD\' if You Have One in Your Inventory to Attack (20pts Damage)" << endl;
                cout << endl;
            }

            else {

                cout << "You Do Not Have That Item!" << endl;

            }

        }

            // If the User Chooses to Flee, Calculate if Flee was Successful
        else if (userChoice == "FLEE") {

            clearScreen();

            // Random Seed
            srand(time(NULL));

            // Generate Random Level Between 1 and 10
            int escapeChance = 1 + (rand() % (int) (10 - 1 + 1));

            if (escapeChance >= eLevel) {
                cout << "You Managed to Escape Successfully!" << endl;
                fleeFailure = false;
            }

            else {
                cout << "You Try to Run, but the Goblin Cuts You Off!" << endl;

                if (escapeChance > 5) {
                    cout << "The Goblin Chooses to Attack!" << endl;
                    int gAttackStrength = enemyGoblin.attack();
                    cout << "Goblin Attacks!" << endl;
                    cout << "Goblin Deals " << gAttackStrength << "pts in Damage!" << endl;
                    mainPlayer.takeDamage(gAttackStrength);
                }

                fleeFailure = true;
            }

        }

        else if (userChoice == "HELP") {

            clearScreen();

            cout << "Type \'FIGHT\' to Engage the Enemy" << endl;
            cout << "Type \'FLEE\' to Attempt to Run Away From the Enemy" << endl;
            cout << endl;
        }

        else {
            clearScreen();
            cout << "Sorry, That's Not an Option!" << endl;
        }

    }

    if (enemyGoblin.returnHealth() <= 0 && mainPlayer.returnHealth() > 0) {

        cout << endl;
        cout << "Enemy Goblin Defeated!" << endl;
        int goldDrop = enemyGoblin.returnLevel() * 5;
        cout <<"You got "<<goldDrop<<" gold."<< endl;
		mainPlayer.addGold(goldDrop);
        cout << endl;

    }

    else if (mainPlayer.returnHealth() > 0) {
        //Nothing Happens
    }

    else {

        cout << endl;
        cout << "You Have Been Killed in Battle. GAME OVER." << endl;
        exit(1);

    }

}

void enemyBattle(Player& mainPlayer, Orc& enemyOrc) {

    int eLevel = enemyOrc.returnLevel();
    string playerName = mainPlayer.getName();
    bool fleeFailure = true;
    vector<string> inventory = mainPlayer.returnInventory();

    cout << "You Have Encountered a Level " << eLevel << " Orc! Get Ready to Battle!" << endl;
    cout << endl;

    while ((enemyOrc.returnHealth() > 0 && mainPlayer.returnHealth() > 0) && fleeFailure) {

        string userChoice;
        string userWeaponChoice;

        cout << endl;
        cout << "Player: " << playerName << endl;
        cout << "Health: " << mainPlayer.returnHealth() << endl;
        cout << "Inventory: " << printInventory(mainPlayer) << endl;
        cout << endl;
        cout << "Orc Level: " << enemyOrc.returnLevel() << endl;
        cout << "Orc Health: " << enemyOrc.returnHealth() << endl;
        cout << endl;
        cout << endl;

        cout << "Fight or Flee: ";
        cin >> userChoice;
        stringToUpper(userChoice);

        if (userChoice == "FIGHT") {

            cout << "What Would You like to Use: ";
            cin >> userWeaponChoice;
            stringToUpper(userWeaponChoice);
            clearScreen();

            // If the Weapon is in the Inventory or If the Item is a Fist
            if (find(inventory.begin(), inventory.end(), userWeaponChoice) != inventory.end() ||
                userWeaponChoice == "FIST") {

                // If Attacked With a Fist Deal 5pts Damage
                if (userWeaponChoice == "FIST") {
                    cout << playerName << " Attacks!" << endl;
                    cout << playerName << " Deals 5pts in Damage!" << endl;
                    enemyOrc.dealDamage(5);

                    cout << endl;

                    // Orc Attack Turn
                    if (enemyOrc.returnHealth() > 0) {
                        int oAttackStrength = enemyOrc.attack();
                        cout << "Orc Attacks!" << endl;
                        cout << "Orc Deals " << oAttackStrength << "pts in Damage!" << endl;
                        mainPlayer.takeDamage(oAttackStrength);
                    }

                }

                else if (userWeaponChoice == "SWORD") {
                    cout << playerName << " Attacks!" << endl;
                    cout << playerName << " Deals 20pts in Damage!" << endl;
                    enemyOrc.dealDamage(20);

                    cout << endl;

                    // Orc Attack Turn if Orc Still Alive
                    if (enemyOrc.returnHealth() > 0) {
                        int oAttackStrength = enemyOrc.attack();
                        cout << "Orc Attacks!" << endl;
                        cout << "Orc Deals " << oAttackStrength << "pts in Damage!" << endl;
                        mainPlayer.takeDamage(oAttackStrength);
                    }

                }

                else {

                    cout << "Sorry, That Item Cannot Be Used Here!" << endl;

                }

            }

            else if (userWeaponChoice == "HELP") {

                clearScreen();

                cout << "Type \'FIST\' to Punch the Enemy (5pts Damage)" << endl;
                cout << "Type \'SWORD\' if You Have One in Your Inventory to Attack (20pts Damage)" << endl;
                cout << endl;
            }

            else {

                cout << "You Do Not Have That Item!" << endl;

            }

        }

            // If the User Chooses to Flee, Calculate if Flee was Successful
        else if (userChoice == "FLEE") {

            clearScreen();

            // Random Seed
            srand(time(NULL));

            // Generate Random Level Between 1 and 10
            int escapeChance = 1 + (rand() % (int) (10 - 1 + 1));

            if (escapeChance >= eLevel) {
                cout << "You Managed to Escape Successfully!" << endl;
                fleeFailure = false;
            }

            else {
                cout << "You Try to Run, but the Orc Cuts You Off!" << endl;

                if (escapeChance > 5) {
                    cout << "The Orc Chooses to Attack!" << endl;
                    int oAttackStrength = enemyOrc.attack();
                    cout << "Orc Attacks!" << endl;
                    cout << "Orc Deals " << oAttackStrength << "pts in Damage!" << endl;
                    mainPlayer.takeDamage(oAttackStrength);
                }

                fleeFailure = true;
            }

        }

        else if (userChoice == "HELP") {

            clearScreen();

            cout << "Type \'FIGHT\' to Engage the Enemy" << endl;
            cout << "Type \'FLEE\' to Attempt to Run Away From the Enemy" << endl;
            cout << endl;
        }

        else {
            clearScreen();
            cout << "Sorry, That's Not an Option!" << endl;
        }

    }

    if (enemyOrc.returnHealth() <= 0 && mainPlayer.returnHealth() > 0) {

        cout << endl;
        cout << "Enemy Orc Defeated!" << endl;
        int goldDrop = enemyOrc.returnLevel() * 5;
        cout <<"You got "<<goldDrop<<" gold."<< endl;
		mainPlayer.addGold(goldDrop);
        cout << endl;

    }

    else if (mainPlayer.returnHealth() > 0) {
        //Nothing Happens
    }

    else {

        cout << endl;
        cout << "You Have Been Killed in Battle. GAME OVER." << endl;
        exit(1);

    }

}

bool loadGame(vector< vector<int> >& integerMap, vector < vector<int> > &integerMap2, Player& mainPlayer){

    vector<string> fileMapLines;
    vector<string> fileMap2Lines;  //added vector for floor 2
    vector<string> filePlayerLines;
    bool loadSuccess = false;

    if(checkFileExists("saveMapData.dat") && checkFileExists("savePlayerData.dat") && checkFileExists("saveMap2Data.dat")){  //now also checks for data of floor 2

        string line;
        ifstream myfile ("saveMapData.dat");

        if (myfile.is_open()){
            while ( getline (myfile,line) )
            {
                fileMapLines.push_back(line);
            }

            myfile.close();
        }

        myfile.open("saveMap2Data.dat");

        if(myfile.is_open()){                   //fills floor 2 vector the same way
            while (getline (myfile, line) ){
                fileMap2Lines.push_back(line);
            }
            myfile.close();
        }

        myfile.open("savePlayerData.dat");

        if (myfile.is_open()){
            while ( getline (myfile,line) )
            {
                filePlayerLines.push_back(line);
            }

            myfile.close();
        }

        for(int i = 0; i < fileMapLines.size(); i++){

            string mapLine = fileMapLines.at(i);

            istringstream iss(mapLine);
            string token;
            vector<int> tempTokens;

            while(std::getline(iss, token, '\t')) {  // but we can specify a different one
                int intToken = atoi(token.c_str());
                tempTokens.push_back(intToken);
            }

            integerMap.push_back(tempTokens);
            tempTokens.clear();

        }

        for(int i = 0; i < fileMap2Lines.size(); i++){  //fills the map of floor 2 the same way

            string mapLine = fileMap2Lines.at(i);

            istringstream iss(mapLine);
            string token;
            vector<int> tempTokens;

            while(std::getline(iss, token, '\t')) {  // but we can specify a different one
                int intToken = atoi(token.c_str());
                tempTokens.push_back(intToken);
            }

            integerMap2.push_back(tempTokens);
            tempTokens.clear();

        }

        string playerName = filePlayerLines.at(0);
        int playerGold = atoi(filePlayerLines.at(3).c_str());
        int playerHealth = atoi(filePlayerLines.at(1).c_str());
        vector<string> playerInventory;

        if(!filePlayerLines.at(2).empty()) {

            istringstream iss(filePlayerLines.at(2));
            string token;

            while (std::getline(iss, token, '\t')) {  // but we can specify a different one
                mainPlayer.addToInventory(token);
            }

        }

        mainPlayer.setName(playerName);
        mainPlayer.setHealth(playerHealth);
        if(mainPlayer.getCurrentFloor() == 1){
            gameFloor = 1;
        }
        else{
            gameFloor = 2;
        }

        loadSuccess = true;

    }

    else if(checkFileExists("saveMapData.dat") != checkFileExists("savePlayerData.dat")){

        cout << "Corrupted Files, Could Not Load Data" << endl;
        loadSuccess = false;

    }

    else{

        cout << "No Save Data Found!" << endl;
        loadSuccess = false;

    }

    return loadSuccess;

}
