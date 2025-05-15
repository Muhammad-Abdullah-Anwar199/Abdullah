#include "user.h"
#include "ticket.h"
#include "membership.h"
#include "review.h"

User::User(int initialSize) {
    reviewCapacity = initialSize;
    reviewCount = 0;
    reviews = new Review[reviewCapacity];
}

void User::setUserName(string name) {
    userName = name;
}

string User::getUserName()const {
    return userName;
}

void User::addTicket(Ticket& ticket) {
    tickets.push_back(ticket);
}

void User::purchaseTickets(const Exhibit& exhibit) {
    cout << "\n=== Purchasing Tickets ===\n";
    int numTickets;
    cout << "Enter the number of tickets to buy: ";
    cin >> numTickets;
    if (numTickets <= 0) {
        cout << "Invalid number of tickets." << endl;
        return;
    }
    cin.ignore();

    Ticket* tempTickets = new Ticket[numTickets];
    for (int i = 0; i < numTickets; i++) {
        int ticketId;
        string expiryDate;
        int hasVipPassInt;
        bool hasVipPass;

        cout << "\nEnter details for Ticket #" << i + 1 << endl;
        cout << "Enter Ticket ID: ";
        cin >> ticketId;
        cin.ignore();
        cout << "Enter Expiry Date: ";
        getline(cin, expiryDate);
        cout << "Do you have a VIP Pass? (1 for Yes, 0 for No): ";
        cin >> hasVipPassInt;
        while (hasVipPassInt != 0 && hasVipPassInt != 1) {
            cout << "Please enter 1 (Yes) or 0 (No): ";
            cin >> hasVipPassInt;
        }
        hasVipPass = (hasVipPassInt == 1);

        Ticket ticket(ticketId, expiryDate, hasVipPass);
        ticket.setExhibit(exhibit);
        tempTickets[i] = ticket;
        addTicket(ticket);
    }

    cout << "Total Tickets: " << countTickets() << endl;
    for (int i = 0; i < numTickets; i++) {
        cout << "\nTicket #" << i + 1 << " Info:\n";
        cout << "Ticket ID: " << tempTickets[i].getTicketId() << endl;
        cout << "Expiry Date: " << tempTickets[i].getExpiryDate() << endl;
        cout << "VIP Access: " << (tempTickets[i].hasVIPAccess() ? "Yes" : "No") << endl;
        cout << "Linked Exhibit:\n";
        tempTickets[i].getExhibit().display();
    }
    delete[] tempTickets;
}

Ticket User::getTicket(int index) {
    if (index >= 0 && index < tickets.size()) {
        return tickets[index];
    }
    cout << "Invalid Index" << endl;
    return Ticket();
}

int User::countTickets() {
    return tickets.size();
}

void User::displayTickets() const {
    cout << "Total Tickets: " << tickets.size() << endl;
    for (size_t i = 0; i < tickets.size(); i++) {
        cout << "\nTicket #" << i + 1 << " Info:\n";
        cout << "Ticket ID: " << tickets[i].getTicketId() << endl;
        cout << "Expiry Date: " << tickets[i].getExpiryDate() << endl;
        cout << "VIP Access: " << (tickets[i].hasVIPAccess() ? "Yes" : "No") << endl;
        cout << "Linked Exhibit:\n";
        tickets[i].getExhibit().display();
    }
}

void User::addMembership(Membership& a) {
    mem.push_back(a);
}

void User::addMemberships() {
    cout << "\n=== Adding Memberships ===\n";
    int numMembership;
    cout << "How many memberships to add? ";
    cin >> numMembership;
    if (numMembership < 0) {
        cout << "Invalid number of memberships." << endl;
        return;
    }
    cin.ignore();

    Membership* memberships = new Membership[numMembership];
    for (int i = 0; i < numMembership; i++) {
        int memberShipId;
        cout << "\nEnter MemberShip ID for Membership #" << i + 1 << ": ";
        cin >> memberShipId;
        cin.ignore();

        string type;
        cout << "Which Type of Membership? (vip/local): ";
        getline(cin, type);

        float discount;
        if (type == "vip") {
            discount = 30.0;
        } else if (type == "local") {
            discount = 10.0;
        } else {
            discount = 0.0;
            cout << "Unknown membership type, no discount applied.\n";
        }

        Membership membership(10, memberShipId, type, discount);
        memberships[i] = membership;
        addMembership(membership);
        cout << "Getting discount --> " << membership.getDiscount() << "%" << endl;
        cout << "Membership #" << i + 1 << " added successfully!" << endl;
    }
    cout << "Total Memberships: " << countMembership() << endl;
    delete[] memberships;
}

int User::countMembership() {
    return mem.size();
}

Membership User::getMembership(int index) {
    if (index >= 0 && index < mem.size()) {
        return mem[index];
    }
    cout << "Invalid Index" << endl;
    return Membership();
}

void User::displayMemberships() const {
    cout << "Total Memberships: " << mem.size() << endl;
    for (size_t i = 0; i < mem.size(); i++) {
        cout << "\nMembership #" << i + 1 << ":\n";
        cout << "Membership ID: " << mem[i].getMemberShipId() << endl;
        cout << "Type: " << mem[i].getType() << endl;
        cout << "Discount: " << mem[i].getDiscount() << "%" << endl;
    }
}

void User::addReviews(Review review) {
    if (reviewCount >= reviewCapacity) {
        int newCapacity = reviewCapacity * 2;
        Review* newReviews = new Review[newCapacity];
        for (int i = 0; i < reviewCount; i++) {
            newReviews[i] = reviews[i];
        }
        delete[] reviews;
        reviews = newReviews;
        reviewCapacity = newCapacity;
    }
    reviews[reviewCount] = review;
    reviewCount++;
}

void User::addMultipleReviews() {
    cout << "\n=== Adding Reviews ===\n";
    int numReviews;
    cout << "How many reviews to add? ";
    cin >> numReviews;
    if (numReviews < 0) {
        cout << "Invalid number of reviews." << endl;
        return;
    }
    cin.ignore();

    Review* tempReviews = new Review[numReviews];
    for (int i = 0; i < numReviews; i++) {
        string reviewerName, comment;
        float rating;

        cout << "\n--- Review #" << i + 1 << " ---\n";
        cout << "Enter your Name: ";
        getline(cin, reviewerName);
        cout << "Enter your Comment: ";
        getline(cin, comment);
        cout << "Give Rating (0-5): ";
        cin >> rating;
        cin.ignore();

        Review review(10, reviewerName, comment, rating);
        tempReviews[i] = review;
        addReviews(review);
        cout << "Review #" << i + 1 << " added successfully!" << endl;
    }
    cout << "Total Reviews: " << countReviews() << endl;
    delete[] tempReviews;
}

int User::countReviews() {
    return reviewCount;
}

void User::displayReviews() const {
    cout << "Total Reviews: " << reviewCount << endl;
    for (int i = 0; i < reviewCount; i++) {
        cout << "\nReview #" << i + 1 << ":\n";
        cout << "Reviewer: " << reviews[i].getReviewerName() << endl;
        cout << "Comment: " << reviews[i].getComment() << endl;
        cout << "Rating: " << reviews[i].getRating() << endl;
    }
}

bool User::hasVipPass() {
    for (const auto& ticket : tickets) {
        if (ticket.hasVIPAccess()) {
            return true;
        }
    }
    return false;
}

User::~User() {
    delete[] reviews;
}

User::User(const User& other) {
    reviewCapacity = other.reviewCapacity;
    reviewCount = other.reviewCount;
    reviews = new Review[reviewCapacity];
    for (int i = 0; i < reviewCount; i++) {
        reviews[i] = other.reviews[i];
    }
    userName = other.userName;
    tickets = other.tickets;
    mem = other.mem;
}

User& User::operator=(const User& other) {
    if (this != &other) {
        delete[] reviews;
        reviewCapacity = other.reviewCapacity;
        reviewCount = other.reviewCount;
        reviews = new Review[reviewCapacity];
        for (int i = 0; i < reviewCount; i++) {
            reviews[i] = other.reviews[i];
        }
        userName = other.userName;
        tickets = other.tickets;
        mem = other.mem;
    }
    return *this;
}

json User::toJson() const {
    json j;
    j["userName"] = userName;
    j["tickets"] = json::array();
    for (const auto& t : tickets)
        j["tickets"].push_back(t.toJson());
    j["memberships"] = json::array();
    for (const auto& m : mem)
        j["memberships"].push_back(m.toJson());
    j["reviews"] = json::array();
    for (int i = 0; i < reviewCount; ++i)
        j["reviews"].push_back(reviews[i].toJson());
    return j;
}

void User::fromJson(const json& j) {
    userName = j.at("userName").get<string>();
    tickets.clear();
    for (const auto& t : j.at("tickets"))
        tickets.push_back(Ticket::fromJson(t));
    mem.clear();
    for (const auto& m : j.at("memberships"))
        mem.push_back(Membership::fromJson(m));
    reviewCount = j.at("reviews").size();
    reviewCapacity = reviewCount + 5;
    delete[] reviews;
    reviews = new Review[reviewCapacity];
    for (int i = 0; i < reviewCount; ++i)
        reviews[i] = Review::fromJson(j.at("reviews")[i]);
}

void User::saveToFile(const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        json j = this->toJson();
        outFile << j.dump(4);
        outFile.close();
        cout << "Saved user data to " << filename << endl;
    } else {
        cerr << "Failed to open file for writing: " << filename << endl;
    }
}

void User::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        json j;
        inFile >> j;
        fromJson(j);
        inFile.close();
    } else {
        cerr << "Failed to open file for reading: " << filename << endl;
    }
}

void User::loadUsers(map<string, User*>& userMap) {
    cout << "\n=== Loading User Data ===\n";
    char loadChoice;
    cout << "Do you want to load existing user data? (y/n): ";
    cin >> loadChoice;
    cin.ignore();

    if (loadChoice == 'y' || loadChoice == 'Y') {
        string userName;
        bool loaded = false;
        while (!loaded) {
            cout << "Enter user name to load: ";
            getline(cin, userName);
            if (userName.empty()) {
                cout << "Username cannot be empty. Try again or type 'exit': ";
                getline(cin, userName);
                if (userName == "exit") break;
                continue;
            }

            User* loadedUser = new User(10);
            string userFile = userName + ".json";
            ifstream userInFile(userFile);
            if (!userInFile.is_open() || userInFile.peek() == -1) {
                cout << "No or empty file found for " << userName << "." << endl;
                delete loadedUser;
            } else {
                try {
                    json j;
                    userInFile >> j;
                    loadedUser->fromJson(j);
                    if (loadedUser->getUserName().empty()) {
                        loadedUser->setUserName(userName);
                    }
                    userMap[userName] = loadedUser;
                    cout << "Loaded user " << userName << ": " << loadedUser->countTickets() << " tickets, "
                         << loadedUser->countReviews() << " reviews, " << loadedUser->countMembership() << " memberships." << endl;
                    loaded = true;
                } catch (const json::exception& e) {
                    cout << "Error reading " << userFile << ": " << e.what() << endl;
                    delete loadedUser;
                }
            }
            userInFile.close();

            if (!loaded) {
                cout << "Try another username? (y/n): ";
                char retry;
                cin >> retry;
                cin.ignore();
                if (retry != 'y' && retry != 'Y') break;
            }
        }
    } else {
        int totalUsers, initialSize;
        cout << "Enter the number of users: ";
        cin >> totalUsers;
        if (totalUsers <= 0) {
            cout << "Invalid number of users." << endl;
            return;
        }
        cout << "Enter the initial ticket array size: ";
        cin >> initialSize;
        if (initialSize <= 0) {
            cout << "Invalid ticket array size." << endl;
            return;
        }
        cin.ignore();

        for (int i = 0; i < totalUsers; i++) {
            string name;
            cout << "Enter the name of user " << i + 1 << ": ";
            getline(cin, name);
            if (name.empty()) {
                cout << "User name cannot be empty." << endl;
                continue;
            }
            User* newUser = new User(initialSize);
            newUser->setUserName(name);
            userMap[name] = newUser;
        }
    }
}