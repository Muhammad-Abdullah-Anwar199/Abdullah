#include "exhibit.h"
#include <iostream>

// Exhibit class implementation
Exhibit::Exhibit() : title(""), description(""), popularity(0), rating(0.0f) {}

Exhibit::Exhibit(string title, string desc, int pop, float rate) 
    : title(title), description(desc), popularity(pop), rating(rate) {}

void Exhibit::setTitle(string title) {
    this->title = title;
}

string Exhibit::getTitle() const {
    return title;
}

void Exhibit::setDescription(const string description) {
    this->description = description;
}

string Exhibit::getDescription() const {
    return description;
}

void Exhibit::setPopularity(int p) {
    popularity = p;
}

int Exhibit::getPopularity() const {
    return popularity;
}

void Exhibit::incrementPopularity() {
    popularity++;
}

string Exhibit::getPopularityStatus() const {
    if (popularity >= 75) return "Highly Popular";
    if (popularity >= 50) return "Moderately Popular";
    if (popularity >= 25) return "Somewhat Popular";
    return "Not Popular";
}

void Exhibit::setRating(float rating) {
    this->rating = rating;
}

float Exhibit::getRating() const {
    return rating;
}

void Exhibit::display() const {
    cout << "Title: " << title << endl;
    cout << "Description: " << description << endl;
    cout << "Popularity: " << popularity << endl;
    cout << "Rating: " << rating << endl;
}

bool Exhibit::operator==(const Exhibit& other) const {
    return title == other.title && description == other.description &&
           popularity == other.popularity && rating == other.rating;
}

bool Exhibit::operator!=(const Exhibit& other) const {
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
    Exhibit ex;
    ex.title = j.at("title").get<string>();
    ex.description = j.at("description").get<string>();
    ex.popularity = j.at("popularity").get<int>();
    ex.rating = j.at("rating").get<float>();
    return ex;
}

// ArtExhibit class implementation
ArtExhibit::ArtExhibit() : Exhibit(), artist("") {}

void ArtExhibit::setArtist(string artist) {
    this->artist = artist;
}

string ArtExhibit::getArtist() const {
    return artist;
}

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
    Exhibit base = Exhibit::fromJson(j);
    title = base.getTitle();
    description = base.getDescription();
    popularity = base.getPopularity();
    rating = base.getRating();
    artist = j.at("artist").get<string>();
}

// HistoryExhibit class implementation
HistoryExhibit::HistoryExhibit() : Exhibit(), era("") {}

void HistoryExhibit::setEra(string era) {
    this->era = era;
}

string HistoryExhibit::getEra() const {
    return era;
}

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
    Exhibit base = Exhibit::fromJson(j);
    title = base.getTitle();
    description = base.getDescription();
    popularity = base.getPopularity();
    rating = base.getRating();
    era = j.at("era").get<string>();
}

// TechExhibit class implementation
TechExhibit::TechExhibit() : Exhibit(), technology("") {}

void TechExhibit::setTechnology(string technology) {
    this->technology = technology;
}

string TechExhibit::getTechnology() const {
    return technology;
}

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
    Exhibit base = Exhibit::fromJson(j);
    title = base.getTitle();
    description = base.getDescription();
    popularity = base.getPopularity();
    rating = base.getRating();
    technology = j.at("technology").get<string>();
}