#include "LibrarySystem.h"
#include <fstream>
#include <iostream>
#include <iomanip> 
#include <limits>
#include "json.hpp"
#include "globals.h"
#include <csignal>   // For signal handling
#include <cstdlib>   // For exit()


using namespace std;
using json = nlohmann::json;

string bookDB = "bookDB.json";
extern std::string bookDB;
string borrowedBooksFilename = "borrowedBooksDB.json";
string queueFilename = "bookWaitlistDB.json";

// Global flag to indicate if termination signal received
volatile sig_atomic_t terminationSignalReceived = 0;

// Constructor to initialize the userInfo
LibrarySystem::LibrarySystem(const UserInfo& userInfo) : userInfo(userInfo) {}

// Method to run the library system
void LibrarySystem::run() {
    bookDatabase.loadFromFile(bookDB);  // Load data from files
    userOrAdminMenu(); // Display menu after successful login
    bookDatabase.saveToFile(bookDB);    // Save data to files
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

void LibrarySystem::userMenu(const string& userName) {
    int choice;
    do {
        // Pause for user to read output before continuing
        pressEnterToContinue();

        clearScreen();
        cout << "Welcome, " << " User: " << userName << endl;
        cout << "===============================" << endl;
        cout << "User Menu" << endl;
        cout << "1. Search for Books" << endl;
        cout << "2. Borrow a Book" << endl;
        cout << "3. Return a Book" << endl;
        cout << "4. View Borrowed Books" << endl;
        cout << "5. Add a Book" << endl;
        cout << "6. View Library" << endl;
        cout << "7. Logout" << endl;
        cout << "===============================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                searchBooks();
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                // viewBorrowedBooks();
                break;
            case 5:
                addBook();
                break;
            case 6:
                viewLibrary();
                break;
            case 7:
                cout << "Logged out." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != 7);
}

void LibrarySystem::returnBook() {
    string bookTitle;
    cout << "Enter the title of the book to return: ";
    cin.ignore();
    getline(cin, bookTitle);
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

void LibrarySystem::adminMenu() {
    int choice;
    do {

        // Pause for user to read output before continuing
        pressEnterToContinue();

        clearScreen();
        cout << "Welcome, " << endl; //<< " Admin: " << userName << endl;
        cout << "===============================" << endl;
        cout << "1. Add a Book" << endl;
        cout << "2. Remove a Book" << endl;
        cout << "3. Update Book Information" << endl;
        cout << "4. Logout" << endl;
        cout << "===============================" << endl;
        cout << "Enter your choice: ";
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
                cout << "Logged out." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
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

    Book newBook(title, author, isbn, copiesInStock); //this is a book object, we have to reference this object

    if (bookDatabase.isBookAvailable(isbn)) {
        cout << "Book with this ISBN already exists.\n";
    } else {
        bookDatabase.addBook(newBook);
        cout << "Book added successfully.\n";
    }
}

void LibrarySystem::borrowBook() {
    string bookTitle;
    cout << "Enter the title of the book to borrow: ";
    cin.ignore();
    getline(cin, bookTitle);

    cout << "Borrowing book: " << bookTitle << endl;

    // Find the book in the book database
    Book book;
    try {
        book = bookDatabase.findBookByTitle(bookTitle);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        return;
    }

    // Check if the book was found
    if (book.getTitle().empty()) {
        cout << "Error: Book with title '" << bookTitle << "' not found." << endl;
        return;
    }

    // Check if there are copies available
    if (book.getCopiesInStock() <= 0) { //If all copies are already borrowed
        cout << "Error: No copies available for book '" << bookTitle << "'." << endl;

        try {
            // Load the FIFO Queue JSON file
            json bookWaitlist;
            ifstream inFile(queueFilename);
            if (inFile.is_open()) {
                inFile >> bookWaitlist; //Possibly change to input values into the queue member variable
                inFile.close();
        } else {
            throw runtime_error("Failed to open file for reading: " + queueFilename);
        }

        // Get the username
        string username = userInfo.getUsername();

        // Add the user to the book's waitlist
        bookWaitlist[book.getISBN()].push_back(username);

        // Save the updated waitlist JSON file
        ofstream outFile(queueFilename);
        if (outFile.is_open()) {
            outFile << bookWaitlist.dump(4); // Pretty print with 4 spaces
            outFile.close();
        } else {
            throw runtime_error("Failed to open file for writing: " + queueFilename);
        }

        cout << "Added to waitlist queue for '" << bookTitle << ".'" << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
        
        return;
    }

    // Proceed to borrow the book
    try {
        // Decrease the number of copies in stock
        bookDatabase.updateBook(book.getISBN(), book.getTitle(), book.getAuthor(), book.getCopiesInStock() - 1);

        // Load the borrowed books JSON file
        json borrowedBooks;
        ifstream inFile(borrowedBooksFilename);
        if (inFile.is_open()) {
            inFile >> borrowedBooks;
            inFile.close();
        } else {
            throw runtime_error("Failed to open file for reading: " + borrowedBooksFilename);
        }

        // Get the username
        string username = userInfo.getUsername();

        // Add the book to the user's borrowed books list
        borrowedBooks[username].push_back(book.getISBN());

        // Save the updated borrowed books JSON file
        ofstream outFile(borrowedBooksFilename);
        if (outFile.is_open()) {
            outFile << borrowedBooks.dump(4); // Pretty print with 4 spaces
            outFile.close();
        } else {
            throw runtime_error("Failed to open file for writing: " + borrowedBooksFilename);
        }

        cout << "Book '" << bookTitle << "' borrowed successfully." << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}


void LibrarySystem::removeBook() {
    string isbn;
    cout << "Enter ISBN of the book to remove: ";
    cin >> isbn;

    try {
        // Check if the book exists
        if (bookDatabase.isBookAvailable(isbn)) {
            bookDatabase.removeBook(isbn);
            cout << "Book with ISBN " << isbn << " removed successfully.\n";
        } else {
            cout << "Error: Book with ISBN " << isbn << " not found.\n";
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}


void LibrarySystem::updateBook() {
    string isbn, title, author;
    int copiesInStock;

    // Input ISBN and validate it
    cout << "Enter ISBN of the book to update: ";
    cin >> isbn;

    try {
        // Check if the book exists
        if (!bookDatabase.isBookAvailable(isbn)) {
            cout << "Error: Book with ISBN " << isbn << " not found." << endl;
            return;
        }

        // Input new title
        cin.ignore(); // Clear the input buffer
        cout << "Enter new title: ";
        getline(cin, title);

        // Input new author
        cout << "Enter new author: ";
        getline(cin, author);

        // Input number of copies in stock
        cout << "Enter number of copies in stock: ";
        cin >> copiesInStock;

        // Update the book in the database
        bookDatabase.updateBook(isbn, title, author, copiesInStock);
        cout << "Book with ISBN " << isbn << " updated successfully." << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
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

// Utility function to clear the screen
void LibrarySystem::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // Assume POSIX compliant system
    system("clear");
#endif
}

// Utility function to prompt user to press Enter to continue
void LibrarySystem::pressEnterToContinue() {
    cout << "Press Enter to continue...";
    cin.ignore(); // Clear input buffer
    cin.get();    // Wait for Enter key press
}

// Signal handler function
void LibrarySystem::signalHandler(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        terminationSignalReceived = 1;
        std::cout << "Termination signal received. Saving data..." << std::endl;

        // Save data to files before exiting
        // Example: Save book database
        bookDatabase.saveToFile(bookDB);

        // You can add more save operations for other databases if needed

        std::exit(EXIT_SUCCESS);  // Exit gracefully
    }
}