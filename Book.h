#ifndef BOOK_H
#define BOOK_H

#include <string>

// Book class definition
class Book {
public:
    Book() = default;  // Default constructor
    Book(const std::string& title, const std::string& author, const std::string& isbn);  // Parameterized constructor

    std::string getTitle() const;  // Get book title
    std::string getAuthor() const;  // Get book author
    std::string getISBN() const;  // Get book ISBN

    void updateBookInfo(const std::string& title, const std::string& author);  // Update book information

private:
    std::string title;  // Book title
    std::string author;  // Book author
    std::string isbn;  // Book ISBN
};

#endif // BOOK_H
