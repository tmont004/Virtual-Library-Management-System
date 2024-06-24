#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "json.hpp" // Include JSON library
#include "queue.h" //Include the definition for the queue class

using json = nlohmann::json; // Alias for JSON namespace

class Book {
public:
    Book() : copiesInStock(0) {}
    // Constructor to initialize a Book object with provided title, author, and ISBN
    Book(const std::string& title, const std::string& author, const std::string& isbn, int copiesInStock);

    // Convert Book object to JSON format
    json toJson() const;

    // Create Book object from JSON data
    static Book fromJson(const json &j);

    // Print details of the Book object
    void print() const;

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    int getCopiesInStock() const;

    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setCopiesInStock(int copies);

    bool operator<(const Book& other) const;
    bool operator==(const Book& other) const;

private:
    std::string title;
    std::string author;
    std::string isbn;
    int copiesInStock;
    linkedQueueType waitlistQueue;
};

#endif // BOOK_H
