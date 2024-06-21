#include "Book.h"
#include <iostream>

// Constructor to initialize Book object with provided title, author, and ISBN
Book::Book(const std::string& title, const std::string& author, const std::string& isbn, int copiesInStock)
: title(title), author(author), isbn(isbn), copiesInStock(copiesInStock) {}

// Convert Book object to JSON format
json Book::toJson() const {
    return json{{"title", title}, {"author", author}, {"isbn", isbn}, {"copiesInStock", copiesInStock}};
}

// Create Book object from JSON data
Book Book::fromJson(const json &j) {
    return Book(j.at("title").get<std::string>(), j.at("author").get<std::string>(), j.at("isbn").get<std::string>(), j.at("copiesInStock").get<int>());
}

// Print details of the Book object
void Book::print() const {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Copies in Stock: " << copiesInStock << std::endl;
}

std::string Book::getTitle() const {
    return title;
}

void Book::setTitle(const std::string &title) {
    Book::title = title;
}

std::string Book::getAuthor() const {
    return author;
}

void Book::setAuthor(const std::string &author) {
    Book::author = author;
}

std::string Book::getISBN() const {
    return isbn;
}

int Book::getCopiesInStock() const {
    return copiesInStock;
}

void Book::setCopiesInStock(int num) {
    copiesInStock = num;
}

bool Book::operator<(const Book& other) const {
    return this->isbn < other.isbn;
}

bool Book::operator==(const Book& other) const {
    return this->isbn == other.isbn;
}
