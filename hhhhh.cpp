#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_COURSES = 50;

struct Course {
    char course_name[50];
    float grade;
    int units;
};

struct Student {
    char name[100];
    char student_id[20];
    char major[50];
    Course courses[MAX_COURSES];
    int course_count;
};

class UniversitySystem {
private:
    Student students[MAX_STUDENTS];
    int student_count;

public:
    UniversitySystem() : student_count(0) {}

    void register_student(const char* name, const char* student_id, const char* major) {
        if (student_count >= MAX_STUDENTS) {
            cout << "Registration capacity is full!" << endl;
            return;
        }
        strcpy(students[student_count].name, name);
        strcpy(students[student_count].student_id, student_id);
        strcpy(students[student_count].major, major);
        students[student_count].course_count = 0;
        cout << "Student " << name << " has been successfully registered." << endl;
        student_count++;
    }

    void add_course_to_student(const char* student_id, const char* course_name, float grade, int units) {
        if (grade < 0 || grade > 20) {
            cout << "Invalid grade! Grade must be between 0 and 20." << endl;
            return;
        }
        if (units <= 0) {
            cout << "Invalid units! Units must be a positive number." << endl;
            return;
        }
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].student_id, student_id) == 0) {
                if (students[i].course_count >= MAX_COURSES) {
                    cout << "Course capacity is full!" << endl;
                    return;
                }
                strcpy(students[i].courses[students[i].course_count].course_name, course_name);
                students[i].courses[students[i].course_count].grade = grade;
                students[i].courses[students[i].course_count].units = units;
                students[i].course_count++;
                cout << "Course " << course_name << " has been added to student " << students[i].name << "." << endl;
                return;
            }
        }
        cout << "Student with this ID not found." << endl;
    }

    float calculate_gpa(int student_index) {
        float total_points = 0;
        int total_units = 0;
        for (int j = 0; j < students[student_index].course_count; j++) {
            total_points += students[student_index].courses[j].grade * students[student_index].courses[j].units;
            total_units += students[student_index].courses[j].units;
        }
        return total_units > 0 ? total_points / total_units : 0;
    }

    void list_students(const char* major = nullptr) {
        cout << "==================================================" << endl;
        cout << "*                   Students List               *" << endl;
        cout << "==================================================" << endl;
        cout << "| Name               | Student ID   | Major         | GPA   |" << endl;
        cout << "--------------------------------------------------" << endl;
        for (int i = 0; i < student_count; i++) {
            if (major == nullptr || strcmp(students[i].major, major) == 0) {
                float gpa = calculate_gpa(i);
                cout << "| " << students[i].name << setw(15 - strlen(students[i].name)) << " | "
                     << students[i].student_id << setw(12 - strlen(students[i].student_id)) << " | "
                     << students[i].major << setw(14 - strlen(students[i].major)) << " | "
                     << fixed << setprecision(2) << gpa << " |" << endl;
            }
        }
        cout << "==================================================" << endl;
    }

    void issue_transcript(const char* student_id) {
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].student_id, student_id) == 0) {
                float gpa = calculate_gpa(i);
                cout << "========================================" << endl;
                cout << "Full Name: " << students[i].name << endl;
                cout << "Student ID: " << students[i].student_id << endl;
                cout << "Major: " << students[i].major << endl;
                cout << "GPA: " << fixed << setprecision(2) << gpa << endl;
                cout << "----------------------------------------" << endl;
                cout << "Courses List:" << endl;
                for (int j = 0; j < students[i].course_count; j++) {
                    cout << "Course: " << students[i].courses[j].course_name
                         << " | Units: " << students[i].courses[j].units
                         << " | Grade: " << students[i].courses[j].grade << endl;
                }
                cout << "========================================" << endl;
                return;
            }
        }
        cout << "Student with this ID not found." << endl;
    }

    void edit_student(const char* student_id, const char* new_name, const char* new_major) {
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].student_id, student_id) == 0) {
                strcpy(students[i].name, new_name);
                strcpy(students[i].major, new_major);
                cout << "Student information has been successfully updated." << endl;
                return;
            }
        }
        cout << "Student with this ID not found." << endl;
    }

    void delete_student(const char* student_id) {
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].student_id, student_id) == 0) {
                for (int j = i; j < student_count - 1; j++) {
                    students[j] = students[j + 1];
                }
                student_count--;
                cout << "Student has been successfully deleted." << endl;
                return;
            }
        }
        cout << "Student with this ID not found." << endl;
    }

    void edit_course(const char* student_id, const char* course_name, float new_grade, int new_units) {
        if (new_grade < 0 || new_grade > 20) {
            cout << "Invalid grade! Grade must be between 0 and 20." << endl;
            return;
        }
        if (new_units <= 0) {
            cout << "Invalid units! Units must be a positive number." << endl;
            return;
        }
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].student_id, student_id) == 0) {
                for (int j = 0; j < students[i].course_count; j++) {
                    if (strcmp(students[i].courses[j].course_name, course_name) == 0) {
                        students[i].courses[j].grade = new_grade;
                        students[i].courses[j].units = new_units;
                        cout << "Course information has been successfully updated." << endl;
                        return;
                    }
                }
                cout << "Course not found for this student." << endl;
                return;
            }
        }
        cout << "Student with this ID not found." << endl;
    }

    void delete_course(const char* student_id, const char* course_name) {
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].student_id, student_id) == 0) {
                for (int j = 0; j < students[i].course_count; j++) {
                    if (strcmp(students[i].courses[j].course_name, course_name) == 0) {
                        for (int k = j; k < students[i].course_count - 1; k++) {
                            students[i].courses[k] = students[i].courses[k + 1];
                        }
                        students[i].course_count--;
                        cout << "Course has been successfully deleted." << endl;
                        return;
                    }
                }
                cout << "Course not found for this student." << endl;
                return;
            }
        }
        cout << "Student with this ID not found." << endl;
    }

    void save_data_to_file(const char* filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file for saving data." << endl;
            return;
        }
        for (int i = 0; i < student_count; i++) {
            file << students[i].name << "," << students[i].student_id << "," << students[i].major << ",";
            for (int j = 0; j < students[i].course_count; j++) {
                file << students[i].courses[j].course_name << ":" << students[i].courses[j].grade << ":"
                     << students[i].courses[j].units;
                if (j != students[i].course_count - 1) file << ";";
            }
            file << endl;
        }
        file.close();
        cout << "Data has been saved to file: " << filename << endl;
    }

    void load_data_from_file(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file for loading data." << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            Student student;
            int course_count = 0;
            size_t pos = line.find(",");
            strcpy(student.name, line.substr(0, pos).c_str());
            line.erase(0, pos + 1);

            pos = line.find(",");
            strcpy(student.student_id, line.substr(0, pos).c_str());
            line.erase(0, pos + 1);

            pos = line.find(",");
            strcpy(student.major, line.substr(0, pos).c_str());
            line.erase(0, pos + 1);

            if (!line.empty()) {
                string course_info = line;
                while (!course_info.empty()) {
                    pos = course_info.find(";");
                    string course = course_info.substr(0, pos);
                    course_info.erase(0, pos + 1);

                    size_t colon_pos = course.find(":");
                    strcpy(student.courses[course_count].course_name, course.substr(0, colon_pos).c_str());
                    course.erase(0, colon_pos + 1);

                    colon_pos = course.find(":");
                    student.courses[course_count].grade = stof(course.substr(0, colon_pos));
                    course.erase(0, colon_pos + 1);

                    student.courses[course_count].units = stoi(course);
                    course_count++;
                }
            }
            student.course_count = course_count;
            students[student_count++] = student;
        }
        file.close();
        cout << "Data has been loaded from file: " << filename << endl;
    }
};

int main() {
    UniversitySystem system;

    system.register_student("Ali Ahmad", "98123456", "Computer Science");
    system.register_student("Fateme Rezaei", "98654321", "Industrial Engineering");

    system.add_course_to_student("98123456", "Programming Fundamentals", 18, 3);
    system.add_course_to_student("98123456", "Discrete Mathematics", 16, 3);
    system.add_course_to_student("98654321", "Production Management", 17, 2);

    cout << "\nList of All Students:" << endl;
    system.list_students();

    cout << "\nList of Computer Science Students:" << endl;
    system.list_students("Computer Science");

    cout << "\nTranscript for Student 98123456:" << endl;
    system.issue_transcript("98123456");

    cout << "\nEdit Student 98123456:" << endl;
    system.edit_student("98123456", "Ali Ahmad New", "Computer Science");

    cout << "\nEdit Course 'Programming Fundamentals' for Student 98123456:" << endl;
    system.edit_course("98123456", "Programming Fundamentals", 19, 3);

    cout << "\nDelete Course 'Discrete Mathematics' for Student 98123456:" << endl;
    system.delete_course("98123456", "Discrete Mathematics");

    cout << "\nDelete Student 98654321:" << endl;
    system.delete_student("98654321");

    system.save_data_to_file("students_data.txt");

    system.load_data_from_file("students_data.txt");

    return 0;
}


//                                        توضیح با من هماهنگ کن



//                                               mido_ali19
