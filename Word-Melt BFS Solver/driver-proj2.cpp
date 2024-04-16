/*
 * file: driver-proj2.cpp
 * author: Francisco Rios
 * course: CSI 3334
 * assignment: Project 2
 * due date: February, 16 2023
 * version: 3.23, c++14
 * This purpose of this driver is to use code the implementations
 * to solve a maze using a sequence of iterations.
 *
 */

#include <iostream>
#include <map>
#include <vector>
#include "location-proj2.h"
#include "maze-proj2.h"
#include "arrayqueue-student-proj2.h"

using namespace std;

int main() {
    Maze maze;
    Location L;

    ArrayQueue<Location> queue;
    vector<Location>order;
    map<Location,Location> m;
    bool solutionFound = false;
    cin >> maze;

    L = maze.getStartLocation();
    queue.add(L);

    while(queue.getLength() > 0 && !solutionFound){
        L = queue.getFront();
        queue.remove();
        L.iterationBegin();
        while(!L.iterationDone() && !solutionFound) {
            Location neighbor = L.iterationCurrent();
            if (maze.isEndLocation(neighbor)) {
                m[neighbor] = L;
                L = neighbor;
                solutionFound = true;
            }
            else if(maze.isValidLocation(neighbor) && m.find(neighbor) == m.end()){
                queue.add(neighbor);
                m[neighbor] = L;
            }
            L.iterationAdvance();
        }
    }

    if(solutionFound){
        cout << "Solution found" << endl;
        for(int i = 0; !(L == maze.getStartLocation());i++){
            order.push_back(L);
            L = m[L];
        }
        order.push_back(maze.getStartLocation());
        for(int i = order.size() - 1; i >= 0; i--) {
            cout << order[i] << endl;
        }
    }
    else {
        cout << "No solution" << endl;
    }


    return 0;
}
