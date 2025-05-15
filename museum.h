#ifndef MUSEUM_H
#define MUSEUM_H

#include "exhibit.h"
#include "guide.h"
#include "schedule.h"
#include "MuseumCollection.h"
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"

using namespace std;
using nlohmann::json;

class Museum {
private:
    static Museum* instance;
    string museumName;
    vector<Exhibit> exhibit;
    Schedule* schedule;
    vector<Guide> g;
    Museum();

public:
    static Museum* getInstance();
    void setMuseumName(string name);
    string getMuseumName();
    void setSchedule(Schedule& newSchedule);
    Schedule getSchedule();
    void addExhibit(Exhibit newExhibit);
    void addExhibitInteractively(MuseumCollection<Exhibit>& exhibitCollection);
    int countExhibit();
    Exhibit getExhibit(int index);
    bool isOpenToday(const string& today);
    void addGuide(Guide& guide);
    void addGuideInteractively(const Exhibit& exhibit);
    int countGuide();
    Guide getGuide(int index);
    json toJson() const;
    void fromJson(const json& j);
    static void loadData(const string& filename);
    void saveData(const string& filename);
    ~Museum();
};

#endif // MUSEUM_H