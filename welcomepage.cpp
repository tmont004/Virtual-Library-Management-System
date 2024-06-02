#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

//stores username-password pairs

//we cant see it, but this is what is making the ordering of the pairs
//the txt file displays this!
unordered_map<string, string> database;

// Function to load the database from a file
void loadDatabase(const string& filename) {
    ifstream file(filename); //open the file for reading
    if (file.is_open()) { //open the file for 
        string username, password; //stores these
        while (file >> username >> password) { //goes through the file
            database[username] = password;  //insert everything into the db
        }
        file.close(); //close the file after reading all pairs
    }
}

// Function to save the database to a file
void saveDatabase(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : database) {
            file << pair.first << " " << pair.second << endl;
        }
        file.close();
    }
}

// Class representing the welcome page
class WelcomePage {
private:
    string username;
    string password;

public:
    // Constructor
    WelcomePage(const string& usr = "", const string& pswrd = "") 
        : username(usr), password(pswrd) {}

    // Method to capture user input
    void inputCredentials() { //promps the user to enter username and password
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
    }

    // Method for authentication
    bool authenticate() {
        auto it = database.find(username);
        if (it != database.end() && it->second == password) {
            return true;
        } else {
            return false;
        }
    }

    // Method to create an account
    bool createAccount(const string& tempUsername, const string& tempPassword) {
        if (database.find(tempUsername) == database.end()) {
            database[tempUsername] = tempPassword;
            return true;
        } else {
            return false; // Username already exists
        }
    }

    // Method to logout
    void logout() {
        username.clear();
        password.clear();
        cout << "Logged out and returned to welcome page.\n";
    }

    // Method to exit the program
    void exit() {
        cout << "Exiting the program.\n";
        std::exit(0);
    }
};

// Function to capture user action
string captureUserAction() {
    string action;
    cout << "Enter action (login, register, logout, exit): ";
    cin >> action;
    return action;
}

// Main function
int main() {
    const string dbFilename = "database.txt"; // this is the filelog

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

    return 0;
}
