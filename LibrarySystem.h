#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <iostream>
#include <unordered_map>
#include <queue>
#include "user_system.hpp"
#include "Book.h"
#include "bookdatabase.h" // Include the BookDatabase header
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

// LibrarySystem class definition
class LibrarySystem {
public:
    // Constructor to initialize the userInfo
    LibrarySystem(const UserInfo& userInfo);

    // Method to run the library system
    void run();

    // Methods for book management
    void addBook();
    void searchBooks();
    void viewLibrary() const;

    // Methods for user and admin management
    bool operator==(const string &title) const;
    void borrowBook(const string& bookTitle);
    void returnBook(const string& bookTitle);
    string getTitle() const;

    // Setters for book details
    void setTitle(const string &title);
    void setAuthor(const string &author);
    void setCopiesInStock(int copies);

private:
    // Data structures
    unordered_map<string, User> users;
    queue<string> checkoutQueue;
    BookDatabase bookDatabase; // Add an instance of BookDatabase
    UserInfo userInfo; // Add an instance of UserInfo

    void removeBook();
    void updateBook();

    // Methods for loading and saving data
    void loadFromFile();
    void saveToFile();
    
    // Methods for menu handling after login
    void userOrAdminMenu();
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
