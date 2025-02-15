#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

const string ADMIN_PASSWORD = "admin123"; // Change this for security

struct Student {
    string name;
    int age;
    int marks;
};

// Function to authenticate admin
bool isAdmin() {
    string password;
    cout << "Enter Admin Password: ";
    cin >> password;
    return password == ADMIN_PASSWORD;
}

// Function to add student (Admin only)
void addStudent() {
    if (!isAdmin()) {
        cout << "Access Denied! Only admin can add students.\n";
        return;
    }

    Student student;
    cout << "Enter Student Name: ";
    cin >> student.name;
    cout << "Enter Age: ";
    cin >> student.age;
    
    // Marks validation
    do {
        cout << "Enter Marks (0-100): ";
        cin >> student.marks;
        if (student.marks < 0 || student.marks > 100) {
            cout << "Invalid input! Enter marks between 0-100.\n";
        }
    } while (student.marks < 0 || student.marks > 100);

    ofstream file("students.txt", ios::app);
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    file << student.name << "," << student.age << "," << student.marks << endl;
    file.close();
    cout << "Student added successfully!\n";
}

// Function to view students
void viewStudents() {
    ifstream file("students.txt");
    if (!file) {
        cout << "No student records found!\n";
        return;
    }

    string line;
    cout << "\n--- Student Records ---\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string name, age, marks;
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, marks, ',');

        cout << "Name: " << name << ", Age: " << age << ", Marks: " << marks << endl;
    }
    file.close();
}

// Function to search student
void searchStudent() {
    ifstream file("students.txt");
    if (!file) {
        cout << "No student records found!\n";
        return;
    }

    string searchName;
    cout << "Enter student name to search: ";
    cin >> searchName;

    string line;
    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, age, marks;
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, marks, ',');

        if (name == searchName) {
            cout << "Student Found!\n";
            cout << "Name: " << name << ", Age: " << age << ", Marks: " << marks << endl;
            found = true;
            break;
        }
    }
    file.close();

    if (!found) cout << "Student not found.\n";
}

// Function to delete student (Admin only)
void deleteStudent() {
    if (!isAdmin()) {
        cout << "Access Denied! Only admin can delete students.\n";
        return;
    }

    ifstream file("students.txt");
    if (!file) {
        cout << "No student records found!\n";
        return;
    }

    string delName;
    cout << "Enter student name to delete: ";
    cin >> delName;

    vector<string> students;
    string line;
    bool deleted = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');

        if (name != delName) {
            students.push_back(line);
        } else {
            deleted = true;
        }
    }
    file.close();

    ofstream outFile("students.txt");
    for (const string &student : students) {
        outFile << student << endl;
    }
    outFile.close();

    if (deleted)
        cout << "Student deleted successfully.\n";
    else
        cout << "Student not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student (Admin Only)\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student (Admin Only)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
