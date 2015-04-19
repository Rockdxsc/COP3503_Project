## COP3503 Project: Text Based Puzzle Adventure Game

#### ABOUT
A text based puzzle adventure game that dynamically generates worlds with items/enemies that the player must navigate through to obtain the key that unlocks the door (it's never the same game twice!).
	
#### CREATORS/MAINTAINERS
- <b>Joshua Andron</b>
- <b>Austin Baker:</b> @agbaker
- <b>Colin Bandish:</b> @colinbnd
- <b>Harsha Kuchampudi:</b> @hkuchampudi
- <b>Matthew Samach</b>
- <b>Kevin Wong:</b> @KWong1996

#### CODE OVERVIEW

- Initialize a player with the command:

```c++
Player mainPlayer
```

- Initializing a list of items that will be randomly placed into the game:

```c++
// Initialize the Items that are Available in the Level
vector<string> itemsList;
itemsList.push_back("SWORD");
itemsList.push_back("HEALING SODA");
itemsList.push_back("HEALING SODA");
itemsList.push_back("KEY");
itemsList.push_back("MAP");
itemsList.push_back("HEALING SODA");
```

- Generate a random map that incorporates the items that you listed as well as the number of enemies that you specify:

```c++
// Generate an int Map Based on the Items in 'itemsList' and Create 40 Enemies
vector< vector<int> > integerMap = generateIntMap(itemsList, 40);
``` 

- Finally, generate the map that the player sees, by passing in the created integerMap

```c++
vector< vector<string> > playerMap = generatePlayerMap(integerMap);
```

- Movement across the map is done through issuing after querying (string) the user's intended direction:

```c++
movePlayer(mainPlayer, userDirection, integerMap, playerMap, itemsList);
```

- Saving the game is done by invoking the command:

```c++
gameSave(integerMap, mainPlayer);
```

- Loading is done by passing through empty integerMap and player vectors. The player map can then be generated off of this integerMap

```c++
// Initializing player, integerMap, and playerMap
Player mainPlayer;
vector< vector<int> > integerMap;
vector< vector<string> > playerMap;

// Passing in to the loadGame() function
loadGame(integerMap, mainPlayer)

// Generating playerMap from the loaded integerMap
playerMap = generatePlayerMap(integerMap);
```

- To print the playerMap for the player, simply invoke:

```c++
printPlayerMap(playerMap);
```

#### CHECKLIST
- [X] Develop Introduction Output
- [X] Create Dynamic Map Engine
- [X] Create Player/Enemy Classes
- [X] Develop Movement Mechanics
- [X] Develop Battle Sequences
- [X] Develop Player Interactions
- [X] Develop Help Dialogues For User Actions
- [X] Save/Load Implementation
- [X] Different Floors *Priority*  I've got it working but please double check me and a third floor is definently possible if you want it (if I have time ill try to make it a differnt shaped floor)
- [ ] Add text based events (active and [X]passive)
- [X] What to have in town 
- [X] Enemy variations
- [X] Enemy Scaling and Player Scaling
- [ ] More items
- [ ] Testing
- [ ] Deployment

#### WHAT NEEDS TO BE DONE

- <b><i>Develop Game/Puzzle Storyboard</i></b>
  - Need someone to develop a storyline for the game, and how puzzles will work in the game. Basically need all the details as to how the gameplay will operate.

- <b><i>Develop Introduction Output</i></b>
  - Need someone to create an introduction to the game using `cout`.

- <b><i>Implement Puzzle Games</i></b>
  - Need someone to actually implement the puzzle games that were outlined in the storyboard.
