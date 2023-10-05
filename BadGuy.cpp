//
// Created by carlo on 9/30/2021.
//

#include "BadGuy.h"

//initialize static variable for badguy location index

//default constructors

BadGuy::BadGuy(string &nm, int &indx,int &indx2) {
    BadGuyName = nm;
    BadGuyIndex = indx;
    BadGuyLifePoints = 10;
};

BadGuy::BadGuy() {
    BadGuyName = "Gregorny";
    BadGuyIndex = 2;
    BadGuyLifePoints = 10;
};

BadGuy::BadGuy(int &indx) {
    BadGuyName = " ";
    BadGuyIndex = indx;
    BadGuyLifePoints = 10;
};

// set getUserName() of user
void BadGuy::setBadGuyUserName(string &BadGuyusername) {
    this->BadGuyName = BadGuyusername;
};

// get user name through constant function
string BadGuy::getBadGuyUserName() const {
    return this->BadGuyName;
};
//get badguy lifepoints
int BadGuy::getBadGuyLifePoints() const
{
    return this -> BadGuyLifePoints;
}
//set bad guy health
void BadGuy:: setBadGuyLifePoints(int attack) {
    this -> BadGuyLifePoints = BadGuyLifePoints -attack;
}
// set index of user by reference
void BadGuy::setIndexofCurrentRoomBadGuy(int &indx) {
    this->BadGuyIndex = indx;
};

// get index of current room constant function
int BadGuy::getIndexofCurrentRoomBadGuy() const {
    return this->BadGuyIndex;
}

// overloading the << operator
ostream &operator<<(ostream &Outputstream, const BadGuy &BadGuyusername) {
    Outputstream << BadGuyusername.getBadGuyUserName();
    return Outputstream;
}
