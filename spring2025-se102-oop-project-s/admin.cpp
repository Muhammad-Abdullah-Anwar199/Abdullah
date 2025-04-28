#include "admin.h"
Admin::Admin(string n,string p){
    adminName=n;
    password=p;
}
bool Admin::login(string n,string p){
    return password==p && adminName==n; // check for correct login for admin.
}