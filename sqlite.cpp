# include "sqlite.h"

void RData::append(char* i, char* n, char* e, char* a, char* p, char* g, char* f, char* t){
        // cout<<"ID = "<<i<<endl;
        // cout<<"Name = "<<n<<endl;
        // cout<<"Email = "<<e<<endl;
        // cout<<"Address = "<<a<<endl;
        // cout<<"Phone = "<<p<<endl;
        // cout<<"Gender = "<<g<<endl;
        // cout<<endl;
        id = new char[strlen(i)+1];
        strcpy(id, i);

        name = new char[strlen(n)+1];
        strcpy(name, n);

        email = new char[strlen(e)+1];
        strcpy(email, e);

        address = new char[strlen(a)+1];
        strcpy(address, a);

        phone = new char[strlen(p)+1];
        strcpy(phone, p);

        gender = new char[strlen(g)+1];
        strcpy(gender, g);

        file_path = new char[strlen(f)+1];
        strcpy(file_path, f);

        tim = new char[strlen(t)+1];
        strcpy(tim, t);
    }

    void RData::callbacks(int argc, char **argv, char **azColName){

        // Assigning returinng data into object variable
        id = new char[strlen(argv[0]) + 1];
        strcpy(id, argv[0]);

        name = new char[strlen(argv[1]) + 1];
        strcpy(name, argv[1]);

        email = new char[strlen(argv[2]) + 1];
        strcpy(email, argv[2]);

        address = new char[strlen(argv[3]) + 1];
        strcpy(address, argv[3]);

        phone = new char[strlen(argv[4]) + 1];
        strcpy(phone, argv[4]);

        gender = new char[strlen(argv[5]) + 1];
        strcpy(gender, argv[5]);

        file_path = new char[strlen(argv[6])+1];
        strcpy(file_path, argv[6]);

        tim = new char[strlen(argv[7])+1];
        strcpy(tim, argv[7]);

    }
// RData *rdatas;


// Return either name is in DB or not
bool SQLite::searchRow(const char* name){
    // SQL command
    char * query = NULL;

    asprintf(&query, "SELECT * FROM USERS WHERE NAME='%s';", name);
    // cout<<"query = "<<query<<endl;

    bool status = false;
    
    // Run sql
    rOpening = sqlite3_exec(db, query, isPresent, &status, &aErrMsg);
    // cout<<"rOpening = "<<rOpening<<endl;

    return status;
}

// Callback function to return user presence in DB
int SQLite::isPresent(void *status, int argc, char **argv, char **azColName){
    bool *found = (bool*)status;
    if(argc != 0)
        *found = true;
    return 0;
}

// Return total no of row present
int SQLite::numback(void *nrow, int argc, char **argv, char **azColName){
    int *num = (int*)nrow;
    *num = atoi(argv[0]);
    // cout<<*num<<endl;
    return 0;
}

// To return the number of row of table
int SQLite::returnNoOfRow(){
    // SQL for display all
    sql = "SELECT COUNT(*) FROM USERS;" ;
    // cout<<"sql = "<<sql<<endl;

    int nrow=0;

    // Run sql
    rOpening = sqlite3_exec(db, sql, numback, &nrow, &aErrMsg);
    // cout<<"rOpening = "<<rOpening<<endl;
    // cout<<nrow<<endl;

    return nrow;
}

// Update a row by its name
bool SQLite::updateRow(const char* id, const char* name, const char* email, const char* address, const char* phone, const char* gender, const char* file_path){
    // SQL command
    char * query = NULL;
    bool success=true;

    asprintf(&query, "UPDATE USERS SET NAME='%s', EMAIL='%s', ADDRESS='%s', PHONE='%s', GENDER='%s', IMAGE='%s' WHERE ID='%s';", name, email, address, phone, gender, file_path, id);

    // cout<<"Query = "<<query<<endl;

    // Prepere the query
    sqlite3_prepare(db, query, strlen(query), &stmt, NULL);
    // cout<<"SQL statement = "<<stmt<<endl;

    // Testing the statement
    rOpening = sqlite3_step(stmt);
    // cout<<"After testing rOpening = "<<rOpening<<endl;
    if(rOpening != 101){
        success=false;
    }

    // Final the statement
    sqlite3_finalize(stmt);

    // Free the space of query
    free(query);
    // cout<<"Query after free: "<<query<<endl;
    return success;
}

// Remove a row by name
bool SQLite::removeRow(const char* name){
    // SQL command
    char * query = NULL;
    bool success = true;

    asprintf(&query, "DELETE FROM USERS WHERE NAME='%s';", name);
    // cout<<"query = "<<query<<endl;

    // Run sql
    rOpening = sqlite3_exec(db, query, callback, 0, &aErrMsg);
    // cout<<"rOpening = "<<rOpening<<endl;
    if(rOpening != 0){
        success = false;
    }
    return success;
}

// Display a row by name
RData SQLite::displayRow(const char* name){
    // SQL command
    char * query = NULL;

    asprintf(&query, "SELECT * FROM USERS WHERE NAME='%s';", name);
    // cout<<"query = "<<query<<endl;

    RData rdata;
    
    // Run sql
    rOpening = sqlite3_exec(db, query, callback, &rdata, &aErrMsg);
    // cout<<"rOpening = "<<rOpening<<endl;

    return rdata;
}

// To display all the data of table
RData SQLite::displayTable(){
    // SQL for display all
    sql = "SELECT * FROM USERS;" ;
    // cout<<"sql = "<<sql<<endl;

    RData rdata;
    // rdata = (RData*) malloc(9*sizeof(RData));

    // Run sql
    rOpening = sqlite3_exec(db, sql, callbackAll, &rdata, &aErrMsg);
    // cout<<"rOpening = "<<rOpening<<endl;

    // drdata();

    return rdata;
}

// Insert al the data into table
bool SQLite::insertData(const char* id, const char* name, const char* email, const char* address, const char* phone, const char* gender, const char* file_path, const char* tim){
    // SQL query
    char * query = NULL;
    bool success=true;

    // Making single string of command and asign into query
    asprintf(&query, "INSERT INTO USERS(ID, NAME, EMAIL, ADDRESS, PHONE, GENDER, IMAGE, TIME) VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');", id, name, email, address, phone, gender, file_path, tim);
    // cout<<"query = "<<query<<endl;

    // Prepere the query
    sqlite3_prepare(db, query, strlen(query), &stmt, NULL);
    // cout<<"SQL statement = "<<stmt<<endl;

    // Testing the statement
    rOpening = sqlite3_step(stmt);
    // cout<<"After testing rOpening = "<<rOpening<<endl;

    if(rOpening != 101){
        success=false;
    }

    // Final the statement
    sqlite3_finalize(stmt);

    // Free the space of query
    free(query);
    // cout<<"Query after free: "<<query<<endl;
    return success;
}

// Creating DB table
bool SQLite::createTable(){
    // SQL command to create table
    sql = "CREATE TABLE IF NOT EXISTS USERS("
            "ID INT PRIMARY KEY NOT NULL UNIQUE, "
            "NAME TEXT NOT NULL, "
            "EMAIL TEXT NOT NULL UNIQUE, "
            "ADDRESS TEXT NOT NULL, "
            "PHONE CHAR(15) NOT NULL UNIQUE, "
            "GENDER CHAR(7) NOT NULL, "
            "IMAGE TEXT NOT NULL, "
            "TIME CHAR(20) NOT NULL);";
    // cout<<"SQL = "<<sql<<endl;
    // Run the sql
    rOpening = sqlite3_exec(db, sql, callback, 0, &aErrMsg);
    // cout<<"After running command rOpening = "<<rOpening<<endl;
    bool success=true;
    if(rOpening != 0){
        success=false;
    }
    return success;
}

// Open connection
SQLite::SQLite(){
    // Store the result of opening file
    rOpening = sqlite3_open("User.db", &db);
    // cout<<"rOpening = "<<rOpening<<endl;
    // Check errors
    // cout<<"DB opened succesfully"<<endl;
    checkDBError();
}

// Closing the connection
void SQLite::closeDB(){
        sqlite3_close(db);
        // cout<<"DB closed succesfully"<<endl;
    }

// Callback function, It contains result of sql statement
int SQLite::callback(void *fArg, int argc, char **argv, char **azColName){
    // void *fArg: It is the fourth argument pass in sqlite3_exec() command
    // int argc: It holds the number of results ie. number of rows(may be in some case)
    // char **argv (array of array of charactor): Holds each values of each column
    // char **azColName (array of pointer to pointer of charactor array): Holds each column returned

    // Now to display the returned contents, It goes row by row
    // cout<<"--- User ---"<<endl;
    // for(int i=0; i<argc; i++){
    //     cout<<azColName[i]<< "--> "<<argv[i]<<endl;
    // }
    //  // Inserting new line after completion of first row
    // cout<<endl;

    RData *rd = (RData *) fArg;
    rd->callbacks(argc, argv, azColName);

    // Returning success
    return 0;
}
int SQLite::callbackAll(void *fArg, int argc, char **argv, char **azColName){
    // void *fArg: It is the fourth argument pass in sqlite3_exec() command
    // int argc: It holds the number of results ie. number of rows(may be in some case)
    // char **argv (array of array of charactor): Holds each values of each column
    // char **azColName (array of pointer to pointer of charactor array): Holds each column returned

    // Now to display the returned contents, It goes row by row

    RData *rd = (RData *) fArg;
    
    // Assigning returinng data into object variable
        char* id = new char[strlen(argv[0]) + 1];
        strcpy(id, argv[0]);

        char* name = new char[strlen(argv[1]) + 1];
        strcpy(name, argv[1]);

        char* email = new char[strlen(argv[2]) + 1];
        strcpy(email, argv[2]);

        char* address = new char[strlen(argv[3]) + 1];
        strcpy(address, argv[3]);

        char* phone = new char[strlen(argv[4]) + 1];
        strcpy(phone, argv[4]);

        char* gender = new char[strlen(argv[5]) + 1];
        strcpy(gender, argv[5]);

        char* file_path = new char[strlen(argv[6])+1];
        strcpy(file_path, argv[6]);

        char* tim = new char[strlen(argv[7])+1];
        strcpy(tim, argv[7]);

        // rdatas[user_count].append(id, name, email, address, phone, gender, file_path, tim);
        rd->append(id, name, email, address, phone, gender, file_path, tim);

        delete [] id;
        delete [] name;
        delete [] email;
        delete [] address;
        delete [] phone;
        delete [] gender;
        delete [] file_path;
        delete [] tim;

    ++user_count;
    // cout<<count<<endl;

    // Returning success
    return 0;
}

void SQLite::checkDBError(){
    if(rOpening){
        // Generally rOpening is zero if not error, If error found display error
        cout<<"DB Error: "<<sqlite3_errmsg(db)<<endl;
        // closing the database
        closeDB();
    }
}