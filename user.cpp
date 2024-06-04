#include "user.h"
#include <fstream>

User::User(std::string uname, std::string fname, std::string lname, std::string phone, std::string addr, std::string bday, std::string pass, bool admin)
    : username(uname), firstName(fname), lastName(lname), phoneNumber(phone), address(addr), birthday(bday), password(pass), isAdmin(admin) {}

std::string User::getUsername() const {
    return username;
}

std::string User::getFirstName() const {
    return firstName;
}

std::string User::getLastName() const {
    return lastName;
}

std::string User::getPhoneNumber() const {
    return phoneNumber;
}

std::string User::getAddress() const {
    return address;
}

std::string User::getBirthday() const {
    return birthday;
}

std::string User::getPassword() const {
    return password;
}

bool User::checkPassword(std::string pass) const {
    return password == pass;
}

bool User::isAdminUser() const {
    return isAdmin;
}

void User::changePassword(std::string newPass) {
    password = newPass;
}

void User::setAdminStatus(bool adminStatus) {
    isAdmin = adminStatus;
}

UserRegistry::UserRegistry(std::string filename) : filename(filename) {}

void UserRegistry::loadUsersFromJSON() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // Handle file open error
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    users.clear();

    for (const auto& userJson : jsonData) {
        User user(
            userJson["username"],
            userJson["firstName"],
            userJson["lastName"],
            userJson["phoneNumber"],
            userJson["address"],
            userJson["birthday"],
            userJson["password"],
            userJson["isAdmin"]
        );
        users[user.getUsername()] = user; // Insert into unordered_map
    }
}

void UserRegistry::saveUsersToJSON() const {
    json jsonData;
    for (const auto& pair : users) {
        const User& user = pair.second;
        json userJson = {
            {"username", user.getUsername()},
            {"firstName", user.getFirstName()},
            {"lastName", user.getLastName()},
            {"phoneNumber", user.getPhoneNumber()},
            {"address", user.getAddress()},
            {"birthday", user.getBirthday()},
            {"password", user.getPassword()},
            {"isAdmin", user.isAdminUser()}
        };
        jsonData.push_back(userJson);
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        // Handle file open error
        return;
    }

    file << jsonData.dump(4); // Pretty print with 4 spaces
    file.close();
}

void UserRegistry::addUser(User newUser) {
    users[newUser.getUsername()] = newUser; // Insert into unordered_map
}

bool UserRegistry::loginUser(std::string username, std::string password) const {
    auto it = users.find(username);
    if (it != users.end()) {
        const User& user = it->second;
        return user.checkPassword(password);
    }
    return false;
}

bool UserRegistry::isUsernameTaken(std::string username) const {
    return users.find(username) != users.end();
}

void UserRegistry::promoteToAdmin(std::string username) {
    auto it = users.find(username);
    if (it != users.end()) {
        User& user = it->second;
        user.setAdminStatus(true);
    }
}

void UserRegistry::demoteFromAdmin(std::string username) {
    auto it = users.find(username);
    if (it != users.end()) {
        User& user = it->second;
        user.setAdminStatus(false);
    }
}

bool UserRegistry::isAdmin(std::string username) const {
    auto it = users.find(username);
    if (it != users.end()) {
        const User& user = it->second;
        return user.isAdminUser();
    }
    return false;
}

void UserRegistry::changeUserPassword(std::string username, std::string newPassword) {
    auto it = users.find(username);
    if (it != users.end()) {
        User& user = it->second;
        user.changePassword(newPassword);
    }
}
