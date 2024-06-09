#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map> // Include unordered_map header
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

    User() : isAdmin(false) {}  // Default constructor

    User(std::string uname, std::string fname, std::string lname, std::string phone, std::string addr, std::string bday, std::string pass, bool admin);
    
    std::string getUsername() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getPhoneNumber() const;
    std::string getAddress() const;
    std::string getBirthday() const;
    std::string getPassword() const;
    bool checkPassword(std::string pass) const;
    bool isAdminUser() const;
    void changePassword(std::string newPass);
    void setAdminStatus(bool adminStatus);
};

class UserRegistry {
private:
    std::unordered_map<std::string, User> users; // Change vector to unordered_map
    std::string filename;

public:
    UserRegistry(std::string filename);

    void loadUsersFromJSON();
    void saveUsersToJSON() const;
    void addUser(User newUser);
    bool loginUser(std::string username, std::string password) const;
    bool isUsernameTaken(std::string username) const;
    void promoteToAdmin(std::string username);
    void demoteFromAdmin(std::string username);
    bool isAdmin(std::string username) const;
    void changeUserPassword(std::string username, std::string newPassword);
};

#endif // USER_H
