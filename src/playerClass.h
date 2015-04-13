#ifndef _TEXTGAME_PLAYERCLASS_H_
#define _TEXTGAME_PLAYERCLASS_H_

#include <iostream>
#include <vector>
#include <algorithm>

#endif //_TEXTGAME_PLAYERCLASS_H_

using namespace std;

// Player Class
class Player{

private:

    string playerName;                  // Player Name
    int playerHealth;                   // Player Health
    vector<string> playerInventory;     // Stores Elements in the Player's Inventory

public:

    /***** FUNCTION PROTOTYPES *****/
    /*
    * void setName(string chosenName);
    * string getName();
    * void takeDamage(int damagePoints);
    * void healDamage(int healPoints);
    * int returnHealth();
    * void displayHealth();
    * void addToInventory(string playerItem);
    * void removeFromInventory(string itemToRemove);
    * vector<string> returnInventory();
    * void displayInventory();
    * */

    // Default Player Constructor
    Player(){

        // Initialize Player as Player1 with 100 pts of Health
        playerName = "Player1";
        playerHealth = 100;

    }

    /***** PLAYER NAME *****/

    // Set the Player Name
    void setName(string chosenName){
        playerName = chosenName;
    }

    // Gets the Player's Name
    string getName(){
        return playerName;
    }

    /***** PLAYER HEALTH *****/

    // Deals Damage to the playerHealth
    void takeDamage(int damagePoints){
        playerHealth = playerHealth - damagePoints;
    }

    // Heals Damage to playerHealth
    void healDamage(int healPoints){

        // Cap Healing at 100 Pts
        if(playerHealth + healPoints >= 100){
            playerHealth = 100;
        }

        else{
            playerHealth = playerHealth + healPoints;
        }

    }

    // Returns Player Health
    int returnHealth(){
        return playerHealth;
    }

    // Displays Current Health
    void displayHealth(){
        cout << "Current Health: " << playerHealth << " pts" << endl;
    }

    /***** PLAYER INVENTORY *****/

    // Add an Item to the Player's Inventory
    void addToInventory(string playerItem){
        playerInventory.push_back(playerItem);
    }

    // Removes Specific Item from Inventory
    void  removeFromInventory(string itemToRemove){
        playerInventory.erase(remove(playerInventory.begin(), playerInventory.end(), itemToRemove), playerInventory.end());
    }

    // Returns Inventory
    vector<string> returnInventory(){
        return playerInventory;
    }

    // Displays Inventory
    void displayInventory(){

        // Display Message
        cout << "Here is Your Inventory: " << endl;

        // Get Inventory Size
        int inventorySize = playerInventory.size();

        // Iterate Through Inventory
        for(int counter = 0; counter < inventorySize; counter++){

            // Display Item
            cout << "Item " << (counter + 1) << ": " << playerInventory.at(counter) << endl;

        }

    }

};