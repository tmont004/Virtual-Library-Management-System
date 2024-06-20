#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <iostream>
#include <unordered_map>
#include <queue>
#include "user_system.hpp" // Changed from user.h to user_system.hpp
#include "Book.h"
#include "BinarySearchTree.h"

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

    // Methods for user and admin management
    bool operator==(const std::string &title) const;
    void borrowBook(const std::string& bookTitle);  // Corrected the parameter name
    void returnBook(const std::string& bookTitle);  // Corrected the parameter name
    std::string getTitle() const;

    // Setters for book details
    void setTitle(const std::string &title);
    void setAuthor(const std::string &author);
    void setCopiesInStock(int copies);

private:
    // Data structures
    BookBST bookTree; // Use BookBST for managing books
    std::unordered_map<std::string, User> users;  // HashMap to store users
    std::unordered_map<std::string, Book> books;  // HashMap to store books
    std::queue<std::string> checkoutQueue;        // Queue to manage book borrowing

    // Methods for loading and saving data
    void loadFromFile();
    void saveToFile();
    
    // Methods for menu handling after login
    void userOrAdminMenu(); // New method to decide between user and admin menu
    void userMenu(const std::string& username);
    void adminMenu();

    // Additional member variables
    std::string title;
    std::string author;
    int copiesInStock;

    // Additional optional functions
    int getNoOfCopiesInStock() const;
    bool checkTitle(const std::string& title);
    void updateInStock(int num);
};

#endif // LIBRARYSYSTEM_H

