#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include "museum.h"
#include "exhibit.h"

using namespace std;

class Admin {
private:
    string adminName;
    string password;

public:
    Admin(string name, string pwd);
    bool login(string name, string pwd);
};

#endif //ADMIN_H