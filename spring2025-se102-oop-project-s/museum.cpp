#include "museum.h"
#include <iostream>

using namespace std;
using nlohmann::json;

Museum* Museum::instance = nullptr;

Museum::Museum() : museumName(""), schedule(nullptr) {}

Museum* Museum::getInstance() {
    if (instance == nullptr) {
        instance = new Museum();
    }
    return instance;
}

void Museum::setMuseumName(string name) {
    museumName = name;
}

string Museum::getMuseumName() {
    return museumName;
}

void Museum::setSchedule(Schedule& newSchedule) {
    if (schedule) {
        delete schedule;
    }
    schedule = new Schedule(newSchedule);
}

Schedule Museum::getSchedule() {
    return schedule ? *schedule : Schedule();
}

void Museum::addExhibit(Exhibit newExhibit) {
    exhibit.push_back(newExhibit);
}

int Museum::countExhibit() {
    return exhibit.size();
}

Exhibit Museum::getExhibit(int index) {
    if (index < 0 || index >= exhibit.size()) {
        cout << "Invalid Index" << endl;
        return Exhibit();
    }
    return exhibit[index];
}

bool Museum::isOpenToday(const string& today) {
    return schedule ? schedule->isOpenOn(today) : false;
}

void Museum::addGuide(Guide& guide) {
    g.push_back(guide);
}

int Museum::countGuide() {
    return g.size();
}

Guide Museum::getGuide(int index) {
    if (index >= 0 && index < g.size()) {
        return g[index];
    }
    cout << "Invalid Index" << endl;
    return Guide();
}

json Museum::toJson() const {
    json j;
    j["museumName"] = museumName.empty() ? "Unknown Museum" : museumName;
    j["schedule"] = schedule ? schedule->toJson() : json::object();
    j["exhibits"] = json::array();
    for (const auto& ex : exhibit) {
        if (dynamic_cast<const ArtExhibit*>(&ex)) {
            j["exhibits"].push_back(dynamic_cast<const ArtExhibit*>(&ex)->toJson());
        } else if (dynamic_cast<const HistoryExhibit*>(&ex)) {
            j["exhibits"].push_back(dynamic_cast<const HistoryExhibit*>(&ex)->toJson());
        } else if (dynamic_cast<const TechExhibit*>(&ex)) {
            j["exhibits"].push_back(dynamic_cast<const TechExhibit*>(&ex)->toJson());
        } else {
            j["exhibits"].push_back(ex.toJson());
        }
    }
    j["guides"] = json::array();
    for (const auto& guide : g) {
        j["guides"].push_back(guide.toJson());
    }
    return j;
}

void Museum::fromJson(const json& j) {
    museumName = j.at("museumName").get<string>();
    if (schedule) {
        delete schedule;
    }
    schedule = new Schedule();
    if (j.contains("schedule") && !j.at("schedule").is_null()) {
        schedule->fromJson(j.at("schedule"));
    }
    exhibit.clear();
    for (const auto& exhibitJson : j["exhibits"]) {
        if (exhibitJson.contains("artist")) {
            ArtExhibit artExhibit;
            artExhibit.fromJson(exhibitJson);
            exhibit.push_back(artExhibit);
        } else if (exhibitJson.contains("era")) {
            HistoryExhibit historyExhibit;
            historyExhibit.fromJson(exhibitJson);
            exhibit.push_back(historyExhibit);
        } else if (exhibitJson.contains("technology")) {
            TechExhibit techExhibit;
            techExhibit.fromJson(exhibitJson);
            exhibit.push_back(techExhibit);
        } else {
            exhibit.push_back(Exhibit::fromJson(exhibitJson));
        }
    }
    g.clear();
    for (const auto& guideJson : j["guides"]) {
        g.push_back(Guide::fromJson(guideJson));
    }
}

Museum::~Museum() {
    delete schedule;
}