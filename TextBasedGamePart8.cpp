#include <iostream>
#include <iomanip>
#include <vector>
#include "Users.h"
#include "Rooms.h"
#include "BadGuy.h"
#include <fstream>
#include<cstdlib>
#include <time.h>
#include "SuperUser.h"
#include "PlayerList.h"
#include "PlayerList.cpp"


/*Name: Carlos Cuellar
  Date: 10/21/2021
  Section: 009
  Assignment:(Assignment8)
  DueDate: 10/24/2021
  About this project:
  The purpose of this assignment is to further improve the text based gamed with the following:

  Develop, compile, and run a C++ program that requires templates, and the creation and the management
  of a multi-file project using g++ and make, and the proper use of these in a program to solve
  a problem utilizing software engineering principles and techniques in design.

  All work below as performed by Carlos Cuellar*/

using namespace std;
//number of rooms
const int NUM_ROOMS = 5;
const int NUM_PLAYERS = 2;

// sets up rooms);
void initRooms(Room rooms[]);

// sets up user and current room index
template<class T>
void initUser(vector<T *> &player);

//sets up how many badguys will be in the game.
void initBadGuys(vector<BadGuy *> &badguys, string arrbadguys[]);

//User selects an action
template<class T>
void
promptUserAction(vector<T *> players, int playernumber,const Room rooms[], string &strCh, vector<BadGuy *> badguys);

//implement Users Action
template<class T>
void implementUserAction( vector<T *> players, int playernumber, const Room rooms[], string &strCh,
                         vector<BadGuy *> &badguys,PlayerList<Users> &UsersInList);

//implement bad guy action
void badGuymovement(vector<BadGuy *> badguys);

// Loads user data from a file
template<class T>
void loadUserData(vector<T *> &players);

// Overwrites a file with new user data
template<class T>
void createUserSavedData(vector<T *> players, int playernumber);

// Appends User data to existing file with user data
template<class T>
void appendUserSavedData(vector<T *> players, int playernumber);


int main() {

    srand(time(0)); // NOLINT(cert-msc51-cpp)
    // Room class object holding the 5 different rooms for our game
    Room rooms[NUM_ROOMS];
    // String array of bad guy names with 10 names total
    string arrbadguys[10] = {"Jim", "Tom", "Anthony", "Bob", "Johnny", "Paul", "Ricky", "Annabelle", "Cynthia",
                             "Leslie"};
    //list of users
    PlayerList<Users> UsersInList;

    //creates object of Users and bad guy class to initialize class variables
    int creatorFavRoom = 3;
    string creator = "carlos";
    //initialize user/badguy and rooms
    initRooms(rooms);
    BadGuy myBadGuy;
    //creates a vector of user names
    vector<Users *> players;
    //creates a vector of bad guys
    vector<BadGuy *> badguys;
    int playerNumber =0;

    // string to gold user choice for loading data
    string LoadData;
    //load user data prompt loop
    while (LoadData != "Y" && LoadData != "y" && LoadData != "N" && LoadData != "n") {
        cout << "Would you liked to the load the previous saved user data? (Y/N): ";
        cin >> LoadData;
        if (LoadData == "Y" || LoadData == "y") {
            // load data from text file of type users to vector players
            loadUserData(players);
            // check if the loaded data is less than our max player number, if so create more users until the max.
            if (players.size() < NUM_PLAYERS) {
                // check if the read in user is of type Normal,SuperUser, or Unkonwn
                if (players.at(players.size() - 1)->getUserType() == Users::NORMAL) {
                    // if the read in player is a normal player, create a super user with default values.
                    SuperUser *user2 = new SuperUser(creator, creatorFavRoom);
                    players.push_back(user2);
                }
                    //if the read in user is a super user, create a normal user and prompt for name.
                else if (players.at(players.size() - 1)->getUserType() == Users::SUPERUSER) {
                    initUser(players);
                }
            }

        } else if (LoadData == "N" || LoadData == "n") {
            // initialize a super user user with the SuperUser class constructor.
            SuperUser *user2 = new SuperUser(creator, creatorFavRoom);
            // initialize regular user
            initUser(players);
            // add super user to players vector.
            players.push_back(user2);
        } else {
            cout << "Invalid input. Please enter Y,y,N, or n." << endl;
        }
    }

    cout << "Welcome to my game!" << endl << "********************************************" << endl;

    //initiate bad guys
    initBadGuys(badguys, arrbadguys);
    string UserAction;

    // initialize number of saved entries performed.
    int dataSavedCounter = 0;
    do {

        // checks if current player is a super user and if so prints a special message
        if (players.at(playerNumber)->getUserType() == Users::SUPERUSER)
            cout << "-----SUPER USER-----" << endl;
        promptUserAction(players, playerNumber, rooms, UserAction, badguys);
        implementUserAction(players, playerNumber, rooms, UserAction, badguys,UsersInList);
        // add player to player list if they reach the mountain top

       if ((UserAction == "Q" || UserAction == "q")) {
            string saveStr;
            while (saveStr != "Y" && saveStr != "y" && saveStr != "N" && saveStr != "n") {
                cout << "Would you like to create a save file? (Y/N)?: " << endl;
                cin >> saveStr;
                // prompt user to see if they would like ot save their data
                if (saveStr == "Y" || saveStr == "y") {

                    // check if this is the first user saved data
                    if (dataSavedCounter < 1) {
                        dataSavedCounter++;
                        // overwrites data in PlayersData.txt
                        createUserSavedData(players, playerNumber);
                    } else {
                        // appends data to PlayersData.txt
                        appendUserSavedData(players, playerNumber);
                    }

                    cout << "Player data saved successfully.\n";
                } else if (saveStr == "N" || saveStr == "n")
                    cout << "Thank you for playing. No data was saved." << endl << endl;
                else
                    cout << " Invalid input.Please enter Y/N." << endl;
            }
            // removes user or superuser from players vector
            players.erase(players.begin() + playerNumber);
            // switches to remaining player
            Users::setCurrentPLayer(playerNumber, players);
        }
        // add player to user list if they go to index 4 "Mountian Top"
        if (players.at(playerNumber)->getIndexofCurrentRoom() == 4)
        {
            UsersInList.addToList(players.at(playerNumber));
        }
        // Allows our bad guys to move after players move
        badGuymovement(badguys);
        // switches between players by increasing the next user index.
        Users::setCurrentPLayer( playerNumber, players);


    } while (!players.empty());
    //continue until all users quit

    return 0;
}

// Initializes user.
template<class T>
void initUser(vector<T *> &player) {
    //prompt and set  user name.
    cout << "What is your name? " << endl;
    string nm; //temp value.
    cin >> nm; // holds name.
    int startingroom = 0;
    // create a new user and set their default values from the input values.
    Users *u = new Users;
    u->setUserName(nm);
    u->setIndexofCurrentRoom(startingroom);
    player.push_back(u);

}

void initBadGuys(vector<BadGuy *> &badguys, string arrbadguys[]) {
    int totalBadGuys = 0;
    // do while loop to obtain a valid number of bad guys
    do {
        cout << "How many BadGuys do you want to play with? Enter 0 through 10\n";
        cin >> totalBadGuys;
        if (totalBadGuys > 10)
            cout << "Sorry, that's too many bad guys.\n";
        if (totalBadGuys < 0)
            cout << "Sorry, you can't have negative bad guys.\n";
    } while (totalBadGuys > 10 || totalBadGuys < 1);
    // for loop to initialize as many bad guys as user entered with a random starting room
    srand(time(NULL));
    for (int i = 0; i < totalBadGuys; i++) {
        int randomindx = 0;
        // random integer should go from 0-4
        randomindx = (rand() % 5) ;
        // dynamic allocation of user
        BadGuy *b = new BadGuy;
        b->setBadGuyUserName(arrbadguys[i]);
        b->setIndexofCurrentRoomBadGuy(randomindx);
        badguys.push_back(b);
    }

};

// sets up rooms
void initRooms(Room rooms[]) {

    //init Cave
    (rooms + 0)->setName("Cave");
    (rooms + 0)->setIndexRoomToNorth(4);
    (rooms + 0)->setIndexRoomToSouth(1);
    (rooms + 0)->setIndexRoomToEast(-99);
    (rooms + 0)->setIndexRoomToWest(-99);
    (rooms + 0)->setRoomDescription("The cave is dark and cold, you won't want to stay here long.");

    //init Forest
    (rooms + 1)->setName("Forest");
    (rooms + 1)->setIndexRoomToNorth(0);
    (rooms + 1)->setIndexRoomToSouth(-99);
    (rooms + 1)->setIndexRoomToEast(2);
    (rooms + 1)->setIndexRoomToWest(3);
    (rooms + 1)->setRoomDescription("You walk into a forest of giant birch trees");

    //init Clearing
    (rooms + 2)->setName("Clearing");
    (rooms + 2)->setIndexRoomToNorth(-99);
    (rooms + 2)->setIndexRoomToSouth(-99);
    (rooms + 2)->setIndexRoomToEast(-99);
    (rooms + 2)->setIndexRoomToWest(1);
    (rooms + 2)->setRoomDescription("You walk into a big clearing int he middle of the forest");
    //init Lake
    (rooms + 3)->setName("Lake");
    (rooms + 3)->setIndexRoomToNorth(-99);
    (rooms + 3)->setIndexRoomToSouth(-99);
    (rooms + 3)->setIndexRoomToEast(1);
    (rooms + 3)->setIndexRoomToWest(-99);
    (rooms + 3)->setRoomDescription("You go west from the forest and arrive at a  large lake full of wildlife.");

    //init Mountain top
    (rooms + 4)->setName("Mountain Top");
    (rooms + 4)->setIndexRoomToNorth(-99);
    (rooms + 4)->setIndexRoomToSouth(0);
    (rooms + 4)->setIndexRoomToEast(-99);
    (rooms + 4)->setIndexRoomToWest(-99);
    (rooms + 4)->setRoomDescription("As you move north from the cave you exit and arrive at the top of a mountain.");
}

//User Action
template<class T>
void
promptUserAction(vector<T *> players, int playernumber,const Room rooms[], string &strCh, vector<BadGuy *> badguys) {
    // tell user where they are and describes the room
    cout <<"-----------------------------------------------\n"<< *players.at(playernumber) << " you are currently in "
         << rooms[players.at(playernumber)->getIndexofCurrentRoom()].getName();
    cout << endl;
    cout << rooms[players.at(playernumber)->getIndexofCurrentRoom()].getDescription() << endl;

    //Inform if badguy is in the same room
    for (int i = 0; i < badguys.size(); i++) {
        if (badguys.at(i)->getIndexofCurrentRoomBadGuy() == players.at(playernumber)->getIndexofCurrentRoom() &&
            badguys.at(i)->getBadGuyLifePoints() > 0)
            cout << "#Bad Guy " << badguys.at(i)->getBadGuyUserName() << " is here. \n";
              }
    //prompt user for choice
    cout << "What would you like to do?" << endl<<"Options are : N,E,W,S,A,Z,T(super user),and I(super user):";
    cin >> strCh;
}

//implement bad guy action
void badGuymovement(vector<BadGuy *> badguys) {

// for loop  to set index of badguys . Increases by one each iteration and loops to 0 after reaching 4.
    for (int i = 0; i < badguys.size(); i++) {
        // allows random movement between 0 and 4.
        int indx = (rand() % 5) ;
        badguys.at(i)->setIndexofCurrentRoomBadGuy(indx);
    }
}

//implement Users Action
template<class T>
void implementUserAction( vector<T *> players, int playernumber, const Room rooms[], string &strCh,
                          vector<BadGuy *> &badguys,PlayerList<Users> &UsersInList) {
    //check if user left room
    bool movementChecker = true;
    if (strCh == "O" || strCh == "o") {
        // user has selected to check if there are other users in the same room
        if (players.at(playernumber)->getIndexofCurrentRoom() ==
            (players[Users::getindexOfNextUser()]->getIndexofCurrentRoom()) && players.size() != 1)
            // checks if the room indexes of player 1 and player 2 are the same
        {
            cout << "The following users are in the same room: " << endl;
            for (int i = 0; i < players.size(); i++) {
                cout << *players[i] << endl;
            }
            // prints out a list of the users in the same room
        } else {
            cout << "No other users in this room." << endl;
            movementChecker = false;
        }

    } else if ((strCh == "N") || (strCh == "n")) {
        //user has selected to move north

        // is it possible to move north from the room the user
        //is currently in

        int indxRoomNorth = rooms[players.at(playernumber)->getIndexofCurrentRoom()].getIndexRoomToNorth();
        if (indxRoomNorth != -99) {
            players.at(playernumber)->setIndexofCurrentRoom(indxRoomNorth);
            cout << *players.at(playernumber)<< ", you are now in "
                 << rooms[players.at(playernumber)->getIndexofCurrentRoom()].getName() << endl;


        } else {
            cout << *players.at(playernumber) << ", you can not move north from "
                 << rooms[players.at(playernumber)->getIndexofCurrentRoom()].getName() << endl;
                 movementChecker = false;

        }
    } else if ((strCh == "S") || (strCh == "s")) {
        //user has selected to move south

        // is it possible to move south from the room the user
        //is currently in
        int indxRoomSouth = rooms[players.at(playernumber)->getIndexofCurrentRoom()].getIndexRoomToSouth();
        if (indxRoomSouth != -99) {
            players.at(playernumber)->setIndexofCurrentRoom(indxRoomSouth);
            cout << *players.at(playernumber) << ", you are now in "
                 << rooms[players.at(playernumber)->getIndexofCurrentRoom()].getName() << endl;

        } else {

            cout << *players.at(playernumber)<< ", you can not move south from "
                 << rooms[players.at(playernumber)->getIndexofCurrentRoom()].getName() << endl;
            movementChecker = false;
        }
    } else if ((strCh == "E") || (strCh == "e")) {
        //user has selected to move east

        // is it possible to move east from the room the user
        //is currently in
        int indxRoomEast = rooms[players.at(playernumber)->getIndexofCurrentRoom()].getIndexRoomToEast();
        if (indxRoomEast != -99) {
            players.at(playernumber)->setIndexofCurrentRoom(indxRoomEast);
            cout << *players.at(playernumber)<< ", you are now in "
                 << rooms[players.at(playernumber)->getIndexofCurrentRoom()].getName() << endl;
        } else {
            cout << *players.at(playernumber)<< ", you can not move east from "
                 << rooms[players.at(playernumber)->getIndexofCurrentRoom()].getName() << endl << "********************************************"
                 << endl;
            movementChecker = false;
        }
    } else if ((strCh == "W") || (strCh == "w")) {
        //user has selected to move west

        // is it possible to move west from the room the user
        //is currently in
        int indxRoomWest = rooms[players.at(playernumber)->getIndexofCurrentRoom()].getIndexRoomToWest();
        if (indxRoomWest != -99) {
            players.at(playernumber)->setIndexofCurrentRoom(indxRoomWest);
            cout << *players.at(playernumber) << ", you are now in "
                 << rooms[players.at(playernumber)->getIndexofCurrentRoom()].getName() << endl;

        } else {
            cout << *players.at(playernumber)<< ", you can not move west from "
                 << rooms[players.at(playernumber)->getIndexofCurrentRoom()].getName() << endl;
            movementChecker = false;
        }
    } else if ((strCh == "A") || (strCh == "a")) {
        // user has selected a/A
        //counter to know how many bad guys there are in the same room as an user
        int badguycounter = 0;
        // for loop to check if bad guys are with an user and to allow user to attack them
        for (int i = 0; i < badguys.size(); i++) {
            // check if badguys are in the room AND have greater than 0 life points
            if (badguys.at(i)->getBadGuyLifePoints() > 0 &&
                players.at(playernumber)->getIndexofCurrentRoom() == badguys.at(i)->getIndexofCurrentRoomBadGuy()) {

                cout << *players.at(playernumber) << " you attack bad guy " << badguys.at(i)->getBadGuyUserName()
                     << ". ";
                badguys.at(i)->setBadGuyLifePoints(5);
                badguycounter++;
                // Print bad guy life points if they have greater than 0 life points.
                if (badguys.at(i)->getBadGuyLifePoints() > 0) {
                    cout << badguys.at(i)->getBadGuyUserName()
                         << " now has " << badguys.at(i)->getBadGuyLifePoints() << " life points left." << endl;
                } else {
                    // print out to screen that a bad guy is dead if they have less than 0 life points
                    cout << badguys.at(i)->getBadGuyUserName() << " is dead.\n";
                    badguys.erase(badguys.begin() + i);
                }
            }
        }
        if (badguycounter == 0)
        //user has selected an invalid option
        cout << strCh << " Is not a valid option if you are not in the same room as any bad guys." <<endl;
    movementChecker = false;

    }   else if(strCh =="Z" || strCh =="z")
    {
        // check if player is on the players list.
        if (UsersInList.verifyList(players.at(playernumber)))
        cout << *players.at(playernumber)<< " you are on the user list.\n";
        else
            cout<< *players.at(playernumber)<<" you are not on the list.\n";
    }
    else if ((strCh == "Q") || (strCh == "q")) {
        //user has selected to quit
        cout << *players.at(playernumber) << " Thank you for playing..." << endl;
    }
    else if (strCh == "I" || strCh == "i") {
        if (players.at(playernumber)->getUserType() == Users::SUPERUSER) {

            cout << "\nSuperUser special abilty: Can of Whoop butt!\n";
            for (int i =0; i < badguys.size(); i++) {
                if (badguys.at(i)->getBadGuyLifePoints() > 0) {
                    cout << *players.at(playernumber) << " you attack bad guy " << badguys.at(i)->getBadGuyUserName()
                         << ", but your special attack only does " << 1 << " damage. ";
                    badguys.at(i)->setBadGuyLifePoints(1);
                    cout << badguys.at(i)->getBadGuyUserName()
                         << " now has " << badguys.at(i)->getBadGuyLifePoints() << " life points left." << endl;
                    if (badguys.at(i)->getBadGuyLifePoints() <= 0)
                        badguys.erase(badguys.begin() + i);
                }
            }
        } else
            cout << "\n***Option I/i is only for super users***\n\n";

        movementChecker = false;
    } else if (strCh == "T" || strCh == "t") {
        // user has selected t/T

        // if loop to check that the user is a super user
        if (players.at(playernumber)->getUserType() == Users::SUPERUSER) {
            cout << "SuperUser special ability:Teleportion no justsu!!\n";
            // mutator function to assign user a random room
            players.at(playernumber)->setTeleportLocation();
            cout << "Teleportation fails...you end up in a random room\n\n";
        } else
            cout << "\n***Option I/i is only for super users***\n\n";
    } else {
        //user has selected an invalid option
        cout << strCh << " is not a valid option." << endl << "********************************************" << endl;
    }


    if (!movementChecker) {
        // set badguy attackpower
        int badGuyAttackPower = 1;

        // for loop to allow bad guys to attack user if they're in the same room.
        for (int i = 0; i < badguys.size(); i++) {
            //creates a 0/1 randomizer to see if bad guy attacks. 0 for false and 1 for true.
            int randomAttack = (rand() % 2);
            //checks badguy room index vs the user index, also checks badguy is alive, and also checks if the badguy is allowed to attack.
            if (badguys.at(i)->getIndexofCurrentRoomBadGuy() == players.at(playernumber)->getIndexofCurrentRoom() &&
                badguys.at(i)->getBadGuyLifePoints() > 0 && randomAttack == 1) {
                cout << badguys.at(i)->getBadGuyUserName() << " attacks " << players.at(playernumber)->getUserName()
                     << " for "
                     << badGuyAttackPower << " damage.\n";
                int lifepoints = players.at(playernumber)->getUserLifePoints();
                players.at(playernumber)->setUserlifePoints(lifepoints - badGuyAttackPower);
                cout << players.at(playernumber)->getUserName() << " now has "
                     << players.at(playernumber)->getUserLifePoints()
                     << " life points left.\n********************************************\n";
            }
        }
    }
    cout<<"-----------------------------------------------\n";
}

// Function to read in data from a file using a pointer to the Users class.
template<class T>
void loadUserData(vector<T *> &players) {
    ifstream inputFile("PlayerData.txt");
    // opening file validation
    if (inputFile.fail()) {
        cout << " Invalid source file." << endl;
        exit(1);
    } else {
        //temp string to hold the names
        string input;
        int userType;
        // temp variable to hold room index of users
        int roomIndx;
        //temp variable to hold user life points
        int lifepoints;

        // Loop to go through data in the file to pull names, room indexes, and user type.
        while (inputFile >> input>>roomIndx>>userType>>lifepoints) {
            // read name
            Users *user = new Users;
            user->setUserName(input);
            user->setIndexofCurrentRoom(roomIndx);
            user->setUserType(userType);
            user ->setUserlifePoints(lifepoints);

            players.push_back(user);
        }
        inputFile.close();
    }
}

// function to replace whatever is in the player file with the value of the first player wanting to save.
template<class T>
void createUserSavedData(vector<T *> players, int playernumber) {
    ofstream outPutFile("PlayerData.txt");
    // Opening file validation
    if (outPutFile.fail()) {
        cout << "Invalid output source file" << endl;
        exit(1);
    }
    // obtain user name and room index to output to file
    outPutFile << players.at(playernumber)->getUserName() << endl;
    outPutFile << players.at(playernumber)->getIndexofCurrentRoom() << endl;
    outPutFile << players.at(playernumber)->getUserType() << endl;
    outPutFile << players.at(playernumber)->getUserLifePoints() << endl;


    outPutFile.close();
}

// function to append to whatever is in the player file with the value of the second player wanting to save.
template<class T>
void appendUserSavedData(vector<T *> players, int playernumber) {
    ofstream outPutFile("PlayerData.txt", ios::app);
    // Opening file validation
    if (outPutFile.fail()) {
        cout << "Invalid output source file" << endl;
        exit(1);
    }
    // obtain user name and room index to output to file
    outPutFile << players.at(playernumber)->getUserName() << endl;
    outPutFile << players.at(playernumber)->getIndexofCurrentRoom() << endl;
    outPutFile << players.at(playernumber)->getUserType() << endl;
    outPutFile << players.at(playernumber)->getUserLifePoints()<< endl;

    outPutFile.close();
}



