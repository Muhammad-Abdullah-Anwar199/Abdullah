#include "review.h"
Review::Review(){
    userName="";
    comment="";
    rating=0.0;
    reviewCapacity=0;
}
Review::Review(int k,string n,string m,float a){
    userName=n;
    comment=m;
    rating=a;
}
string Review::getComment(){
    return comment;
}
float Review::getRating(){
    return rating;
}

string Review::getReviewerName()const{
    return userName;
}

json Review::toJson() const {
    json j;
    j["userName"] = userName;
    j["comment"] = comment;
    j["rating"] = rating;
    j["reviewCapacity"] = reviewCapacity; // Always positive
    return j;
}

Review Review::fromJson(const json& j) {
    std::string userName = j.at("userName").get<std::string>();
    std::string comment = j.at("comment").get<std::string>();
    float rating = j.at("rating").get<float>();
    int capacity = j.contains("reviewCapacity") ? j.at("reviewCapacity").get<int>() : 10;
    if (capacity <= 0) {
        capacity = 10; // Ensure valid capacity
    }
    return Review(capacity, userName, comment, rating);
}