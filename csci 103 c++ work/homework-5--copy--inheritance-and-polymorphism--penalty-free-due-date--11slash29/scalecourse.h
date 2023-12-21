#ifndef SCALECOURSE_H
#define SCALECOURSE_H


#include <iostream>
#include <string>
#include <vector>
#include "course.h"
using namespace std;


//Complete this header file below
class ScaleCourse : public Course {
  public:
  ScaleCourse(string name, int credit, vector<double> scales);
  string getFinalLetterGrade(double grade);
  private:
  vector<double> scales;
};

#endif