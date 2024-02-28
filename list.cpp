#include <iostream>
#include <string>
using namespace std;

struct student {
    int id;
    string gender;
    int age;
    int progress;
    student *next;
};

void DataCheck(int id, string gender, int age, int progress) {
    if (id <= 0) {
        cout << "invalid id: " << id << ". the id should be a positive integer." << endl;
        return;
    }
    if (gender != "female" && gender != "male") {
        cout << "invalid gender: " << gender << ". the sex should be either 'female' or 'male'." << endl;
        return;
    }
    if (age <= 0 || age > 150) {
        cout << "invalid age: " << age << ". the age should be a positive integer between 1 and 150." << endl;
        return;
    }
    if (progress < 0 || progress > 100) {
        cout << "invalid progress: " << progress << "%. the progress should be an integer between 0 and 100." << endl;
        return;
    }
}

void AddFirst (student*& people, int id, string gender, int age, int progress){
    DataCheck(id, gender, age, progress);

    student *newstudent = new student;
    newstudent -> id = id;
    newstudent -> gender = gender;
    newstudent -> age = age;
    newstudent -> progress = progress;
    student *tmp = people;
    while (tmp != NULL){
        if (tmp -> id == id){
            cout << "student with this id already in list\n" << endl;
            return;
        }
        tmp = tmp -> next;
    }
    newstudent -> next = people;
    people = newstudent;
    return;
}

void AddLast(student*& people, int id, string gender, int age, int progress) {
    DataCheck(id, gender, age, progress);

    student* newstudent = new student;
    newstudent->id = id;
    newstudent->gender = gender;
    newstudent->age = age;
    newstudent->progress = progress;
    newstudent->next = nullptr;

    if (people == nullptr) {
        people = newstudent;
    } else {
        student* tmp = people;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = newstudent;
    }
}

void AddBefore(student*& head, int id, int new_id, string new_gender, int new_age, int new_progress) {
    DataCheck(new_id, new_gender, new_age, new_progress);
    if (head == nullptr) {
        cout << "List is empty" << endl;
        return;
    }

    if (head->id == id) {
        student* new_student = new student;
        new_student->id = new_id;
        new_student->gender = new_gender;
        new_student->age = new_age;
        new_student->progress = new_progress;
        new_student->next = head;
        head = new_student;
        return;
    }

    student* prev = head;
    student* current = head->next;
    while (current != nullptr) {
        if (current->id == id) {
            student* new_student = new student;
            new_student->id = new_id;
            new_student->gender = new_gender;
            new_student->age = new_age;
            new_student->progress = new_progress;
            new_student->next = current;
            prev->next = new_student;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "element with id " << id << " not found in the list" << endl;
}

void AddAfter(student* head, int id, int new_id, string new_gender, int new_age, int new_progress) {
    DataCheck(new_id, new_gender, new_age, new_progress);

    student* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            student* new_student = new student;
            new_student->id = new_id;
            new_student->gender = new_gender;
            new_student->age = new_age;
            new_student->progress = new_progress;
            new_student->next = current->next;
            current->next = new_student;
            return;
        }
        current = current->next;
    }
    cout << "element with id " << id << " not found in the list" << endl;
}

void RemoveStudentById(student*& head, int id) {
    student* curr = head;
    student* prev = nullptr;

    if (curr != nullptr && curr -> id == id) {
        head = curr -> next;
        delete curr;
        return;
    }
    while (curr != nullptr && curr -> id != id) {
        prev = curr;
        curr = curr->next;
    }
    if (curr != nullptr) {
        prev -> next = curr->next;
        delete curr;
    }
    else {
        cout << "student with id " << id << " not found in the list" << endl;
    }
}

void PrintList (student *people){
    if (people == NULL){
        cout << "this list is empty" << endl;
        return;
    }
    student *tmp = people;
    while (tmp != NULL){
        cout << "student id:" << tmp -> id << "  gender:" << tmp -> gender
        << "  age:" << tmp -> age << "  progress:" << tmp -> progress << "%" << endl;
        tmp = tmp -> next;
    }
}

int main() {
    student *head = NULL;

    PrintList(head);
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    AddFirst(head, 4, "female", 18, 97);
    PrintList(head);
    cout << "======================================================\n";

    AddFirst(head, 1, "female", 21, 91);
    AddLast(head, 5, "female", 20, 81);
    AddAfter(head, 1, 2, "female", 22, 85);
    AddBefore(head, 4, 3, "female", 20, 65);
    PrintList(head);
    cout << "******************************************************\n";

    RemoveStudentById(head, 4);
    PrintList(head);
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
}
