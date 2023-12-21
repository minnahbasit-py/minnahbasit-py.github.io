#include <iostream>
#include <string>
#include <vector>
#include "scalecourse.h"

using namespace std;

//You complete the cpp file below
ScaleCourse::ScaleCourse(string name, int credit, vector<double>scales): Course(name,credit) {
  this->scales = scales;
}
string ScaleCourse::getFinalLetterGrade(double grade) {
  if (grade >= scales[0]) {
    return "A";
  }
  if (grade >= scales[1]) {
    return "B";
  }
  if (grade >= scales[2]) {
    return "C";
  }
  if (grade >= scales[3]) {
    return "D";
  }
  else {
    return "F";
  }
  return 0;
}
