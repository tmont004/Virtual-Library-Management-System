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
    string firstName;
    string lastName;
    string phoneNumber;
    string address;
    string birthday;
    string password;
    bool isAdmin;

public:
    User() : isAdmin(false) {}  // Default constructor

    User(string uname, string fname, string lname, string phone, string addr, string bday, string pass, bool admin)
        : username(uname), firstName(fname), lastName(lname), phoneNumber(phone), address(addr), birthday(bday), password(pass), isAdmin(admin) {}

    string getUsername() const { return username; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getPhoneNumber() const { return phoneNumber; }
    string getAddress() const { return address; }
    string getBirthday() const { return birthday; }
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
};

// Class representing the welcome page
class WelcomePage { // From welcomepage.hpp
private:
    string username;
    string password;
    UserRegistry& userRegistry;

public:
    // Constructor
    WelcomePage(UserRegistry& registry, const string& usr = "", const string& pswrd = ""); // From welcomepage.hpp

    // Method to capture user input
    void inputCredentials(); // From welcomepage.hpp

    // Method for authentication
    bool authenticate(); // From welcomepage.hpp

    // Method to create an account
    bool createAccount(const string& tempUsername, const string& tempPassword); // From welcomepage.hpp

    // Method to logout
    void logout(); // From welcomepage.hpp

    // Method to exit the program
    void exit(); // From welcomepage.hpp
};

// Function to capture user action
string captureUserAction(); // From welcomepage.hpp

// Function to handle the user interface logic
void runUserInterface(UserRegistry& userRegistry); // From welcomepage.hpp

#endif // USER_SYSTEM_HPP
