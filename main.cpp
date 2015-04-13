#include "mainHeader.h"

using namespace std;

/* Function Prototypes */


int main() {

    string userAction;
    string userDirection;
    Player mainPlayer;

    vector<string> itemsList;
    itemsList.push_back("Item1");
    itemsList.push_back("Item2");
    itemsList.push_back("Item3");
    itemsList.push_back("Item4");
    itemsList.push_back("Item5");
    itemsList.push_back("Item6");

    vector< vector<int> > integerMap = generateIntMap(itemsList, 20);
    vector< vector<string> > playerMap = generatePlayerMap(integerMap);

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