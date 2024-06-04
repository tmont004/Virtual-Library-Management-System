#include "book.h"
#include <iostream>

// Constructor to initialize Book object with provided title, author, and ISBN
Book::Book(const std::string &title, const std::string &author, const std::string &isbn)
    : title(title), author(author), isbn(isbn) {}

// Convert Book object to JSON format
json Book::toJson() const {
    return json{{"title", title}, {"author", author}, {"isbn", isbn}};
}

// Create Book object from JSON data
Book Book::fromJson(const json &j) {
    return Book(j.at("title").get<std::string>(), j.at("author").get<std::string>(), j.at("isbn").get<std::string>());
}

// Print details of the Book object
void Book::print() const {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
}
