#ifndef LIBRARY_MANAGEMENT_SYSTEM_H
#define LIBRARY_MANAGEMENT_SYSTEM_H

#include <string>
#include <iostream>

class Book {
public:
    int id;
    std::string title;
    std::string author;
    bool isBorrowed;

    Book(int id, const std::string& title, const std::string& author);
};

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
    BSTNode* findBook(BSTNode* node, int id) const;

public:
    BookBST();
    void addBook(Book* book);
    void displayBooks() const;
    Book* searchBook(int id) const;
};

#endif //LIBRARY_MANAGEMENT_SYSTEM_H