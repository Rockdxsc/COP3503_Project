#include "mainHeader.h"

using namespace std;

/* Function Prototypes */


int main() {

    string userAction;
    string userDirection;
    string userUse;
    string userCheck;
    Player mainPlayer;

    // Initialize the Items that are Available in the Level
    vector<string> itemsList;
    itemsList.push_back("SWORD");
    itemsList.push_back("HEALING SODA");
    itemsList.push_back("HEALING SODA");
    itemsList.push_back("KEY");
    itemsList.push_back("MAP");
    itemsList.push_back("HEALING SODA");

    // Generate an int Map Based on the Items in 'itemsList' and Create 40 Enemies
    vector< vector<int> > integerMap = generateIntMap(itemsList, 40);

    // Generate a Player Map Based on the Generated Integer Map
    vector< vector<string> > playerMap = generatePlayerMap(integerMap);

    // Game/Level Loop
    while (userAction != "EXIT") {

        cout << endl;
        printIntMap(integerMap);
        printInventory(mainPlayer);
        printPlayerMap(playerMap);
        cout << "What Would You Like to Do: ";
        cin >> userAction;
        stringToUpper(userAction);

        if(userAction == "MOVE") {

            cout << "What Direction Do You Wish to Move In: ";
            cin >> userDirection;
            clearScreen();
            stringToUpper(userDirection);
            movePlayer(mainPlayer, userDirection, integerMap, playerMap, itemsList);

        }

        else if(userAction == "USE"){

            printInventory(mainPlayer);
            cout << "What Would You Like to Use: ";
            getline(cin, userUse);
            getline(cin, userUse);
            stringToUpper(userUse);
            clearScreen();
            playerUse(mainPlayer, userUse, integerMap);

        }

        else if(userAction == "CHECK"){

            cout << "What Would You Like to Check: ";
            cin >> userCheck;

        }

        else{

            cout << "Unknown Action \'" << userAction << "\'" << endl;

        }

    }

    // Success Return
    return 0;

}