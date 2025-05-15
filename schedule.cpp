#include "schedule.h"
#include <iostream>
using namespace std;

Schedule::Schedule() {
    for (int i = 0; i < 7; ++i) {
        openDays[i] = false;
    }
    openingTime = "";
    closingTime = "";
    holidayCount = 0;
    holidayCapacity = 10;
}
void Schedule::setTimings(string open, string close) {
    openingTime = open;
    closingTime = close;
}

void Schedule::getTimings() {
    cout << "Opening Time: " << openingTime << endl;
    cout << "Closing Time: " << closingTime << endl;
}

void Schedule::setOpenDays(bool days[7]) {
    for (int i = 0; i < 7; ++i) {
        openDays[i] = days[i];
    }
}
void Schedule::getOpenDays() {
    string dayNames[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    cout << "Open Days: ";
    for (int i = 0; i < 7; ++i) {
        if (openDays[i]) {
            cout << dayNames[i] << " ";
        }
    }
    cout << endl;
}

void Schedule::addHoliday(string holiday) {
    if (holidayCount < holidayCapacity) {
        holidays[holidayCount++] = holiday;
    } else {
        cout << "Holiday limit reached!" << endl;
    }
}
bool Schedule::isOpenOn(string date) {
    // Check if it's a holiday
    for (int i = 0; i < holidayCount; ++i) {
        if (holidays[i] == date) {
            return false;
        }
    }
    // Convert weekday name to index
    string dayNames[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    for (int i = 0; i < 7; ++i) {
        if (dayNames[i] == date) {
            return openDays[i];
        }
    }
    return false; // Invalid date
}

Schedule:: Schedule(const Schedule& other){
     // Copy values from the other Schedule object
     for (int i = 0; i < 7; i++) {
        this->openDays[i] = other.openDays[i];
 }
    this->openingTime = other.openingTime;
    this->closingTime = other.closingTime;
    for (int i = 0; i < 10; i++) {
        this->holidays[i] = other.holidays[i];
}
    this->holidayCount = other.holidayCount;
    this->holidayCapacity = other.holidayCapacity;
}

json Schedule::toJson() const {
    json j;
    j["openingTime"] = openingTime;
    j["closingTime"] = closingTime;

    vector<bool> days(openDays, openDays + 7);
    j["openDays"] = days;

    vector<string> holidayList(holidays, holidays + holidayCount);
    j["holidays"] = holidayList;

    return j;
}
void Schedule::fromJson(const json& j) {
    openingTime = j.at("openingTime").get<string>();
    closingTime = j.at("closingTime").get<string>();

    auto days = j.at("openDays").get<vector<bool>>();
    for (int i = 0; i < 7; ++i) openDays[i] = days[i];

    auto holidayList = j.at("holidays").get<vector<string>>();
    holidayCount = holidayList.size();
    for (int i = 0; i < holidayCount && i < 10; ++i) {
        holidays[i] = holidayList[i];
    }
}