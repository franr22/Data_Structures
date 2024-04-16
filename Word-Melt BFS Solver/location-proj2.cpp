/*
 * file: location-proj2.cpp
 * author: Francisco Rios
 * course: CSI 3334
 * assignment: Project 2
 * due date: February, 16 2023
 * version: 3.23, c++14
 * This purpose of this driver is to use code the implementations
 * for the location functions.
 *
 */
#include "location-proj2.h"

Location::Location(){
    iterationMode = CHANGE_LETTER;
    indexToChange = 0;
    nextLetter = 'a';
}

void Location::iterationBegin(void){
    iterationMode = CHANGE_LETTER;
}

Location Location::iterationCurrent(void) const{

    Location neighbor;
    neighbor.word = word;

    if(iterationMode == CHANGE_LETTER){
        neighbor.word[indexToChange] = nextLetter;
    }
    else if(iterationMode == INSERT_LETTER){
        neighbor.word.insert(indexToChange,1,nextLetter);
    }
    else if(iterationMode == DELETE_LETTER){
        neighbor.word.erase(indexToChange,1);
    }

    return neighbor;
}

void Location::iterationAdvance(void){

    if (iterationMode == CHANGE_LETTER) {
        if (nextLetter < 'z') {
            nextLetter++;
        } else if (word.length() > indexToChange) {
            nextLetter = 'a';
            indexToChange++;
        }
        if (word[indexToChange] == nextLetter) {
            nextLetter++;
            if (nextLetter > 'z') {
                nextLetter = 'a';
                indexToChange++;
            }
        }
        if(word.length() <= indexToChange){
            iterationMode = INSERT_LETTER;
            nextLetter = 'a';
            indexToChange = 0;
        }
    }
    else if(iterationMode == INSERT_LETTER){
        if(nextLetter < 'z'){
            nextLetter++;
        }
        else if(word.length() > indexToChange){
            nextLetter = 'a';
            indexToChange++;
        }
        else{
            iterationMode = DELETE_LETTER;
            indexToChange = 0;
        }
    }
    else if(iterationMode == DELETE_LETTER){
        if(indexToChange < word.length() - 1){
            indexToChange++;
        }
        else{
            iterationMode = DONE;
        }
    }
}

bool Location::iterationDone(void) const{
    return iterationMode == DONE;
}

bool Location::operator==(const Location &loc) const{
    return word == loc.word;
}

ostream &operator<<(ostream &os, const Location &loc){
    os << loc.word;
    return os;
}

istream &operator>>(istream &is, Location &loc){
    is >> loc.word;
    return is;
}

bool Location::operator<(const Location &loc) const{
    return word < loc.word;
}