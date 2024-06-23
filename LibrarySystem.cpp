#include "LibrarySystem.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
#include "globals.h"

using namespace std;
using json = nlohmann::json;

string filename2 = "bookDB.json";

// Constructor to initialize the userInfo
LibrarySystem::LibrarySystem(const UserInfo& userInfo) : userInfo(userInfo) {}

// Method to run the library system
void LibrarySystem::run() {
    bookDatabase.loadFromFile(filename2);  // Load data from files
    userOrAdminMenu(); // Display menu after successful login
    bookDatabase.saveToFile(filename2);    // Save data to files
}

// Method to display the user or admin menu after login
void LibrarySystem::userOrAdminMenu() {
    
    // Get the username and admin status from the UserInfo instance
    string userName = userInfo.getUsername();
    
    bool isAdmin = userInfo.isAdmin();

    

    // Check if the user is an admin or a regular user
    if (isAdmin) {
        adminMenu();
    } else {
        userMenu(userName);
    }
}

void LibrarySystem::borrowBook(const string& bookTitle) {
    cout << "Borrowing book: " << bookTitle << endl;
}

void LibrarySystem::returnBook(const string& bookTitle) {
    cout << "Returning book: " << bookTitle << endl;
}

void LibrarySystem::searchBooks() {
    cout << "Searching for books..." << endl;
}

string LibrarySystem::getTitle() const {
    string title = "a title";
    return title;
}

void LibrarySystem::viewLibrary() const {
    cout << "pretend that this is the library" << endl;
}

void LibrarySystem::userMenu(const string& userName) {
    int choice;
    do {
        
        cout << "You are logged in as " << userName << " this is for testing" << endl;
        cout << "User Menu\n";
        cout << "1. Search for Books\n2. Borrow a Book\n3. Return a Book\n4. View Borrowed Books\n5. Add a Book\n6. View Library\n7. Admin Menu\n8. Logout\n";
        cin >> choice;
        switch (choice) {
            case 1:
                searchBooks();
                break;
            case 2: {
                string bookTitle;
                cout << "Enter the title of the book to borrow: ";
                cin.ignore();
                getline(cin, bookTitle);
                borrowBook(bookTitle);
                break;
            }
            case 3: {
                string bookTitle;
                cout << "Enter the title of the book to return: ";
                cin.ignore();
                getline(cin, bookTitle);
                returnBook(bookTitle);
                break;
            }
            case 4:
                // users[username].viewBorrowedBooks();
                break;
            case 5:
                addBook();
                break;
            case 6:
                bookDatabase.printAllBooks();
                break;
            case 7:
                adminMenu();
                break;
            case 8:
                cout << "Logged out.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);
}

void LibrarySystem::adminMenu() {
    int choice;
    do {
        cout << "Admin Dashboard\n";
        cout << "1. Add a Book\n2. Remove a Book\n3. Update Book Information\n4. Logout\n";
        cin >> choice;
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                removeBook();
                break;
            case 3:
                updateBook();
                break;
            case 4:
                cout << "Logged out.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

void LibrarySystem::addBook() {
    cout << "Enter book information\n";
    string title, author, isbn;
    int copiesInStock;

    cin.ignore(); // To clear the newline character left by previous input
    cout << "Enter book title: ";
    getline(cin, title);
    cout << "Enter author: ";
    getline(cin, author);
    cout << "Enter ISBN: ";
    getline(cin, isbn);
    cout << "Enter number of copies: ";
    cin >> copiesInStock;

    Book newBook(title, author, isbn, copiesInStock);

    if (bookDatabase.isBookAvailable(isbn)) {
        cout << "Book with this ISBN already exists.\n";
    } else {
        bookDatabase.addBook(newBook);
        cout << "Book added successfully.\n";
    }
}

void LibrarySystem::removeBook() {
    string isbn;
    cout << "Enter ISBN of the book to remove: ";
    cin >> isbn;

    if (bookDatabase.isBookAvailable(isbn)) {
        bookDatabase.removeBook(isbn);
        cout << "Book removed successfully.\n";
    } else {
        cout << "Book not found.\n";
    }
}

void LibrarySystem::updateBook() {
    string isbn, title, author;
    int copiesInStock;
    cout << "Enter ISBN of the book to update: ";
    cin >> isbn;

    if (bookDatabase.isBookAvailable(isbn)) {
        cout << "Enter new title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter new author: ";
        getline(cin, author);
        cout << "Enter number of copies in stock: ";
        cin >> copiesInStock;

        bookDatabase.updateBook(isbn, title, author, copiesInStock);
        cout << "Book updated successfully.\n";
    } else {
        cout << "Book not found.\n";
    }
}

bool LibrarySystem::operator==(const string &title) const {
    return this->getTitle() == title;
}

int LibrarySystem::getNoOfCopiesInStock() const {
    return copiesInStock;
}

void LibrarySystem::updateInStock(int num) {
    copiesInStock += num;
}

void LibrarySystem::setCopiesInStock(int num) {
    copiesInStock = num;
}
