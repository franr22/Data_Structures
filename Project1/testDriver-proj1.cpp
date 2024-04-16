#include <iostream>
#include "location-proj1.h"


int main() {

    cout << "Testing Default Constructor" << endl;
    Location location;
    cout << "Initial Location(Expected Output: 1 1): " << location << endl << endl;

    cout << "Testing Iteration Begin Function" << endl;
    location.iterationBegin();
    cout << "Location after iterationBegin(Expected: 1 2): " << location.iterationCurrent() << endl << endl;

    cout << "Testing Iteration Current and Advance Functions" << endl;
    while (!location.iterationDone()) {
        Location current = location.iterationCurrent();
        cout << "Current Neighbor: " << current << endl;
        location.iterationAdvance();
    }
    cout << endl;
    /*
     * Current Neighbor: 1 2 (Expected output)
     * Current Neighbor: 2 1 (Expected output)
     * Current Neighbor: 1 0 (Expected output)
     * Current Neighbor: 0 1 (Expected output)
     */

    cout << "Testting Equality Operation Function" << endl;
    Location location1, location2;
    location1.row = 3; location1.col = 4;
    location2.row = 3; location2.col = 4;
    if (location1 == location2) {
        cout << "Equality operator has passes the test." << endl;
    }
    cout << endl;

    cout << "Testing Stream Operators Function" << endl;
    cout << "Enter a Location in the Format 'row col': ";
    cin >> location;
    cout << "You Entered: " << location << endl;

    return 0;
}

/*
 * unsolvable Maze (Maze One)
 * 5
 * -2 -2
 * -1 -1
 * 0 0
 * 1 1
 * 2 2
 * 0 0
 * 2 2
 *
 * Maze Two
 * 4
 * 0 0
 * 0 1
 * 1 1
 * 2 1
 * 0 0
 * 2 1
 *
 * Maze Three
 * 16
 * 0 0
 * 0 1
 * 0 2
 * 0 3
 * 1 0
 * 1 1
 * 1 2
 * 1 3
 * 2 0
 * 2 1
 * 2 2
 * 2 3
 * 3 0
 * 3 1
 * 3 2
 * 3 3
 *
 * Maze Four
 * 6
 * 2 2
 * 2 3
 * 3 3
 * 3 2
 * 4 2
 * 4 3
 * 2 2
 * 4 3
 *
 * Maze Five
 * 7
 * 1 1
 * 1 2
 * 2 2
 * 2 3
 * 3 3
 * 3 4
 * 4 4
 * 1 1
 * 4 4
 *
 * Maze Six
 *
 * 8
 * 5 5
 * 5 6
 * 6 6
 * 7 6
 * 7 7
 * 7 8
 * 8 8
 * 9 8
 * 5 5
 * 9 8
 *
 * Maze Seven
 * 10
 * 0 0
 * 0 1
 * 0 2
 * 1 2
 * 2 2
 * 2 1
 * 2 0
 * 1 0
 * 1 1
 * 2 3
 *
 *
 * Maze Eight
 * 5
 * 0 0
 * 1 0
 * 2 0
 * 3 0
 * 3 1
 *
 *
 * Maze Nine
 * 13
 * 0 0
 * 0 1
 * 0 2
 * 0 3
 * 1 3
 * 1 2
 * 1 1
 * 1 0
 * 2 0
 * 2 1
 * 2 2
 * 2 3
 * 3 3
 *
 * Maze Ten
 * 6
 * 0 0
 * 1 0
 * 2 0
 * 2 1
 * 1 1
 * 0 1
 *
*/