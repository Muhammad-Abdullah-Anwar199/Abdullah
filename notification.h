#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <iostream>
#include "user.h"
#include <map> // Needed for map<string, User*>
using namespace std;

class Notification {
public:
    static void sendAlert(User& user, const string& message);
    static void notifyAllUsers(const map<string, User*>& userMap, const string& message);
};

#endif //NOTIFICATION_H