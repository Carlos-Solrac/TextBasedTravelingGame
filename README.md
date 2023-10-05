# Text-Based C++ Game


## Project Description

This C++ project is a text-based game where players explore different rooms, interact with bad guys, and make decisions to progress in the game. 
The game also includes super users with special abilities, and players can save their progress. This project is a C++ program that demonstrates 
various software engineering principles and practices. It includes features such as object-oriented programming, 
data structures, file handling, and operator overloading.

## Assumptions

- The program assumes that user data is stored in a file named "PlayerData.txt."
- It assumes that the program should model user entities, bad guys, rooms, and actions in a game-like scenario.

## Implementation Details

Modularization: The program is organized into multiple files for improved code structure and organization.

Object-Oriented Programming (OOP): The code follows OOP principles by defining classes and objects to model real-world entities.
Templates are also used to allow for reusability.

Data Structures: The program uses data structures like vectors to manage collections of objects (e.g., `players`, `badguys`, etc.).

File Handling: Data is read from and written to files ("PlayerData.txt") for data persistence.

Randomization: Random numbers are generated for various game aspects.

Error Handling: The program handles potential errors when working with files.

Operator Overloading: Custom behaviors are provided for operators like << and == for the Users class.

Static Members: Static member variables are used for tracking the next user's index.


## Game Features:

Multiple Rooms: The game includes various rooms to explore, each with its own description.
Bad Guys: Encounter bad guys in some rooms and engage in combat with them.
User Types: Players can be regular users or super users, each with different abilities.
Save Progress: Players can save their progress and load it in subsequent sessions.
How to Play
When prompted, choose an action:

N: Move north
S: Move south
E: Move east
W: Move west
A: Attack bad guys in the room
Z: Check if you are on the user list (super users only)
T: Use super user teleportation ability (super users only)
I: Use super user special attack (super users only)
Q: Quit the game
Explore rooms, defeat bad guys, and try to reach the mountain top.

## Credits

All work below was performed by Carlos Cuellar Benitez.

