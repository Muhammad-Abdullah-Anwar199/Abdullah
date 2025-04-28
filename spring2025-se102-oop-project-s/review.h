#ifndef REVIEW_H
#define REVIEW_H
#include <iostream>
#include "json.hpp"
using namespace std;
using nlohmann::json;
class Review{
  private:
  int reviewCapacity;
    string userName;
    string comment;
    float rating;
    public:
    Review();
    Review(int,string,string,float);
    string getComment();
    float getRating();
    json toJson() const;
    static Review fromJson(const json& j);
};
#endif //REVIEW_H
