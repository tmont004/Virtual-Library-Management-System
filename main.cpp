//Name: William Denson, Constantine Ewan, Taylor Montgomery, Cesar Ortiz Machin, John Parker, Riley Pence
//Description:  Week 8 Project: Virtual Library Management System
//Date:  06/29/2024

#include <iostream>
#include <string>
#include "LibrarySystem.h"
#include "welcomepage.hpp" // logic for the welcome page

string filename = "userDatabase.json";

// Main function: Entry point of the program
int main() {
    
    // Create the UserRegistry instance with the specified file
    UserRegistry userRegistry(filename);
    
     
        //this runs the user interface and this function returns a bool value
     if (runUserInterface(userRegistry) == true) {
        cout << "welcome" << endl;
        cout << "pretend this is the library system" << endl;
    }
    
    // Create a LibrarySystem object
    LibrarySystem library;
    // Run the library system
    library.run();
    return 0;
}
