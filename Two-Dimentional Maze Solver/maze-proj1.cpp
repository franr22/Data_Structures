/*
 * file: maze-proj1.cpp
 * author: Francisco Rios
 * course: CSI 3334
 * assignment: Project 1
 * due date: February, 2 2023
 * version: 3.23, c++14
 * The purpose of this cpp driver is to implement code functions
 * from the Maze class.
 */

#include "maze-proj1.h"

/** Maze Constructor
 * parameters: None
 * return value: None
 *
 * The purpose of this constructor is to initialize the maze object by
 * allocating dynamic memory.
 */

Maze::Maze(void){
    validLocationCount = 0;
    validLocations = new Location[validLocationCount];
}

/** Maze Destructor
 * parameters: None
 * return value: None
 *
 * The purpose of this function is to free up allocated memory for
 * validLocations and resets the count
 */

Maze::~Maze(){
    delete [] validLocations;

}

/** getStartLocation
 * parameters: None
 * return value: returns the start location for the maze
 *
 * The purpose of this function is to start the location of the maze
 */

Location Maze::getStartLocation(void) const{
    return startLocation;
}

/** isValidLocation
 * parameters:
 * - loc: A location that has to be checked for validation
 * return value: If the location is valid returns true, if not then is false
 *
 * The purpose of this function is to check if location of the maze
 * is actually valid
 */

bool Maze::isValidLocation(const Location &loc) const{
    for(int i = 0; i < validLocationCount; i++){
        if(loc == validLocations[i]) {
            return true;
        }
    }
    return false;
}

/** isEndLocation
 * parameters:
 * - loc: Location that has to be checked to see if is the endpoint
 * return value: returns true if the location is the end of the maze, if not
 * it returns false
 *
 * The purpose of this function is to check whether the location given is
 * the end location of the maze
 */

bool Maze::isEndLocation(const Location &loc) const{
    if(loc == endLocation){
        return true;
    }
    else{
        return false;
    }
}

/** operator>>
 * parameters:
 * - is:The Reference to the input stream where input data is read in from
 * - m: The address of the maze object being changed
 * return value: The maze objects data members are changed with
 * the new data received from the input
 *
 * The purpose of this function is to read the maze input into the Maze object
 */

istream &operator>>(istream &is, Maze &m){
    is >> m.validLocationCount;

    delete [] m.validLocations;

    m.validLocations = new Location[m.validLocationCount];

    for (int i = 0; i < m.validLocationCount; i++) {
        is >> m.validLocations[i];
    }


    is >> m.startLocation >> m.endLocation;

    return is;
}



