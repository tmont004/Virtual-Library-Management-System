//Name: William Denson, Constantine Ewan, Taylor Montgomery, Cesar Ortiz Machin, John Parker, Riley Pence
//Description:  Week 8 Project: Virtual Library Management System
//Date:  06/29/2024

#include <iostream>
#include <string>
#include "LibrarySystem.h"
#include "user_system.hpp" // Logic for the welcome page
#include "globals.h"

string filename = "userDatabase.json";

// Main function: Entry point of the program
int main() {
    // Create the UserRegistry instance with the specified file
    UserRegistry userRegistry(filename);
    
    string loggedInUsername;
    // Run the user interface and capture the username of the logged-in user
    if (runUserInterface(userRegistry, loggedInUsername)) {
        // Create a UserInfo object with the logged-in username
        UserInfo userInfo(loggedInUsername, userRegistry);
        
        // Create a LibrarySystem object with the UserInfo
        LibrarySystem librarySystem(userInfo);
        
        // Run the library system
        librarySystem.run();
    }
    
    return 0;
}