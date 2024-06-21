#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <iostream>
#include <unordered_map>
#include <queue>
#include "user_system.hpp" // Changed from user.h to user_system.hpp
#include "Book.h"
#include "BinarySearchTree.h"
#include "json.hpp"

// Use the std namespace
using namespace std;
using json = nlohmann::json;

// LibrarySystem class definition
class LibrarySystem {
public:
    // Method to run the library system
    void run();

    // Methods for book management
    void addBook();
    void removeBook();
    void updateBook();
    void searchBooks();
    void viewLibrary() const;

    // Methods for user and admin management
    bool operator==(const string &title) const;
    void borrowBook(const string& bookTitle);  // Corrected the parameter name
    void returnBook(const string& bookTitle);  // Corrected the parameter name
    string getTitle() const;

    // Setters for book details
    void setTitle(const string &title);
    void setAuthor(const string &author);
    void setCopiesInStock(int copies);

private:
    // Data structures
    BookBST bookTree; // Use BookBST for managing books
    unordered_map<string, User> users;  // HashMap to store users
    unordered_map<string, Book> books;  // HashMap to store books
    queue<string> checkoutQueue;        // Queue to manage book borrowing

    // Methods for loading and saving data
    void loadFromFile();
    void saveToFile();
    
    // Methods for menu handling after login
    void userOrAdminMenu(); // New method to decide between user and admin menu
    void userMenu(const string& username);
    void adminMenu();

    // Additional member variables
    string title;
    string author;
    int copiesInStock;

    // Additional optional functions
    int getNoOfCopiesInStock() const;
    bool checkTitle(const string& title);
    void updateInStock(int num);
};

#endif // LIBRARYSYSTEM_H

