#include <fstream>
#include <iostream>
#include "globals.h"
#include "bookdatabase.h"

using namespace std;

// Load book data from a JSON file
void BookDatabase::loadFromFile(const string &filename2) {
    ifstream file(filename2);
    if (file.is_open()) {
        json j;
        file >> j;
        root.reset();
        for (const auto &item : j) {
            addBook(Book::fromJson(item));
        }
    } else {
        throw runtime_error("Could not open file for reading: " + filename2);
    }
}

// Save book data to a JSON file
void BookDatabase::saveToFile(const string &filename2) const {
    json j;
    function<void(TreeNode*)> saveToJson = [&](TreeNode* node) {
        if (node) {
            j.push_back(node->book.toJson());
            saveToJson(node->left.get());
            saveToJson(node->right.get());
        }
    };
    saveToJson(root.get());
    ofstream file(filename2);
    if (file.is_open()) {
        file << j.dump(4);
    } else {
        throw runtime_error("Could not open file for writing: " + filename2);
    }
}


// Add a book to the database
void BookDatabase::addBook(const Book &book) {
    root = addBook(std::move(root), book);
}

unique_ptr<BookDatabase::TreeNode> BookDatabase::addBook(unique_ptr<TreeNode> node, const Book &book) {
    if (!node) {
        return make_unique<TreeNode>(book);
    }
    if (book.getISBN() < node->book.getISBN()) {
        node->left = addBook(std::move(node->left), book);
    } else {
        node->right = addBook(std::move(node->right), book);
    }
    return node;
}

// Remove a book from the database by ISBN
void BookDatabase::removeBook(const string &isbn) {
    root = removeBook(std::move(root), isbn);
}

unique_ptr<BookDatabase::TreeNode> BookDatabase::removeBook(unique_ptr<TreeNode> node, const string &isbn) {
    if (!node) {
        return nullptr;
    }
    if (isbn < node->book.getISBN()) {
        node->left = removeBook(std::move(node->left), isbn);
    } else if (isbn > node->book.getISBN()) {
        node->right = removeBook(std::move(node->right), isbn);
    } else {
        if (!node->left) {
            return std::move(node->right);
        } else if (!node->right) {
            return std::move(node->left);
        }
        TreeNode* minNode = findMin(node->right.get());
        node->book = minNode->book;
        node->right = removeBook(std::move(node->right), minNode->book.getISBN());
    }
    return node;
}

BookDatabase::TreeNode* BookDatabase::findMin(TreeNode* node) const {
    while (node && node->left) {
        node = node->left.get();
    }
    return node;
}

// Print details of all books in the database
void BookDatabase::printAllBooks() const {
    inOrderTraversal(root.get());
}

void BookDatabase::inOrderTraversal(TreeNode* node) const {
    if (node) {
        inOrderTraversal(node->left.get());
        node->book.print();
        cout << "-------------------------" << endl;
        inOrderTraversal(node->right.get());
    }
}

// Check if a book is available in the database by ISBN
bool BookDatabase::isBookAvailable(const string &isbn) const {
    return findBook(root.get(), isbn) != nullptr;
}

// Get a book from the database by ISBN
Book BookDatabase::getBookByISBN(const string &isbn) const {
    TreeNode* node = findBook(root.get(), isbn);
    if (node) {
        return node->book;
    }
    throw runtime_error("Book with ISBN " + isbn + " not found");
}

BookDatabase::TreeNode* BookDatabase::findBook(TreeNode* node, const string &isbn) const {
    if (!node) {
        return nullptr;
    }
    if (isbn < node->book.getISBN()) {
        return findBook(node->left.get(), isbn);
    } else if (isbn > node->book.getISBN()) {
        return findBook(node->right.get(), isbn);
    } else {
        return node;
    }
}

// Find a book by its title
Book BookDatabase::findBookByTitle(const std::string &title) const {
    TreeNode* node = findBookByTitle(root.get(), title);
    if (node) {
        return node->book;
    }
    throw runtime_error("Book not found");
}

BookDatabase::TreeNode* BookDatabase::findBookByTitle(TreeNode* node, const string &title) const {
    if (!node) {
        return nullptr;
    }
    if (title < node->book.getTitle()) {
        return findBookByTitle(node->left.get(), title);
    } else if (title > node->book.getTitle()) {
        return findBookByTitle(node->right.get(), title);
    } else {
        return node;
    }
}

// Update a book's details
void BookDatabase::updateBook(const string &isbn, const string &title, const string &author, int copiesInStock) {
    TreeNode* node = findBook(root.get(), isbn);
    if (node) {
        node->book.setTitle(title);
        node->book.setAuthor(author);
        node->book.setCopiesInStock(copiesInStock);
    } else {
        cout << "Book not found" << endl;
    }
}
