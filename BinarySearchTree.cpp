#include "BinarySearchTree.h"

// Constructor
BookBST::BookBST() : root(nullptr) {}

// Destructor
BookBST::~BookBST() {
    destroyTree();
}

// Add Book (Public)
void BookBST::addBook(Book* book) {
    addBook(root, book);
}

// Add Book (Private)
void BookBST::addBook(BSTNode*& node, Book* book) {
    if (!node) {
        node = new BSTNode(book);
    } else if (book->getISBN() < node->book->getISBN()) {
        addBook(node->left, book);
    } else {
        addBook(node->right, book);
    }
}

// Search Book (Public)
Book* BookBST::searchBook(const std::string& isbn) const {
    BSTNode* foundNode = findBook(root, isbn);
    return foundNode ? foundNode->book : nullptr;
}

// Find Book (Private)
BSTNode* BookBST::findBook(BSTNode* node, const std::string& isbn) const {
    if (!node) {
        return nullptr;
    } else if (isbn == node->book->getISBN()) {
        return node;
    } else if (isbn < node->book->getISBN()) {
        return findBook(node->left, isbn);
    } else {
        return findBook(node->right, isbn);
    }
}

// Remove Book (Public)
void BookBST::removeBook(const std::string& isbn) {
    root = removeBook(root, isbn);
}

// Remove Book (Private)
BSTNode* BookBST::removeBook(BSTNode* node, const std::string& isbn) {
    if (!node) {
        return nullptr;
    }
    if (isbn < node->book->getISBN()) {
        node->left = removeBook(node->left, isbn);
    } else if (isbn > node->book->getISBN()) {
        node->right = removeBook(node->right, isbn);
    } else {
        if (!node->left) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }
        BSTNode* temp = findMin(node->right);
        node->book = temp->book;
        node->right = removeBook(node->right, temp->book->getISBN());
    }
    return node;
}

// Find Minimum Node
BSTNode* BookBST::findMin(BSTNode* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Display Books (In-order Traversal)
void BookBST::displayBooks() const {
    inOrderTraversal(root);
    std::cout << std::endl;
}

// In-order Traversal (Private)
void BookBST::inOrderTraversal(BSTNode* node) const {
    if (node) {
        inOrderTraversal(node->left);
        std::cout << node->book->getTitle() << " ";
        inOrderTraversal(node->right);
    }
}

// Check if Tree is Empty (Public)
bool BookBST::isEmpty() const {
    return isEmpty(root);
}

// Check if Tree is Empty (Private)
bool BookBST::isEmpty(BSTNode* node) const {
    return node == nullptr;
}

// Calculate Tree Height (Public)
int BookBST::treeHeight() const {
    return height(root);
}

// Calculate Tree Height (Private)
int BookBST::height(BSTNode* node) const {
    if (!node) {
        return 0;
    }
    return 1 + max(height(node->left), height(node->right));
}

// Get Max Value
int BookBST::max(int x, int y) const {
    return (x > y) ? x : y;
}

// Count Tree Nodes (Public)
int BookBST::treeNodeCount() const {
    return treeNodeCount(root);
}

// Count Tree Nodes (Private)
int BookBST::treeNodeCount(BSTNode* node) const {
    if (!node) {
        return 0;
    }
    return 1 + treeNodeCount(node->left) + treeNodeCount(node->right);
}

// Count Tree Leaves (Public)
int BookBST::treeLeavesCount() const {
    return treeLeavesCount(root);
}

// Count Tree Leaves (Private)
int BookBST::treeLeavesCount(BSTNode* node) const {
    if (!node) {
        return 0;
    }
    if (!node->left && !node->right) {
        return 1;
    }
    return treeLeavesCount(node->left) + treeLeavesCount(node->right);
}

// Destroy Tree (Public)
void BookBST::destroyTree() {
    destroy(root);
}

// Destroy Tree (Private)
void BookBST::destroy(BSTNode*& node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
        node = nullptr;
    }
}
