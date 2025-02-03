#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

struct Course {
    char name[50];
    int units;
    float grade;
};

struct Student {
    char firstName[50];
    char lastName[50];
    int studentId;
    char major[50];
    Course courses[10];
    int courseCount;
    float gpa;
};

float calculateGPA(Student& student) {
    if (student.courseCount == 0) return 0.0f;
    float totalGradePoints = 0.0f;
    int totalUnits = 0;
    for (int i = 0; i < student.courseCount; ++i) {
        totalGradePoints += student.courses[i].grade * student.courses[i].units;
        totalUnits += student.courses[i].units;
    }
    return totalUnits > 0 ? totalGradePoints / totalUnits : 0.0f;
}

void listStudents(Student students[], int count, const char* filterMajor = nullptr) {
    cout << "Student List:\n";
    cout << setw(20) << "First Name" << setw(20) << "Last Name" << setw(15) << "Student ID"
         << setw(15) << "Major" << setw(10) << "GPA" << endl;
    cout << string(80, '-') << endl;

    for (int i = 0; i < count; ++i) {
        if (filterMajor != nullptr && strcmp(students[i].major, filterMajor) != 0) continue;

        cout << setw(20) << students[i].firstName << setw(20) << students[i].lastName
             << setw(15) << students[i].studentId << setw(15) << students[i].major
             << setw(10) << fixed << setprecision(2) << students[i].gpa << endl;
    }
    cout << endl;
}

void showTranscript(const Student& student) {
    cout << "Student Transcript:\n";
    cout << "Name: " << student.firstName << " " << student.lastName << endl;
    cout << "Student ID: " << student.studentId << endl;
    cout << "Major: " << student.major << endl;
    cout << "GPA: " << fixed << setprecision(2) << student.gpa << endl;
    cout << "\nCourse List:\n";
    cout << setw(20) << "Course Name" << setw(10) << "Units" << setw(10) << "Grade" << endl;
    cout << string(40, '-') << endl;

    for (int i = 0; i < student.courseCount; ++i) {
        cout << setw(20) << student.courses[i].name << setw(10) << student.courses[i].units
             << setw(10) << student.courses[i].grade << endl;
    }
    cout << endl;
}

void sortStudentsByGPA(Student students[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (students[j].gpa < students[j + 1].gpa) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int main() {
    const int MAX_STUDENTS = 10;
    Student students[MAX_STUDENTS];
    int studentCount = 0;

    int choice;
    while (true) {
        cout << "Menu:\n";
        cout << "1. Register Student\n";
        cout << "2. Register Courses\n";
        cout << "3. List Students\n";
        cout << "4. Print Transcript\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            if (studentCount >= MAX_STUDENTS) {
                cout << "Maximum number of students reached.\n";
                continue;
            }

            cout << "Register New Student:\n";
            cout << "First Name: ";
            cin.ignore();
            cin.getline(students[studentCount].firstName, 50);
            cout << "Last Name: ";
            cin.getline(students[studentCount].lastName, 50);
            cout << "Student ID: ";
            cin >> students[studentCount].studentId;
            cout << "Major: ";
            cin.ignore();
            cin.getline(students[studentCount].major, 50);

            students[studentCount].courseCount = 0;
            students[studentCount].gpa = 0.0f;

            studentCount++;
            cout << "Student registered successfully.\n";

        } else if (choice == 2) {
            int id;
            cout << "Enter Student ID to register a course: ";
            cin >> id;

            bool found = false;
            for (int i = 0; i < studentCount; ++i) {
                if (students[i].studentId == id) {
                    if (students[i].courseCount >= 10) {
                        cout << "Maximum number of courses registered.\n";
                        break;
                    }

                    cout << "Register New Course:\n";
                    cout << "Course Name: ";
                    cin.ignore();
                    cin.getline(students[i].courses[students[i].courseCount].name, 50);
                    cout << "Units: ";
                    cin >> students[i].courses[students[i].courseCount].units;
                    cout << "Grade: ";
                    cin >> students[i].courses[students[i].courseCount].grade;

                    students[i].courseCount++;
                    students[i].gpa = calculateGPA(students[i]);
                    cout << "Course registered successfully.\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "No student found with this ID.\n";
            }

        } else if (choice == 3) {
            cout << "List Students:\n";
            cout << "1. List All Students\n";
            cout << "2. Filter by Major\n";
            cout << "Choice: ";
            cin >> choice;

            if (choice == 1) {
                sortStudentsByGPA(students, studentCount);
                listStudents(students, studentCount);
            } else if (choice == 2) {
                char filterMajor[50];
                cout << "Enter Major to Filter: ";
                cin.ignore();
                cin.getline(filterMajor, 50);
                listStudents(students, studentCount, filterMajor);
            } else {
                cout << "Invalid choice.\n";
            }

        } else if (choice == 4) {
            int id;
            cout << "Enter Student ID to Print Transcript: ";
            cin >> id;

            bool found = false;
            for (int i = 0; i < studentCount; ++i) {
                if (students[i].studentId == id) {
                    showTranscript(students[i]);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "No student found with this ID.\n";
            }

        } else if (choice == 5) {
            cout << "Exiting the program.\n";
            break;

        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
//برای توضیح با من هماهنگ کنید
//@mido_ali19
