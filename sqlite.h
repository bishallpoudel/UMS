#ifndef SQLITE_H
#define SQLITE_H
#pragma once


# include <iostream>
#include<string.h>
#include<sqlite3.h>
// #include<vector>
using namespace std;

class RData{
    public:
    char* id;
    char* name;
    char* email;
    char* address;
    char* phone;
    char* gender;
    char* file_path;
    char* tim;

    public:
    void append(char* i, char* n, char* e, char* a, char* p, char* g, char* f, char* t);
    void callbacks(int argc, char **argv, char **azColName);
    // void display(){
    //     // cout<<"from main"<<endl;
    //     cout<<"ID = "<<id<<endl;
    //     cout<<"Name = "<<name<<endl;
    //     cout<<"Email = "<<email<<endl;
    //     cout<<"Address = "<<address<<endl;
    //     cout<<"Phone = "<<phone<<endl;
    //     cout<<"Gender = "<<gender<<endl;
    //     cout<<endl;
    // }
};

static int user_count = 0;

class SQLite{
    // Pointer to SQLite connection
    sqlite3 *db;
    // Error message
    char *aErrMsg;
    // Result of the opening file
    int rOpening;
    // SQL command
    const char *sql;
    // Compile sqlite statement
    sqlite3_stmt *stmt;

    // Callback function, It contains result of sql statement
    static int callbackAll(void *fArg, int argc, char **argv, char **azColName);

    static int callback(void *fArg, int argc, char **argv, char **azColName);

    // Callback function for returning no of row
    static int numback(void *nrow, int argc, char **argv, char **azColName);

    // Callback function to return user presence in DB
    static int isPresent(void *status, int argc, char **argv, char **azColName);

    // Checking for error if any
    void checkDBError();

    public:

    // Open DB when creating an object
    SQLite();

    // Closing the connection
    void closeDB();

    // Creating DB table
    bool createTable();

    // Insert data into table
    bool insertData(const char* id, const char* name, const char* email, const char* address, const char* phone, const char* gender, const char* file_path, const char* tim);

    // Display all the data of table
    RData displayTable();

    // Display specific data
    RData displayRow(const char* name);

    // Remove the specific user
    bool removeRow(const char* name);

    // Update the specific user
    bool updateRow(const char* name,const char* new_name, const char* email, const char* address, const char* phone, const char* gender, const char* file_path);

    int returnNoOfRow();

    bool searchRow(const char* name);

    // void drdata(){
    //     for(int i=0; i<10; i++)
    //         rdatas[i].display();
    // }
};

#endif