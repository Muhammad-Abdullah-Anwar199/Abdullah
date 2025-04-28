#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <iostream>
#include "user.h"
using namespace std;
class Notification:public User{
  public:
    static void sendAlert(User&,string);
};
#endif //NOTIFICATION_H
