#include "notification.h"

void Notification::sendAlert(User& user, const string& message) {
    cout << "This Notification is for " << user.getUserName() << ": " << message << endl;
    if (user.hasVipPass()) {
        cout << "This is an exclusive notification for VIP users!" << endl;
    }
}

void Notification::notifyAllUsers(const map<string, User*>& userMap, const string& message) {
    cout << "\n=== Sending Notification to All Users ===\n";
    for (const auto& pair : userMap) {
        sendAlert(*pair.second, message);
    }
}