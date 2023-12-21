#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Complete this header file below
class Course {
  public:
    Course(string name, int credit);
    string getName();
    int getNumCredit();
    virtual string getFinalLetterGrade(double grade) = 0;
  private:
    int credit;
    string name;
};
#endif