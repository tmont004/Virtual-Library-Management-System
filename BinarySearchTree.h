#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <string>
#include <iostream>
#include "book.h"


class BSTNode {
public:
    Book* book;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Book* book);
};

class BookBST {
private:
    BSTNode* root;

    void addBook(BSTNode*& node, Book* book);
    void inOrderTraversal(BSTNode* node) const;
    BSTNode* findBook(BSTNode* node, std::string isbn) const;

public:
    BookBST();
    void addBook(Book* book);
    void displayBooks() const;
    Book* searchBook(std::string isbn) const;
};

#endif //BINARY_SEARCH_TREE_H