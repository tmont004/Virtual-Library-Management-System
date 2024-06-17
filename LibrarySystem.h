#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <iostream>
#include <unordered_map>
#include <queue>
#include "user_system.hpp" // user.h file is depracated, changed it
#include "Book.h"
#include "BinarySearchTree.h"

// LibrarySystem class definition
class LibrarySystem {
public:
    // Method to run the library system
    void run();

    void addBook();  //(need to be updated)
    void removeBook();  //(need to be updated)
    void updateBook();  //(need to be updated)
    // void searchBooks();  //(need to be updated)
    bool operator==(const std::string &title) const;

    void borrowBook(const std::string& username); //this needs a definition
    void returnBook(const std::string& username); // this needs a definition
    void searchBooks();  //this needs a definition
    std::string getTitle() const; //this needs a definition
    
    

    void setTitle(const std::string &title);
    void setAuthor(const std::string &author);
    void setCopiesInStock(int copies);

private:

    BookBST bookTree; // Use BookBST for managing books

    std::unordered_map<std::string, User> users;  // HashMap to store users (need to be updated)
    std::unordered_map<std::string, Book> books;  // HashMap to store books (need to be updated)
    std::queue<std::string> checkoutQueue;        // Queue to manage book borrowing (need to be updated)

    // Methods for loading and saving data
    void loadFromFile(); //(need to be updated)
    void saveToFile();  //(need to be updated)
    
    
    void userMenu(const std::string& username);  //(need to be updated)
    void adminMenu();  //(need to be updated)
    
   
    
    std::string title;
    std::string author;
    int copiesInStock;
    

    // Additional optional functions
    int getNoOfCopiesInStock() const;
    bool checkTitle(std::string title);            // ADT to compliment searchBooks()?
    void updateInStock(int num);
    

};

#endif // LIBRARYSYSTEM_H
