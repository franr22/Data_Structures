#include "process-proj5.h"
/*
 * file: process-proj5.cpp
 * author: Francisco Rios
 * course: CSI 2334
 * assignment Title: Project 5
 * due date: 4/12/24
 * version: 3.23, C++14
 * The purpose of this file to implement the Process class.
 */

/* Process Constructor
 * The purpose of this constructor is to set the id number
 * and initialize all the members to default values
 *
 * Parameters: theId- The Id number for this object
 * Return Value: none
 */
Process::Process(int theId){
    id = theId;
    submissionTime = 0;
    deadline = 0;
    requiredTime = 0;
    information = "";
}

/* Process run
 * The purpose of this function is to print out the running process id
 * and current systemTime. Followed by the information.
 *
 * Parameters: currentSystemTime - The current system's time
 * Return Value: the new runtime
 */
int Process::run(int currentSystemTime) const{
    int runtime;
    cout << "running process id " << id << " at "
    << currentSystemTime << endl;
    cout << information << endl;
    runtime = currentSystemTime + requiredTime;
    return runtime;
}

/* Process canComplete
 * The purpose of this function is to return true if the required time
 * is less than or equal to the time left until the deadline.
 *
 * Parameters: currentSystemTime - The current system's time
 * Return Value: if the process can be completed returns true, if not is false
 */
bool Process::canComplete(int currentSystemTime) const{
    return requiredTime <= (deadline - currentSystemTime);
}

/* Process getId
 * The purpose of this function is to get the Id of the
 * object
 *
 * Parameters: None
 * Return Value: The object's Id number
 */
int Process::getId() const{
    return id;
}

/* Process getSubmissionTime
 * The purpose of this function to get the object's submission time
 *
 * Parameters: None
 * Return Value: the object's submission time
 */
int Process::getSubmissionTime() const{
    return submissionTime;
}

/* Process operator<
 * The purpose of this function is to order the processes first by deadline,
 * and then the required time.
 *
 * Parameters: p - The process that's being compared
 * Return Value: returns true if the process and deadline are not equal
 */
bool Process::operator<(Process const &p) const {
    if (deadline != p.deadline) {
        return deadline < p.deadline;
    }
    if (requiredTime != p.requiredTime) {
        return requiredTime < p.requiredTime;
    }

    return id < p.id;
}

/* Process operator>>
 * The purpose of this function is to read in the values for submission time,
 * deadline, requiredTime and information.
 *
 * Parameters: is - The input stream
 *             p - The object's process
 * Return Value: The input stream buffer
 */
istream &operator>>(istream &is, Process &p){
    is >> p.submissionTime;
    is >> p.deadline;
    is >> p.requiredTime;

    getline(is >> ws, p.information);

    return is;
}



