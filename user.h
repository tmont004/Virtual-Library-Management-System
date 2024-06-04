#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

class User {
private:
    std::string username;
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string address;
    std::string birthday;
    std::string password;
    bool isAdmin;

public:
    User(std::string uname, std::string fname, std::string lname, std::string phone, std::string addr, std::string bday, std::string pass, bool admin);
    
    std::string getUsername() const; // Added const specifier
    std::string getFirstName() const; // Added const specifier
    std::string getLastName() const; // Added const specifier
    std::string getPhoneNumber() const; // Added const specifier
    std::string getAddress() const; // Added const specifier
    std::string getBirthday() const; // Added const specifier
    std::string getPassword() const; // Added const specifier
    bool checkPassword(std::string pass) const; // Added const specifier
    bool isAdminUser() const; // Added const specifier
    void changePassword(std::string newPass);

    // Function to set admin status
    void setAdminStatus(bool adminStatus);
};

class UserRegistry {
private:
    std::vector<User> users;
    std::string filename;

public:
    UserRegistry(std::string filename);

    void loadUsersFromJSON();
    void saveUsersToJSON() const; // Added const specifier
    void addUser(User newUser);
    bool loginUser(std::string username, std::string password) const; // Added const specifier
    bool isUsernameTaken(std::string username) const; // Added const specifier
    void promoteToAdmin(std::string username);
    void demoteFromAdmin(std::string username);
    bool isAdmin(std::string username) const; // Added const specifier
    void changeUserPassword(std::string username, std::string newPassword);
};

#endif // USER_H
