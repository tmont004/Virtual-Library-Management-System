#include "BinarySearchTree.h"
#include "Book.h"

// Book class implementation
Book::Book(int isbn, const std::string& title, const std::string& author)
    : isbn(isbn), title(title), author(author), isBorrowed(false) {}

// BSTNode class implementation
BSTNode::BSTNode(Book* book) : book(book), left(nullptr), right(nullptr) {}

// BookBST class implementation
BookBST::BookBST() : root(nullptr) {}

void BookBST::addBook(BSTNode*& node, Book* book) {
    if (node == nullptr) {
        node = new BSTNode(book);
    } else if (book->isbn < node->book->isbn {
        addBook(node->left, book);
    } else {
        addBook(node->right, book);
    }
}

void BookBST::addBook(Book* book) {
    addBook(root, book);
}

void BookBST::inOrderTraversal(BSTNode* node) const {
    if (node == nullptr) return;
    inOrderTraversal(node->left);
    std::cout << "ID: " << node->book->isbn << ", Title: " << node->book->title
              << ", Author: " << node->book->author << ", Borrowed: " << (node->book->isBorrowed ? "Yes" : "No") << std::endl;
    inOrderTraversal(node->right);
}

void BookBST::displayBooks() const {
    inOrderTraversal(root);
}

BSTNode* BookBST::findBook(BSTNode* node, std::string isbn) const {
    if (node == nullptr || node->book->isbn == isbn) {
        return node;
    } else if (id < node->book->isbn) {
        return findBook(node->left, isbn);
    } else {
        return findBook(node->right, isbn);
    }
}

Book* BookBST::searchBook(int id) const {
    BSTNode* node = findBook(root, isbn);
    return node ? node->book : nullptr;
}