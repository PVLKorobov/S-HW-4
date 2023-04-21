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


Student** read_file_to(int size);
void print_student_data(Student* data);
bool is_best_student(Student* data, Student** arr, int size);
int count_with_good_grades(Student** arr, int size);