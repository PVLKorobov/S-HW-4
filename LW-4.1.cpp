#include <iostream>
#include <Windows.h>
#include "Header.h"
using std::fstream;


int main()
{
    SetConsoleOutputCP(1251);
    int size;
    string buffer;

    fstream fileStream;
    fileStream.open("data-ansi.txt");
    getline(fileStream, buffer);
    size = stoi(buffer);
    fileStream.close();

    Student* structArray = new Student[size];
    readFileTo(structArray, size);

    cout << "Количество учеников с оценками не ниже 4: " << countWithGoodGrades(structArray, size) << '\n';

    vector<Student*> bestStudents;
    for (int i = 0; i < size; ++i)
        if (isBestStudent(structArray[i], structArray, size))
            bestStudents.push_back(&structArray[i]);
    cout << "Лучшие ученики школы\n";
    for (Student* studPtr : bestStudents)
    {
        printStudentData(*studPtr);
        cout << '\n';
    }
        
    delete[] structArray;
}