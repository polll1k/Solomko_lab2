#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "Pipe.h"
#include "CompressorStation.h"
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
    map<int,CompressorStation> stations;
    int choice;
    Logger::write("Запуск программы");
    while (true) {
        cout<<endl;
        cout<<"1. Добавить трубу"<<endl;
        cout<<"2. Добавить КС"<<endl;
        cout<<"3. Просмотреть все объекты"<<endl;
        cout<<"4. Поиск труб"<<endl;
        cout<<"5. Поиск КС"<<endl;
        cout<<"6. Сохранить трубы"<<endl;
        cout<<"7. Загрузить трубы"<<endl;
        cout<<"0. Выход"<<endl;
        cin>>choice;
        while (cin.fail() || choice<0 || choice>7) {
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
            CompressorStation cs;
            cs.input();
            stations.emplace(cs.getId(),cs);
            cout<<"КС добавлена. ID: "<<cs.getId()<<endl;
            Logger::write("Добавлена КС ID "+to_string(cs.getId()));
        }

        else if (choice==3) {
            if (pipes.empty() && stations.empty()) {
                cout<<"Объектов нет"<<endl;
            }
            for (const auto& pair:pipes) {
                pair.second.print();
                cout<<endl;
            }
            for (const auto& pair:stations) {
                pair.second.print();
                cout<<endl;
            }
        }

        else if (choice==4) {
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

        else if (choice==5) {
            if (stations.empty()) {
                cout<<"КС нет"<<endl;
            }
            else {
                int searchChoice;
                vector<int> foundIds;
                cout<<"1. По названию"<<endl;
                cout<<"2. По проценту незадействованных цехов"<<endl;
                cin>>searchChoice;
                cin.ignore(100,'\n');

                if (searchChoice==1) {
                    string text;
                    cout<<"Введите название: ";
                    getline(cin,text);
                    for (const auto& pair:stations) {
                        if (pair.second.matchesName(text)) {
                            pair.second.print();
                            cout<<endl;
                            foundIds.push_back(pair.first);
                        }
                    }
                }

                else if (searchChoice==2) {
                    double percent;
                    cout<<"Введите минимальный процент: ";
                    cin>>percent;
                    cin.ignore(100,'\n');

                    for (const auto& pair:stations) {
                        if (pair.second.matchesIdlePercent(percent)) {
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
                    int id;
                    cout<<"Введите ID КС: ";
                    cin>>id;

                    bool found=false;
                    for (int foundId:foundIds) {
                        if (foundId==id) {
                            found=true;
                        }
                    }

                    if (found) {
                        int action;
                        cout<<"1. Запустить цех"<<endl;
                        cout<<"2. Остановить цех"<<endl;
                        cout<<"3. Удалить КС"<<endl;
                        cin>>action;

                        if (action==1) {
                            stations.at(id).startWorkshop();
                            Logger::write("Запущен цех на КС ID "+to_string(id));
                        }
                        else if (action==2) {
                            stations.at(id).stopWorkshop();
                            Logger::write("Остановлен цех на КС ID "+to_string(id));
                        }
                        else if (action==3) {
                            stations.erase(id);
                            Logger::write("Удалена КС ID "+to_string(id));
                        }
                    }
                    else {
                        cout<<"Такой КС среди найденных нет"<<endl;
                    }
                }
            }
        }

        else if (choice==6) {
            savePipes(pipes);
            Logger::write("Сохранение труб");
        }

        else if (choice==7) {
            loadPipes(pipes);
            Logger::write("Загрузка труб");
        }
    }

    return 0;
}
