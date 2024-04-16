/*
  * File: avl-tree-student-proj4.h
  * Author: Francisco Rios
  * Course: CSI 3334
  * Assignment: Project 4
  * Due Date: March, 22 2024
  * Version: C++14
  * The purpose of this .h file is to template from the other .h file
  * and implement the given code.
  *
  */
#ifndef PROJECT4_ALV_TREE_STUDENT_PROJ4_H
#define PROJECT4_ALV_TREE_STUDENT_PROJ4_H

#include "avl-tree-prof-proj4.h"
#include <queue>

/*AVLNode Destructor
 * Deletes the node's children
 *
 * Parameters: None
 * Return Value: None
 *
 */
template <class Base>
AVLNode<Base>::~AVLNode(){
    delete left;
    delete right;
}

/*AVLNode printPreorder
 * Using recursion, it prints the tree in preorder form.
 *
 * Parameters:
 *          os - output stream object is going to print
 *          indent - the set indentation is printed
 * Return Value: None
 *
 */
template <class Base>
void AVLNode<Base>::printPreorder(ostream &os, string indent) const{
    os << indent << this->data << endl;

    if(left){
        this->left->printPreorder(os, indent + "  ");
    }
    else{
        os << indent << "  NULL" << endl;
    }

    if(right){
        this->right->printPreorder(os, indent + "  ");
    }
    else{
        os << indent << "  NULL" << endl;
    }
}

/*AVLNode minNode
 * Using recursion, finds the lowest value node
 * in the tree.
 *
 * Parameters: None
 * Return Value: the leftmost node in the tree
 *
 */
template <class Base>
const AVLNode<Base>* AVLNode<Base>::minNode() const{
    if(left == nullptr){
        return this;
    }
    return left->minNode();
}

/*AVLNode maxNode
 * Using recursion, finds the highest value node
 * in the tree.
 *
 * Parameters: None
 * Return Value: the rightmost node in the tree
 *
 */
template <class Base>
const AVLNode<Base>* AVLNode<Base>::maxNode() const{
    if(right == nullptr){
        return this;
    }
    return right->maxNode();
}

/*AVLNode singleRotateLeft
 * Performs a single rotation to the left at the node's position and
 * updates the height at the end
 *
 * Parameters: None
 * Return Value: The rightChild pointer that takes the new position
 *
 */
template <class Base>
AVLNode<Base>* AVLNode<Base>::singleRotateLeft(){
    AVLNode<Base> *rightChild = right;
    right = rightChild->left;
    rightChild->left = this;

    updateHeight();
    rightChild->updateHeight();

    return rightChild;
}

/*AVLNode singleRotateRight
 * Performs a single rotation to the right at the node's position and
 * updates the height at the end
 *
 * Parameters: None
 * Return Value: The leftChild pointer that takes the new position
 *
 */
template <class Base>
AVLNode<Base>* AVLNode<Base>::singleRotateRight(){
    AVLNode<Base> *leftChild = left;
    left = leftChild->right;
    leftChild->right = this;

    updateHeight();
    leftChild->updateHeight();

    return leftChild;
}

/*AVLNode doubleRotateLeftRight
 * Performs a double rotation to the node's position.
 * Does this by performing a single rotation left at first
 * and then a right single rotation.
 *
 * Parameters: None
 * Return Value: The pointer of the node that is replaces the original
 * this, or left, node in the tree after the rotation is done.
 *
 */
template <class Base>
AVLNode<Base>* AVLNode<Base>::doubleRotateLeftRight(){
    left = left->singleRotateLeft();

    return singleRotateRight();
}

/*AVLNode doubleRotateRightLeft
 * Performs a double rotation to the node's position.
 * Does this by performing a single rotation right at first
 * and then a left single rotation.
 *
 * Parameters: None
 * Return Value: The pointer of the node that is replaces the original
 * this, or right, node in the tree after the rotation is done.
 *
 */
template <class Base>
AVLNode<Base>* AVLNode<Base>::doubleRotateRightLeft(){
    right = right->singleRotateRight();

    return singleRotateLeft();
}

/*AVLNode printLevelOrder
 * Prints out the tree in level order going through it iteratively
 * using a queue
 *
 * Parameters: os - the ostream object that is going to be printed
 * Return Value: none
 *
 */
template <class Base>
void AVLTree<Base>::printLevelOrder(ostream &os) const {
    const int MAX_NODES = 20;
    queue<AVLNode<Base>*> queue;
    int count = 0;

    if(root == nullptr){
        os << "NULL" << endl;
        return;
    }
    queue.push(root);

    while(!queue.empty()){
        AVLNode<Base>* toOrder = queue.front();
        queue.pop();

        if(toOrder != nullptr){
            os << toOrder->data;
            queue.push(toOrder->left);
            queue.push(toOrder->right);
        }
        else{
            os << "NULL";
        }
        count++;

        if(count >= MAX_NODES){
            os << endl;
            count = 0;
        }
        else if(!queue.empty()){
            os << " ";
        }
    }
    if(count > 0){
        os << endl;
    }
}

/*AVLTree rebalancePathToRoot
 * Using a loop, it traverses through the nodes on the given path
 * and check for imbalanced in the AVL Tree. When it is require to
 * do a rotation, it does accordingly.
 *
 * Parameters: path - the path that is going through to check
 * for imbalances
 * Return Value: none
 *
 */
template <class Base>
void AVLTree<Base>::rebalancePathToRoot(vector<AVLNode<Base> *> const &path){
    int nodeIndex = path.size() - 1;
    int balance;

    while(nodeIndex >= 0) {
        AVLNode<Base> *toBalance = path.at(nodeIndex);
        AVLNode<Base> *parent;
        if(nodeIndex > 0){
            parent = path.at(nodeIndex - 1);
        }

        balance = toBalance->getHeight(toBalance->left) -
                  toBalance->getHeight(toBalance->right);
        if (abs(balance) > 1) {
            if (balance < -1) {
                balance = toBalance->getHeight(path.at(nodeIndex)->right->left) -
                          toBalance->getHeight(path.at(nodeIndex)->right->right);
                if (balance <= 0) {
                    if(parent != nullptr) {
                        if(nodeIndex == 0){
                            root = toBalance->singleRotateLeft();
                        } else if (parent->left == path.at(nodeIndex)) {
                            parent->left = toBalance->singleRotateLeft();
                        }
                        else{
                            parent->right = toBalance->singleRotateLeft();
                        }
                    }
                } else if (balance > 0) {
                    if(parent != nullptr) {
                        if(nodeIndex == 0){
                            root = toBalance->doubleRotateRightLeft();
                        } else if (parent->left == path.at(nodeIndex)) {
                            parent->left = toBalance->doubleRotateRightLeft();
                        }
                        else{
                            parent->right = toBalance->doubleRotateRightLeft();
                        }
                    }
                }
            } else if (balance > 1) {
                balance = toBalance->getHeight(path.at(nodeIndex)->left->left) -
                        toBalance->getHeight(path.at(nodeIndex)->left->right);
                if (balance >= 0) {
                    if(parent != nullptr) {
                        if(nodeIndex == 0){
                            root = toBalance->singleRotateRight();
                        }
                        else if(parent->left == path.at(nodeIndex)){
                            parent->left = toBalance->singleRotateRight();
                        }
                        else{
                            parent->right = toBalance->singleRotateRight();
                        }
                    }
                } else if (balance < 0) {
                    if(parent != nullptr) {
                        if(nodeIndex == 0){
                            root = toBalance->doubleRotateLeftRight();
                        }
                        else if(parent->left == path.at(nodeIndex)){
                            parent->left = toBalance->doubleRotateLeftRight();
                        }
                        else{
                            parent->right = toBalance->doubleRotateLeftRight();
                        }
                    }
                }
            }
        }
        for(int i = path.size() - 1; i >= 0; i--){
            path.at(i)->updateHeight();
        }
        nodeIndex--;
    }
}

/*AVL insert
 * Checks if the given item is a duplicate, and if not
 * inserts it onto the tree
 *
 * Parameters:
 *          item - the item that is going to be inserted in the tree
 * Return Value: None
 *
 */
template <class Base>
void AVLTree<Base>::insert(const Base &item){
    vector<AVLNode<Base>*> path;
    AVLNode<Base> *parent;
    AVLNode<Base> *toInsert = root;

    if(root) {
        while (toInsert != nullptr) {
            path.push_back(toInsert);
            parent = toInsert;
            if (item < toInsert->data) {
                toInsert = toInsert->left;
            } else if (toInsert->data < item) {
                toInsert = toInsert->right;
            } else {
                return;
            }
        }

        if (item < parent->data) {
            parent->left = new AVLNode<Base>(item);
            path.push_back(parent->left);
        } else {
            parent->right = new AVLNode<Base>(item);
            path.push_back(parent->right);
        }
    } else{
        root = new AVLNode<Base>(item);
        path.push_back(root);
    }

    rebalancePathToRoot(path);
}

/*AVL remove
 * Finds the node that it wants to remove based on the path, then
 * depending on if it has two children, one child, or is the root.
 * It follows a specific instructions to delete the node and
 * balance the tree.
 *
 * Parameters:
 *          item - the item that is going to be removed from the BST
 * Return Value: None
 *
 */
template <class Base>
void AVLTree<Base>::remove(const Base &item) {
    vector<AVLNode<Base>*> path;
    AVLNode<Base> *toRemove = root;
    AVLNode<Base> *parent = nullptr;

    while (toRemove != nullptr && (toRemove->data < item || item < toRemove->data)) {
        path.push_back(toRemove);
        parent = toRemove;
        if (item < toRemove->data) {
            toRemove = toRemove->left;
        } else {
            toRemove = toRemove->right;
        }
    }

    if (toRemove == nullptr) {
        return;
    }

    if (toRemove->left == nullptr || toRemove->right == nullptr) {
        AVLNode<Base> *child = nullptr;

        if (toRemove->left != nullptr) {
            child = toRemove->left;
            toRemove->left = nullptr;
        } else {
            child = toRemove->right;
            toRemove->right = nullptr;
        }
        if (parent == nullptr) {
            root = child;
        } else if (parent->left == toRemove) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    }

    if (toRemove->left != nullptr && toRemove->right != nullptr) {
        AVLNode<Base> *leftMost = toRemove->right;
        AVLNode<Base> *leftMostParent = toRemove;
        int index = path.size();

        if (leftMost->left != nullptr) {
            while (leftMost->left != nullptr) {
                path.push_back(leftMost);
                leftMostParent = leftMost;
                leftMost = leftMost->left;
            }
            leftMostParent->left = leftMost->right;
            leftMost->right = toRemove->right;
        }

        leftMost->left = toRemove->left;
        path.insert(path.begin() + index, leftMost);
        if (parent == nullptr) {
            root = leftMost;
        } else if (parent->left == toRemove) {
            parent->left = leftMost;
        } else {
            parent->right = leftMost;
        }
        toRemove->left = toRemove->right = nullptr;
    }
    delete toRemove;

    for(int i = path.size() - 1; i >= 0; --i){
        path.at(i)->updateHeight();
    }
    rebalancePathToRoot(path);
}

/*EncryptionTree Encrypt
 * Using a while loop, it goes through the tree
 * and encrypts the provided string message, returning
 * the encrypted message at the end
 *
 * Parameters:
 *          item - the item that is going to be encrypted
 * Return Value: the provided string that has been encrypted
 *
 */
template <class Base>
string EncryptionTree<Base>::encrypt(const Base &item) const{
    AVLNode<Base> const *encryptTemp = this->root;
    string root = "r";

    while(encryptTemp != nullptr){
        if(encryptTemp->getData() < item){
            root += "1";
            encryptTemp = encryptTemp->getRight();
        }
        else if(item < encryptTemp->getData()){
            root += "0";
            encryptTemp = encryptTemp->getLeft();
        }
        else{
            return root;
        }
    }
    if(encryptTemp == nullptr){
        root = "?";
    }
    return root;
}


/*EncryptionTree decrypt
 * Using a for loop, it goes through the tree to find
 * the encrypted string provided.
 *
 * Parameters:
 *          path - the path of the encrypted string
 * Return Value: the address of the encrypted string data, if there is none
 * then it returns nullptr.
 *
 */
template <class Base>
const Base* EncryptionTree<Base>::decrypt(const string &path) const{
    AVLNode<Base> const *decryptTemp = this->root;

    for(unsigned int i = 1; i < path.length() && decryptTemp != nullptr; i++){
        if(path[i] == '0'){
            decryptTemp = decryptTemp->getLeft();
        }
        else{
            decryptTemp = decryptTemp->getRight();
        }
    }

    if(decryptTemp == nullptr){
        return nullptr;
    }
    else{
        return &decryptTemp->getData();
    }
}





#endif //PROJECT4_ALV_TREE_STUDENT_PROJ4_H
