#ifndef USER_SYSTEM_HPP
#define USER_SYSTEM_HPP

#include <string>
#include <unordered_map>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Class representing a user
class User {
private:
    string username;
    string password;
    bool isAdmin;

public:
    User() : isAdmin(false) {}  // Default constructor

    User(const string& uname, const string& pass, bool admin)
        : username(uname), password(pass), isAdmin(admin) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    bool checkPassword(string pass) const { return password == pass; }
    bool isAdminUser() const { return isAdmin; }
    void changePassword(string newPass) { password = newPass; }
    void setAdminStatus(bool adminStatus) { isAdmin = adminStatus; }
};

// Class managing user registry
class UserRegistry {
private:
    unordered_map<string, User> users;
    string filename;

public:
    UserRegistry(string filename);

    void loadUsersFromJSON();
    void saveUsersToJSON() const;
    void addUser(User newUser);
    bool loginUser(string username, string password) const;
    bool isUsernameTaken(string username) const;
    void promoteToAdmin(string username);
    void demoteFromAdmin(string username);
    bool isAdmin(string username) const;
    void changeUserPassword(string username, string newPassword);
    User getUser(string username) const; // New method to get a User object
};

// Class representing the welcome page
class WelcomePage {
private:
    string username;
    string password;
    UserRegistry& userRegistry;

public:
    // Constructor
    WelcomePage(UserRegistry& registry, const string& usr = "", const string& pswrd = "");

    // Method to capture user input
    void inputCredentials();

    // Method for authentication
    bool authenticate();

    // Method to create an account
    bool createAccount(const string& tempUsername, const string& tempPassword);

    // Method to logout
    void logout();

    // Method to exit the program
    void exit();

    string getUsername() const { return username; } // Getter for username
};

// Class representing user information
class UserInfo {
private:
    string username;
    UserRegistry& userRegistry;

public:
    UserInfo(const string& uname, UserRegistry& registry);

    string getUsername() const;
    string getPassword() const;
    bool isAdmin() const;
};

// Function to capture user action
string captureUserAction();

// Function to handle the user interface logic
bool runUserInterface(UserRegistry& userRegistry, string& loggedInUsername);

#endif // USER_SYSTEM_HPP
