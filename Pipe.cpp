#include "Pipe.h"
using namespace std;

int Pipe::nextId = 1;
Pipe::Pipe()
    : id(nextId++), name(""), length(0),
      diameter(0), inRepair(false) {
}

int Pipe::getId() const {
    return id;
}

void Pipe::input() {
    int repair;

    cout << "Название: ";
    getline(cin >> ws, name);
    cout << "Длина: ";
    cin >> length;
    while (cin.fail() || length <= 0) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Введите длину еще раз: ";
        cin >> length;
    }
    cin.ignore(100, '\n');

    cout << "Диаметр: ";
    cin >> diameter;
    while (cin.fail() || diameter <= 0) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Введите диаметр еще раз: ";
        cin >> diameter;
    }
    cin.ignore(100, '\n');

    cout << "В ремонте (1/0): ";
    cin >> repair;
    while (cin.fail() || (repair != 0 && repair !=1)) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Введите 1 или 0: ";
        cin >> repair;
    }
    cin.ignore(100, '\n');
    inRepair = repair;
}

void Pipe::print() const {
    cout << "Труба ID: " << id<< endl;
    cout<< "Название: " <<name << endl;
    cout<< "Длина: " << length << endl;
    cout <<"Диаметр: " << diameter <<endl;
    cout << "Ремонт: " << inRepair <<endl;
}
void Pipe::setRepair(bool value) {
    inRepair = value;
}
bool Pipe::matchesName(const string& text) const {
    return name.find(text) != string::npos;
}
bool Pipe::matchesRepair(bool value) const {
    return inRepair == value;
}