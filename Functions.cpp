#include "Header.h"
using std::ifstream;


vector<string> parseLine(string line)
{
	int pos = 0;
	vector<string> res;
	while (line.find(' ', pos + 1) != string::npos)
	{
		int prevPos = pos;
		pos = line.find(' ', pos + 1);
		int len;
		if (prevPos == 0)
			len = pos - prevPos;
		else
			len = pos - prevPos - 1;

		res.push_back(line.substr(prevPos, len));
		if (line.find(' ', pos + 1) == string::npos)
			res.push_back(line.substr(pos + 1, line.length() - pos - 1));
	}
	return res;
}

void readFileTo(Student* arr, int size)
{
	string buffer;
	ifstream fileStream;
	fileStream.open("data-ansi.txt");
	bool first = true;
	int i = 0, pos = 1;
	while (getline(fileStream, buffer))
	{
		if (not first)
		{
			if (pos == 1)
			{
				vector<string> data = parseLine(buffer);
				arr[i].name = data.at(0);
				arr[i].surname = data.at(1);
			}
			if (pos == 2) { arr[i].year = buffer; }
			if (pos == 3)
			{
				for (char num : buffer)
				{
					int grade = num - '0';
					arr[i].lastGrades.push_back(grade);
				}
				++i;
				pos = 0;
			}

			++pos;
		}
		else
			first = false;
	}

	fileStream.close();
}

void printStudentData(Student data)
{
	cout << data.name << ' ' << data.surname << '\n';
	cout << data.year << '\n';
	for (int grade : data.lastGrades)
		cout << grade << ' ';
}

bool hasBadGrades(Student data)
{
	for (int grade : data.lastGrades)
		if (grade < 4)
			return true;
	return false;
}

int maxRelativeGrade(Student* arr, int size, string year)
{
	int maxSum = 0;
	for (int i = 0; i < size; ++i)
	{
		if (arr[i].year.length() == 3)
		{
			if (arr[i].year.substr(0, 2) == year)
			{
				int sum = 0;
				for (int grade : arr[i].lastGrades)
					sum += grade;
				if (sum > maxSum)
					maxSum = sum;
			}
		}
		else
			if (arr[i].year.substr(0, 1) == year)
			{
				int sum = 0;
				for (int grade : arr[i].lastGrades)
					sum += grade;
				if (sum > maxSum)
					maxSum = sum;
			}
	}
	return maxSum;
}

bool isBestStudent(Student data, Student* arr, int size)
{
	int maxGrade;
	if (data.year.length() == 3)
		maxGrade = maxRelativeGrade(arr, size, data.year.substr(0, 2));
	else
		maxGrade = maxRelativeGrade(arr, size, data.year.substr(0, 1));

	int gradeSum = 0;
	for (int grade : data.lastGrades)
		gradeSum += grade;

	return (gradeSum >= maxGrade && not hasBadGrades(data));
}

int countWithGoodGrades(Student* arr, int size)
{
	int count = 0;
	for (int i = 0; i < size; ++i)
		if (not hasBadGrades(arr[i]))
			++count;
	return count;
}