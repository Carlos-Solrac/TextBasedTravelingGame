//
// Created by carlo on 9/25/2021.
//


#include <iomanip>
#include <vector>
#include <iostream>
#include<cstdlib>
#include <time.h>

using namespace std;

#include "Users.h"
#include "BadGuy.h"
// Initializes the user name and current room index.
Users::Users(const string &nm,const int &indx) //default constructor
{
    this->UserName = nm;
    this->IndexOfCurrentRoom = indx;
    this ->UserType = NORMAL;
    this ->UserLifepoints = 10;
};

Users::Users() {
    this->UserName = "NO NAME ";
    this->IndexOfCurrentRoom = 0;
    this ->UserType = NORMAL;
    this ->UserLifepoints = 10;
}

Users::Users(const int &indx) {
    this -> UserName = "NO NAME";
    this->IndexOfCurrentRoom = 0;
    this ->UserType = NORMAL;
    this ->UserLifepoints = 10;
}

int Users::IndNextUser = 0;

//Mutator function for usertypes

void Users:: setUserType (int type)
{
    this -> UserType = type;
}
//Accessor function for usertypes

int Users::getUserType() const {
    return this-> UserType;
};
//mutator function to set user life points

void Users:: setUserlifePoints(int lifepoints) { this -> UserLifepoints = lifepoints;}

//Accessor function to get user life points

int Users::getUserLifePoints() const { return this-> UserLifepoints;}

// set getUserName() of user

void Users::setUserName(string &username) { this->UserName = username; }

// getuser getUserName()

string Users::getUserName() const { return this->UserName; }

// set getUserName() of user
void Users::setIndexofCurrentRoom(int &indx) { this->IndexOfCurrentRoom = indx; }

// getuser getUserName()
int Users::getIndexofCurrentRoom() const { return this->IndexOfCurrentRoom; }

// static void switches between users and keeps track of the room where the other user is located.
void Users::setCurrentPLayer(int &playerNumber, const vector <Users *>& players) {
    IndNextUser = playerNumber;
    if (playerNumber == (players.size() - 1) || players.size() == 1)
        playerNumber = 0;
    else
        playerNumber++;
}
//Function is meant to assign a random room to user from numbers 0-4
 void Users::setTeleportLocation() {
    //intentionally left empty
};

//overloaded the << operator for the User class to display user names

ostream &operator<<(ostream &Outputstream, const Users &username) {
    Outputstream << username.getUserName();
    return Outputstream;
}

// overloading a bool operator to compare user object to find when users are in the same room.

bool operator==(const Users &currentUser, const Users &nextUsers) {
    return (currentUser.getIndexofCurrentRoom() == nextUsers.getIndexofCurrentRoom());
}

int Users::getindexOfNextUser() {
    return IndNextUser;
}




