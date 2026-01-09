#include <iostream>
#include <sqlite3.h>


sqlite3* openDatabase(const char* filename) {
    sqlite3* db = nullptr;  // declare pointer
    int rc = sqlite3_open(filename, &db); // open DB

    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;  // return nullptr on failure
    }

    return db; // return the sqlite3* pointer
}

void create_student(const char* name, const char* surname, const char* sex, const char* dob) {
    std::string sql_command = std::string("INSERT INTO Student VALUES ('") 
                        + name + "', '" 
                        + surname + "', '" 
                        + sex + "', '" 
                        + dob + "');";

    std::cout << sql_command;
}

int main() {
    sqlite3* myDB = openDatabase("test.db");
    int age =  22;
    if (myDB) {
        std::cout << "Database opened successfully!" << std::endl;
        
        create_student("Tash", "Not Tash", "M", "07-05-2003");

        sqlite3_close(myDB);  // always close it when done
    }
}
