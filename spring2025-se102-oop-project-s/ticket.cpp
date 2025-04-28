#include "ticket.h"
#include "exhibit.h"
Ticket::Ticket() {
    ticketId=0;
    expiryDate="";
    isVIP=false;
}

Ticket::Ticket(int i,string date,bool is){
    ticketId=i;
    expiryDate=date;
    isVIP=is;
}

void Ticket::setTicketId(int i){
    ticketId=i;
}

int Ticket::getTicketId(){
    return ticketId;
}

void Ticket::setExpiryDate(string i){
    expiryDate=i;
}

string Ticket::getExpiryDate(){
    return expiryDate;
}

void Ticket::setViPAccess(bool is){
    isVIP=is;
}

bool Ticket::hasVIPAccess()const{
    return isVIP;
}

void Ticket::setExhibit(Exhibit exhibit){
    this->exhibit=exhibit;
}

Exhibit Ticket::getExhibit()const{
    return exhibit;
}

// operator overloading
bool Ticket::operator==(Ticket& t)const{
    return ticketId==t.ticketId&& expiryDate==t.expiryDate&& isVIP==t.isVIP;
}

bool Ticket::operator!=(Ticket& t)const{
    return ticketId!=t.ticketId|| expiryDate!=t.expiryDate|| isVIP!=t.isVIP;
}

bool isTicketOfUser(const Ticket& ticket, const int & userId) {
    return ticket.ticketId == userId;
}

json Ticket::toJson() const {
    json j;
    j["ticketId"] = ticketId;
    j["expiryDate"] = expiryDate;
    j["isVIP"] = isVIP;
    j["exhibit"] = exhibit.toJson();  // Requires Exhibit::toJson()
    return j;
}

Ticket Ticket::fromJson(const json& j) {
    Ticket t;
    t.ticketId = j.at("ticketId").get<int>();
    t.expiryDate = j.at("expiryDate").get<string>();
    t.isVIP = j.at("isVIP").get<bool>();
    t.exhibit = Exhibit::fromJson(j.at("exhibit")); // Requires Exhibit::fromJson()
    return t;
}