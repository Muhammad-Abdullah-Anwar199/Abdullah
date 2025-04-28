#include "user.h"
#include "ticket.h"
#include "membership.h"
#include "review.h"

User::User(int initialSize) {

  reviewCapacity = initialSize;
  reviewCount = 0;
  reviews = new Review[reviewCapacity];
}
void User::setUserName(string name){
  userName=name;
}
string User:: getUserName(){
  return userName;
}

void User::addTicket(Ticket& ticket){
  tickets.push_back(ticket);
}

Ticket User::getTicket(int index){
  if(index>=0 && index<tickets.size()){
    return tickets[index];
  }
  cout<<"Invalid Index"<<endl;
  return Ticket();
}

int User:: countTickets(){
  return tickets.size();
}

void User::addMemberShip(Membership& a){
  mem.push_back(a);
}

int User::countMembership() {
  return mem.size();
}

Membership User::getMemberShip(int index){
  if(index>=0 && index<mem.size()){
    return mem[index];
  }
  cout<<"Invalid Index"<<endl;
  return Membership();
}

void User::addReviews(Review review) {
  if (reviewCount >= reviewCapacity) {
      int newCapacity = reviewCapacity * 2;
      Review* newReviews = new Review[newCapacity];
      for (int i = 0; i < reviewCount; i++) {
          newReviews[i] = reviews[i];
      }
      delete[] reviews;
      reviews = newReviews;
      reviewCapacity = newCapacity;
  }
  reviews[reviewCount] = review;
  reviewCount++;
}
int User::countReviews(){
  return reviewCount;
}
User::~User() {
  delete[] reviews;
  // delete[] reviews; ← when you implement dynamic array for reviews too
}

bool User::hasVipPass() {
  for (const auto& ticket : tickets) {
      if (ticket.hasVIPAccess()) {
          return true;
      }
  }
  return false;
}

// Copy Constructor
User::User(const User& other) {

  reviewCapacity = other.reviewCapacity;
  reviewCount = other.reviewCount;
  reviews = new Review[reviewCapacity];
  for (int i = 0; i < reviewCount; i++) {
      reviews[i] = other.reviews[i];
  }

}

// Assignment Operator
User& User::operator=(const User& other) {
  if (this != &other) {

      delete[] reviews;

      reviewCapacity = other.reviewCapacity;
      reviewCount = other.reviewCount;
      reviews = new Review[reviewCapacity];
      for (int i = 0; i < reviewCount; i++) {
          reviews[i] = other.reviews[i];
      }
  }
  return *this;
}

json User::toJson() const {
  json j;
  j["userName"] = userName;

  j["tickets"] = json::array();
  for (const auto& t : tickets)
      j["tickets"].push_back(t.toJson());  // assumes Ticket has toJson()

  j["memberships"] = json::array();
  for (const auto& m : mem)
      j["memberships"].push_back(m.toJson());  // assumes Membership has toJson()

  j["reviews"] = json::array();
  for (int i = 0; i < reviewCount; ++i)
      j["reviews"].push_back(reviews[i].toJson());  // assumes Review has toJson()

  return j;
}

// Load User object from JSON
void User::fromJson(const json& j) {
  userName = j.at("userName").get<string>();

  tickets.clear();
  for (const auto& t : j.at("tickets"))
      tickets.push_back(Ticket::fromJson(t)); // assumes static fromJson()

  mem.clear();
  for (const auto& m : j.at("memberships"))
      mem.push_back(Membership::fromJson(m)); // assumes static fromJson()

  reviewCount = j.at("reviews").size();
  reviewCapacity = reviewCount + 5;
  delete[] reviews;
  reviews = new Review[reviewCapacity];
  for (int i = 0; i < reviewCount; ++i)
      reviews[i] = Review::fromJson(j.at("reviews")[i]);
}

// Save to file
void User::saveToFile(const string& filename) {
  ofstream outFile(filename);
  if (outFile.is_open()) {
      json j = this->toJson();
      outFile << j.dump(4); // Pretty print with 4 spaces
      outFile.close();
  } else {
      cerr << "Failed to open file for writing: " << filename << endl;
  }
}

// Load from file
void User::loadFromFile(const string& filename) {
  ifstream inFile(filename);
  if (inFile.is_open()) {
      json j;
      inFile >> j;
      fromJson(j);
      inFile.close();
  } else {
      cerr << "Failed to open file for reading: " << filename << endl;
  }
}