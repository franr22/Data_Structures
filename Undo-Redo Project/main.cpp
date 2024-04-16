#include <iostream>
#include <string>
#include <stack>

using namespace std;

void printStack(stack <string> stak) {
    stack<string> reverse;
    while(!stak.empty()){
        reverse.push(stak.top());
        stak.pop();
    }

    while(!reverse.empty()){
        cout << reverse.top();
        reverse.pop();
        if(!reverse.empty()){
            cout << " ";
        }
    }
    cout << endl;
}


int main() {
    int a;
    cin >> a;
    cin.ignore();

    stack<string> typingStack, undoStack;

    for(int i = 0; i < a; i++){
        string comm;
        getline(cin, comm);

        if(comm[0] == 't'){
            typingStack.push(comm.substr(2));
        }
        else if(comm[0] == 'u' && !typingStack.empty()) {
            undoStack.push(typingStack.top());
        }
        else if(comm[0] == 'r' && !undoStack.empty()){
            typingStack.push(undoStack.top());
            undoStack.pop();
        }
    }

    printStack(typingStack);
    printStack(undoStack);

    return 0;
}
