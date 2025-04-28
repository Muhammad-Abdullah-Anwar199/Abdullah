#ifndef MuseumCollection_H
#define MuseumCollection_H
#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class MuseumCollection {
private:
    vector<T> items;
public:
    void addItem(const T& item) {
        items.push_back(item);
    }

    void displayItems() const {
        for (const auto& item : items) {
            cout << item << endl;
        }
    }
};

#endif