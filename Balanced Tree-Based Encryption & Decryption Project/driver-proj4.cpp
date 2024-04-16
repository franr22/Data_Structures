/*
  * File: driver-proj4.cpp
  * Author: Francisco Rios
  * Course: CSI 3334
  * Assignment: Project 4
  * Due Date: March, 22 2024
  * Version: C++14
  * The purpose of this driver is to use code implementation to encrypt
  * and decrypt strings from the avl tree code
  *
  */
#include "avl-tree-student-proj4.h"
#include <sstream>

/* main
 * The purpose of this function is to use a loop that continuously
 * reads in commands. When the command is given 'i', it indicates
 * to insert the word that is provided. The command 'r' indicates
 * the user to wants to remove the word they provided. The command
 * 'e' indicates the user wants to encrypt a specific word/message.
 * The commands are encrypting using 'r', '0' and '1' to give a
 * specific code. The command 'd' indicates the user wants to
 * decrypt the message they provided. If the command is 'p',
 * it indicates the user wants to print the codeBook in a preOrder
 * traversal form. Finally, if the command is 'l' it indicates the user
 * wants to print the codebook in levelOrder. Once the user
 * gives the command 'q', then the program quits.
 *
 * parameters: None
 * Return Value: 0 (successful run)
 *
 */


int main() {
    EncryptionTree<string> codeBookTree;
    string input;
    stringstream treeWords;

    cin >> input;

    while(input != "q"){
        if(input == "i"){
            cin >> input;
            codeBookTree.insert(input);
        }
        else if(input == "r"){
            cin >> input;
            codeBookTree.remove(input);
        }
        else if(input == "e"){
            getline(cin, input, '\'');
            getline(cin, input, '\'');

            treeWords.clear();
            treeWords.str(input);
            bool firstWordSpace = true;
            while(treeWords >> input){
                if(firstWordSpace){
                    firstWordSpace = false;
                }
                else {
                    cout << " ";
                }
                cout << codeBookTree.encrypt(input);
            }
            cout << endl;
        }
        else if(input == "d"){
            getline(cin, input, '\'');
            getline(cin, input, '\'');
            treeWords.clear();
            treeWords.str(input);
            bool firstWordSpace = true;

            while(treeWords >> input){
                if(firstWordSpace){
                    firstWordSpace = false;
                }
                else{
                    cout << " ";
                }
                if(codeBookTree.decrypt(input)!= nullptr){
                    cout << *(codeBookTree.decrypt(input));
                }
                else{
                    cout << "?";
                }
            }
            cout << endl;
        }
        else if(input == "p"){
            codeBookTree.printPreorder(cout);
        }
        else if(input == "l"){
            codeBookTree.printLevelOrder(cout);
        }
        cin >> input;
    }
    return 0;
}