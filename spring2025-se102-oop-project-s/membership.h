#ifndef MEMBERSHIP_H
#define MEMBERSHIP_H

#include <iostream>
#include <string>
#include "json.hpp"
using namespace std;
using nlohmann::json;
class Membership {
private:
    int memberShipId;
    string type;
    float discount;

public:
    // Constructors
    Membership();
    Membership(int membershipCapacity,int memberShipId, string type, float discount);

    // Setters
    void setMemberShipId(int id);
    void setType(string t);
    void setDiscount(float d);

    // Getters
    int getMemberShipId() const;
    string getType() const;
    float getDiscount() const;
    json toJson() const;
    static Membership fromJson(const json& j);

};

#endif // MEMBERSHIP_H
