#include "notification.h"
void Notification::sendAlert(User & user, string message){
    cout<<"This Notification is for "<<user.getUserName()<<": "<<message<<endl;
    if(user.hasVipPass()){
        cout << "This is an exclusive notification for VIP users!" << endl;
    }
}