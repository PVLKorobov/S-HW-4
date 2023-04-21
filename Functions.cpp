#include "Header.h"
using std::ifstream;


vector<string> parse_line(string line, char divider)
{
	int pos = 0;
	vector<string> res;
	while (line.find(divider, pos + 1) != string::npos)
	{
		int prevPos = pos;
		pos = line.find(divider, pos + 1);
		int len;
		if (prevPos == 0)
			len = pos - prevPos;
		else
			len = pos - prevPos - 1;

		res.push_back(line.substr(prevPos, len));
		if (line.find(divider, pos + 1) == string::npos)
			res.push_back(line.substr(pos + 1, line.length() - pos - 1));
	}
	return res;
}

string get_file_as_str()
{
	ifstream fileStream;
	fileStream.open("data-ansi.txt");
	string fileContents;
	string buffer;
	while (getline(fileStream, buffer))
		fileContents += buffer + '\n';

	fileStream.close();
	return fileContents;
}

Student** read_file_to(int size)
{
	Student** arr = new Student*[size];
	string fileContents = get_file_as_str();

	vector<string> segments = parse_line(fileContents, '=');
	segments.erase(segments.begin());

	return arr;
}

void print_student_data(Student* data)
{
	cout << data->name << ' ' << data->surname << '\n';
	cout << data->year << '\n';
	for (int grade : data->lastGrades)
		cout << grade << ' ';
}

bool has_bad_grades(Student* data)
{
	for (int grade : data->lastGrades)
		if (grade < 4)
			return true;
	return false;
}

int max_relative_grade(Student** arr, int size, string year)
{
	int maxSum = 0;
	for (int i = 0; i < size; ++i)
	{
		if (arr[i]->year.length() == 3)
		{
			if (arr[i]->year.substr(0, 2) == year)
			{
				int sum = 0;
				for (int grade : arr[i]->lastGrades)
					sum += grade;
				if (sum > maxSum)
					maxSum = sum;
			}
		}
		else
			if (arr[i]->year.substr(0, 1) == year)
			{
				int sum = 0;
				for (int grade : arr[i]->lastGrades)
					sum += grade;
				if (sum > maxSum)
					maxSum = sum;
			}
	}
	return maxSum;
}

bool is_best_student(Student* data, Student** arr, int size)
{
	int maxGrade;
	Student studStruct = *data;
	string year = studStruct.year;
	if (year.length() == 3)
		maxGrade = max_relative_grade(arr, size, year.substr(0, 2));
	else
		maxGrade = max_relative_grade(arr, size, year.substr(0, 1));

	int gradeSum = 0;
	vector<int> grades = data->lastGrades;
	for (int grade : grades)
		gradeSum += grade;

	return (gradeSum >= maxGrade && not has_bad_grades(data));
}

int count_with_good_grades(Student** arr, int size)
{
	int count = 0;
	for (int i = 0; i < size; ++i)
		if (not has_bad_grades(arr[i]))
			++count;
	return count;
}