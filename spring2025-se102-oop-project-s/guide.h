#ifndef GUIDE_H
#define GUIDE_H

#include <string>
#include "json.hpp"
using namespace std;
using nlohmann::json;
class Exhibit;  // Forward declaration

class Guide {
private:
    string guideName;
    string language;
public:
    Guide();
    Guide(string name, string lang);
    void startTour(Exhibit& exhibit);  // Exhibit ka reference
    json toJson() const;
    static Guide fromJson(const json& j);
};

#endif //GUIDE_H
