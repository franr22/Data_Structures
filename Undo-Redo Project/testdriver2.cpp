/* CSI 3334
 * Project 0 -- Undo Redo
 * Filename: driver-proj0.cpp
 * Student name: Karina Garza
 *
 */
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <sstream>
#include <fstream>

using namespace std;

void printStack(stack <string> stacks) {
    if (stacks.empty()) {
        return;
    }
    string s = stacks.top();
    stacks.pop(); //removes the top element

    printStack(stacks); //recursive call to reduce the stack


    if (!stacks.empty()) {
        cout << " ";
    }
    cout << s; //outputs the stored top element

}

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 */
int main(int argc, char **argv) { // QUESTION: WHAT ARE ARGC AND ARGV? GO LOOK THEM UP!
    // these are the two stacks used to store the typed words and the undone
    // words
    stack<string> typing, undo;

    int amount;
    char command, space;
    string word;

    cin >> amount;
    cin.ignore();

    /* for (int i = 1; i <= amount; i++){
         cin.get(command);
         if (command == 'u') {
             if(!typing.empty()){
             cin.ignore();
             undo.push(typing.top());
             typing.pop();
         } else {
             cerr << "nothing to undo on command " << i << endl;
             }
         }
         else if (command == 'r') {
             if (!typing.empty()) {
                 typing.push(undo.top());
                 undo.pop();
             } else {
                 cerr << "nothing to redo on command " << i << endl;
             }
         } else{
             cin.get(space);
             getline(cin, word);

             if (command == 't') {
                 typing.push(word);
             }
         }
     }
     */
    for(int i = 1; i <= amount; i++){
        cin >> command;
        if(command == 't'){
            cin >> word;
            typing.push(word);

        } else if(command == 'u'){
            if(!typing.empty()){
                undo.push(typing.top());
                typing.pop();
            } else {
                cout << "nothing to undo on command " << i << endl;
            }
        } else if(command == 'r'){
            if(!undo.empty()){
                typing.push(undo.top());
                undo.pop();
            } else {
                cout << "nothing to redo on command " << i << endl;
            }
        }
    }
    printStack(typing);
    cout << endl;
    printStack(undo);
    cout << endl;

    return 0;
}
