#include "Book.h"
#include <iostream>

// Constructor to initialize Book object with provided title, author, and ISBN
Book::Book(const std::string& title, const std::string& author, const std::string& isbn, int copiesInStock)
: title(title), author(author), isbn(isbn), copiesInStock(copiesInStock) {}

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

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getISBN() const {
    return isbn;
}

int Book::getCopiesInStock() const {
    return copiesInStock;
}

bool Book::operator<(const Book& other) const {
    return this->isbn < other.isbn;
}

bool Book::operator==(const Book& other) const {
    return this->isbn == other.isbn;
}