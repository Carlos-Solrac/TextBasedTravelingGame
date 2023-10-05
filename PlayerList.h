/*
// This is the header file for PlayerList.h.This is the interface for the template class P of PlayerList.
 this template is meant to work with player vector pointers.
*/

#ifndef TEXTBASEDGAMEPART7_CPP_PLAYERPOINTERLIST_H
#define TEXTBASEDGAMEPART7_CPP_PLAYERPOINTERLIST_H
#include <vector>
using namespace std;

template <class P>
class PlayerList
{
public:
    //constructor for the list
    PlayerList();
    //destructor
    ~PlayerList() = default;
    //Add player to the list
    void addToList (P* player);
    //Verify players in list
    bool verifyList (P* player);
private:
    vector <P *> playersList;
};

#endif /*TEXTBASEDGAMEPART7_CPP_PLAYERPOINTERLIST_H*/

