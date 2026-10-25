#include <iostream>
#include <map>
#include "Pipe.h"
using namespace std;

int main() {
    map<int, Pipe> pipes;
    int choice;
    while (true) {
        cout << endl;
        cout<< "1. Добавить трубу" <<endl;
        cout<<"2. Просмотреть все трубы"<<endl;
        cout<<"3. Поиск труб"<<endl;
        cout<< "0. Выход"<<endl;

        cin>>choice;

        while (cin.fail() || choice<0 || choice >3) {
            cin.clear();
            cin.ignore(100, '\n');
            cout<<"Введите пункт меню еще раз: ";
            cin>> choice;
        }

        cin.ignore(100, '\n');

        if (choice == 0) {
            break;
        }

        if (choice == 1) {
            Pipe pipe;
            pipe.input();
            pipes.emplace(pipe.getId(), pipe);
            cout<< "Труба добавлена. ID: " <<pipe.getId() <<endl;
        }

        else if (choice == 2) {
            if (pipes.empty()) {
                cout<<"Труб нет"<< endl;
            }
            else {
                for (const auto& pair : pipes) {
                    pair.second.print();
                    cout<<endl;
                }
            }
        }

        else if (choice == 3) {
            if (pipes.empty()) {
                cout<<"Труб нет"<<endl;
            }
            else {
                int searchChoice;
                cout<<"1. По названию"<<endl;
                cout<<"2. По ремонту"<<endl;
                
                cin>>searchChoice;
                cin.ignore(100, '\n');
                if (searchChoice == 1) {
                    string text;
                    cout<<"Введите название: ";
                    getline(cin,text);
                    for (const auto& pair : pipes) {
                        if (pair.second.matchesName(text)) {
                            pair.second.print();
                            cout<<endl;
                        }
                    }
                }
                else if (searchChoice == 2) {
                    int repair;
                    cout<<"В ремонте? 1/0: ";
                    cin>>repair;
                    cin.ignore(100, '\n');
                    for (const auto& pair : pipes) {
                        if (pair.second.matchesRepair(repair)) {
                            pair.second.print();
                            cout<<endl;
                        }
                    }
                }
            }
        }
    }
    return 0;
}