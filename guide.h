#ifndef GUIDE_H
#define GUIDE_H

#include <string>
#include "json.hpp"
#include "exhibit.h" // Include exhibit.h for the Exhibit class definition

using namespace std;
using nlohmann::json;

class Guide {
private:
    string guideName;
    string language;

public:
    Guide();
    Guide(string name, string lang);
    string getGuideName() const; // Getter for guideName
    string getLanguage() const;  // Getter for language
    void startTour(const Exhibit& exhibit);  // Exhibit ka reference
    json toJson() const;
    static Guide fromJson(const json& j);
};

#endif //GUIDE_H