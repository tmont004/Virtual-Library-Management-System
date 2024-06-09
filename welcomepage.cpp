#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include "json.hpp"
#include "welcomepage.hpp"

using namespace std;
using json = nlohmann::json;

// Define the external database variable
unordered_map<string, string> userDatabase;

// Function to load the user database from a JSON file
void loadDatabase(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        json jsonData;
        if (file.peek() == ifstream::traits_type::eof()) {
            // File is empty, initialize with empty JSON object
            jsonData = json::object();
        } else {
            try {
                file >> jsonData;
            } catch (json::parse_error& e) {
                cerr << "Error parsing JSON: " << e.what() << endl;
                return;
            }
        }
        file.close();

        userDatabase.clear();
        for (auto& [key, value] : jsonData.items()) {
            userDatabase[key] = value;
        }
        cout << "Database loaded successfully." << endl;
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

// Function to save the user database to a JSON file
void saveDatabase(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        json jsonData(userDatabase);
        file << jsonData.dump(4); // Pretty print with 4 spaces
        file.close();
        cout << "Database saved successfully." << endl;
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

// Class representing the welcome page

// Constructor
WelcomePage::WelcomePage(const string& usr, const string& pswrd) 
    : username(usr), password(pswrd) {}

// Method to capture user input
void WelcomePage::inputCredentials() {
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
}

// Method for authentication
bool WelcomePage::authenticate() {
    auto it = userDatabase.find(username);
    if (it != userDatabase.end() && it->second == password) {
        return true;
    } else {
        return false;
    }
}

// Method to create an account
bool WelcomePage::createAccount(const string& tempUsername, const string& tempPassword) {
    if (userDatabase.find(tempUsername) == userDatabase.end()) {
        userDatabase[tempUsername] = tempPassword;
        return true;
    } else {
        return false; // Username already exists
    }
}

// Method to logout
void WelcomePage::logout() {
    username.clear();
    password.clear();
    cout << "Logged out and returned to welcome page.\n";
}

// Method to exit the program
void WelcomePage::exit() {
    cout << "Exiting the program.\n";
    std::exit(0);
}

// Function to capture user action
string captureUserAction() {
    string action;
    cout << "Enter action (login, register, logout, exit): ";
    cin >> action;
    return action;
}

// Function to handle the user interface logic
void runUserInterface() {
    const string dbFilename = "authenticationBank.json"; // Filename for the JSON file

    // Load the database from the file
    loadDatabase(dbFilename);

    WelcomePage user;

    while (true) {
        string action = captureUserAction(); // Login, Register, Logout, Exit

        if (action == "login") {
            user.inputCredentials();
            if (user.authenticate()) {
                cout << "Authentication successful. Welcome!\n";
            } else {
                cout << "Authentication failed. Please try again.\n";
            }
        } else if (action == "register") {
            string username, password;
            cout << "Enter new username: ";
            cin >> username;
            cout << "Enter new password: ";
            cin >> password;
            if (user.createAccount(username, password)) {
                // Save the updated database to the file
                saveDatabase(dbFilename);
                cout << "Account creation successful.\n";
            } else {
                cout << "Username already exists.\n";
            }
        } else if (action == "logout") {
            user.logout();
        } else if (action == "exit") {
            user.exit();
        } else {
            cout << "Invalid action. Please try again.\n";
        }
    }
}
