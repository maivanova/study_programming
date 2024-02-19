#include <iostream>
#include <string>
using namespace std;

struct student {
    int id;
    string sex;
    int age;
    int progress;
    student *next;
};

void AddFirst (student*& people, int id1, string sex1, int age1, int progress1){

    if (id1 <= 0) {
        cout << "invalid id: " << id1 << ". the id should be a positive integer." << endl;
        return;
    }
    if (sex1 != "female" && sex1 != "male") {
        cout << "invalid sex: " << sex1 << ". the sex should be either 'female' or 'male'." << endl;
        return;
    }
    if (age1 <= 0 || age1 > 120) {
        cout << "invalid age: " << age1 << ". the age should be a positive integer between 1 and 150." << endl;
        return;
    }
    if (progress1 < 0 || progress1 > 100) {
        cout << "invalid progress: " << progress1 << "%. the progress should be an integer between 0 and 100." << endl;
        return;
    }

    student *newstudent = new student;
    newstudent -> id = id1;
    newstudent -> sex = sex1;
    newstudent -> age = age1;
    newstudent -> progress = progress1;
    student *tmp = people;
    while (tmp != NULL){
        if (tmp -> id == id1){
            cout << "student with this id already in list\n" << endl;
            return;
        }
        tmp = tmp -> next;
    }
    newstudent -> next = people;
    people = newstudent;
    return;
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
        curr = curr -> next;
    }
    if (curr != nullptr) {
        prev -> next = curr -> next;
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
        cout << "student id:" << tmp -> id << "  sex:" << tmp -> sex
        << "  age:" << tmp -> age << "  progress:" << tmp -> progress << "%" << endl;
        tmp = tmp -> next;
    }
}

int main() {
    student *head = NULL;

    int id1 = 1;
    string sex1 = "female";
    int age1 = 19;
    int progress1 = 95;

    int id2 = 2;
    string sex2 = "female";
    int age2 = 21;
    int progress2 = 88;

    int id3 = 3;
    string sex3 = "female";
    int age3 = 17;
    int progress3 = 79;

    int id4 = 4;
    string sex4 = "female";
    int age4 = 18;
    int progress4 = 99;

    PrintList(head);
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    AddFirst(head, id1, sex1, age1, progress1);
    PrintList(head);
    cout << "======================================================\n";

    AddFirst(head, id2, sex2, age2, progress2);
    AddFirst(head, id3, sex3, age3, progress3);
    AddFirst(head, id4, sex4, age4, progress4);
    PrintList(head);
    cout << "******************************************************\n";

    RemoveStudentById(head, 2);
    PrintList(head);
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
}
