#ifndef TICKET_H
#define TICKET_H
#include "exhibit.h"
#include <iostream>
#include "json.hpp"
using namespace std;
using nlohmann::json;
class Ticket {
private:
    int ticketId;
    string expiryDate;
    bool isVIP;
    Exhibit exhibit; //Composition
public:
    Ticket();
    Ticket(int,string,bool);
    void setTicketId(int);
    int getTicketId();
    void setExpiryDate(string);
    string getExpiryDate();
    void setViPAccess(bool);
    bool hasVIPAccess()const;
    void setExhibit(const Exhibit exhibit);
    Exhibit getExhibit()const;
    bool operator==(Ticket&)const;
    bool operator!=(Ticket&)const;
    friend bool isTicketOfUser(const Ticket& ticket, const int & userID);
    json toJson() const;
    static Ticket fromJson(const json& j);

};
#endif //TICKET_H
