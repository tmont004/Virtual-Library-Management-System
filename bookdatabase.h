#ifndef BOOKDATABASE_H
#define BOOKDATABASE_H

#include <memory>
#include <string>
#include "Book.h"
#include "json.hpp"
#include "globals.h"

using namespace std;
using json = nlohmann::json;

class BookDatabase {
public:
    // Add a book to the database
    void addBook(const Book &book);

    // Remove a book from the database by ISBN
    void removeBook(const std::string &isbn);

    // Load book data from a JSON file
    void loadFromFile(const std::string &filename2);

    // Save book data to a JSON file
    void saveToFile(const std::string &filename2) const;

    // Print details of all books in the database
    void printAllBooks() const;

    // Check if a book is available in the database by ISBN
    bool isBookAvailable(const std::string &isbn) const;

    // Get a book from the database by ISBN
    Book getBookByISBN(const std::string &isbn) const;

    // Update a book's details
    void updateBook(const std::string &isbn, const std::string &title, const std::string &author, int copiesInStock);

    // Find a book by its title
    Book findBookByTitle(const std::string &title) const;

private:
    struct TreeNode {
        Book book;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;

        TreeNode(const Book &book) : book(book), left(nullptr), right(nullptr) {}

        // Disable copy constructor and assignment operator
        TreeNode(const TreeNode&) = delete;
        TreeNode& operator=(const TreeNode&) = delete;

        // Enable move constructor and assignment operator
        TreeNode(TreeNode&&) = default;
        TreeNode& operator=(TreeNode&&) = default;
    };

    std::unique_ptr<TreeNode> root;

    // Helper functions for BST operations
    std::unique_ptr<TreeNode> addBook(std::unique_ptr<TreeNode> node, const Book &book);
    std::unique_ptr<TreeNode> removeBook(std::unique_ptr<TreeNode> node, const std::string &isbn);
    TreeNode* findMin(TreeNode* node) const;
    TreeNode* findBook(TreeNode* node, const std::string &isbn) const;
    void inOrderTraversal(TreeNode* node) const;
    TreeNode* findBookByTitle(TreeNode* node, const std::string &title) const;
};

#endif // BOOKDATABASE_H
