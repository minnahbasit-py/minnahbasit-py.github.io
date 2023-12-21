#include <iostream>
#include <string>
#include <vector>
#include "passfailcourse.h"

using namespace std;

//You complete the cpp file below
PassFailCourse::PassFailCourse(string name, int credit, double threshold): Course(name,credit) {
  this->threshold = threshold;
}

string PassFailCourse::getFinalLetterGrade(double grade) {
  string letter_grade = "";
  if (grade < threshold) {
    letter_grade = "NP";
  }
  else {
    letter_grade = "P";
  }
  return letter_grade;
}