/*
// This is the header file for users.h.This is the interface for the class "users".
 values of this type are names and room numbers.
*/

#ifndef ASSIGMENT4_USERS_H
#define ASSIGMENT4_USERS_H

#include <iostream>
#include <vector>
#include<cstdlib>
#include <ctime>
#include "BadGuy.h"

using namespace std;


// User class
class Users {

private:
    string UserName;
    int IndexOfCurrentRoom;
    int UserType;
    int UserLifepoints;




public:
    static int IndNextUser;

    // create a custom data type for the dfferent user types
    enum UserTypes {NORMAL,SUPERUSER,UNKNOWN};

    // Initializes the user name and current room index.
    Users(const string &nm, const int &indx);//default constructor
    Users();

    Users(const int &indx);

    //mutator function for custom UserTypes
    void setUserType (int type);

    //Accessor function for usertypes
    int getUserType () const;
    //mutator function to set user life points
    void setUserlifePoints(int lifepoints);

    //Accessor function to get user life points
    int getUserLifePoints() const;

    // set getUserName() of user
    void setUserName(string &username);

    // getuser getUserName()
    string getUserName() const;

    // set getUserName() of user
    void setIndexofCurrentRoom(int &indx);

    // getuser getUserName()
    int getIndexofCurrentRoom() const;

    // static void switches between users and keeps track of the room where the other user is located.
    static void setCurrentPLayer(int &playerNumber, const vector <Users *>& players);

    // calls the next users room number.
    static int getindexOfNextUser();

    //Function is meant to assign a random room to user from numbers 0-4
    virtual void setTeleportLocation();

    // overloading the << operator
    friend ostream &operator<<(ostream &Outputstream, const Users &username);

    //overloading the == operator
    friend bool operator==(const Users &currentUser, const Users &nextUser);
};


#endif //ASSIGMENT4_USERS_H
