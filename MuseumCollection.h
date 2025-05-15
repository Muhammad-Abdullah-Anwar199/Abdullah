#ifndef MUSEUMCOLLECTION_H
#define MUSEUMCOLLECTION_H

#include "exhibit.h"
#include <vector>
#include <iostream>

template <typename T>
class MuseumCollection {
public: // Changed from private to public
    std::vector<T> items;

    void addItem(const T& item) {
        items.push_back(item);
    }

    void displayItems() const {
        std::cout << "Total Items: " << items.size() << std::endl;
        for (size_t i = 0; i < items.size(); i++) {
            std::cout << "\nItem #" << i << ":\n"; // Adjusted to show 0-based index for consistency with userMenu
            items[i].display();
        }
    }

    size_t size() const {
        return items.size();
    }
};

#endif // MUSEUMCOLLECTION_H