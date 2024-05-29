#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Структура для хранения данных строки таблицы
struct Record {
    string name;
    int year;
    string color;
    double price;
    string description;
};

// Функция для загрузки данных из файла в оперативную память
vector<Record> loadDatabase(string filename) {
    vector<Record> database;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Record record;
            sscanf(line.c_str(), "%s %d %s %lf %s", &record.name, &record.year, &record.color, &record.price, &record.description);
            database.push_back(record);
        }
        file.close();
    }
    return database;
}

// Функция для сохранения данных из оперативной памяти в файл
void saveDatabase(vector<Record> database, string filename) {
    ofstream file(filename);
    for (Record record : database) {
        file << record.name << " " << record.year << " " << record.color << " " << record.price << " " << record.description << endl;
    }
    file.close();
}

// Функция для добавления новой записи в таблицу
void addRecord(vector<Record> &database, Record record) {
    database.push_back(record);
}

// Функция для удаления записи из таблицы
void deleteRecord(vector<Record> &database, string name) {
    for (auto it = database.begin(); it != database.end(); ++it) {
        if (it->name == name) {
            database.erase(it);
            break;
        }
    }
}

// Функция для поиска и вывода записи на экран
void searchRecord(vector<Record> database, string name) {
    for (Record record : database) {
        if (record.name == name) {
            cout << "Name: " << record.name << endl;
            cout << "Year: " << record.year << endl;
            cout << "Color: " << record.color << endl;
            cout << "Price: " << record.price << endl;
            cout << "Description: " << record.description << endl;
            return;
        }
    }
    cout << "Record not found." << endl;
}

int main() {
    vector<Record> database = loadDatabase("database.txt");

    while (true) {
        cout << "1. Add Record" << endl;
        cout << "2. Delete Record" << endl;
        cout << "3. Search Record" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            Record newRecord;
            cout << "Enter Name: ";
            cin >> newRecord.name;
            cout << "Enter Year: ";
            cin >> newRecord.year;
            cout << "Enter Color: ";
            cin >> newRecord.color;
            cout << "Enter Price: ";
            cin >> newRecord.price;
            cout << "Enter Description: ";
            cin >> newRecord.description;

            addRecord(database, newRecord);
        } else if (choice == 2) {
            string name;
            cout << "Enter Name to delete: ";
            cin >> name;
            deleteRecord(database, name);
        } else if (choice == 3) {
            string name;
            cout << "Enter Name to search: ";
            cin >> name;
            searchRecord(database, name);
        } else if (choice == 4) {
            saveDatabase(database, "database.txt");
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}