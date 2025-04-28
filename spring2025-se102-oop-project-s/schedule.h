#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include "json.hpp"
using namespace std;
using nlohmann::json;

#include <string>
using namespace std;

class Schedule {
private:
    bool openDays[7];
    string openingTime;
    string closingTime;
    string holidays[10];        // Fixed-size holiday array
    int holidayCount;
    int holidayCapacity;

public:
    Schedule();
    void setTimings(string open, string close);
    void getTimings();
    Schedule(const Schedule& other);
    void setOpenDays(bool days[7]);
    void getOpenDays();
    void addHoliday(string holiday);
    bool isOpenOn(string date);  // Assume format "Monday", "Sunday" etc.
    json toJson() const;
    void fromJson(const json& j);
};

#endif //SCHEDULE_H
