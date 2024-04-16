/*
 * file: driver-proj5.cpp
 * author: Francisco Rios
 * course: CSI 2334
 * assignment Title: Project 5
 * due date: 4/12/24
 * version: 3.23, C++14
 * The purpose of this file is to use the implementations in the process class
 * and ArrayHeap class to write an operating system.
 */

#include <iostream>
#include "arrayheap-student-proj5.h"
#include "process-proj5.h"

using namespace std;

/* Main
 * Parameters: None
 * Return Value: 0 (indicates successful run)
 *
 * The purpose of this function is to implement an operating system that reads
 * in processes from the user and then determines if the process is able to
 * run or not. If it is not able to be run, then it will output information
 * on the process that's skipped, or which one is running in the process.
 */

int main() {
    ArrayHeap<Process> myHeap;
    int totalProcesses, readProcesses = 0;
    int currentTime = 0;
    int processCount = 0;
    int skipCount = 0;

    cin >> totalProcesses;
    Process *nextProcess = new Process(0);
    if(!(cin >> *nextProcess)){
        delete nextProcess;
        nextProcess = nullptr;
    }

    while(readProcesses < totalProcesses || myHeap.getNumItems() > 0) {
        while (nextProcess && nextProcess->getSubmissionTime()
        <= currentTime) {
            myHeap.insert(*nextProcess);
            readProcesses++;
            if (readProcesses < totalProcesses) {
                delete nextProcess;
                nextProcess = new Process(readProcesses);
                if (!(cin >> *nextProcess)) {
                    delete nextProcess;
                    nextProcess = nullptr;
                    break;
                }
            }
            else{
                delete nextProcess;
                nextProcess = nullptr;
            }
        }
        if(myHeap.getNumItems() > 0){
            Process current = myHeap.getMinItem();
            myHeap.removeMinItem();

            if(current.getSubmissionTime() > currentTime){
                currentTime = current.getSubmissionTime();
            }

            if(current.canComplete(currentTime)){
                currentTime = current.run(currentTime);
                processCount++;
            }
            else{
                cout << "skipping process id " << current.getId()
                << " at " << currentTime << endl;
                skipCount++;
                currentTime++;
            }
        }
        else{
            currentTime++;
        }
    }

    cout << "final clock is                 " << currentTime << endl;
    cout << "number of processes run is     " << processCount << endl;
    cout << "number of processes skipped is " << skipCount << endl;


    return 0;
}
