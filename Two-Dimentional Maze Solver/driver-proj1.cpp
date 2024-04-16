/*
 * file: driver-proj1.cpp
 * author: Francisco Rios
 * course: CSI 3334
 * assignment: Project 1
 * due date: February, 2 2023
 * version: 3.23, c++14
 * This purpose of this driver is to use code the implementations
 * to solve Da maze using a sequence of iterations.
 * Starts with the location and goes through the puzzle till every valid
 * location is visited. Moving from four different directions:
 * Right, Down, Left, and up.
 *
 */

#include <iostream>
#include "stack-proj1.h"
#include "maze-proj1.h"

using namespace std;


/** main
 * parameters: None
 * return value: 0 (indicating a successful run)
 *
 * The purpose of this function is to solve a maze puzzle using iterations.
 * Through the usage of stacks, we store the location of the data that
 * were already visited, and the stack helps make it easier to go back
 * to the previous one. Utilizing the implementation of depth-first
 * search algorithm, it helps simulate recursion and saves the path that is
 * being taken on the maze. The stack is very important to store the information
 * and keep track of previous locations. The function will continue till either
 * it found the solution, or till there is no solution.
 *
 *
 */

int main() {
    Maze maze;
    Location neighbor, m;
    LocationStack locationStack;

    bool solution = true;

    cin >> maze;

    m = maze.getStartLocation();
    m.iterationBegin();
    locationStack.push(m);

    while(solution && !maze.isEndLocation(locationStack.getTop())){
        m = locationStack.getTop();
        locationStack.pop();
        if(!m.iterationDone()) {
            neighbor = m.iterationCurrent();
            neighbor.iterationBegin();
            m.iterationAdvance();
            locationStack.push(m);
        }
        if(!locationStack.isOn(neighbor) && maze.isValidLocation(neighbor)) {
            locationStack.push(neighbor);
        } else if (locationStack.isEmpty()){
            solution = false;
        }
    }

    if(solution){
        cout << "Solution found" << endl;
        cout << locationStack;
    }
    else {
        cout << "No solution" << endl;
    }


    return 0;
}