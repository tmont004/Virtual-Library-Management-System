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
    std::ifstream userFile("userDatabase.json");
    std::ifstream bookFile("bookDB.json");

    if (userFile.is_open() && bookFile.is_open()) {
        nlohmann::json userData, bookData;
        userFile >> userData;
        bookFile >> bookData;

        for (auto& [key, value] : userData.items()) {
            users[key] = User(value["username"], value["firstName"], value["lastName"], value["phoneNumber"], value["address"], value["birthday"], value["password"], value["isAdmin"]);
        }

        for (auto& [key, value] : bookData.items()) {
            books[key] = Book(value["title"], value["author"], value["isbn"], value["copiesInStock"]);
        }

        userFile.close();
        bookFile.close();
    } else {
        std::cerr << "Error opening files for loading data.\n";
    }
}

// Method to save data to files
void LibrarySystem::saveToFile() {
    std::ofstream userFile("userDatabase.json");
    std::ofstream bookFile("bookDB.json");

    if (userFile.is_open() && bookFile.is_open()) {
        nlohmann::json userData, bookData;

        for (const auto& [key, user] : users) {
            userData[key] = { {"username", user.getUsername()}, {"password", user.getPassword()}, {"isAdmin", user.isAdmin()} };
        }

        for (const auto& [key, book] : books) {
            bookData[key] = { {"title", book.getTitle()}, {"author", book.getAuthor()}, {"isbn", book.getISBN()}, {"copiesInStock", book.getCopiesInStock()} };
        }

        userFile << userData.dump(4);
        bookFile << bookData.dump(4);

        userFile.close();
        bookFile.close();
    } else {
        std::cerr << "Error opening files for saving data.\n";
    }
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
    int copiesInStock;

    std::cin.ignore(); // To clear the newline character left by previous input
    std::cout << "Enter book title: ";
    std::getline(std::cin, title);
    std::cout << "Enter author: ";
    std::getline(std::cin, author);
    std::cout << "Enter ISBN: ";
    std::getline(std::cin, isbn);
    std::cout << "Enter number of copies: ";
    std::cin >> copiesInStock;

    // Create a new Book object
    Book* newBook = new Book(title, author, isbn, copiesInStock);

    // Check if the book with the given ISBN already exists using search
    if (bookTree.searchBook(isbn)) {
        std::cout << "Book with this ISBN already exists.\n";
        delete newBook; // Avoid memory leak
    } else {
        bookTree.addBook(newBook); // Add the new book to the BST
        std::cout << "Book added successfully.\n";
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

// Method to update book information
void LibrarySystem::updateBook() {
    std::string isbn, title, author;
    int copiesInStock;
    std::cout << "Enter ISBN of the book to update: ";
    std::cin >> isbn;

    if (books.find(isbn) != books.end()) {
        std::cout << "Enter new title: ";
        std::cin.ignore(); // Ignore the newline character left by previous input
        std::getline(std::cin, title);
        std::cout << "Enter new author: ";
        std::getline(std::cin, author);
        std::cout << "Enter number of copies in stock: ";
        std::cin >> copiesInStock;

        books[isbn].setTitle(title);
        books[isbn].setAuthor(author);
        books[isbn].setCopiesInStock(copiesInStock);
        std::cout << "Book updated successfully.\n";
    } else {
        std::cout << "Book not found.\n";
    }
}

bool LibrarySystem::operator==(const std::string &title) const {
    // Assuming the class has a member function or variable to get the title.
    return this->getTitle() == title;
}


//-------------------------------------------------------
int LibrarySystem::getNoOfCopiesInStock() const
{
    return copiesInStock;                        // This variable is from "Book.h"; am wondering if a scope :: is needed to pull from the Book class?
}

bool LibrarySystem::checkTitle(std::string title) {
    // This function should probably check titles of books within the LibrarySystem's collection
    for (const auto& pair : books) {
        if (pair.second.getTitle() == title) {
            return true;
        }
    }
    return false;
}

void LibrarySystem::updateInStock(int num)
{
    copiesInStock += num;
}

void LibrarySystem::setCopiesInStock(int num)
{
    copiesInStock = num;
}
