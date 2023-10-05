//
// Created by carlo on 10/8/2021.
//

#include "SuperUser.h"
#include <iostream>
#include<cstdlib>
#include <ctime>
using namespace std;

// default constructors
SuperUser:: SuperUser(string &nm, int &indx): Users(nm,indx)
{
setUserType(SUPERUSER);

}
SuperUser::SuperUser(): Users()
{
    setUserType(SUPERUSER);
}
SuperUser::SuperUser(int &indx) : Users(indx)
{
    setUserType(SUPERUSER);
}
void SuperUser:: setTeleportLocation()
{
    int indx = (rand() %  4) + 1 ;
     setIndexofCurrentRoom(indx);
};

