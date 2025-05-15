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

void Museum::addExhibitInteractively(MuseumCollection<Exhibit>& exhibitCollection) {
    cout << "\n=== Adding Exhibit ===\n";
    string type;
    cout << "Enter exhibit type (art/history/tech/regular): ";
    cin >> type;
    cin.ignore();

    string title, description;
    int popularity;
    float rating;

    cout << "Enter Exhibit Title: ";
    getline(cin, title);
    cout << "Enter Description: ";
    getline(cin, description);
    cout << "Enter Popularity (0-100): ";
    cin >> popularity;
    cout << "Enter Rating (0-5): ";
    cin >> rating;
    cin.ignore();

    if (type == "art") {
        string artist;
        cout << "Enter Artist Name: ";
        getline(cin, artist);
        ArtExhibit artExhibit;
        artExhibit.setArtist(artist);
        artExhibit.setTitle(title);
        artExhibit.setDescription(description);
        artExhibit.setPopularity(popularity);
        artExhibit.setRating(rating);
        addExhibit(artExhibit);
        exhibitCollection.addItem(artExhibit);
        cout << "Added Art Exhibit by " << artist << endl;
    } else if (type == "history") {
        string era;
        cout << "Enter Era: ";
        getline(cin, era);
        HistoryExhibit historyExhibit;
        historyExhibit.setEra(era);
        historyExhibit.setTitle(title);
        historyExhibit.setDescription(description);
        historyExhibit.setPopularity(popularity);
        historyExhibit.setRating(rating);
        addExhibit(historyExhibit);
        exhibitCollection.addItem(historyExhibit);
        cout << "Added History Exhibit from " << era << endl;
    } else if (type == "tech") {
        string technology;
        cout << "Enter Technology: ";
        getline(cin, technology);
        TechExhibit techExhibit;
        techExhibit.setTechnology(technology);
        techExhibit.setTitle(title);
        techExhibit.setDescription(description);
        techExhibit.setPopularity(popularity);
        techExhibit.setRating(rating);
        addExhibit(techExhibit);
        exhibitCollection.addItem(techExhibit);
        cout << "Added Tech Exhibit featuring " << technology << endl;
    } else {
        Exhibit exhibit;
        exhibit.setTitle(title);
        exhibit.setDescription(description);
        exhibit.setPopularity(popularity);
        exhibit.setRating(rating);
        addExhibit(exhibit);
        exhibitCollection.addItem(exhibit);
        cout << "Added Regular Exhibit" << endl;
    }
    exhibitCollection.displayItems();
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

void Museum::addGuideInteractively(const Exhibit& exhibit) {
    cout << "\n=== Adding Guide ===\n";
    string guideName, language;
    cout << "Enter Guide Name: ";
    cin >> guideName;
    cout << "Enter Language: ";
    cin >> language;
    Guide guide(guideName, language);
    guide.startTour(exhibit); // Assumes startTour accepts const Exhibit&
    addGuide(guide);
    cout << "Guide " << guideName << " added." << endl;
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

void Museum::loadData(const string& filename) {
    Museum* museum = getInstance();
    ifstream museumInFile(filename);
    if (!museumInFile.is_open() || museumInFile.peek() == -1) {
        cout << "No or empty museum.json found. Creating new museum." << endl;
        museum->setMuseumName("National Museum");
    } else {
        try {
            json j;
            museumInFile >> j;
            museum->fromJson(j);
            cout << "Loaded museum with " << museum->countExhibit() << " exhibits, " 
                 << museum->countGuide() << " guides." << endl;
        } catch (const json::exception& e) {
            cout << "Error reading museum.json: " << e.what() << ". Creating new museum." << endl;
            museum->setMuseumName("National Museum");
        }
    }
    museumInFile.close();
}

void Museum::saveData(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Failed to open " << filename << " for writing." << endl;
        return;
    }
    try {
        json j = toJson();
        outFile << j.dump(4);
        cout << "Saved museum data to " << filename << endl;
    } catch (const json::exception& e) {
        cout << "Error saving " << filename << ": " << e.what() << endl;
    }
    outFile.close();
}

Museum::~Museum() {
    delete schedule;
}