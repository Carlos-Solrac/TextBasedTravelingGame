/*
// This is the header file for BadGuy.h.This is the interface for the class "BadGuy".
 values of this type are names and room numbers.
*/

#ifndef ASSIGMENT4_BADGUY_H
#define ASSIGMENT4_BADGUY_H

#include <iostream>

using namespace std;


// Badguy class

class BadGuy {
private:
    string BadGuyName;
    int BadGuyIndex;
    int BadGuyLifePoints;
public:
    // Initializes BadGuy and current room index.
    BadGuy(string &nm, int &indx, int &indx2);//default constructor
    BadGuy();

    BadGuy(int &indx);
    // set badguy name
    void setBadGuyUserName(string &nm);

        // getuser getUserName()
    string getBadGuyUserName() const;

    //get bad guy life points
    int getBadGuyLifePoints() const;
    //set badguy health after user attack
    void  setBadGuyLifePoints(int attack);

    // set getUserName() of user
    void setIndexofCurrentRoomBadGuy(int &indx);

    // getuser getUserName()
    int getIndexofCurrentRoomBadGuy() const;

    // static variable to know badguy location
    //overloading the << operand to use with BadGuy class
    friend ostream &operator<<(ostream &Outputstream, const BadGuy &BadGuyusername);

};


#endif //ASSIGMENT4_BADGUY_H
