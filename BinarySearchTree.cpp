#include "libraryManagementSystem.h"

// Book class implementation
Book::Book(int id, const std::string& title, const std::string& author)
    : id(id), title(title), author(author), isBorrowed(false) {}

// BSTNode class implementation
BSTNode::BSTNode(Book* book) : book(book), left(nullptr), right(nullptr) {}

// BookBST class implementation
BookBST::BookBST() : root(nullptr) {}

void BookBST::addBook(BSTNode*& node, Book* book) {
    if (node == nullptr) {
        node = new BSTNode(book);
    } else if (book->id < node->book->id) {
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
    std::cout << "ID: " << node->book->id << ", Title: " << node->book->title
              << ", Author: " << node->book->author << ", Borrowed: " << (node->book->isBorrowed ? "Yes" : "No") << std::endl;
    inOrderTraversal(node->right);
}

void BookBST::displayBooks() const {
    inOrderTraversal(root);
}

BSTNode* BookBST::findBook(BSTNode* node, int id) const {
    if (node == nullptr || node->book->id == id) {
        return node;
    } else if (id < node->book->id) {
        return findBook(node->left, id);
    } else {
        return findBook(node->right, id);
    }
}

Book* BookBST::searchBook(int id) const {
    BSTNode* node = findBook(root, id);
    return node ? node->book : nullptr;
}