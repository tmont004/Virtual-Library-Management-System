#include <iostream>
#include "user.h"
#include "user.cpp"

int main() {
    // Create a UserRegistry object with a JSON filename
    UserRegistry userRegistry("users.json");

    // Load users from JSON file
    userRegistry.loadUsersFromJSON();

    // Add a new user
    User newUser("testuser", "Test", "User", "1234567890", "123 Test St", "01/01/2000", "password", false);
    userRegistry.addUser(newUser);

    // Save users to JSON file
    userRegistry.saveUsersToJSON();

    // Test login functionality
    std::cout << "Login test:" << std::endl;
    std::cout << "Login result: " << (userRegistry.loginUser("testuser", "password") ? "Success" : "Failure") << std::endl;

    // Test promoting a user to admin
    std::cout << "\nPromoting user to admin..." << std::endl;
    userRegistry.promoteToAdmin("testuser");

    // Test if the user is now an admin
    std::cout << "Admin check test:" << std::endl;
    std::cout << "Is admin: " << (userRegistry.isAdmin("testuser") ? "Yes" : "No") << std::endl;

    // Test demoting a user from admin
    std::cout << "\nDemoting user from admin..." << std::endl;
    userRegistry.demoteFromAdmin("testuser");

    // Test if the user is no longer an admin
    std::cout << "Admin check test:" << std::endl;
    std::cout << "Is admin: " << (userRegistry.isAdmin("testuser") ? "Yes" : "No") << std::endl;

    // Test changing user password
    std::cout << "\nChanging user password..." << std::endl;
    userRegistry.changeUserPassword("testuser", "newpassword");

    // Test login with new password
    std::cout << "Login test with new password:" << std::endl;
    std::cout << "Login result: " << (userRegistry.loginUser("testuser", "newpassword") ? "Success" : "Failure") << std::endl;

    return 0;
}