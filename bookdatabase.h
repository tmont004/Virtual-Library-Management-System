#ifndef BOOKDATABASE_H
#define BOOKDATABASE_H

#include <list>
#include <memory>
#include <string>
#include "Book.h" // book.h will throw an error, changed it to Book.h 
#include "json.hpp" // Include JSON library

using json = nlohmann::json; // Alias for JSON namespace

class BookDatabase {
public:
    // Add a book to the database
    void addBook(const Book &book);

    // Remove a book from the database by ISBN
    void removeBook(const std::string &isbn);

    // Load book data from a JSON file
    void loadFromFile(const std::string &filename);

    // Save book data to a JSON file
    void saveToFile(const std::string &filename) const;

    // Print details of all books in the database
    void printAllBooks() const;

    // Check if a book is available in the database by ISBN
    bool isBookAvailable(const std::string &isbn) const;

    // Get a book from the database by ISBN
    Book getBookByISBN(const std::string &isbn) const;

private:
    std::list<Book> books; // List to store Book objects
};

#endif
