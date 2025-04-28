#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include "ticket.h"
#include "membership.h"
#include "review.h"
#include <fstream>
#include "json.hpp"
using namespace std;
using nlohmann::json;
class Ticket; //forward decelerarion
class Membership;
class Review; 
class User {
private:
    string userName;
    vector<Ticket>tickets;
    vector<Membership>mem;
    Review* reviews;         // Changed to dynamic array for consistency
    int reviewCount;
    int reviewCapacity;      // Added for dynamic array
public:
    User(int initialSize = 5);
    User(const User& other);                // Copy constructor
    User& operator=(const User& other);
    void setUserName(string);
    string getUserName();
    void addTicket(Ticket&);
    Ticket getTicket(int index);
    int countTickets();
    void addMemberShip(Membership&); // Suggest renaming to addMembership
    int countMembership();
    Membership getMemberShip(int index);
    void addReviews(Review);
    int countReviews();
    bool hasVipPass();
    User increaseSizeofArray(int);
    ~User();                // Destructor to free dynamic memory
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
    json toJson() const;
    void fromJson(const json& j);

};
#endif //USER_H