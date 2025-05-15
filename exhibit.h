#ifndef EXHIBIT_H
#define EXHIBIT_H

#include <string>
#include "json.hpp"
using namespace std;
using nlohmann::json;

class Exhibit {
protected:
    string title;
    string description;
    int popularity;
    float rating;

public:
    Exhibit();
    Exhibit(string title, string desc, int pop, float rate);
    void setTitle(string title);
    string getTitle() const;
    void setDescription(const string description);
    string getDescription() const;
    void setPopularity(int p);
    int getPopularity() const; // Added const
    void incrementPopularity();
    string getPopularityStatus() const; // Added const
    void setRating(float rating);
    float getRating() const; // Added const
    virtual void display() const;
    bool operator==(const Exhibit& other) const; // Added const
    bool operator!=(const Exhibit& other) const; // Added const
    friend ostream& operator<<(ostream& os, const Exhibit& ex) {
        os << ex.title << ex.description;
        return os;
    }
    virtual json toJson() const;
    static Exhibit fromJson(const json& j);
};

class ArtExhibit : public Exhibit {
private:
    string artist;

public:
    ArtExhibit();
    void setArtist(string artist);
    string getArtist() const; // Added const
    void display() const override;
    json toJson() const override;
    void fromJson(const json& j);
};

class HistoryExhibit : public Exhibit {
private:
    string era;

public:
    HistoryExhibit();
    void setEra(string era);
    string getEra() const; // Added const
    void display() const override;
    json toJson() const override;
    void fromJson(const json& j);
};

class TechExhibit : public Exhibit {
private:
    string technology;

public:
    TechExhibit();
    void setTechnology(string technology);
    string getTechnology() const; // Added const
    void display() const override;
    json toJson() const override;
    void fromJson(const json& j);
};

#endif //EXHIBIT_H