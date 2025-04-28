#include "guide.h"
#include "exhibit.h"  // Required for Exhibit class
#include <iostream>
using namespace std;

Guide::Guide(){
    guideName="";
    language="";
}

Guide::Guide(string name, string lang):guideName(name),language(lang){}
void Guide::startTour(Exhibit& exhibit) {
    cout << "Guide " << guideName << " is starting a tour in " << language << " for exhibit: "<<endl;
    exhibit.display();  // Exhibit class ka method
}


json Guide::toJson() const {
    json j;
    j["guideName"] = guideName;
    j["language"] = language;
    return j;
}


Guide Guide::fromJson(const json& j) {
    string name = j.at("guideName").get<string>();
    string lang = j.at("language").get<string>();
    return Guide(name, lang);
}