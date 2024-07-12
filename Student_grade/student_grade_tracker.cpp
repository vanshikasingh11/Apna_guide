#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>

using namespace std;

struct Student {
    string name;
    string id;
    vector<float> grades;
    float overallGrade;

    Student(string n, string i, vector<float> g)
        : name(n), id(i), grades(g), overallGrade(0) {}
};

class StudentGradeTracker {
private:
    vector<Student> students;

    void calculateOverallGrades() {
        for (auto& student : students) {
            if (!student.grades.empty()) {
                student.overallGrade = accumulate(student.grades.begin(), student.grades.end(), 0.0f) / student.grades.size();
            } else {
                student.overallGrade = 0;
            }
        }
    }

    void saveData() {
        ofstream outFile("C:\\Users\\VANSHIKA\\project_c++\\Student_grade\\student_grade.txt");
        if (!outFile) {
            cerr << "Error opening file for writing." << endl;
            return;
        }
        for (const auto& student : students) {
            outFile << student.name << "," << student.id << ",";
            for (const auto& grade : student.grades) {
                outFile << grade << ",";
            }
            outFile << student.overallGrade << "\n";
        }
        outFile.close();
    }

    void loadData() {
        ifstream inFile("C:\\Users\\VANSHIKA\\project_c++\\Student_grade\\student_grade.txt");
        if (!inFile) {
            cerr << "Error opening file for reading." << endl;
            return;
        }
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) {
                continue;
            }
            stringstream ss(line);
            string name, id, gradeStr;
            vector<float> grades;

            getline(ss, name, ',');
            getline(ss, id, ',');

            // Read all grades and the overallGrade (last value)
            vector<string> tokens;
            while (getline(ss, gradeStr, ',')) {
                tokens.push_back(gradeStr);
            }

            // Separate grades and overallGrade
            for (size_t i = 0; i < tokens.size() - 1; ++i) {
                try {
                    grades.push_back(stof(tokens[i]));
                } catch (const invalid_argument&) {
                    cerr << "Invalid grade found in the file, skipping: " << tokens[i] << endl;
                } catch (const out_of_range&) {
                    cerr << "Grade out of range found in the file, skipping: " << tokens[i] << endl;
                }
            }

            if (!grades.empty()) {
                students.emplace_back(name, id, grades);
            }
        }
        inFile.close();
        calculateOverallGrades();
    }

public:
    StudentGradeTracker() {
        loadData();
    }

    void addStudentFromInput() {
        string name, id, gradeStr;
        vector<float> grades;

        cout << "Enter student name: ";
        getline(cin >> ws, name);

        cout << "Enter student ID: ";
        getline(cin, id);

        cout << "Enter grades (separated by spaces): ";
        getline(cin, gradeStr);

        istringstream iss(gradeStr);
        float grade;
        while (iss >> grade) {
            grades.push_back(grade);
        }

        students.emplace_back(name, id, grades);
        calculateOverallGrades();
        saveData();

        cout << "Student added successfully.\n";
    }

    void displayClassAverages() {
        if (students.empty()) {
            cout << "No students data available.\n";
            return;
        }

        float totalAverage = 0;
        for (const auto& student : students) {
            totalAverage += student.overallGrade;
        }
        cout << "Class Average: " << totalAverage / students.size() << endl;
    }

    void displayTopStudents() {
        if (students.empty()) {
            cout << "No students data available.\n";
            return;
        }

        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.overallGrade > b.overallGrade;
        });
        cout << "Top 3 Students:" << endl;
        for (int i = 0; i < min(3, static_cast<int>(students.size())); ++i) {
            cout << students[i].name << " (ID: " << students[i].id << ") - Overall Grade: " << students[i].overallGrade << endl;
        }
    }
};

int main() {
    StudentGradeTracker tracker;

    char choice;
    do {
        cout << "\n1. Add a student\n";
        cout << "2. Display class average\n";
        cout << "3. Display top students\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character left in buffer

        switch (choice) {
            case '1':
                tracker.addStudentFromInput();
                break;
            case '2':
                tracker.displayClassAverages();
                break;
            case '3':
                tracker.displayTopStudents();
                break;
            case '4':
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '4');

    return 0;
}
