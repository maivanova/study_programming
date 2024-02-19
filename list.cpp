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

    PrintList(head);
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    AddFirst(head, id1, sex1, age1, progress1);
    PrintList(head);
    cout << "======================================================\n";

    AddFirst(head, id2, sex2, age2, progress2);
    AddFirst(head, id3, sex3, age3, progress3);
    PrintList(head);
    cout << "******************************************************\n";
}
