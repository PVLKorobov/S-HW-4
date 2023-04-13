#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using std::getline;
using std::string;
using std::vector;
using std::stoi;
using std::cout;


struct Student
{
	string name;
	string surname;
	string year;
	vector<int> lastGrades;
};


void readFileTo(Student* arr, int size);
void printStudentData(Student data);
bool isBestStudent(Student data, Student* arr, int size);
int countWithGoodGrades(Student* arr, int size);