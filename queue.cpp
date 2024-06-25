#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
#include <iostream>

//First in First out Queue classes
//Based on textbook ch 17
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};

template <class Type>
class queueADT
{
public:
    virtual bool isEmptyQueue() const = 0;
    //Function to return wheter the queue is empty

    virtual bool isFullQueue() const = 0;
    //Function to return whether the queue is full

    virtual void initializeQueue() const = 0;
    //Function to initialize the queue
    //Postcondition: the queue is empty

    virtual Type front() const = 0;
    //Function to return the first element in the queue
    //Precondition: the queue exists and is not empty

    virtual Type back() const = 0;
    //Function to return the last element in the queue
    //Precondition: the queue exists and is not empty

    virtual void addQueue(const Type& queueElement) = 0;
    //Function to add queueElement to the queue
    //Precondition: The queue exists and in not full

    virtual void deleteQueue() = 0;
    //Function to remove the first element of the queue
    //Precondition: The queue exists and is not empty
};


template <class Type>
class linkedQueueType: public queueADT<Type>
{
public:
const linkedQueueType<Type>& operator=(const linkedQueueType<Type>&);
//Overload the assignment operator

bool isEmptyQueue() const;
//Function to return whether the queue is empty

bool isFullQueue() const;
//Function to return whether the queue is full

void initializeQueue();
//Function to initialize the queue
//Postcondition: The queue is empty

Type front() const;
//Function to return the first element in the queue
//Precondition: The queue exists and is not empty

Type back() const;
//Function to return the last element in the queue
//Precondition: The queue exists and is not empty

void addQueue(const Type& queueElement);
//Function to add queueElement to the queue
//Precondition: The queue exists and is not full

void deleteQueue();
//Function to remove the first element in the queue
//Precondition The queue exists and is not empty


linkedQueueType();
//Default constructor

queueType(const linkedQueueType<Type>& otherQueue);
//Copy constructor

~linkedQueueType();
//Destructor

protected:
    nodeType<Type> *queueFront; //Pointer to the front of the queue
    nodeType<Type> *queueRear;  //Pointer to the rear of the queue
};


template <class Type>
bool linkedQueueType<Type>::isEmptyQueue() const
{
    return (queueFront == nullptr);
}//end isEmptyQueue

template <class Type>
bool linkedQueueType<Type>::isFullQueue() const
{
    return false;
}//end isFullQueue

template <class Type>
void linkedQueueType<Type>::initializeQueue()
{
    nodeType<Type> *temp;

    while (queueFront != nullptr)        //While there are elements left in the queue
    {
        temp = queueFront;              //Set temp to point to the current node
        queueFront = queueFront->link;  //Advance first to the next node
        delete temp;                    //deallocate memory pointed to by temp
    }

    queueRear = nullptr;                //Set rear to nullptr
}//end initializeQueue

template <class Type>
void linkedQueueType<Type>::addQueue(const Type& newElement)
{
    nodeType<Type> *newNode;

    newNode = new nodeType<Type>;   //Create the node

    newNode->info = newElement;     //Store the info
    newNode->link = nullptr;        //Initialize the link field to nullptr

    if (queueFront == nullptr)      //If initially the queue is empty
    {
        queueFront = newNode;       //Set the newNode as the first
        queueRear = newNode;        //and last node
    }
    else                            //Otherwise, add newNode at the end
    {
        queueRear->link = newNode;
        queueRear = queueRear->link;
    }
}//end addQueue

template <class Type>
Type linkedQueueType<Type>::front() const
{
    assert (queueFront != nullptr);
    return queueFront->info;
}//end front

template <class Type>
Type linkedQueueType<Type>::back() const
{
    assert (queueRear != nullptr);
    return queueRear->info;
}//end back

template <class Type>
void linkedQueueType<Type>::deleteQueue()
{
    nodeType<Type> *temp;

    if (!isEmptyQueue())
    {
        temp = queueFront;              //Set temp to point to the first elment in the queue
        queueFront = queueFront->link;  //Advance queueFront
        delete temp;                    //Delete the first node

        if (queueFront == nullptr)      //If after deletion the queue is empty
        {
            queueRear = nullptr;        //Set queueRear to nullptr
        }
    }
    else
            std::cout << "Cannot remove from an empty queue" << std::endl;
}//end deleteQueue


template <class Type>
linkedQueueType<Type>::linkedQueueType()
{
    queueFront = nullptr;               //Set front to nullptr
    queueRear = nullptr;                //Set rear to nullptr
}//end default constructor

template <class Type>
linkedQueueType<Type>::linkedQueueType(const linkedQueueType<Type>& otherQueue)
{
    nodeType<Type> *newNode, *current, *last;

    if (queueFront != nullptr)          //If queue is not empty, make it empty
        initializeQueue();

    if (otherQueue.front == nullptr)
        queueFront = nullptr;
    else
    {
        current = otherQueue.front;     //Set current to point to the front of the queue to be copied

        //Copy the front element in the queue
        queueFront = new nodeType<Type>;//Create the node

        queueFront->info = current->info;//Copy the info
        queueFront->link = nullptr;      //Set the link field of the node to nullptr
        last = queueFront;              //Set last to point to the node
        current = current->link;        //Set current to point to the next node

        //Copy the remaining elements in the queue
        while (current != nullptr)
        {
            newNode = new nodeType<Type>;
            
            newNode->info = current->info;
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }//end while
    }//end else
}//end copy constructor

template <class Type>
linkedQueueType<Type>::~linkedQueueType()
{
    initializeQueue();
}//end destructor

#endif  //QUEUE_H
