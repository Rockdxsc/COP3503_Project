#include "mainHeader.h"

using namespace std;

/* Function Prototypes */


int main() {

    string userAction;
    string userDirection;
    Player mainPlayer;

    // Initialize the Items that are Available in the Level
    vector<string> itemsList;
    itemsList.push_back("Item1");
    itemsList.push_back("Item2");
    itemsList.push_back("Item3");
    itemsList.push_back("Item4");
    itemsList.push_back("Item5");
    itemsList.push_back("Item6");

    // Generate an int Map Based on the Items in 'itemsList' and Create 40 Enemies
    vector< vector<int> > integerMap = generateIntMap(itemsList, 40);

    // Generate a Player Map Based on the Generated Integer Map
    vector< vector<string> > playerMap = generatePlayerMap(integerMap);

    // Game/Level Loop
    while (userAction != "EXIT") {

        printPlayerMap(playerMap);
        cout << "What Would You Like to Do: ";
        cin >> userAction;
        stringToUpper(userAction);

        if(userAction == "MOVE") {

            cout << "What Direction Do You Wish to Move In: ";
            cin >> userDirection;
            stringToUpper(userDirection);
            movePlayer(mainPlayer, userDirection, integerMap, playerMap, itemsList);

        }

        else{

            cout << "Unknown Action \'" << userAction << "\'" << endl;

        }

    }

    // Success Return
    return 0;

}