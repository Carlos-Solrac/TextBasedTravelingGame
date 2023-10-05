//
// This is the header file for SuperUser.h. This is the interface for the class "SuperUser".
//values of this type are names and room numbers.
//

#ifndef ASSIGMENT4_SUPERUSER_H
#define ASSIGMENT4_SUPERUSER_H
#include <iostream>
#include "Users.h"
#include<cstdlib>
#include <ctime>
using namespace  std;


class SuperUser : public Users
{
public:
    // default constructor
    SuperUser(string &nm, int &indx);
    SuperUser();
    SuperUser(int &indx);
    void  setTeleportLocation();
private:


};


#endif //ASSIGMENT4_SUPERUSER_H

