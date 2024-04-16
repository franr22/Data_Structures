/*
 * File: bst-student-proj3.h
 * Author: Francisco Rios
 * Course: CSI 3334
 * Assignment: Project 3
 * Due Date: March, 1 2024
 * Version: C++14
 * The purpose of this header file is to template and implement code from the
 * other bst-prof-proj3.h
 *
*/

 #ifndef BST_STUDENT_PROJ3
 #define BST_STUDENT_PROJ3

 #include "bst-prof-proj3.h"

/*BSTNode Destructor
 * Deletes the node's children
 *
 * Parameters: None
 * Return Value: None
 *
 */

template <class Base>
BSTNode<Base>::~BSTNode(){
    delete left;
    delete right;
}

/*BSTNode printPreorder
 * Using recursion, it prints the tree in preorder form.
 *
 * Parameters:
 *          os - output stream object is going to print
 *          indent - the set indentation is printed
 * Return Value: None
 *
 */
template <class Base>
void BSTNode<Base>::printPreorder(ostream &os, string indent) const{
    os << indent << this->data << endl;

    if(left){
        this->left->printPreorder(os, indent + "  ");
    }
    else {
        os << indent << "  NULL" << endl;
    }

    if(right){
        this->right->printPreorder(os, indent + "  ");
    }
    else{
        os << indent << "  NULL" << endl;
    }

}

/*BSTNode minNode
 * Using recursion, finds the lowest value node
 * in the tree.
 *
 * Parameters: None
 * Return Value: the leftmost node in the tree
 *
 */
template <class Base>
const BSTNode<Base>* BSTNode<Base>::minNode() const{
    if(!left){
        return this;
    }

    return left->minNode();

}

/*BSTNode maxNode
 * Using recursion, finds the highest value node
 * in the tree.
 *
 * Parameters: None
 * Return Value: the rightmost node in the tree
 *
 */
template <class Base>
const BSTNode<Base>* BSTNode<Base>::maxNode() const {
    if(!right){
        return this;

    }
    return right->maxNode();
}

/*BST insert
 * Checks if the given item is a duplicate, and if not
 * inserts it onto the tree
 *
 * Parameters:
 *          item - the item that is going to be inserted in the tree
 * Return Value: None
 *
 */

template <class Base>
void BST<Base>::insert(const Base &item) {
    BSTNode<Base> *parent;
    BSTNode<Base> *toInsert = root;

    if (root) {
        while (toInsert != nullptr) {
            parent = toInsert;
            if (item < toInsert->data) {
                toInsert = toInsert->left;
            } else if (toInsert->data < item) {
                toInsert = toInsert->right;
            } else {
                return;
            }
        }

        if (item < parent->getData()) {
            parent->left = new BSTNode<Base>(item);
        } else {
            parent->right = new BSTNode<Base>(item);
        }
    } else {
        root = new BSTNode<Base>(item);
    }
}

/*BST remove
 * Finds the node that it wants to remove, then
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
void BST<Base>::remove(const Base &item) {
    BSTNode<Base> *toRemove = root;
    BSTNode<Base> *parent = nullptr;

    while (toRemove != nullptr && (toRemove->data < item || item < toRemove->data)) {
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
        BSTNode<Base> *child = nullptr;

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
        BSTNode<Base> *leftMost = toRemove->right;
        BSTNode<Base> *leftMostParent = toRemove;

        if (leftMost->left != nullptr) {
            while (leftMost->left != nullptr) {
                leftMostParent = leftMost;
                leftMost = leftMost->left;
            }
            leftMostParent->left = leftMost->right;
            leftMost->right = toRemove->right;
        }
        leftMost->left = toRemove->left;
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
    BSTNode<Base> const *encryptTemp = this->root;
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
    BSTNode<Base> const *decryptTemp = this->root;

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

#endif