#include "BinarySearchTree.h"
#include "Book.h"

// Book class implementation
Book::Book(std::string isbn, const std::string& title, const std::string& author)
    : isbn(isbn), title(title), author(author), isBorrowed(false) {}

// BSTNode class implementation
BSTNode::BSTNode(Book* book) : book(book), left(nullptr), right(nullptr) {}

// BookBST class implementation
BookBST::BookBST() : root(nullptr) {}

void BookBST::addBook(BSTNode*& node, Book* book) {
    if (node == nullptr) {
        node = new BSTNode(book);
    } else if (book->isbn < node->book->isbn){
        addBook(node->left, book);
    } else {
        addBook(node->right, book);
    }
}

void BookBST::addBook(Book* book) {
    addBook(root, book);
}

void BookBST::removeBook()

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
    } else if (isbn < node->book->isbn) {
        return findBook(node->left, isbn);
    } else {
        return findBook(node->right, isbn);
    }
}

Book* BookBST::searchBook(std::string isbn) const {
    BSTNode* node = findBook(root, isbn);
    return node ? node->book : nullptr;
}


//----------------------------------------------------------------
// Public nonabstract methods con't. for review.

bool BookBST::isEmpty() const{
    return (root == nullptr);
}

BookBST::BookBST(){
    root = nullptr;
}

int BookBST::treeHeight() const{
    return height(root);
}

int BookBST::treeNodeCount() const{
    return nodeCount(root);
}

int BookBST::treeLeavesCount() const{
    return leavesCount(root);
}

int BookBST::height(BSTNode *p) const{
    if (p == nullptr)
        return 0;
    else
        return 1 + max(height(p->lLink, height(p->rLink));
}

int BookBST::max(int x, int y) const{
    if (x >= y)
        return x;
    else
        return y;
}

void BookBST::destroy(BSTNode* &p){
    if(p != nullptr){
        destroy(p->lLink);
        destroy(p->rLink);
        delete p;
        p = nullptr;
    }
}

void BookBST::destroyTree(){
    destroy(root);
}

BookBST::~BookBST(){
    destroy(root);
}
//----------------------------------------------------------------
