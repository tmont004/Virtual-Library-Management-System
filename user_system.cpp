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
            string uname = element.value().value("username", "");
            User user(
                uname,
                element.value().value("password", ""),
                element.value().value("isAdmin", false)
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
                {"password", pair.second.getPassword()},
                {"isAdmin", pair.second.isAdminUser()}
            };
        }
        outFile << j.dump(4);
        outFile.close();
    } else {
        cout << "There was a problem accessing the db, please try again" << endl;
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

User UserRegistry::getUser(string username) const {
    auto it = users.find(username);
    if (it != users.end()) {
        return it->second;
    }
    throw runtime_error("User not found: " + username);
}

// WelcomePage class methods
WelcomePage::WelcomePage(UserRegistry& registry, const std::string& usr, const std::string& pswrd)
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
    User newUser(tempUsername, tempPassword, false);
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

// UserInfo class methods
UserInfo::UserInfo(const string& uname, UserRegistry& registry)
    : username(uname), userRegistry(registry) {}

string UserInfo::getUsername() const {
    return username;
}

string UserInfo::getPassword() const {
    try {
        User user = userRegistry.getUser(username);
        return user.getPassword();
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return "";
    }
}

bool UserInfo::isAdmin() const {
    try {
        User user = userRegistry.getUser(username);
        return user.isAdminUser();
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return false;
    }
}

// Function to capture user action
string captureUserAction() {
    string action;

     cout << "==== Welcome to the Library System ====" << endl;
        cout << "Choose an action:" << endl;
        cout << "1. Login" << endl;
        cout << "2. Create an Account" << endl;
        cout << "3. Logout" << endl;
        cout << "4. Exit" << endl;
        cout << "=======================================" << endl;
        cout << "Enter your choice (1-4): ";
    cin >> action;
    return action;
}

// Function to handle the user interface logic
bool runUserInterface(UserRegistry& userRegistry, string& loggedInUsername) {
    WelcomePage welcomePage(userRegistry);

    bool isLoggedIn = false;
    bool running = true;

    while (running) {
        string action = captureUserAction();

        if (action == "1") {

        //if (action == "login") {

            welcomePage.inputCredentials();
            if (welcomePage.authenticate()) {
                isLoggedIn = true;
                loggedInUsername = welcomePage.getUsername();
                cout << "Login successful." << endl;
                UserInfo userInfo(welcomePage.getUsername(), userRegistry);
                cout << "Welcome, " << userInfo.getUsername() << endl;
                cout << "Admin status: " << (userInfo.isAdmin() ? "Yes" : "No") << endl;
                running = false;
            } else {
                cout << "Login failed." << endl;
            }
        } else if (action == "2") {
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
        } else if (action == "3") {
            welcomePage.logout();
            cout << "Logged out." << endl;
        } else if (action == "4") {
            welcomePage.exit();
        } else {
            cout << "Invalid action." << endl;
        }
    }

    return isLoggedIn;
}
