#include "LibrarySystem.h"
#include "BinarySearchTree.h"
#include <fstream>
#include <iostream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

// Method to run the library system
void LibrarySystem::run() {
    loadFromFile();  // Load data from files
    userOrAdminMenu(); // Display menu after successful login
    saveToFile();    // Save data to files
}

// Method to display the user or admin menu after login
void LibrarySystem::userOrAdminMenu() {
    // Assuming the login details are already validated before calling this function
    string username; // You should pass the username from the login context
    bool isAdmin = false; // You should get this information from the login context

    // Check if the user is an admin or a regular user
    if (isAdmin) {
        adminMenu();
    } else {
        userMenu(username);
    }
}

// Method to load data from files
void LibrarySystem::loadFromFile() {
    ifstream userFile("userDatabase.json");
    ifstream bookFile("bookDB.json");

    if (userFile.is_open() && bookFile.is_open()) {
        json userData, bookData;
        userFile >> userData;
        bookFile >> bookData;

        for (auto& [key, value] : userData.items()) {
            users[key] = User(value["username"], value["password"], value["isAdmin"]);
        }

        for (auto& [key, value] : bookData.items()) {
            books[key] = Book(value["title"], value["author"], value["isbn"], value["copiesInStock"]);
        }

        userFile.close();
        bookFile.close();
    } else {
        cerr << "Error opening files for loading data.\n";
    }
}

// Method to save data to files
void LibrarySystem::saveToFile() {
    ofstream userFile("userDatabase.json");
    ofstream bookFile("bookDB.json");

    if (userFile.is_open() && bookFile.is_open()) {
        json userData, bookData;

        for (const auto& [key, user] : users) {
            userData[key] = { {"username", user.getUsername()}, {"password", user.getPassword()}, {"isAdmin", user.isAdminUser()} };
        }

        for (const auto& [key, book] : books) {
            bookData[key] = { {"title", book.getTitle()}, {"author", book.getAuthor()}, {"isbn", book.getISBN()}, {"copiesInStock", book.getCopiesInStock()} };
        }

        userFile << userData.dump(4);
        bookFile << bookData.dump(4);

        userFile.close();
        bookFile.close();
    } else {
        cerr << "Error opening files for saving data.\n";
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

void LibrarySystem::userMenu(const string& username) {
    int choice;
    do {
        cout << "User Menu\n";
        cout << "1. Search for Books\n2. Borrow a Book\n3. Return a Book\n4. View Borrowed Books\n5. Add a Book\n6. View Library\n7. Admin Menu\n8. Logout\n";
        cin >> choice;
        switch (choice) {
            case 1:
                searchBooks();  // Handle book search
                break;
            case 2: {
                string bookTitle;
                cout << "Enter the title of the book to borrow: ";
                cin.ignore();
                getline(cin, bookTitle);
                borrowBook(bookTitle);  // Handle book borrowing
                break;
            }
            case 3: {
                string bookTitle;
                cout << "Enter the title of the book to return: ";
                cin.ignore();
                getline(cin, bookTitle);
                returnBook(bookTitle);  // Handle book returning
                break;
            }
            case 4:
                // users[username].viewBorrowedBooks();  // View borrowed books
                break;
            case 5:
                addBook();  // Handle adding a book
                break;
            case 6:
                viewLibrary();  // Handle viewing the library
                break;
            case 7:
                adminMenu();  // Handle displaying the admin menu
                break;
            case 8:
                cout << "Logged out.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);
}

// Method to display admin menu
void LibrarySystem::adminMenu() {
    int choice;
    do {
        cout << "Admin Dashboard\n";
        cout << "1. Add a Book\n2. Remove a Book\n3. Update Book Information\n4. Logout\n";
        cin >> choice;
        switch (choice) {
            case 1:
                addBook();  // Handle adding a book
                break;
            case 2:
                removeBook();  // Handle removing a book
                break;
            case 3:
                updateBook();  // Handle updating book information
                break;
            case 4:
                cout << "Logged out.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

// Method to add a book to the library
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

    // Create a new Book object
    Book newBook(title, author, isbn, copiesInStock);

    // Check if the book with the given ISBN already exists using search
    if (books.find(isbn) != books.end()) {
        cout << "Book with this ISBN already exists.\n";
    } else {
        books[isbn] = newBook; // Add the new book to the map
        cout << "Book added successfully.\n";
    }
}

// Method to remove a book from the library
void LibrarySystem::removeBook() {
    string isbn;
    cout << "Enter ISBN of the book to remove: ";
    cin >> isbn;

    // Check if the book exists
    if (books.find(isbn) != books.end()) {
        books.erase(isbn);  // Remove the book
        cout << "Book removed successfully.\n";
    } else {
        cout << "Book not found.\n";
    }
}

// Method to update book information
void LibrarySystem::updateBook() {
    string isbn, title, author;
    int copiesInStock;
    cout << "Enter ISBN of the book to update: ";
    cin >> isbn;

    if (books.find(isbn) != books.end()) {
        cout << "Enter new title: ";
        cin.ignore(); // Ignore the newline character left by previous input
        getline(cin, title);
        cout << "Enter new author: ";
        getline(cin, author);
        cout << "Enter number of copies in stock: ";
        cin >> copiesInStock;

        books[isbn].setTitle(title);
        books[isbn].setAuthor(author);
        books[isbn].setCopiesInStock(copiesInStock);
        cout << "Book updated successfully.\n";
    } else {
        cout << "Book not found.\n";
    }
}

bool LibrarySystem::operator==(const string &title) const {
    // Assuming the class has a member function or variable to get the title.
    return this->getTitle() == title;
}

int LibrarySystem::getNoOfCopiesInStock() const {
    return copiesInStock;  // This variable is from "Book.h"; am wondering if a scope :: is needed to pull from the Book class?
}

bool LibrarySystem::checkTitle(const string& title) {
    // This function should probably check titles of books within the LibrarySystem's collection
    for (const auto& pair : books) {
        if (pair.second.getTitle() == title) {
            return true;
        }
    }
    return false;
}

void LibrarySystem::updateInStock(int num) {
    copiesInStock += num;
}

void LibrarySystem::setCopiesInStock(int num) {
    copiesInStock = num;
}
