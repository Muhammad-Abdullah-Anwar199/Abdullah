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

class Ticket;
class Membership;
class Review;

class User {
private:
    string userName;
    vector<Ticket> tickets;
    vector<Membership> mem;
    Review* reviews;
    int reviewCount;
    int reviewCapacity;

public:
    User(int initialSize = 5);
    User(const User& other);
    User& operator=(const User& other);
    void setUserName(string);
    string getUserName()const;
    void addTicket(Ticket&);
    void purchaseTickets(const Exhibit& exhibit);
    Ticket getTicket(int index);
    int countTickets();
    void displayTickets() const;
    void addMembership(Membership&);
    void addMemberships();
    int countMembership();
    Membership getMembership(int index);
    void displayMemberships() const;
    void addReviews(Review);
    void addMultipleReviews();
    int countReviews();
    void displayReviews() const;
    bool hasVipPass();
    User increaseSizeofArray(int);
    ~User();
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
    json toJson() const;
    void fromJson(const json& j);
    static void loadUsers(map<string, User*>& userMap);
};

#endif //USER_H