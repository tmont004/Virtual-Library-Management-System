#include "LibrarySystem.h"
#include <fstream>

// Method to run the library system
void LibrarySystem::run() {
    loadFromFile();  // Load data from files
    preLoginMenu();  // Display pre-login menu
    saveToFile();    // Save data to files
}

// Method to load data from files
void LibrarySystem::loadFromFile() {
    // TODO: Implement file loading for users and books
}

// Method to save data to files
void LibrarySystem::saveToFile() {
    // TODO: Implement file saving for users and books
}

// Method to display pre-login menu
void LibrarySystem::preLoginMenu() {
    int choice;
    do {
        std::cout << "Welcome to the Virtual Library Management System\n";
        std::cout << "1. Login\n2. Register\n3. Exit\n";
        std::cin >> choice;
        switch (choice) {
            case 1:
                login();  // Handle login
                break;
            case 2:
                registerUser();  // Handle user registration
                break;
            case 3:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}
/*
// Method to handle user login
void LibrarySystem::login() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    // Check if the user exists and the password is correct
    if (users.find(username) != users.end() && users[username].checkPassword(password)) {
        if (users[username].isAdmin()) {
            adminMenu();  // Display admin menu if the user is an admin
        } else {
            userMenu(username);  // Display user menu if the user is a standard user
        }
    } else {
        std::cout << "Invalid username or password.\n";
    }
}

// Method to handle user registration
void LibrarySystem::registerUser() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    // Check if the username already exists
    if (users.find(username) == users.end()) {
        users[username] = User(username, password, false);  // Create a new user
        std::cout << "Registration successful.\n";
    } else {
        std::cout << "Username already exists.\n";
    }
}
*/
// Method to display user menu
void LibrarySystem::userMenu(const std::string& username) {
    int choice;
    do {
        std::cout << "User Menu\n";
        std::cout << "1. Search for Books\n2. Borrow a Book\n3. Return a Book\n4. View Borrowed Books\n5. Logout\n";
        std::cin >> choice;
        switch (choice) {
            case 1:
                searchBooks();  // Handle book search
                break;
            case 2:
                borrowBook(username);  // Handle book borrowing
                break;
            case 3:
                returnBook(username);  // Handle book returning
                break;
            case 4:
               // users[username].viewBorrowedBooks();  // View borrowed books
                break;
            case 5:
                std::cout << "Logged out.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}

// Method to display admin menu
void LibrarySystem::adminMenu() {
    int choice;
    do {
        std::cout << "Admin Dashboard\n";
        std::cout << "1. Add a Book\n2. Remove a Book\n3. Update Book Information\n4. Logout\n";
        std::cin >> choice;
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
                std::cout << "Logged out.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

// Method to add a book to the library
void LibrarySystem::addBook() {
    std::string title, author, isbn;
    std::cout << "Enter book title: ";
    std::cin >> title;
    std::cout << "Enter author: ";
    std::cin >> author;
    std::cout << "Enter ISBN: ";
    std::cin >> isbn;

    // Check if the book with the given ISBN already exists
    if (books.find(isbn) == books.end()) {
        books[isbn] = Book(title, author, isbn);  // Add the new book
        std::cout << "Book added successfully.\n";
    } else {
        std::cout << "Book with this ISBN already exists.\n";
    }
}

// Method to remove a book from the library
void LibrarySystem::removeBook() {
    std::string isbn;
    std::cout << "Enter ISBN of the book to remove: ";
    std::cin >> isbn;

    // Check if the book exists
    if (books.find(isbn) != books.end()) {
        books.erase(isbn);  // Remove the book
        std::cout << "Book removed successfully.\n";
    } else {
        std::cout << "Book not found.\n";
    }
}
/*
// Method to update book information
void LibrarySystem::updateBook() {
    std::string isbn, title, author;
    std::cout << "Enter ISBN of the book to update: ";
    std::cin >> isbn;

    // Check if the book exists
    if (books.find(isbn) != books.end()) {
        std
*/