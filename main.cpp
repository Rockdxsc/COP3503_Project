#include "mainHeader.h"

using namespace std;

/* Function Prototypes */


int main() {

    string userDirection;

    vector<string> itemsList;
    itemsList.push_back("Item1");
    itemsList.push_back("Item2");
    itemsList.push_back("Item3");
    itemsList.push_back("Item4");
    itemsList.push_back("Item5");
    itemsList.push_back("Item6");

    vector< vector<int> > integerMap = generateIntMap(itemsList, 10);
    vector< vector<string> > playerMap = generatePlayerMap(integerMap);

    while (userDirection != "EXIT") {

        printIntMap(integerMap);
        printPlayerMap(playerMap);
        cout << "WHAT DIRECTION SHALL I MOVE: ";
        cin >> userDirection;
        stringToUpper(userDirection);

        if(userDirection != "EXIT") {
            movePlayer(userDirection, integerMap, playerMap);
        }

    }

    // Success Return
    return 0;

}