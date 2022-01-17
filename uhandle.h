#ifndef UHANDLE_H
#define UHANDLE_H
#pragma once
#include "sqlite.h"
#include<time.h> 
// #define BISHAL 5

class User{
    // User Informations
    string id;
    string name;
    string email;
    string address;
    string phone;
    string gender;
    string file_path;
    string tim;

    public:
    // Set default constructor
    User(){}

    // Make a constructor to accept parameters
    User(string name, string email, string address, string phone, string gender, string file_path);

    bool addUser();

    RData displayAllUser();

    RData displayUser(string name);

    bool removeUser(string name);

    bool updateUser(string id);

    int rowNumber();

    bool isPresent(string name);

};
#endif