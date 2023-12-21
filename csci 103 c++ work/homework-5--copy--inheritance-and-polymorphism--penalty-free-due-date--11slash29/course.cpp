#include <iostream>
#include <string>
#include <vector>
#include "course.h"

using namespace std;

//You complete the cpp file below
Course::Course(string name, int credit) {
  this->name = name;
  this->credit = credit;
}
string Course::getName() {
  return this->name;
}
int Course::getNumCredit() {
  return this->credit;
}


