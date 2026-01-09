#include <iostream>
#include <sqlite3.h>
#include <string>

enum DBFlag {STUDENT};
enum COMMAND {ADD, REMOVE, CHANGE};


struct Student {
    std::string name, surname, sex, dob;
};

sqlite3* openDatabase(const char* filename) {
    sqlite3* db = nullptr;  // declare pointer
    int rc = sqlite3_open(filename, &db); // open DB

    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;  // return nullptr on failure
    }

    return db; // return the sqlite3* pointer
}

void student_func(sqlite3* db, Student student, COMMAND flag) {
        int rc;
        sqlite3_stmt* stmt;
        char* zErrMsg = nullptr;
        auto callback = [](void*, int, char**, char**) -> int { return 0; };
        switch (flag){        
            case ADD:
                
                sqlite3_prepare_v2(db, "INSERT INTO Student(name, surname, sex, dob) VALUES (?, ?, ?, ?);", -1, &stmt, nullptr);
                sqlite3_bind_text(stmt, 1, student.name.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 2, student.surname.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 3, student.sex.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 4, student.dob.c_str(), -1, SQLITE_STATIC);
                if (sqlite3_step(stmt) != SQLITE_DONE) {
                    std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
                } else {
                    std::cout << "Student inserted successfully!" << std::endl;
                }

                sqlite3_finalize(stmt);


                
        }
}

Student create_student(const char* name, const char* surname, const char* sex, const char* dob) {
    Student student;
    student.name = name;
    student.surname = surname;
    student.sex = sex;
    student.dob = dob;
    
    
    return student;
    
}

int main() {
    sqlite3* myDB = openDatabase("test.db");
    int age =  22;
    if (myDB) {
        std::cout << "Database opened successfully!" << std::endl;
        
        Student student = create_student("Tash", "Not Tash", "M", "07-05-2003");
        student_func(myDB, student, ADD);
        sqlite3_close(myDB);  // always close it when done
    }
}
