#include "membership.h"

// Default Constructor
Membership::Membership() {
    memberShipId = 0;
    type = "";
    discount = 0.0;
}

// Parameterized Constructor
Membership::Membership(int membershipCapacity,int memberShipId, string type, float discount) {
    this->memberShipId = memberShipId;
    this->type = type;
    this->discount = discount;
}

// Setters
void Membership::setMemberShipId(int id) {
    memberShipId = id;
}

void Membership::setType(string t) {
    type = t;
}

void Membership::setDiscount(float d) {
    discount = d;
}

// Getters
int Membership::getMemberShipId() const {
    return memberShipId;
}

string Membership::getType() const {
    return type;
}

float Membership::getDiscount() const {
    return discount;
}

json Membership::toJson() const {
    json j;
    j["memberShipId"] = memberShipId;
    j["type"] = type;
    j["discount"] = discount;
    return j;
}

Membership Membership::fromJson(const json& j) {
    Membership m;
    m.memberShipId = j.at("memberShipId").get<int>();
    m.type = j.at("type").get<string>();
    m.discount = j.at("discount").get<float>();
    return m;
}