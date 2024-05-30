#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <iostream>
#include <unordered_map>
#include <queue>
#include "User.h"
#include "Book.h"

// LibrarySystem class definition
class LibrarySystem {
public:
    // Method to run the library system
    void run();
private:
    std::unordered_map<std::string, User> users;  // HashMap to store users (need to be updated)
    std::unordered_map<std::string, Book> books;  // HashMap to store books (need to be updated)
    std::queue<std::string> checkoutQueue;        // Queue to manage book borrowing (need to be updated)

    // Methods for loading and saving data
    void loadFromFile(); //(need to be updated)
    void saveToFile();  //(need to be updated)
    
    // Menu methods
    void preLoginMenu();  //(need to be updated)
    void userMenu(const std::string& username);  //(need to be updated)
    void adminMenu();  //(need to be updated)
    
    // User and book management methods
    void login();  //(need to be updated)
    void registerUser();  //(need to be updated)
    void addBook();  //(need to be updated)
    void removeBook();  //(need to be updated)
    void removeBook();  //(need to be updated)
    void updateBook();  //(need to be updated)
    void searchBooks();  //(need to be updated)
    void borrowBook(const std::string& username);  //(need to be updated)
    void returnBook(const std::string& username);  //(need to be updated)
};

#endif // LIBRARYSYSTEM_H
