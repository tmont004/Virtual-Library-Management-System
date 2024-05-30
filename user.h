#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

// User class definition
class User {
public:
    User() = default;  // Default constructor
    User(const std::string& username, const std::string& password, bool isAdmin);  // Parameterized constructor

    std::string getUsername() const;  // Get username
    bool checkPassword(const std::string& password) const;  // Check password
    bool isAdmin() const;  // Check if the user is an admin

    void borrowBook(const std::string& bookTitle);  // Borrow a book
    void returnBook(const std::string& bookTitle);  // Return a book
    void viewBorrowedBooks() const;  // View borrowed books

private:
    std::string username;  // Username
    std::string password;  // Password
    bool admin;            // Admin flag
    std::vector<std::string> borrowedBooks;  // List of borrowed books
};

#endif // USER_H
