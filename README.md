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
~ To Be Filled In

#### CHECKLIST
- [ ] Develop Game/Puzzle Storyboard <b> **URGENT! </b>
- [X] Create Dynamic Map Engine
- [X] Create Player/Enemy Classes
- [X] Develop Movement Mechanics
- [X] Develop Battle Sequences
- [ ] Implement Puzzle Games
- [X] Develop Player Interactions
- [ ] Develop Help Dialogues For User Actions
- [ ] Implement Multiple Levels?
- [X] Save/Load Implementation
- [ ] Testing
- [ ] Deployment

#### WHAT NEEDS TO BE DONE

- <b><i>Develop Game/Puzzle Storyboard</i></b>
  - Need someone to develop a storyline for the game, and how puzzles will work in the game. Basically need all the details as to how the gameplay will operate.

- <b><i>Implement Puzzle Games</i></b>
  - Need someone to actually implement the puzzle games that were outlined in the storyboard

- <b><i>Develop Help Dialogues</i></b>
  - In the current stage of user interactions, someone needs to create an output for the `HELP` command in the following situations:
  
    - <b> Main Game Help: </b> `"What Would You Like to Do: "` The `HELP` command here should give an explaination of the following inputs: `MOVE`, `USE`, and `CHECK` 
      - `MOVE` allows the player to move either `NORTH`, `SOUTH`, `EAST`, or `WEST`
      - `USE` allows the player to use a `HEALING SODA` or the `MAP` if they are in the inventory
      - `CHECK` allows the player to view their `HEALTH` or the contents of their `INVENTORY`
      - <b> `MOVE` Command Help: </b> This should let the player know what the direction commands are
      - <b> `USE` Command Help: </b> This sould outline what items can be used outside of battle
      - <b> `CHECK` Command Help: </b> This should outline what can be checked
      
    - <b> Battle Help: </b> `"Fight or Flee: "` The `HELP` command here should give an explaination of the following inputs: `FIGHT` and `FLEE`
      - `FIGHT` allows the user to choose either choose his/her `FIST` (in case that no weapons have been collected yet) or a weapon from his/her inventory such as a `SWORD` to fight the enemy.
      - `FLEE` allows the user a chance to run away from the enemy, however this is not always successful, especially with stronger enemeies
      - <b> `FIGHT` Command Help: </b> This should let the player know what items/commands are viable weapons
