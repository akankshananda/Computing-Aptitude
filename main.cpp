#include <iostream>
using namespace std;

class Student {
public:
    int id;
    string name;
    int marks;
    Student* next;

    Student(int i, string n, int m) {
        id = i;
        name = n;
        marks = m;
        next = NULL;
    }
};

Student* head = NULL;

void addStudent() {
    int id;
    string name;
    int marks;

    cout << "Enter Student ID: ";
    cin >> id;

    cout << "Enter Student Name: ";
    cin >> name;

    cout << "Enter Marks: ";
    cin >> marks;

    Student* newStudent = new Student(id, name, marks);

    if (head == NULL) {
        head = newStudent;
    } else {
        Student* temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newStudent;
    }

    cout << "Student added successfully.\n";
}

void displayStudents() {
    Student* temp = head;

    if (temp == NULL) {
        cout << "No students found.\n";
        return;
    }

    cout << "\nStudent Records\n";
    cout << "------------------\n";

    while (temp != NULL) {
        cout << "ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Marks: " << temp->marks << endl;
        cout << "------------------\n";

        temp = temp->next;
    }
}

void searchStudent() {
    int id;

    cout << "Enter Student ID to search: ";
    cin >> id;

    Student* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            cout << "\nStudent Found\n";
            cout << "ID: " << temp->id << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Marks: " << temp->marks << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Student not found.\n";
}

void deleteStudent() {
    int id;

    cout << "Enter Student ID to delete: ";
    cin >> id;

    if (head == NULL) {
        cout << "No students found.\n";
        return;
    }

    if (head->id == id) {
        Student* temp = head;
        head = head->next;
        delete temp;

        cout << "Student deleted.\n";
        return;
    }

    Student* temp = head;

    while (temp->next != NULL) {
        if (temp->next->id == id) {
            Student* deleteNode = temp->next;
            temp->next = temp->next->next;
            delete deleteNode;

            cout << "Student deleted.\n";
            return;
        }

        temp = temp->next;
    }

    cout << "Student not found.\n";
}
void stackOptimization() {
    int n, k;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter number of elements to remove: ";
    cin >> k;

    int stack[100];

    cout << "Enter stack elements from top to bottom:\n";

    for (int i = 0; i < n; i++) {
        cin >> stack[i];
    }

    long long maximumSum = 0;

    for (int popped = 1; popped <= k; popped++) {

        int queue[100];
        int queueSize = n - popped;

        for (int i = 0; i < queueSize; i++) {
            queue[i] = stack[n - 1 - i];
        }

        long long sum = 0;

        for (int i = 0; i < popped; i++) {
            sum += stack[i];
        }

        int remaining = k - popped;

        for (int i = 0; i < remaining; i++) {
            sum += queue[i];
        }

        if (sum > maximumSum) {
            maximumSum = sum;
        }
    }

    cout << "Maximum possible sum: " << maximumSum << endl;
}

int main() {
    int choice;

    do {
        cout << "\n===== DataX C++ Backend =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Stack Optimization\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            addStudent();
        } else if (choice == 2) {
            displayStudents();
        } else if (choice == 3) {
            searchStudent();
        } else if (choice == 4) {
            deleteStudent();
        } else if (choice == 5) {
            stackOptimization();
        } else if (choice == 6) {
          cout << "Exiting DataX...\n";
        } else {
            cout << "Invalid choice.\n";
        }
   
    } while (choice != 6);

    return 0;
}