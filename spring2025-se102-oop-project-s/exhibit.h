#ifndef EXHIBIT_H
#define EXHIBIT_H

#include <string>
#include "json.hpp"
using namespace std;
using nlohmann::json;
class Exhibit {
private:
    string title;
    string description;
    int popularity;
    float rating;
public:
    Exhibit();
    Exhibit(string,string,int,float);
    void setTitle(string title);
    string getTitle();
    void setDescription(string description);
    string getDescription();
    void setPopularity(int p);
    int getPopularity();
    void incrementPopularity();
    string getPopularityStatus();
    void setRating(float rating);
    float getRating();
    virtual void display()const;
    bool operator==(const Exhibit& other);
    bool operator!=(const Exhibit& other);
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
    string getArtist();
    void display()const override;
    json toJson() const override;
    void fromJson(const json& j);
};

class HistoryExhibit : public Exhibit {
private:
    string era;
public:
    HistoryExhibit();
    void setEra(string era);
    string getEra();
    void display()const override;
    json toJson() const override;
    void fromJson(const json& j);
};

class TechExhibit : public Exhibit {
private:
    string technology;
public:
    TechExhibit();
    void setTechnology(string technology);
    string getTechnology();
    void display()const override;
    json toJson() const override;
    void fromJson(const json& j);
};
#endif //EXHIBIT_H