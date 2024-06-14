//this db uses filename as a placeholder, however, filename is already a placeholder for userDatabase
//Ill replace filename with filename2 and define it in the main function
//ill add a .json file to correspond with this
#include "bookdatabase.h"
#include <fstream>
#include <iostream>

// Add a book to the database
void BookDatabase::addBook(const Book &book) {
    books.push_back(book);
}

// Remove a book from the database by ISBN
void BookDatabase::removeBook(const std::string &isbn) {
    books.remove_if([&](const Book &book) { return book.toJson().at("isbn") == isbn; });
}

// Load book data from a JSON file
void BookDatabase::loadFromFile(const std::string &filename2) {
    std::ifstream file(filename2);
    if (file.is_open()) {
        json j;
        file >> j;
        books.clear();
        for (const auto &item : j) {
            books.push_back(Book::fromJson(item));
        }
    }
}

// Save book data to a JSON file
void BookDatabase::saveToFile(const std::string &filename2) const {
    json j;
    for (const auto &book : books) {
        j.push_back(book.toJson());
    }
    std::ofstream file(filename2);
    if (file.is_open()) {
        file << j.dump(4); // Dump with 4 spaces for indentation
    }
}

// Print details of all books in the database
void BookDatabase::printAllBooks() const {
    for (const auto &book : books) {
        book.print();
        std::cout << "-------------------------" << std::endl;
    }
}

// Check if a book is available in the database by ISBN
bool BookDatabase::isBookAvailable(const std::string &isbn) const {
    for (const auto &book : books) {
        if (book.toJson().at("isbn") == isbn) {
            return true;
        }
    }
    return false;
}

// Get a book from the database by ISBN
Book BookDatabase::getBookByISBN(const std::string &isbn) const {
    for (const auto &book : books) {
        if (book.toJson().at("isbn") == isbn) {
            return book;
        }
    }
    throw std::runtime_error("Book not found");
}
