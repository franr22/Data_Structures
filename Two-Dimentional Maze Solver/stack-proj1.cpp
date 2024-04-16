/**
 * file: stack-proj1.cpp
 * author: Francisco Rios
 * course: CSI 3334
 * assignment: Project 1
 * due date: February, 2 2023
 * version: 1.3, c++14
 * The purpose of this cpp file is to implement functions from
 * the LocationStackNode class and LocationStack class
 */

#include "stack-proj1.h"

/** LocationStack Default Constructor
 * parameters: None
 * return value: None
 *
 * The function initializes an empty stack by making the top pointer to NULL
 */

LocationStack::LocationStack(void){
    this->top = NULL;
}

/** LocationStack Destructor
 * parameters: None
 * return value: None
 *
 * The function destructor frees us allocated memory for the
 * top node of the stack
 */

LocationStack::~LocationStack(){
    delete this->top;
}

/** Push
 * parameters:
 * - Loc: The location push onto stack
 * return value: None
 *
 * The function adds a new location to the top of the stack
 */

void LocationStack::push(const Location &loc){
    LocationStackNode* temp = new LocationStackNode(loc, this->top);
    top = temp;
}

/** pop
 * parameters: None
 * return value: None
 *
 * The purpose of this function is to remove the top element of the stack
 */

void LocationStack::pop(void){
    assert(!isEmpty());

    if(!this->isEmpty()) {
        LocationStackNode *temp = this->top;
        this->top = this->top->getNextNode();
        temp->setNextNode(NULL);
        delete temp;

    }
}

/** getTop
 * parameters: None
 * return value: Returns the locationStackNode to the top of the stack
 *
 * The purpose of this function is to return a reference to the Location
 */

const Location& LocationStack::getTop(void) const{
    return top->getLocation();
}

/** isEmpty
 * parameters: None
 * return value: Returns true if the stack is empty, and lse if is not
 *
 * The function is to check if th stack is empty
 */

bool LocationStack::isEmpty(void) const{
    return this->top == NULL;
}

/** isOn
 * parameters:
 * - Loc: The location that is going to be checked
 * return value: If the location is on the stack returns true, otherwise
 * if is not it returns false
 *
 * The purpose of this function is to iterate thru the stack and compares
 * location to the locations on the stack
 */

bool LocationStack::isOn(const Location &loc) const{
    LocationStackNode* temp = top;
    while(temp != NULL){
        if(temp->getLocation() == loc){
            return true;
        }
        temp = temp->getNextNode();
    }
    return false;
}

/** operator<<
 * parameters:
 * - os: output stream where data is going to be outputted
 * - s: The stack that's being outputted
 * return value: Outputs the location on stack s at the bottom to the top
 * The purpose of this function is to output whats on the LocationStack
 */
ostream &operator<<(ostream &os, const LocationStack &s) {

    LocationStackNode *currentNode = s.top;
    LocationStackNode *previousNode = NULL;
    LocationStackNode *nextNode = s.top;

    while (currentNode != NULL) {
        nextNode = nextNode->getNextNode();
        currentNode->setNextNode(previousNode);
        previousNode = currentNode;
        currentNode = nextNode;
    }
    currentNode = nextNode = previousNode;
    previousNode = NULL;

    while (currentNode != NULL) {
        os << currentNode->getLocation() << endl;

        nextNode = nextNode->getNextNode();
        currentNode->setNextNode(previousNode);
        previousNode = currentNode;
        currentNode = nextNode;
    }

    return os;

}

/** LocationStackNode Constructor
 * parameters:
 * - loc: A location data
 * - next: A pointer that points to the next LocationStackNode
 * return value: None
 *
 * The purpose of this function is to construct a node with a provided location
 * and the next node pointer
 */

LocationStackNode::LocationStackNode(const Location &loc, LocationStackNode *next) {
    this->location = loc;
    this->nextNode = next;
}

/** LocationStackNode destructor
 * parameters: None
 * return value: None
 *
 * The purpose of this function is to free the allocated memory for next node
 */

LocationStackNode::~LocationStackNode() {
    delete this->nextNode;
}

/** getLocation
 * parameters: None
 * return value: Returns all location data members
 *
 * The purpose of this function is to return the reference to the
 * location that's in the node
 */

const Location& LocationStackNode::getLocation() const {
    return this->location;
}

/** getNextNode
 * parameters: None
 * return value: Pointer to the next node that's in the stack
 *
 * The purpose of the function returns a pointer to the next node of the stack
 */

LocationStackNode* LocationStackNode::getNextNode() const {
    return this->nextNode;
}

/** setNextNode
 * parameters: None
 * - next: A pointer that points to the next LocationStackNode
 * return value: None
 *
 * The purpose of this function is to set a node pointer of the node
 */
void LocationStackNode::setNextNode(LocationStackNode *next){
    this->nextNode = next;
}
