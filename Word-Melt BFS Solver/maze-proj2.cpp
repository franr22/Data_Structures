/*
 * file: maze-proj2.cpp
 * author: Francisco Rios
 * course: CSI 3334
 * assignment: Project 2
 * due date: February, 16 2023
 * version: 3.23, c++14
 * This purpose of this driver is to use code the implementations
 * for the maze functions.
 *
 */
#include "maze-proj2.h"

Maze::Maze(void) {
}


Location Maze::getStartLocation(void) const{
    return startLocation;

}
bool Maze::isValidLocation(const Location &loc) const{
    if(validLocations.find(loc) != validLocations.end()) {
        return true;
    }
    else{
        return false;
    }

}
bool Maze::isEndLocation(const Location &loc) const{
    if(endLocation == loc){
        return true;
    }
    else{
        return false;
    }
}

istream &operator>>(istream &is, Maze &m){
    m.validLocations.clear();
    int n;
    Location temp;

    is >> n;
    for(int i = 0; i < n; i++){
        is >> temp;
        m.validLocations.insert(temp);
    }
    is >> m.startLocation >> m.endLocation;

    return is;
}
