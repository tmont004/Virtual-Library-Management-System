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


//----------------------------------------------------------------
// Public methods con't. for review.

    bool isEmpty() const;
    int treeHeight() const;
    //...


    //-------------------------------------------------------------------------------------------------------
    // Leaf/node count from root could be used to help aid in efficient Big-O algorithm sorting evaluations?
    int treeNodeCount() const;
    int treeLeavesCount() const;
    //-------------------------------------------------------------------------------------------------------
    //...


    //----------------------------------------------------
    // Helping prevent memory leaks and dangling pointers.
    void destroyTree();            // Will delete nodes & set to NULL/nullptr before rearrangement/shuffling and deallocate memory for future dereferencing.

    virtual void insert(const Book* book insertItem) = 0;        // I am not sure if the formal parameter class type/template/data type is correct.

    virtual void deleteNode(const Book* book deleteItem) = 0;

    ~BookBST();
//----------------------------------------------------------------




};

#endif //BINARY_SEARCH_TREE_H
