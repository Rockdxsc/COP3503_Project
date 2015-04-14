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
#endif //_TEXTGAME_MAINHEADER_H_

/* FUNCTION PROTOTYPES */
vector< vector<int> > generateIntMap(vector<string> itemsList, int numEnemies);
vector< vector<string> > generatePlayerMap(vector< vector<int> > intMap);
vector<int> getPlayerPosition(vector< vector<string> >& playerMap);
void enemyBattle(Player& mainPlayer, Spider& enemySpider);
void stringToUpper(string &s);
void printIntMap(vector< vector<int> > inputVector);
void printPlayerMap(vector< vector<string> > inputVector);
void printItemMap(vector< vector<int> > inputVector);
void clearScreen();
void movePlayer(Player& gamePlayer, string direction, vector< vector<int> >& intMap, vector< vector<string> >& playerMap, vector<string> itemsList);
void enemyBattle(Player& mainPlayer, Spider& enemySpider);
void playerUse(Player& player, string usingItem, vector< vector<int> > intMap);
void gameSave(vector< vector<int> > integerMap, Player mainPlayer);
bool loadGame(vector< vector<int> >& integerMap, Player& mainPlayer);
bool checkFileExists(string file);
string printInventory(Player player);

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
    if(direction == "NORTH"){

        int futureYPosition = playerPosition.at(1) - 1;

        if(futureYPosition <= maxSize && futureYPosition >= 0 ){

            if(playerMap.at(futureYPosition).at(currentXPosition) != "D") {

                // Mark Old Space as Walked On
                if (intMap.at(currentYPosition).at(currentXPosition) != 111) {
                    intMap.at(currentYPosition).at(currentXPosition) = 0;
                    playerMap.at(currentYPosition).at(currentXPosition) = "*";
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

    else if(direction == "SOUTH"){

        int futureYPosition = playerPosition.at(1) + 1;

        if(futureYPosition <= maxSize && futureYPosition >= 0){

            if(playerMap.at(futureYPosition).at(currentXPosition) != "D") {

                // Mark Old Space as Walked On
                if (intMap.at(currentYPosition).at(currentXPosition) != 111) {
                    intMap.at(currentYPosition).at(currentXPosition) = 0;
                    playerMap.at(currentYPosition).at(currentXPosition) = "*";
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

    else if(direction == "WEST"){

        int futureXPosition = playerPosition.at(0) - 1;

        if(futureXPosition <= maxSize && futureXPosition >= 0){

            if(playerMap.at(currentYPosition).at(futureXPosition) != "D") {

                // Mark Old Space as Walked On
                if (intMap.at(currentYPosition).at(currentXPosition) != 111) {
                    intMap.at(currentYPosition).at(currentXPosition) = 0;
                    playerMap.at(currentYPosition).at(currentXPosition) = "*";
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

    else if(direction == "EAST"){

        int futureXPosition = playerPosition.at(0) + 1;

        if(futureXPosition <= maxSize && futureXPosition >= 0){

            if(playerMap.at(currentYPosition).at(futureXPosition) != "D") {

                // Mark Old Space as Walked On
                if (intMap.at(currentYPosition).at(currentXPosition) != 111) {
                    intMap.at(currentYPosition).at(currentXPosition) = 0;
                    playerMap.at(currentYPosition).at(currentXPosition) = "*";
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

void gameSave(vector< vector<int> > integerMap, Player mainPlayer){

    if (checkFileExists("saveMapData.dat")){

        string saveOverwrite;
        cout << "Are You Sure You Want to Save? This Will Overwrite the Old Save (yes/no): ";
        cin >> saveOverwrite;
        stringToUpper(saveOverwrite);

        if(saveOverwrite == "YES" || saveOverwrite == "NO") {

            if(saveOverwrite == "YES") {

                remove("saveMapData.dat");
                ofstream mapfile;
                mapfile.open("saveMapData.dat");

                // Get Vector Size
                int inputSize = integerMap.size();

                // Print Every Element of Vector
                for (int i = 0; i < inputSize; i++) {
                    for (int j = 0; j < inputSize; j++) {
                        mapfile << integerMap.at(i).at(j) << "\t";
                    }
                    mapfile << "\n";
                }

                mapfile.close();

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
                playerFile.close();

                cout << "Game Successfully Saved!" << endl;

            }

            else{

                cout << "Game Not Saved" << endl;

            }

        }

        else{

            cout << "Invalid Command" << endl;
            gameSave(integerMap, mainPlayer);

        }

    }

    else{

        ofstream mapfile;
        mapfile.open("saveMapData.dat");

        // Get Vector Size
        int inputSize = integerMap.size();

        // Print Every Element of Vector
        for(int i = 0; i < inputSize; i++){
            for(int j = 0; j < inputSize; j++){
                mapfile << integerMap.at(i).at(j) << "\t";
            }
            mapfile << "\n";
        }

        mapfile.close();

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
        playerFile.close();

        cout << "Game Successfully Saved!" << endl;

    }

}

bool loadGame(vector< vector<int> >& integerMap, Player& mainPlayer){

    vector<string> fileMapLines;
    vector<string> filePlayerLines;
    bool loadSuccess = false;

    if(checkFileExists("saveMapData.dat") && checkFileExists("savePlayerData.dat")){

        string line;
        ifstream myfile ("saveMapData.dat");

        if (myfile.is_open()){
            while ( getline (myfile,line) )
            {
                fileMapLines.push_back(line);
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

        string playerName = filePlayerLines.at(0);
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