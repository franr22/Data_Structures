/**
 * file: driver-proj0.cpp
 * author: Francisco Rios
 * course: CSI 3334
 * assignment: project 0
 * due date: January 18, 2024
 * version: 1.3, c++14
 *
 * This file contents the driver for project 0. The purpose is to create
 * a test editor programs using two stacks. Having functionalities
 * that include typing text, undoing text, and redoing the last
 * undone word.
 */

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <sstream>

using namespace std;

/** outputStack
 *
 * This purpose of this function is to print out the contents of a stack
 * of strings. Is done by printing out the elements in order in which they
 * were originally pushed in to the stack, bottom to top.
 * Furthermore, it uses recursion to get the correct order.
 *  parameters:
 *      *n -- A pointer to a stack of strings, and then passed by reference
 * return value: Does not return a value but outputs the
 * contents of the stack as standard output
 *
 *
*/

void outputStack(stack <string> *stringOfStacks) {
    if(stringOfStacks->empty()){
        return;
    }

    string top = stringOfStacks->top();

    stringOfStacks->pop();
    outputStack(stringOfStacks);

    if (!stringOfStacks->empty()) {
        cout << " ";  // Add space between words, except after the last word
    }

    cout << top;
    stringOfStacks->push(top);

}


/** main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  The purpose of this function is to create a simple text
 *  editor program. As it uses two stacks to implement both a
 *  undo and a typing stack. Furthermore, incorporate a
 *  redo statement that takes the last thing that was done and re-does it.
 *  This helps keep track of all the commands used throughout the program.
 *  Having the typing stack hold the current state of the text, storing
 *  all the words being typed. While the undo holds the words that were
 *  removed from the typing stack.
 *
 *  typing(t) -- The "Typing" stack is to keep up with every word in the stack
 *  undo(u) -- The "Undo" stack is to keep up with the words that have been undone.
 *  redo(r)- Redo is meant to undone the last word
 *
 */

const int COMMAND_POSITION = 0;
const int WORD_START_POSITION = 2;

int main(int argc, char **argv) {
    stack<string> typing, undo;

    int number;
    cin >> number;
    cin.ignore(); //Ignores the line after reading the number

    for(int i = 1; i <= number; i++) {
        string commands; //Stores all the commands
        getline(cin, commands);

        if(commands[COMMAND_POSITION] == 't') {
            //If the command is "t" then is pushed onto the typing stack
            typing.push(commands.substr(WORD_START_POSITION));
        } else if(commands[COMMAND_POSITION] == 'u') {
            if (!typing.empty()) {
                //if the command is "u" then it moves the word to the undo stack
                undo.push(typing.top());
                typing.pop();
            } else {
                cout << "nothing to undo on command " << i << endl;
            }
        } else if(commands[COMMAND_POSITION] == 'r') {
            if (!undo.empty()) {
                //Move the top word from the undo stack back to the typing stack
                typing.push(undo.top());
                undo.pop();
            } else {
                cout << "nothing to redo on command " << i << endl;
            }
        }
    }

    outputStack(&typing); //outputs what's in the typing stack
    cout << endl;
    outputStack(&undo); //outputs what's in the undo stack
    cout << endl;

    return 0;
}




