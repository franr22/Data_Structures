#include <iostream>
#include "bst-prof-proj3.h"
#include "bst-student-proj3.h"

using namespace std;

int main(){
    BSTNode<int> *leftChild1 = new BSTNode<int>(5); //left child of left subtree
    BSTNode<int> *leftChild2 = new BSTNode<int>(8); //Right child of left subtree
    BSTNode<int> *leftChild3 = new BSTNode<int>(30); //Left child of right subtree
    BSTNode<int> *leftChild4 = new BSTNode<int>(33); //Right child of right subtree

    BSTNode<int> *parent1 = new BSTNode<int>(10, leftChild1, leftChild2); //parent of child1 and child2
    BSTNode<int> *parent2 = new BSTNode<int>(21, leftChild3, leftChild4); //Parent of child 2 and child3

    BSTNode<int> *root = new BSTNode<int>(15, parent1, parent2); //Root of the tree

    //Test printPreorder
    cout << "Testing printPreorder: " << endl;
    root->printPreorder(cout, " ");
    /*
     * Expected Output:
     * 15
     *   20
     *     5
     *     8
     *   21
     *     30
     *     33
     */

    const BSTNode<int> *minNode = root->minNode();
    const BSTNode<int> *maxNode = root->maxNode();
    cout << endl << endl;
    cout << "Testing Min" << endl;
    cout << "Min Node: " << minNode->getData() << endl; //output should be 5
    cout << endl;
    cout << "Testing Max" << endl;
    cout << "Max Node: " << maxNode->getData() << endl; //output should be 33


    BST<int> newTree;
    newTree.insert(15);
    newTree.insert(10);
    newTree.insert(5);
    newTree.insert(8);
    newTree.insert(21);
    newTree.insert(30);
    newTree.insert(33);

    newTree.printPreorder(cout);

    EncryptionTree<string> treeTest;

    cout << endl;

    treeTest.insert("score");
    treeTest.insert("and");
    treeTest.insert("seven");
    treeTest.insert("ago");
    treeTest.insert("four");
    treeTest.insert("years");

    treeTest.printPreorder(cout);

    cout << "ABCD" << endl;
    treeTest.remove("ago");
   treeTest.printPreorder(cout);
//
//    cout << endl;
//    cout << "Testing Encryption: " << endl;
//    cout << "Expected Output: r01 r r0 r1 r11 r00 " << endl;
//    cout << "Testing output: ";
//    cout << treeTest.encrypt("four") << " ";
//    cout << treeTest.encrypt("score") << " ";
//    cout << treeTest.encrypt("and") << " ";
//    cout << treeTest.encrypt("seven") << " ";
//    cout << treeTest.encrypt("years") << " ";
//    cout << treeTest.encrypt("ago") << " ";
//    cout << endl << endl;
//
//    cout << "Testing Decryption: " << endl;
//    cout << "Expected output: four score and seven years ago" << endl;
//    cout << "Actual output: ";
//    cout << *(treeTest.decrypt("r01")) << " ";
//    cout << *(treeTest.decrypt("r")) << " ";
//    cout << *(treeTest.decrypt("r0")) << " ";
//    cout << *(treeTest.decrypt("r1")) << " ";
//    cout << *(treeTest.decrypt("r11")) << " ";
//    cout << *(treeTest.decrypt("r00")) << " ";

    return 0;
}
