/*
 * file: location-proj1.cpp
 * author: Francisco Rios
 * course: CSI 3334
 * assignment: Project 1
 * due Date: February, 2 2023
 * version: 3.23, c++14
 * This purpose of this file is to implement functions from the Location class
 * that relates to iterations.
 */

#include "location-proj1.h"

/** Location Constructor
 * parameters: None
 *
 * The purpose of this function is to initialize the location objects with
 * the default row and col values.
 */
Location::Location(){
    row = 1;
    col = 1;
    nextDirection = RIGHT;
}

/** iterationBegin
 * parameters: None
 * return value: None
 *
 * The purpose of this function is to set where the iteration begins to right
 */

void Location::iterationBegin(){
    this->nextDirection = RIGHT;
}

/** iterationCurrent
 * parameters: None
 * return value: Returns the location object that represents the neighbor
 * and current direction
 *
 * The purpose of this function is to return the
 * location that represents current the neighbor
 */

Location Location::iterationCurrent() const {
    Location neighbor = *this;

    neighbor.row = this->row;
    neighbor.col = this->col;

    if(nextDirection == RIGHT){
        neighbor.col += 1;
    }
    else if(nextDirection == DOWN){
        neighbor.row += 1;
    }
    else if(nextDirection == LEFT){
        neighbor.col -= 1;
    }
    else if(nextDirection == UP){
        neighbor.row -= 1;
    }

    return neighbor;
}

/** iterationAdvance
 * parameters:None
 * return value: None
 *
 * The purpose of this function is to advance the iteration to the next
 * direction
 */

void Location::iterationAdvance(){
    if(nextDirection != DONE){
        nextDirection += 1;
    }

}

/** iterationDone
 * parameters: None
 * return value: returns true if the iteration is done, if not returns false
 *
 * The purpose of this function is to check if the iteration has completed
 */

bool Location::iterationDone() const{
    if(nextDirection == DONE){
        return true;
    }
    else{
        return false;
    }
}

/** operator==
 * parameters:
 * - loc: References the location being compared to the objects
 * return value: if the locations are equal it returns true,
 * otherwise it returns false
 *
 * The purpose of this function is to compare the two location of row and col
 * to see if they are equal
 */

bool Location::operator==(const Location &loc) const{
    if (row == loc.row && col == loc.col){
        return true;
    }
    else {
        return false;
    }

}

/** operator<<
 * parameters:
 * - loc: References the location row and col objects
 * - os: References the output stream where location data will be outputted
 * return value: Returns the location row and col on the ostream
 *
 * The purpose of this function is to output the location's row and col values
 */

ostream &operator<<(ostream &os, const Location &loc){
    os << loc.row << " " << loc.col;
    return os;
}

/** operator>>
 * parameters:
 * - loc: The input stream where input data is read in from
 * - os: The Reference to the location object being changed
 * return value: the istream row and col
 *
 * The purpose of this function is put the row and col values from the istream
 * to the designated location
 */

istream &operator>>(istream &is, Location &loc){
    is >> loc.row >> loc.col;
    return is;
}





