#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
using namespace std;
class Admin{
    private:
    string adminName;
    string password;
    public:
    Admin(string,string);
    bool login(string,string);
};
#endif //ADMIN_H
