//
// Created by carlo on 9/25/2021.
//


#include <iomanip>
#include <vector>
#include <iostream>

using namespace std;

#include "Rooms.h"


// return the getUserName() of the room
string Room::getName() const {
    return this->Name;
};

//set the getUserName() of the room
void Room::setName(string nm) {
    this->Name = nm;
};

// set the description for a particular room
void Room::setRoomDescription(string desc) {
    this->RoomDescription = desc;
};

//return the room description
string Room::getDescription() const {
    return this->RoomDescription;
};

//set the index of the room to the north

void Room::setIndexRoomToNorth(int indx) { this->IndexOfRoomToNorth = indx; };

//get the index of the room to the north
int Room::getIndexRoomToNorth() const { return this->IndexOfRoomToNorth; };

//set the index of the room to the south
void Room::setIndexRoomToSouth(int indx) { this->IndexOfRoomToSouth = indx; };

//get the index of the room to the south
int Room::getIndexRoomToSouth() const { return this->IndexOfRoomToSouth; };

//set the index of the room to the east
void Room::setIndexRoomToEast(int indx) { this->IndexOfRoomToEast = indx; };

//get the index of the room to the east
int Room::getIndexRoomToEast() const { return this->IndexOfRoomToEast; };

//set the index of the room to the west
void Room::setIndexRoomToWest(int indx) { this->IndexOfRoomToWest = indx; };

//get the index of the room to the west
int Room::getIndexRoomToWest() const { return this->IndexOfRoomToWest; };

// overloaded >> operator for the room class to display room names and descriptions
ostream const &operator<<(ostream &Outputstream, const Room &room) {
    string roomName = room.Room::getName();
    string roomDesc = room.Room::getDescription();
    Outputstream << roomName << endl;
    Outputstream << roomDesc;
    return Outputstream;
}