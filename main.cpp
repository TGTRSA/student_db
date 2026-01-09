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

int main() {
    sqlite3* myDB = openDatabase("test.db");

    if (myDB) {
        std::cout << "Database opened successfully!" << std::endl;
        sqlite3_close(myDB);  // always close it when done
    }
}
