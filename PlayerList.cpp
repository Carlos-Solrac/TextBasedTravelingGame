//
// Created by carlo on 10/21/2021.
//
#include <vector>
#include<iostream>
#include <algorithm>
using namespace std;
#include "PlayerList.h"

//constructor for the list
template <class P>
PlayerList<P>::PlayerList( )
{

}

//Add player to the list
template <class P>
void PlayerList<P>::addToList(P *player)
{
    //add player if they are not on the list
    if(find(playersList.begin(),playersList.end(),player)==playersList.end())
    {
        //player not on list, so we will add it to the vector.
        playersList.push_back(player);
    }
}
//Display players in list
template <class P> bool PlayerList<P>::verifyList (P* player)
{
    if(find(playersList.begin(),playersList.end(),player)!=playersList.end())
    {
        return true;
    }
    else
        return false;
}



