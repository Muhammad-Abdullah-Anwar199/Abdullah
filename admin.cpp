#include "admin.h"

Admin::Admin(string name, string pwd) : adminName(name), password(pwd) {}

bool Admin::login(string name, string pwd) {
    return name == adminName && pwd == password;
}