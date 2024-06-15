#include <string>
#include <iostream>

#include "bSearchTreeType.h"

template <class elemType>
bool bSearchTreetype<elemType>::search(const elemType& searchItem) const
{
  BSTNode<elemType> *current;
  bool found = false;

  if(root == nullptr)
    std::cout << "Root of tree is empty, book is not in inventory" << std::endl;
  else
  {
    current = root;

    while(current != nullptr && !found)
    {
      if(current != nullptr && !found)
        found = true;
      else if (current->info > searchItem)
        current = current->lLink;
      else
        current = current->rLink;
    }
  }
}


template <class elemType>
void bSearchTreetype<elemType>::insert(const elemType& insertItem)
{
  BSTNode<elemType> *current;
  BSTNode<elemType> *trailCurrent;
  BSTNode<elemType> *newNode;

  newNode = new BSTNode<elemType>;
  newNode->info = insertItem;
  newNode->lLink = nullptr;
  newNode->rLink = nullptr;

  if(root == nullptr)
    root = newNode;
  else
  {
    current = root;

    while (current != nullptr)
    {
      trailCurrent = current;

      if(current->info == insertItem)
      {
          std::cout << "Book is already in the tree" << std::endl;

          return;
      }
      else if(current->info > insertItem)
          current = current->lLink;
      else
          current = current->rLink;
    }

    if(trailCurrent->info > insertItem)
      trailCurrent->lLink = newNode;
    else
      trailCurrent->rLink = newNode;
  }

}



template <class elemType>
void bSearchTreetype<elemType>::deleteNode(const elemType& deleteItem)
{
  BSTNode<elemType> *current;
  BSTNode<elemType> *trailCurrent;
  bool found = false;

  if(root == nullptr)
    std::cout << "Cannot delete from an empty inventory" << std::endl;
  else
  {
    current = root;
    trailCurrent = root;

    while(current != nullptr && !found)
    {
      if(current->info == deleteItem)
        found = true;
      else
      {
        trailCurrent = current;

        if(current->info > deleteItem)
          current = current->lLink;
        else
          current = current->rLink;
      }
    }

    if(current == nullptr)
      std::cout << "Book is not in inventory." << std::endl;
    else if (found)
    {
      if(current == root)
        deleteFromTree(root);
      else if(trailCurrent->info > deleteItem)
        deleteFromTree(trailCurrent->lLink);
      else
        deleteFromTree(trailCurrent->rLink);
    }
    else
      std::cout << "The book you searched for is not in the inventory." << std::endl;
  }
}


template <class elemType>
void bSearchTreetype<elemType>::deleteFromTree(BSTNode<elemType>* &p)
{
  BSTNode<elemType> *current;
  BSTNode<elemType> *trailCurrent;
  BSTNode<elemType> *temp;

  if(p == nullptr)
    std::cout << "Error: the list is pointing to NULL." << std::endl;
  else if(p->lLink == nullptr && p->rLink == nullptr)
  {
    temp = p;
    p = nullptr;
    delete temp;
  }
  else if(p->lLink == nullptr)
  {
    temp = p;
    p = temp->rLlink;
    delete temp;
  }
  else if(p->lLink == nullptr)
  {
    temp = p;
    p = temp->lLlink;
    delete temp;
  }
  else
  {
    current = p->lLink;
    trialCurrent = nullptr;

    while(current->rLink != nullptr)
    {
      trailCurrent = current;
      current = current->rLink;
    }

    p->info = current->info;

    if(trialCurrent == nullptr)
      p->lLink = current->lLink;
    else
      trailcurrent->rLink = current->lLink;

    delete current;
  }
}
    













