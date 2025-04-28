#include "exhibit.h"
#include <iostream>

using namespace std;
using nlohmann::json;

// Exhibit Implementation
Exhibit::Exhibit() : title(""), description(""), popularity(0), rating(0.0f) {}

Exhibit::Exhibit(string title, string description, int popularity, float rating)
    : title(title), description(description), popularity(popularity), rating(rating) {
    if (popularity < 0) this->popularity = 0;
    if (rating < 0.0f || rating > 5.0f) this->rating = 0.0f;
}

void Exhibit::setTitle(string title) { this->title = title; }
string Exhibit::getTitle() { return title; }

void Exhibit::setDescription(string description) { this->description = description; }
string Exhibit::getDescription() { return description; }

void Exhibit::setPopularity(int p) {
    popularity = (p >= 0) ? p : 0;
}
int Exhibit::getPopularity() { return popularity; }

void Exhibit::incrementPopularity() { popularity++; }

string Exhibit::getPopularityStatus() {
    if (popularity >= 80) return "Highly Popular";
    if (popularity >= 50) return "Moderately Popular";
    return "Less Popular";
}

void Exhibit::setRating(float rating) {
    this->rating = (rating >= 0.0f && rating <= 5.0f) ? rating : 0.0f;
}
float Exhibit::getRating() { return rating; }

void Exhibit::display() const {
    cout << "Title: " << title << "\nDescription: " << description
         << "\nPopularity: " << popularity << "\nRating: " << rating << endl;
}

bool Exhibit::operator==(const Exhibit& other) {
    return title == other.title && description == other.description &&
           popularity == other.popularity && rating == other.rating;
}

bool Exhibit::operator!=(const Exhibit& other) {
    return !(*this == other);
}

json Exhibit::toJson() const {
    json j;
    j["title"] = title;
    j["description"] = description;
    j["popularity"] = popularity;
    j["rating"] = rating;
    return j;
}

Exhibit Exhibit::fromJson(const json& j) {
    Exhibit exhibit;
    exhibit.title = j.at("title").get<string>();
    exhibit.description = j.at("description").get<string>();
    exhibit.popularity = j.at("popularity").get<int>();
    exhibit.rating = j.at("rating").get<float>();
    if (exhibit.popularity < 0) exhibit.popularity = 0;
    if (exhibit.rating < 0.0f || exhibit.rating > 5.0f) exhibit.rating = 0.0f;
    return exhibit;
}

// ArtExhibit Implementation
ArtExhibit::ArtExhibit() : Exhibit(), artist("") {}

void ArtExhibit::setArtist(string artist) { this->artist = artist; }
string ArtExhibit::getArtist() { return artist; }

void ArtExhibit::display() const {
    Exhibit::display();
    cout << "Artist: " << artist << endl;
}

json ArtExhibit::toJson() const {
    json j = Exhibit::toJson();
    j["artist"] = artist;
    return j;
}

void ArtExhibit::fromJson(const json& j) {
    setTitle(j.at("title").get<string>());
    setDescription(j.at("description").get<string>());
    setPopularity(j.at("popularity").get<int>());
    setRating(j.at("rating").get<float>());
    artist = j.at("artist").get<string>();
}

// HistoryExhibit Implementation
HistoryExhibit::HistoryExhibit() : Exhibit(), era("") {}

void HistoryExhibit::setEra(string era) { this->era = era; }
string HistoryExhibit::getEra() { return era; }

void HistoryExhibit::display() const {
    Exhibit::display();
    cout << "Era: " << era << endl;
}

json HistoryExhibit::toJson() const {
    json j = Exhibit::toJson();
    j["era"] = era;
    return j;
}

void HistoryExhibit::fromJson(const json& j) {
    setTitle(j.at("title").get<string>());
    setDescription(j.at("description").get<string>());
    setPopularity(j.at("popularity").get<int>());
    setRating(j.at("rating").get<float>());
    era = j.at("era").get<string>();
}

// TechExhibit Implementation
TechExhibit::TechExhibit() : Exhibit(), technology("") {}

void TechExhibit::setTechnology(string technology) { this->technology = technology; }
string TechExhibit::getTechnology() { return technology; }

void TechExhibit::display() const {
    Exhibit::display();
    cout << "Technology: " << technology << endl;
}

json TechExhibit::toJson() const {
    json j = Exhibit::toJson();
    j["technology"] = technology;
    return j;
}

void TechExhibit::fromJson(const json& j) {
    setTitle(j.at("title").get<string>());
    setDescription(j.at("description").get<string>());
    setPopularity(j.at("popularity").get<int>());
    setRating(j.at("rating").get<float>());
    technology = j.at("technology").get<string>();
}