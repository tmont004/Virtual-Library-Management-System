#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <string>
#include <iostream>
#include "Book.h"

class BSTNode {
public:
    Book* book;
    BSTNode* left;
    BSTNode* right;

    explicit BSTNode(Book* book) : book(book), left(nullptr), right(nullptr) {}
};

class BookBST {
private:
    BSTNode* root;

    void addBook(BSTNode*& node, Book* book);
    void inOrderTraversal(BSTNode* node) const;
    BSTNode* findBook(BSTNode* node, const std::string& isbn) const;
    BSTNode* removeBook(BSTNode* node, const std::string& isbn);
    BSTNode* findMin(BSTNode* node) const;

    // Utility functions
    bool isEmpty(BSTNode* node) const;
    int treeHeight(BSTNode* node) const;
    int treeNodeCount(BSTNode* node) const;
    int treeLeavesCount(BSTNode* node) const;
    int height(BSTNode* node) const;
    int max(int x, int y) const;

    // Memory management
    void destroy(BSTNode*& node);
    void destroyTree(BSTNode* node);

public:
    BookBST();
    ~BookBST();

    void addBook(Book* book);
    void removeBook(const std::string& isbn);
    void displayBooks() const;
    Book* searchBook(const std::string& isbn) const;

    bool isEmpty() const;
    int treeHeight() const;
    int treeNodeCount() const;
    int treeLeavesCount() const;
    void destroyTree();
};

#endif // BINARY_SEARCH_TREE_H
