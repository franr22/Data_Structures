#include <iostream>
#include "arrayheap-student-proj5.h"
#include "process-proj5.h"

using namespace std;

int main() {
    ArrayHeap<Process> myHeap;
    int totalProcesses;
    cin >> totalProcesses; // Read the total number of processes

    int currentTime = 0;
    int processCount = 0;
    int skipCount = 0;

    // Directly use a for loop to handle each process
    for (int i = 0; i < totalProcesses; ++i) {
        Process current(i); // Initialize Process with ID as loop index
        cin >> current; // Read the process details

        // Insert into the heap if its submission time has already been reached
        while (currentTime < current.getSubmissionTime()) {
            // If the heap has items, process the top priority process
            if (myHeap.getNumItems() > 0) {
                Process topProcess = myHeap.getMinItem();
                myHeap.removeMinItem();

                // Process logic
                if (topProcess.canComplete(currentTime)) {
                    currentTime = topProcess.run(currentTime);
                    processCount++;
                } else {
                    cout << "Skipping process id " << topProcess.getId() << " at " << currentTime << endl;
                    skipCount++;
                    currentTime++; // Increment currentTime by 1 when skipping
                }
            } else {
                // If no processes are ready to run, just advance the time
                currentTime++;
            }
        }

        // After potentially processing and advancing time, insert the current process
        myHeap.insert(current);

        // End of the for loop, proceed to next iteration (next process read)
    }

    // After reading all processes, ensure all remaining processes in the heap are processed
    while (myHeap.getNumItems() > 0) {
        Process topProcess = myHeap.getMinItem();
        myHeap.removeMinItem();

        // Remaining process logic
        if (topProcess.canComplete(currentTime)) {
            currentTime = topProcess.run(currentTime);
            processCount++;
        } else {
            cout << "Skipping process id " << topProcess.getId() << " at " << currentTime << endl;
            skipCount++;
            currentTime++; // Increment currentTime by 1 when skipping
        }
    }

    // Final output
    cout << "Final clock is                 " << currentTime << endl;
    cout << "Number of processes run is     " << processCount << endl;
    cout << "Number of processes skipped is " << skipCount << endl;

    return 0;
}
