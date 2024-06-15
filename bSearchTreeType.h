// ADT from Ch. 19 to complement BinarySearchTree

#ifndef BSEARCHTREETYPE_H
#define BSEARCHTREETYPE_H

#include <string>
#include <iostream>
#include "BinarySearchTree.h"

template <class elemType>
class bSearchTreeType: public BinarySearchTree<elemType>
{
public:
  bool search(const elemType& searchItem) const;          // Search function that utilizes searchItem; returns boolean value.

  void insert(const elemType& insertItem);                // Insert function.

  void deleteNode(const elemType& deleteItem);            // Deletes deleteItem from BST.

private:
  void deleteFromTree(BSTNode<elemType>* &p);            // Where p is updated to, function deletes the node from the BST.

};












#endif
