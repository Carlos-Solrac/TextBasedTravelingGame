/*
// This is the header file for rooms.h. This is the interface for the class "rooms".
 Values of this type are rooms numbers. The rooms are in an array of size 4 with names and descriptions
 initialized.
*/

#ifndef ASSIGMENT4_ROOMS_H
#define ASSIGMENT4_ROOMS_H

#include <iostream>

using namespace std;

//room class
class Room {
private:
    string Name;
    string RoomDescription;
    int IndexOfRoomToNorth{};
    int IndexOfRoomToSouth{};
    int IndexOfRoomToEast{};
    int IndexOfRoomToWest{};

public:
    // return the getUserName() of the room
    string getName() const;

    //set the getUserName() of the room
    void setName(string nm);

    // set the description for a particular room
    void setRoomDescription(string desc);

    //return the room description
    string getDescription() const;

    //set the index of the room to the north

    void setIndexRoomToNorth(int indx);

    //get the index of the room to the north
    int getIndexRoomToNorth() const;

    //set the index of the room to the south
    void setIndexRoomToSouth(int indx);

    //get the index of the room to the south
    int getIndexRoomToSouth() const;

    //set the index of the room to the east
    void setIndexRoomToEast(int indx);

    //get the index of the room to the east
    int getIndexRoomToEast() const;

    //set the index of the room to the west
    void setIndexRoomToWest(int indx);

    //get the index of the room to the west
    int getIndexRoomToWest() const;

    // overlaoding the << operator
    friend const ostream &operator<<(ostream &Outputstream, const Room &room);
};

#endif //ASSIGMENT4_ROOMS_H
