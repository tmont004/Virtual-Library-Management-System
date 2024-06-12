#ifndef WELCOMEPAGE_HPP
#define WELCOMEPAGE_HPP

#include <string>
#include <unordered_map>

// Declare the database variable externally
extern std::unordered_map<std::string, std::string> userDatabase;

// Function declarations
void loadDatabase(const std::string& filename);
void saveDatabase(const std::string& filename);

// Class representing the welcome page
class WelcomePage {
private:
    std::string username;
    std::string password;

public:
    // Constructor
    WelcomePage(const std::string& usr = "", const std::string& pswrd = "");

    // Method to capture user input
    void inputCredentials();

    // Method for authentication
    bool authenticate();

    // Method to create an account
    bool createAccount(const std::string& tempUsername, const std::string& tempPassword);

    // Method to logout
    void logout();

    // Method to exit the program
    void exit();
};

// Function to capture user action
std::string captureUserAction();

// Function to handle the user interface logic
void runUserInterface();

#endif // WELCOMEPAGE_HPP