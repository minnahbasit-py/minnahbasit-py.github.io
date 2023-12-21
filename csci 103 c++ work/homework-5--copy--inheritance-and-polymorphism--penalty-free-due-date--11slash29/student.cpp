#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "student.h"

using namespace std;


Student::Student(string name){
  //You complete
  name_ = name;
  
}


void Student::setMajor(string major){
  //You complete
  major_ = major;
  
  
  
  
  
}

//Add course to the courses_ vector
//Add course_grade to the grades_ vector
void Student::addCourse(Course* course, double course_grade){
  //You complete
  courses_.push_back(course);
  grades_.push_back(course_grade);
  
}

//Compute the overall GPA
double Student::getTotalGPA() const {
  //you complete
  double gpa = 0;
  int total_credits = 0;
  for (unsigned int i = 0; i < courses_.size(); i++) {
    string letter_grade = courses_[i]->getFinalLetterGrade(grades_[i]);
    if (letter_grade == "A") {
      gpa += 4.0 * courses_[i]->getNumCredit();
      total_credits += courses_[i]->getNumCredit();
    }
    if (letter_grade == "B") {
      gpa += 3.0 * courses_[i]->getNumCredit();
      total_credits += courses_[i]->getNumCredit();
    }
    if (letter_grade == "C") {
      gpa += 2.0 * courses_[i]->getNumCredit();
      total_credits += courses_[i]->getNumCredit();
    }
    if (letter_grade == "D") {
      gpa += 1.0 * courses_[i]->getNumCredit();
      total_credits += courses_[i]->getNumCredit();
    }
    if (letter_grade == "F") {
      total_credits += courses_[i]->getNumCredit();
    }
  }
  double total_gpa = gpa/total_credits;
  return total_gpa;
}

//Get the total course credits.
int Student::getSemesterCourseCredit() const {
  //you complete
  int total_credit = 0;
  for (size_t i = 0; i < courses_.size(); i++) {
    if(courses_[i]->getFinalLetterGrade(grades_[i]) != "NP") {
      total_credit += courses_[i]->getNumCredit();
    }
  }
  return total_credit;
}


//***********************
//This function is done. 
//do Not change anything
//***********************
void Student::printReport() const
{
  cout<<"Name: "<<name_<<endl;
  cout<<"Major: "<<major_<<endl;
  cout<<"Courses Taken: "<<endl;
  cout << '|' << setw(10) <<"Course";
  cout << '|' << setw(10) <<"Credit";
  cout << '|' << setw(10) <<"RawGrade";
  cout << '|' << setw(12) <<"LetterGrade";
  cout <<endl;
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(12) <<"------------";
  cout <<endl;
  for(size_t i = 0; i < courses_.size(); i++){
    cout << '|' << setw(10) << courses_[i]->getName();
    cout << '|' << setw(10) << courses_[i]->getNumCredit();
    cout << '|' << setw(10) << grades_[i];
    cout << '|' << setw(12) << courses_[i]->getFinalLetterGrade(grades_[i]);
    cout << endl;
  }
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(10) <<"----------";
  cout << '|' << setw(12) <<"------------";
  cout <<endl;
  cout<<"Total Credits: "<<getSemesterCourseCredit()<<endl;
  cout<<"Overall GPA: "<< setprecision(2) << std::fixed << getTotalGPA()<<endl;
}
