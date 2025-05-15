#include "guide.h"
#include <iostream>

Guide::Guide() : guideName(""), language("") {}

Guide::Guide(string name, string lang) : guideName(name), language(lang) {}

string Guide::getGuideName() const {
    return guideName;
}

string Guide::getLanguage() const {
    return language;
}

void Guide::startTour(const Exhibit& exhibit) {
    cout << "Guide " << guideName << " is starting a tour in " << language << " for exhibit: " << exhibit.getTitle() << endl;
    cout << "Exhibit Description: " << exhibit.getDescription() << endl;
}

json Guide::toJson() const {
    json j;
    j["guideName"] = guideName;
    j["language"] = language;
    return j;
}

Guide Guide::fromJson(const json& j) {
    Guide guide;
    guide.guideName = j.at("guideName").get<string>();
    guide.language = j.at("language").get<string>();
    return guide;
}