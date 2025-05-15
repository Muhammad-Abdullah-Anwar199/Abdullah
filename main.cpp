#include "guide.h"
#include "museum.h"
#include "exhibit.h"
#include "ticket.h"
#include "user.h"
#include "review.h"
#include "membership.h"
#include "MuseumCollection.h"
#include "notification.h"
#include <iostream>
#include <string>
#include <map>
#include "json.hpp"

using namespace std;
using nlohmann::json;

// Placeholder for isTicketOfUser
bool isTicketOfUser(Ticket& ticket, int userId) {
    return ticket.getTicketId() == userId;
}

// User menu
void userMenu(User* currentUser, Museum* museum, MuseumCollection<Exhibit>& exhibitCollection) {
    while (true) {
        cout << "\n=== User Menu (" << currentUser->getUserName() << ") ===\n";
        cout << "1. View Exhibits\n";
        cout << "2. Purchase Tickets\n";
        cout << "3. Add Reviews\n";
        cout << "4. Add Membership\n";
        cout << "5. View My Tickets\n";
        cout << "6. View My Reviews\n";
        cout << "7. View My Memberships\n";
        cout << "8. Check Museum Schedule\n"; // New option
        cout << "9. Back to Main Menu\n";     // Adjusted numbering
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "\n--- Exhibit Collection ---\n";
                exhibitCollection.displayItems();
                break;
            case 2: {
                cout << "\n--- Exhibit Collection ---\n";
                exhibitCollection.displayItems();
                if (exhibitCollection.size() == 0) {
                    cout << "No exhibits available to purchase tickets for.\n";
                    break;
                }
                int exhibitIndex;
                cout << "Enter the index of the exhibit to purchase tickets for (0 to " << exhibitCollection.size() - 1 << "): ";
                cin >> exhibitIndex;
                cin.ignore();
                if (exhibitIndex >= 0 && exhibitIndex < static_cast<int>(exhibitCollection.size())) {
                    Exhibit selectedExhibit = exhibitCollection.items[exhibitIndex];
                    currentUser->purchaseTickets(selectedExhibit);
                } else {
                    cout << "Invalid exhibit index. Please try again." << endl;
                }
                break;
            }
            case 3:
                currentUser->addMultipleReviews();
                break;
            case 4:
                currentUser->addMemberships();
                break;
            case 5:
                currentUser->displayTickets();
                break;
            case 6:
                currentUser->displayReviews();
                break;
            case 7:
                currentUser->displayMemberships();
                break;
            case 8: { // Check Museum Schedule
                cout << "\n=== Check Museum Schedule ===\n";
                // Check if open today (May 15, 2025, is Thursday)
                string today = "Thursday";
                bool isOpen = museum->isOpenToday(today);
                cout << "Museum is " << (isOpen ? "OPEN" : "CLOSED") << " on " << today << " (today).\n";
                // Display full schedule
                Schedule schedule = museum->getSchedule();
                schedule.getOpenDays();
                schedule.getTimings();
                // Check specific day
                string day;
                cout << "Enter a day to check (e.g., Monday): ";
                getline(cin, day);
                isOpen = museum->isOpenToday(day);
                cout << "Museum is " << (isOpen ? "OPEN" : "CLOSED") << " on " << day << ".\n";
                break;
            }
            case 9: // Adjusted from 8 to 9
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

// Admin menu
void adminMenu(Museum* museum, MuseumCollection<Exhibit>& exhibitCollection, const map<string, User*>& userMap) {
    Exhibit dummyExhibit; // Placeholder for guide linking
    while (true) {
        cout << "\n=== Admin Menu ===\n";
        cout << "1. Add Exhibit\n";
        cout << "2. Add Guide\n";
        cout << "3. View All Users\n";
        cout << "4. View Exhibits\n";
        cout << "5. Send Notification to All Users\n";
        cout << "6. Set Museum Open Days\n"; // New option
        cout << "7. Set Museum Timings\n";     // New option
        cout << "8. Add Holiday\n";           // New option
        cout << "9. Back to Main Menu\n";     // Adjusted numbering
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                museum->addExhibitInteractively(exhibitCollection);
                break;
            case 2:
                museum->addGuideInteractively(dummyExhibit);
                break;
            case 3:
                cout << "\n=== All Users ===\n";
                for (const auto& pair : userMap) {
                    cout << "User: " << pair.first << ", Tickets: " << pair.second->countTickets()
                         << ", Reviews: " << pair.second->countReviews()
                         << ", Memberships: " << pair.second->countMembership() << endl;
                }
                break;
            case 4:
                cout << "\n--- Exhibit Collection ---\n";
                exhibitCollection.displayItems();
                break;
            case 5: {
                string message;
                cout << "Enter the notification message: ";
                getline(cin, message);
                Notification::notifyAllUsers(userMap, message);
                break;
            }
            case 6: { // Set Open Days
                cout << "\n=== Set Museum Open Days ===\n";
                bool days[7] = {false};
                string dayNames[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
                for (int i = 0; i < 7; i++) {
                    char open;
                    cout << "Is the museum open on " << dayNames[i] << "? (y/n): ";
                    cin >> open;
                    cin.ignore();
                    days[i] = (open == 'y' || open == 'Y');
                }
                Schedule schedule = museum->getSchedule();
                schedule.setOpenDays(days);
                museum->setSchedule(schedule);
                schedule.getOpenDays();
                break;
            }
            case 7: { // Set Timings
                cout << "\n=== Set Museum Timings ===\n";
                string openTime, closeTime;
                cout << "Enter opening time (e.g., 09:00 AM): ";
                getline(cin, openTime);
                cout << "Enter closing time (e.g., 05:00 PM): ";
                getline(cin, closeTime);
                Schedule schedule = museum->getSchedule();
                schedule.setTimings(openTime, closeTime);
                museum->setSchedule(schedule);
                schedule.getTimings();
                break;
            }
            case 8: { // Add Holiday
                cout << "\n=== Add Holiday ===\n";
                string holiday;
                cout << "Enter holiday date (e.g., 2025-12-25): ";
                getline(cin, holiday);
                Schedule schedule = museum->getSchedule();
                schedule.addHoliday(holiday);
                museum->setSchedule(schedule);
                cout << "Holiday added: " << holiday << endl;
                break;
            }
            case 9: // Adjusted from 6 to 9
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

int main() {
    cout << "Starting program..." << endl;

    // Initialize museum
    Museum* museum = Museum::getInstance();
    string museumFile = "museum.json";
    museum->loadData(museumFile);

    // Set a default schedule if none exists (e.g., after creating a new museum)
    Schedule defaultSchedule = museum->getSchedule();
    if (defaultSchedule.toJson().empty() || defaultSchedule.toJson()["openingTime"] == "") {
        // Default: Open Monday to Friday, 9:00 AM to 5:00 PM
        bool defaultDays[7] = {false, true, true, true, true, true, false}; // Sunday to Saturday
        defaultSchedule.setOpenDays(defaultDays);
        defaultSchedule.setTimings("09:00 AM", "05:00 PM");
        museum->setSchedule(defaultSchedule);
        cout << "Initialized default museum schedule.\n";
    }

    // Initialize users
    map<string, User*> userMap;
    User::loadUsers(userMap);

    MuseumCollection<Exhibit> exhibitCollection;

    // Main menu loop
    while (true) {
        cout << "\n=== Main Menu ===\n";
        cout << "1. User Login\n";
        cout << "2. Admin Mode\n";
        cout << "3. Save Data\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "\n=== User Login ===\n";
                string userName;
                cout << "Enter your name: ";
                getline(cin, userName);

                User* currentUser = nullptr;
                if (userMap.find(userName) != userMap.end()) {
                    currentUser = userMap[userName];
                    cout << "Welcome, " << userName << "!" << endl;
                    userMenu(currentUser, museum, exhibitCollection);
                } else {
                    cout << "User not found." << endl;
                }
                break;
            }
            case 2:
                adminMenu(museum, exhibitCollection, userMap);
                break;
            case 3:
                museum->saveData(museumFile);
                for (const auto& pair : userMap) {
                    pair.second->saveToFile(pair.first + ".json");
                }
                break;
            case 4:
                cout << "\n=== Cleaning Up ===\n";
                for (auto& pair : userMap) {
                    delete pair.second;
                }
                cout << "Program terminating normally!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}