#include "guide.h"
#include "museum.h"
#include "exhibit.h"
#include "ticket.h"
#include "user.h"
#include "review.h"
#include "membership.h"
#include "MuseumCollection.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "json.hpp"

using namespace std;
using nlohmann::json;

// Placeholder for isTicketOfUser
bool isTicketOfUser(Ticket& ticket, int userId) {
    return ticket.getTicketId() == userId;
}

int main() {
    cout << "Starting program..." << endl;

    // Create a map to store users
    map<string, User*> userMap;

    // Load Museum instance
    Museum* museum = Museum::getInstance();
    string museumFile = "museum.json";
    ifstream museumInFile(museumFile);
    if (!museumInFile.is_open()) {
        cout << "No museum.json found. Creating new museum." << endl;
        museum->setMuseumName("National Museum");
    } else if (museumInFile.peek() == ifstream::traits_type::eof()) {
        cout << "museum.json is empty. Creating new museum." << endl;
        museum->setMuseumName("National Museum");
    } else {
        try {
            json j;
            museumInFile >> j;
            museum->fromJson(j);
            cout << "Loaded museum with " << museum->countExhibit() << " exhibits, " << museum->countGuide() << " guides." << endl;
        } catch (const json::exception& e) {
            cout << "Error reading museum.json: " << e.what() << ". Creating new museum." << endl;
            museum->setMuseumName("National Museum");
        }
    }
    museumInFile.close();

    // Ask if user wants to load existing users
    char loadChoice;
    cout << "Do you want to load existing user data? (y/n): ";
    cin >> loadChoice;
    cin.ignore();

    if (loadChoice == 'y' || loadChoice == 'Y') {
        string userName;
        bool loaded = false;
        while (!loaded) {
            cout << "Enter user name to load: ";
            getline(cin, userName);
            if (userName.empty()) {
                cout << "Username cannot be empty. Try again or type 'exit': ";
                getline(cin, userName);
                if (userName == "exit") {
                    loadChoice = 'n';
                    break;
                }
                continue;
            }

            User* loadedUser = new User(10);
            string userFile = userName + ".json";
            ifstream userInFile(userFile);
            if (!userInFile.is_open()) {
                cout << "No file found for " << userName << "." << endl;
                delete loadedUser;
            } else if (userInFile.peek() == ifstream::traits_type::eof()) {
                cout << userFile << " is empty." << endl;
                delete loadedUser;
            } else {
                try {
                    json j;
                    userInFile >> j;
                    loadedUser->fromJson(j);
                    if (loadedUser->getUserName().empty()) {
                        cout << "Setting username to " << userName << "." << endl;
                        loadedUser->setUserName(userName);
                    }
                    userMap[userName] = loadedUser;
                    cout << "Loaded user " << userName << ": " << loadedUser->countTickets() << " tickets, "
                         << loadedUser->countReviews() << " reviews, " << loadedUser->countMembership() << " memberships." << endl;
                    loaded = true;
                } catch (const json::exception& e) {
                    cout << "Error reading " << userFile << ": " << e.what() << endl;
                    delete loadedUser;
                }
            }
            userInFile.close();

            if (!loaded) {
                cout << "Try another username? (y/n): ";
                char retry;
                cin >> retry;
                cin.ignore();
                if (retry != 'y' && retry != 'Y') {
                    loadChoice = 'n';
                    break;
                }
            }
        }
    }

    if (loadChoice == 'n' || loadChoice == 'N') {
        int totalUsers;
        cout << "Enter the number of users: ";
        cin >> totalUsers;
        if (totalUsers <= 0) {
            cout << "Invalid number of users." << endl;
            return 1;
        }

        int initialSize;
        cout << "Enter the initial ticket array size: ";
        cin >> initialSize;
        if (initialSize <= 0) {
            cout << "Invalid ticket array size." << endl;
            return 1;
        }
        cin.ignore();

        for (int i = 0; i < totalUsers; i++) {
            string name;
            cout << "Enter the name of user " << i + 1 << ": ";
            getline(cin, name);
            if (name.empty()) {
                cout << "User name cannot be empty." << endl;
                return 1;
            }

            User* newUser = new User(initialSize);
            newUser->setUserName(name);
            userMap[name] = newUser;
        }
    }

    // Let the active user log in
    string userName;
    cout << "\nEnter your name to proceed: ";
    getline(cin, userName);

    User* currentUser = nullptr;
    if (userMap.find(userName) != userMap.end()) {
        currentUser = userMap[userName];
        cout << "Welcome, " << userName << "!" << endl;
    } else {
        cout << "User not found. Exiting." << endl;
        for (auto& pair : userMap) {
            delete pair.second;
        }
        return 1;
    }

    MuseumCollection<Exhibit> exhibitCollection;

    // Create and add exhibits
    string title, description;
    int popularity;
    float rating;
    Exhibit exhibit;

    cout << "Enter your Exhibit Title: ";
    getline(cin, title);
    cout << "Enter some Description about the Exhibit: ";
    getline(cin, description);
    cout << "Give popularity out of 100: ";
    cin >> popularity;
    cout << "Rate the Exhibit (0-5): ";
    cin >> rating;

    exhibit.setTitle(title);
    exhibit.setDescription(description);
    exhibit.setPopularity(popularity);
    exhibit.setRating(rating);
    exhibitCollection.addItem(exhibit);
    museum->addExhibit(exhibit);
    cout << "\n--- Exhibit Collection ---\n";
    exhibitCollection.displayItems();

    cout << "\nExhibit Details:\n";
    exhibit.display();
    cout << "Popularity Status: " << exhibit.getPopularityStatus() << endl;

    int numTickets;
    cout << "Enter the number of tickets you want to buy: ";
    cin >> numTickets;
    if (numTickets <= 0) {
        cout << "Invalid number of tickets." << endl;
        for (auto& pair : userMap) {
            delete pair.second;
        }
        return 1;
    }
    cin.ignore();

    Ticket* tickets = new Ticket[numTickets];
    for (int i = 0; i < numTickets; i++) {
        int ticketId;
        string expiryDate;
        int hasVipPassInt;
        bool hasVipPass;

        cout << "\nEnter details for Ticket #" << i + 1 << endl;
        cout << "Enter your Ticket ID: ";
        cin >> ticketId;
        cin.ignore();

        cout << "Enter your Ticket's Expiry Date: ";
        getline(cin, expiryDate);

        cout << "Do you have a VIP Pass? (1 for Yes, 0 for No): ";
        cin >> hasVipPassInt;
        while (hasVipPassInt != 0 && hasVipPassInt != 1) {
            cout << "Please enter 1 (Yes) or 0 (No): ";
            cin >> hasVipPassInt;
        }
        hasVipPass = (hasVipPassInt == 1);

        Ticket ticket(ticketId, expiryDate, hasVipPass);
        ticket.setExhibit(exhibit);
        tickets[i] = ticket;
        currentUser->addTicket(ticket);
    }

    cout << "Counting the Tickets how many added: " << currentUser->countTickets() << endl;

    cout << "\nDisplaying All Tickets:\n";
    for (int i = 0; i < numTickets; i++) {
        cout << "\nTicket #" << i + 1 << " Info:\n";
        cout << "Ticket ID: " << tickets[i].getTicketId() << endl;
        cout << "Expiry Date: " << tickets[i].getExpiryDate() << endl;
        cout << "VIP Access: " << (tickets[i].hasVIPAccess() ? "Yes" : "No") << endl;
        cout << "Linked Exhibit:\n";
        tickets[i].getExhibit().display();
    }

    Ticket ticket1(8, "17 April 2025", true);
    try {
        for (int i = 0; i < numTickets; i++) {
            if (tickets[i] != ticket1) {
                throw runtime_error("This Ticket is not Equal to Ticket!");
            } else {
                cout << "Ticket1 is equal to that Ticket" << endl;
            }
        }
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    Ticket t1(123, "18 April 2025", true);
    if (isTicketOfUser(t1, 123)) {
        cout << "Ticket belongs to user 123." << endl;
    } else {
        cout << "Ticket does not belong to user 123." << endl;
    }

    // Add reviews
    int numReviews;
    cout << "\nHow many reviews do you want to give? ";
    cin >> numReviews;
    if (numReviews < 0) {
        cout << "Invalid number of reviews." << endl;
        delete[] tickets;
        for (auto& pair : userMap) {
            delete pair.second;
        }
        return 1;
    }
    cin.ignore();

    Review* reviews = new Review[numReviews];
    for (int i = 0; i < numReviews; i++) {
        string reviewerName, comment;
        float rating1;

        cout << "\n--- Review #" << i + 1 << " ---\n";
        cout << "Enter your Name: ";
        getline(cin, reviewerName);
        cout << "Enter your Comment: ";
        getline(cin, comment);
        cout << "Give the Rating (0-5): ";
        cin >> rating1;
        cin.ignore();

        Review review(10, reviewerName, comment, rating1);
        reviews[i] = review;
        currentUser->addReviews(review);
        cout << "Review #" << i + 1 << " added successfully!" << endl;
    }

    cout << "Total Reviews added by user: " << currentUser->countReviews() << endl;
    delete[] reviews;

    // Add memberships
    int numMembership;
    cout << "How many memberships do you want to add? ";
    cin >> numMembership;
    if (numMembership < 0) {
        cout << "Invalid number of memberships." << endl;
        delete[] tickets;
        for (auto& pair : userMap) {
            delete pair.second;
        }
        return 1;
    }
    cin.ignore();

    Membership* memberships = new Membership[numMembership];
    for (int i = 0; i < numMembership; i++) {
        int memberShipId;
        cout << "\nEnter your MemberShip ID for Membership #" << i + 1 << ": ";
        cin >> memberShipId;
        cin.ignore();

        string type;
        cout << "Which Type of Membership? Vip or Local?: ";
        getline(cin, type);

        float discount;
        if (type == "vip") {
            discount = 30.0;
        } else if (type == "local") {
            discount = 10.0;
        } else {
            discount = 0.0;
            cout << "Unknown membership type, no discount applied.\n";
        }

        Membership membership(10, memberShipId, type, discount);
        memberships[i] = membership;
        currentUser->addMemberShip(membership);
        cout << "Getting discount --> " << membership.getDiscount() << "%" << endl;
        cout << "Membership #" << i + 1 << " added successfully!" << endl;
        cout << "Total Memberships added by user: " << currentUser->countMembership() << endl;
    }

    // Save user data
    cout << "Saving user data..." << endl;
    for (const auto& pair : userMap) {
        string userFile = pair.first + ".json";
        ofstream outFile(userFile);
        if (!outFile.is_open()) {
            cout << "Failed to open " << userFile << " for writing." << endl;
            continue;
        }
        try {
            json j = pair.second->toJson();
            outFile << j.dump(4);
            cout << "Saved user data to " << userFile << endl;
        } catch (const json::exception& e) {
            cout << "Error saving " << userFile << ": " << e.what() << endl;
        }
        outFile.close();
    }

    // Save museum data before cleanup
    cout << "Saving museum data..." << endl;
    ofstream museumOutFile(museumFile);
    if (!museumOutFile.is_open()) {
        cout << "Failed to open " << museumFile << " for writing." << endl;
    } else {
        try {
            json j = museum->toJson();
            cout << "Museum JSON: " << j.dump() << endl; // Debug
            museumOutFile << j.dump(4);
            cout << "Saved museum data to " << museumFile << endl;
        } catch (const json::exception& e) {
            cout << "Error saving museum.json: " << e.what() << endl;
        }
        museumOutFile.close();
    }

    // Add guide
    string guideName, language;
    cout << "Enter the name of the Guide: ";
    cin >> guideName;
    cout << "Enter the language you want to choose: ";
    cin >> language;
    Guide guide(guideName, language);
    guide.startTour(exhibit);
    museum->addGuide(guide);

    // Add derived exhibits
    string artist;
    cout << "Enter the name of the Artist: ";
    cin >> artist;
    ArtExhibit artExhibit;
    artExhibit.setArtist(artist);

    cin.ignore();
    cout << "Enter the title of the Art Exhibit: ";
    getline(cin, title);
    cout << "Enter the description of the Art Exhibit: ";
    getline(cin, description);
    cout << "Enter the popularity of the Art Exhibit: ";
    cin >> popularity;
    cout << "Rate the Art Exhibit (0-5): ";
    cin >> rating;

    artExhibit.setTitle(title);
    artExhibit.setDescription(description);
    artExhibit.setPopularity(popularity);
    artExhibit.setRating(rating);

    cout << "Showing the Name of the Artist: " << artExhibit.getArtist() << endl;
    artExhibit.display();
    museum->addExhibit(artExhibit);

    // History Exhibit
    HistoryExhibit historyExhibit;
    string era;
    cout << "\nEnter the Era of the History Exhibit: ";
    cin >> era;
    cin.ignore();
    cout << "Enter the title of the History Exhibit: ";
    getline(cin, title);
    cout << "Enter the description of the History Exhibit: ";
    getline(cin, description);
    cout << "Enter the popularity of the History Exhibit: ";
    cin >> popularity;
    cout << "Rate the History Exhibit (0-5): ";
    cin >> rating;

    historyExhibit.setEra(era);
    historyExhibit.setTitle(title);
    historyExhibit.setDescription(description);
    historyExhibit.setPopularity(popularity);
    historyExhibit.setRating(rating);

    cout << "Showing the Era of the Exhibit: " << historyExhibit.getEra() << endl;
    historyExhibit.display();
    museum->addExhibit(historyExhibit);

    // Tech Exhibit
    TechExhibit techExhibit;
    string technology;
    cout << "\nEnter the Technology showcased in the Tech Exhibit: ";
    cin >> technology;
    cin.ignore();
    cout << "Enter the title of the Tech Exhibit: ";
    getline(cin, title);
    cout << "Enter the description of the Tech Exhibit: ";
    getline(cin, description);
    cout << "Enter the popularity of the Tech Exhibit: ";
    cin >> popularity;
    cout << "Rate the Tech Exhibit (0-5): ";
    cin >> rating;

    techExhibit.setTechnology(technology);
    techExhibit.setTitle(title);
    techExhibit.setDescription(description);
    techExhibit.setPopularity(popularity);
    techExhibit.setRating(rating);

    cout << "Showing the Technology used: " << techExhibit.getTechnology() << endl;
    techExhibit.display();
    museum->addExhibit(techExhibit);

    // Save museum data again
    cout << "Saving museum data with new exhibits..." << endl;
    ofstream finalMuseumOutFile(museumFile);
    if (!finalMuseumOutFile.is_open()) {
        cout << "Failed to open " << museumFile << " for writing." << endl;
    } else {
        try {
            json j = museum->toJson();
            cout << "Final Museum JSON: " << j.dump() << endl; // Debug
            finalMuseumOutFile << j.dump(4);
            cout << "Saved museum data to " << museumFile << endl;
        } catch (const json::exception& e) {
            cout << "Error saving museum.json: " << e.what() << endl;
        }
        finalMuseumOutFile.close();
    }

    // Clean up
    cout << "Cleaning up resources..." << endl;
    delete[] memberships;
    delete[] tickets;
    for (auto& pair : userMap) {
        delete pair.second;
    }
    cout << "Program terminating normally." << endl;
    return 0;
}