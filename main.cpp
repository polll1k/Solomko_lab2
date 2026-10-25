#include <iostream>
#include <map>
#include <vector>
#include "Pipe.h"
using namespace std;

int main() {
    map<int, Pipe> pipes;
    int choice;
    while (true) {
        cout<<endl;
        cout<<"1. Добавить трубу"<<endl;
        cout<<"2. Просмотреть все трубы"<<endl;
        cout<<"3. Поиск труб"<<endl;
        cout<<"0. Выход"<<endl;
        cin>>choice;
        while (cin.fail() || choice<0 || choice>3) {
            cin.clear();
            cin.ignore(100, '\n');
            cout<<"Введите пункт меню еще раз: ";
            cin>>choice;
        }
        cin.ignore(100, '\n');
        if (choice==0) {
            break;
        }
        if (choice==1) {
            Pipe pipe;
            pipe.input();
            pipes.emplace(pipe.getId(),pipe);
            cout<<"Труба добавлена. ID: "<<pipe.getId()<<endl;
        }
        else if (choice==2) {
            if (pipes.empty()) {
                cout<<"Труб нет"<<endl;
            }
            else {
                for (const auto& pair:pipes) {
                    pair.second.print();
                    cout<<endl;
                }
            }
        }
        else if (choice==3) {
            if (pipes.empty()) {
                cout<<"Труб нет"<<endl;
            }
            else {
                int searchChoice;
                vector<int> foundIds;
                cout<<"1. По названию"<<endl;
                cout<<"2. По ремонту"<<endl;
                cin>>searchChoice;
                cin.ignore(100, '\n');

                if (searchChoice==1) {
                    string text;
                    cout<<"Введите название: ";
                    getline(cin,text);
                    for (const auto& pair:pipes) {
                        if (pair.second.matchesName(text)) {
                            pair.second.print();
                            cout<<endl;
                            foundIds.push_back(pair.first);
                        }
                    }
                }
                else if (searchChoice==2) {
                    int repair;
                    cout<<"В ремонте? 1/0: ";
                    cin>>repair;
                    cin.ignore(100, '\n');
                    for (const auto& pair:pipes) {
                        if (pair.second.matchesRepair(repair)) {
                            pair.second.print();
                            cout<<endl;
                            foundIds.push_back(pair.first);
                        }
                    }
                }
                if (foundIds.empty()) {
                    cout<<"Ничего не найдено"<<endl;
                }
                else {
                    int editChoice;
                    vector<int> selectedIds;
                    cout<<"1. Изменить все найденные"<<endl;
                    cout<<"2. Выбрать по ID"<<endl;
                    cin>>editChoice;

                    if (editChoice==1) {
                        selectedIds=foundIds;
                    }
                    else if (editChoice==2) {
                        int id;
                        cout<<"Введите ID труб, для окончания 0"<<endl;
                        while (true) {
                            cout<<"ID: ";
                            cin>>id;
                            if (id==0) {
                                break;
                            }
                            bool found=false;
                            for (int foundId:foundIds) {
                                if (foundId==id) {
                                    found=true;
                                }
                            }
                            if (found) {
                                selectedIds.push_back(id);
                            }
                            else {
                                cout<<"Такой трубы среди найденных нет"<<endl;
                            }
                        }
                    }
                    if (!selectedIds.empty()) {
                        int action;
                        cout<<"1. В ремонт"<<endl;
                        cout<<"2. Из ремонта"<<endl;
                        cout<<"3. Удалить"<<endl;
                        cin>>action;
                        for (int id:selectedIds) {
                            if (action==1) {
                                pipes.at(id).setRepair(true);
                            }
                            else if (action==2) {
                                pipes.at(id).setRepair(false);
                            }
                            else if (action==3) {
                                pipes.erase(id);
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}