#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "json.hpp" // Include JSON library

using json = nlohmann::json; // Alias for JSON namespace

class Book {
public:
    // Constructor to initialize a Book object with provided title, author, and ISBN
    Book(const std::string &title = "", const std::string &author = "", const std::string &isbn = "");

    // Convert Book object to JSON format
    json toJson() const;

    // Create Book object from JSON data
    static Book fromJson(const json &j);

    // Print details of the Book object
    void print() const;

    std::string title; // Title of the book
    std::string author; // Author of the book
    std::string isbn; // ISBN (International Standard Book Number) of the book
    std::int copiesInStock;
    bool isBorrowed; // Checks to see if book is available for borrowing
};

#endif
