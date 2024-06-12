#include "user_system.hpp"
#include <iostream>
#include <fstream>

using namespace std;

// Global variable for the filename


// UserRegistry class methods
UserRegistry::UserRegistry(string filename) : filename(filename) {
    loadUsersFromJSON();
}

void UserRegistry::loadUsersFromJSON() {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        json j;
        inFile >> j;
        for (auto& element : j.items()) {
            string uname = element.value()["username"];
            User user(
                uname,
                element.value()["firstName"],
                element.value()["lastName"],
                element.value()["phoneNumber"],
                element.value()["address"],
                element.value()["birthday"],
                element.value()["password"],
                element.value()["isAdmin"]
            );
            users[uname] = user;
        }
        inFile.close();
    }
}

void UserRegistry::saveUsersToJSON() const {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        json j;
        for (const auto& pair : users) {
            j[pair.first] = {
                {"username", pair.second.getUsername()},
                {"firstName", pair.second.getFirstName()},
                {"lastName", pair.second.getLastName()},
                {"phoneNumber", pair.second.getPhoneNumber()},
                {"address", pair.second.getAddress()},
                {"birthday", pair.second.getBirthday()},
                {"password", pair.second.getPassword()},
                {"isAdmin", pair.second.isAdminUser()}
            };
        }
        outFile << j.dump(4);
        outFile.close();
    }
}

void UserRegistry::addUser(User newUser) {
    users[newUser.getUsername()] = newUser;
    saveUsersToJSON();
}

bool UserRegistry::loginUser(string username, string password) const {
    auto it = users.find(username);
    return it != users.end() && it->second.checkPassword(password);
}

bool UserRegistry::isUsernameTaken(string username) const {
    return users.find(username) != users.end();
}

void UserRegistry::promoteToAdmin(string username) {
    if (users.find(username) != users.end()) {
        users[username].setAdminStatus(true);
        saveUsersToJSON();
    }
}

void UserRegistry::demoteFromAdmin(string username) {
    if (users.find(username) != users.end()) {
        users[username].setAdminStatus(false);
        saveUsersToJSON();
    }
}

bool UserRegistry::isAdmin(string username) const {
    auto it = users.find(username);
    return it != users.end() && it->second.isAdminUser();
}

void UserRegistry::changeUserPassword(string username, string newPassword) {
    if (users.find(username) != users.end()) {
        users[username].changePassword(newPassword);
        saveUsersToJSON();
    }
}

// WelcomePage class methods
WelcomePage::WelcomePage(UserRegistry& registry, const string& usr, const string& pswrd)
    : userRegistry(registry), username(usr), password(pswrd) {}

void WelcomePage::inputCredentials() {
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
}

bool WelcomePage::authenticate() {
    return userRegistry.loginUser(username, password);
}

bool WelcomePage::createAccount(const string& tempUsername, const string& tempPassword) {
    if (userRegistry.isUsernameTaken(tempUsername)) {
        return false;
    }
    User newUser(tempUsername, "", "", "", "", "", tempPassword, false);
    userRegistry.addUser(newUser);
    return true;
}

void WelcomePage::logout() {
    username = "";
    password = "";
}

void WelcomePage::exit() {
    cout << "Exiting the program." << endl;
    std::exit(0);
}

// Function to capture user action
string captureUserAction() {
    string action;
    cout << "Choose an action: (login, create, logout, exit): ";
    cin >> action;
    return action;
}

// Function to handle the user interface logic
void runUserInterface(UserRegistry& userRegistry) {
    WelcomePage welcomePage(userRegistry);
    while (true) {
        string action = captureUserAction();
        if (action == "login") {
            welcomePage.inputCredentials();
            if (welcomePage.authenticate()) {
                cout << "Login successful." << endl;
            } else {
                cout << "Login failed." << endl;
            }
        } else if (action == "create") {
            string newUsername, newPassword;
            cout << "Enter new username: ";
            cin >> newUsername;
            cout << "Enter new password: ";
            cin >> newPassword;
            if (welcomePage.createAccount(newUsername, newPassword)) {
                cout << "Account created successfully." << endl;
                cout << "log in to enter" << endl;
            } else {
                cout << "Username already taken." << endl;
            }
        } else if (action == "logout") {
            welcomePage.logout();
            cout << "Logged out." << endl;
        } else if (action == "exit") {
            welcomePage.exit();
        } else {
            cout << "Invalid action." << endl;
        }
    }
}