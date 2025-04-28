#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

struct Course {
    string courseName;
    string courseNumber;
    vector<string> prerequisites;
};

vector<Course> courses;
void loadDataStructure() {
        string fileName;
        fileName = "CS 300 ABCU_Advising_Program_Input.csv";
        ifstream file(fileName);

        if (!file.is_open()) {
            cout << "Error opening file: " << fileName << endl;
            exit(1);
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string courseNumber;
            string courseName;
            vector<string> prerequisites;

            // Extract course number and title
            if (getline(ss, courseNumber, ' ') && getline(ss, courseName, ' ')) {
                // Extract prerequisites (if any)
                string prerequisite;
                while (getline(ss, prerequisite, ',')) {
                    prerequisites.push_back(prerequisite);
                }

                // Create a Course object and add to the vector
                Course course;
                course.courseNumber = courseNumber;
                course.courseName = courseName;
                course.prerequisites = prerequisites;
                courses.push_back(course);
            }
            else {
                cout << "Error: Invalid line format in file: " << line << endl;
            }
        }

        file.close();
}
void printCourseList(const vector<Course>& courses) {
    cout << "Here is a sample schedule:" << endl;
    // Sort the courses alphabetically by course number
    vector<Course> sortedCourses = courses;  // Create a copy to sort
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    cout << "Here is a sample schedule:" << endl;
    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << ": " << course.courseName << endl;
    }
    cout << endl;
}
void printCourseInformation() {
    string courseNumber;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    // Find the course
    bool found = false;
    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            // Print course information
            cout << "Course: " << course.courseNumber << " - " << course.courseName << endl;

            if (!course.prerequisites.empty()) {
                cout << "Prerequisites:" << endl;
                for (const string& prereq : course.prerequisites) {
                    bool prereqFound = false;
                    for (const auto& prereqCourse : courses) {
                        if (prereqCourse.courseNumber == prereq) {
                            cout << prereqCourse.courseNumber << " - " << prereqCourse.courseName << endl;
                            prereqFound = true;
                            break;
                        }
                    }
                    if (!prereqFound) {
                        cout << "  Error: Could not find prerequisite course " << prereq << endl;
                    }
                }
            }
            else {
                cout << "No prerequisites." << endl;
            }

            found = true;
            break; // Exit the loop after finding the course
        }
    }

    // Handle case where the course is not found
    if (!found) {
        cout << "Course not found." << endl;
    }


}


int main()
{
    int userChoice = 0;
    while (userChoice != 9) {
        cout << "Welcome to the course planner." << endl;
        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? " << endl;
        cin >> userChoice;

        switch (userChoice) {
        case 1:
            loadDataStructure();
            break;
        case 2:
            printCourseList(courses);
            break;
        case 3:
            printCourseInformation();
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << userChoice << " is not a valid option." << endl;
            break;
        }


    }

  
}