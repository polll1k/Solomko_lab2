#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "Pipe.h"
#include "Logger.h"
using namespace std;

void savePipes(const map<int,Pipe>& pipes) {
    string filename;
    cout<<"Введите имя файла: ";
    getline(cin,filename);
    ofstream file(filename);
    if (!file) {
        cout<<"Ошибка файла"<<endl;
        return;
    }
    if (pipes.empty()) {
        file<<0<<endl;
    }
    else {
        file<<1<<endl;
        file<<pipes.size()<<endl;
        for (const auto& pair:pipes) {
            file<<pair.second;
        }
    }
    cout<<"Данные сохранены"<<endl;
}

void loadPipes(map<int,Pipe>& pipes) {
    string filename;
    cout<<"Введите имя файла: ";
    getline(cin,filename);
    ifstream file(filename);
    if (!file) {
        cout<<"Файл не найден"<<endl;
        return;
    }
    int marker;
    file>>marker;
    if (marker==0) {
        pipes.clear();
        cout<<"Труб в файле нет"<<endl;
        return;
    }
    if (marker!=1) {
        cout<<"Ошибка файла"<<endl;
        return;
    }
    int count;
    file>>count;
    file.ignore(100,'\n');
    pipes.clear();
    for (int i=0;i<count;i++) {
        Pipe pipe;
        file>>pipe;
        if (file.fail()) {
            cout<<"Ошибка чтения"<<endl;
            return;
        }
        pipes.emplace(pipe.getId(),pipe);
    }
    cout<<"Данные загружены"<<endl;
}

int main() {
    map<int,Pipe> pipes;
    int choice;
    Logger::write("Запуск программы");
    while (true) {
        cout<<endl;
        cout<<"1. Добавить трубу"<<endl;
        cout<<"2. Просмотреть все трубы"<<endl;
        cout<<"3. Поиск труб"<<endl;
        cout<<"4. Сохранить"<<endl;
        cout<<"5. Загрузить"<<endl;
        cout<<"0. Выход"<<endl;
        cin>>choice;
        while (cin.fail() || choice<0 || choice>5) {
            cin.clear();
            cin.ignore(100,'\n');
            cout<<"Введите пункт меню еще раз: ";
            cin>>choice;
        }
        cin.ignore(100,'\n');
        Logger::write("Выбран пункт меню "+to_string(choice));
        if (choice==0) {
            Logger::write("Выход из программы");
            break;
        }
        if (choice==1) {
            Pipe pipe;
            pipe.input();
            pipes.emplace(pipe.getId(),pipe);
            cout<<"Труба добавлена. ID: "<<pipe.getId()<<endl;
            Logger::write("Добавлена труба ID "+to_string(pipe.getId()));
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
                cin.ignore(100,'\n');
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
                    cin.ignore(100,'\n');
                    for (const auto& pair:pipes) {
                        if (pair.second.matchesRepair(repair)) {
                            pair.second.print();
                            cout<<endl;
                            foundIds.push_back(pair.first);
                        }
                    }
                }
                Logger::write("Выполнен поиск труб");
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
                                Logger::write("Труба ID "+to_string(id)+" отправлена в ремонт");
                            }
                            else if (action==2) {
                                pipes.at(id).setRepair(false);
                                Logger::write("Труба ID "+to_string(id)+" выведена из ремонта");
                            }
                            else if (action==3) {
                                pipes.erase(id);
                                Logger::write("Удалена труба ID "+to_string(id));
                            }
                        }
                    }
                }
            }
        }
        else if (choice==4) {
            savePipes(pipes);
            Logger::write("Сохранение данных");
        }
        else if (choice==5) {
            loadPipes(pipes);
            Logger::write("Загрузка данных");
        }
    }
    return 0;
}
