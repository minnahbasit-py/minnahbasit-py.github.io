#ifndef PASSFAILCOURSE_H
#define PASSFAILCOURSE_H

#include <iostream>
#include <string>
#include <vector>
#include "course.h"
using namespace std;

//Complete this header file below
class PassFailCourse: public Course {
  public:
  PassFailCourse(string name, int credit, double threshold);
  string getFinalLetterGrade(double grade);
  private:
  double threshold;
};

#endif