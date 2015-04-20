#include "mainHeader.h"

using namespace std;

/* Function Prototypes */

int main() {

    string userAction;
    string userDirection;
    string userUse;
    string userCheck;
    string userLoadCheck;
    string userName;
    Player mainPlayer;
    bool gameLoaded = false;

    // Initialize the Items that are Available in the Level
    vector<string> itemsList;
    itemsList.push_back("SWORD");
    itemsList.push_back("HEALING SODA");
    itemsList.push_back("HEALING SODA");
    itemsList.push_back("MAP");
    itemsList.push_back("HEALING SODA");

    vector< vector<int> > integerMap;
    vector< vector<int> > integerMap2;     //added another integermap for floor two
    vector< vector<string> > playerMap;
    vector< vector<string> > playerMap2;   //added another playermap as well

    cout << "Would You Like to Load the Game? (yes/no): ";
    cin >> userLoadCheck;
    stringToUpper(userLoadCheck);

    // If Load File Can Successfully be Loaded, Use it
    if(userLoadCheck == "YES" || userLoadCheck == "Y"){

        if(loadGame(integerMap, integerMap2, mainPlayer)){   //now also load with a second integermap for floor 2
            gameLoaded = true;
            cout << "Successfully Loaded Save!" << endl;
            cout << "Welcome Back " << mainPlayer.getName() << "!" << endl;
        }

        else{

            loadGame(integerMap, integerMap2, mainPlayer);

            // Generate an int Map Based on the Items in 'itemsList' and Create 40 Enemies
            integerMap = generateIntMap(itemsList, 20);
	    integerMap2 = generateIntMap(itemsList, 20);

        }

    }

    else if(userLoadCheck == "NO" || userLoadCheck == "N"){

        cout << "Generating New Map" << endl;

        // Generate an int Map Based on the Items in 'itemsList' and Create 40 Enemies
        integerMap = generateIntMap(itemsList, 20);
	integerMap2 = generateIntMap2(itemsList, 20);
	
	//Intro Text

        cout<< "A great hydra has emerged from its slumber and has stolen the key to the supplies for the land.\n It is now up to you to slay the mighty beast and retrieve the key that will save the people. Your adventure begins now" << endl;
        cout << endl;
    }

    else{

        cout << "Sorry, that isn't an Option" << endl;
        cout << "Generating New Map Instead..." << endl;

        // Generate an int Map Based on the Items in 'itemsList' and Create 40 Enemies
        integerMap = generateIntMap(itemsList, 20);
	integerMap2 = generateIntMap2(itemsList, 20);

    }

    // Generate a Player Map Based on the Generated Integer Map
    playerMap = generatePlayerMap(integerMap);
    playerMap2 = generatePlayerMap(integerMap2);          //second playermap created from the 2nd integermap created

    if(!gameLoaded){

        cout << "What Would You Like to be Called Adventurer?: ";
        cin >> userName;
        mainPlayer.setName(userName);
        cout << "Thanks " << userName << ", Let's Get Started!" << endl;
    }

    // Game/Level Loop
    while (userAction != "EXIT") {

        cout << endl;
	if(mapCheck() == 1){    //added mapCheck to see which floor the player was on
	        printPlayerMap(playerMap);
	}
	else{
		printPlayerMap(playerMap2);
	}
        cout << "What Would You Like to Do: ";
        cin >> userAction;
        stringToUpper(userAction);

        if(userAction == "MOVE") {

            cout << "What Direction Do You Wish to Move In: ";
            cin >> userDirection;
            stringToUpper(userDirection);
            clearScreen();
		if(mapCheck() == 1){     //again, checks which floor the player is on before performing the move action
           		 movePlayer(mainPlayer, userDirection, integerMap, playerMap, itemsList);
		}
		else{
			movePlayer(mainPlayer, userDirection, integerMap2, playerMap2, itemsList);
		}

        }

        else if(userAction == "USE"){

            printInventory(mainPlayer);
            cout << "What Would You Like to Use: ";
            getline(cin, userUse);
            getline(cin, userUse);
            stringToUpper(userUse);

            clearScreen();
		if(mapCheck() == 1){
	            playerUse(mainPlayer, userUse, integerMap);
		}
		else{
			playerUse(mainPlayer, userUse, integerMap2);
		}
        }

        else if(userAction == "CHECK"){

            cout << "What Would You Like to Check: ";
            cin >> userCheck;
            stringToUpper(userCheck);

            clearScreen();

            if(userCheck == "INVENTORY"){

                mainPlayer.displayInventory();

            }

            else if(userCheck == "HEALTH"){

                mainPlayer.displayHealth();

            }

            else if(userCheck == "GOLD"){

                int userGold = mainPlayer.getGold();

                cout << "Your Current Gold is: " << userGold << endl;

            }

            else if(userCheck == "HELP"){

                cout << "Type \'INVENTORY\' to View Your Inventory" << endl;
                cout << "Type \'HEALTH\' to View Your Current Health" << endl;
                cout << "Type \'GOLD\' to View Your Current Gold" << endl;
                cout << endl;
            }

            else{

                cout << "Sorry Unrecognized Command" << endl;

            }

        }

        else if(userAction == "EXIT"){

            string userExit;

            cout << "Would You Like to Save the Game? (yes/no): ";
            cin >> userExit;
            stringToUpper(userExit);

            if(userExit == "YES"){
		if(mapCheck() == 1){
	                gameSave(integerMap, integerMap2, mainPlayer);
		}
		else{
			gameSave(integerMap, integerMap2, mainPlayer);
		}
            }

            else{

                cout << "Game Not Saved" << endl;

            }

        }

        else if(userAction == "HELP"){

            clearScreen();

            cout << "Type \'MOVE\' to Move Your Character Across the Map" << endl;
            cout << "Type \'USE\' to Use Healing Sodas or View the Item Map if they are in Your Inventory" << endl;
            cout << "Type \'CHECK\' to be Given the Option to Check Properties Like Your Inventory and Health" << endl;
            cout << "Type \'EXIT\' to Quit the Game and be Given the Option to Save Your Progress" << endl;
            cout << endl;

        }
	else if(userAction == "CHEAT"){
		mainPlayer.addGold(100);
		
	}
        else{

            clearScreen();

            cout << "Unknown Action \'" << userAction << "\'" << endl;
            cout << "Please use the \'HELP\' Command for a List of Actions" << endl;

        }

    }

    // Success Return
    return 0;

}
