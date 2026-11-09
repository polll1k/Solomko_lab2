#include "Manager.h"
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
void Manager::addPipe() {
    Pipe pipe;
    pipe.input();
    pipes.emplace(pipe.getId(), pipe);
    cout << "Труба добавлена. ID: " << pipe.getId() << endl;
}

void Manager::addStation() {
    CompressorStation cs;
    cs.input();
    stations.emplace(cs.getId(), cs);
    cout << "КС добавлена. ID: " << cs.getId() << endl;
}

void Manager::showObjects() {
    if (pipes.empty() && stations.empty()) {
        cout << "Объектов нет" << endl;
    }
    for (const auto& pair : pipes) {
        pair.second.print();
        cout << endl;
    }
    for (const auto& pair : stations) {
        pair.second.print();
        cout << endl;
    }
}

void Manager::searchPipes() {
    if (pipes.empty()) {
        cout << "Труб нет" << endl;
        return;
    }
    int searchChoice;
    vector<int> foundIds;
    cout << "1. По названию" << endl;
    cout << "2. По ремонту" << endl;
    cin >> searchChoice;
    Logger::write(searchChoice);
    cin.ignore(100, '\n');
    if (searchChoice == 1) {
        string text;
        cout << "Введите название: ";
        getline(cin, text);
        Logger::write(text);
        foundIds = findMatches(pipes, [&](const Pipe& obj) {
            return obj.matchesName(text);
        });
    }

    else if (searchChoice == 2) {
        int repair;
        cout << "В ремонте? 1/0: ";
        cin >> repair;
        Logger::write(repair);
        cin.ignore(100, '\n');
        foundIds = findMatches(pipes, [&](const Pipe& obj) {
            return obj.matchesRepair(repair);
        });
    }
    if (foundIds.empty()) {
        cout << "Ничего не найдено" << endl;
        return;
    }
    int editChoice;
    vector<int> selectedIds;
    cout << "1. Изменить все найденные" << endl;
    cout << "2. Выбрать по ID" << endl;
    cin >> editChoice;
    Logger::write(editChoice);
    if (editChoice == 1) {
        selectedIds = foundIds;
    }
    else if (editChoice == 2) {
        int id;
        cout << "Введите ID труб, для окончания 0" << endl;
        while (true) {
            cout << "ID: ";
            cin >> id;
            Logger::write(id);
            if (id == 0) {
                break;
            }
            bool found = false;
            for (int foundId : foundIds) {
                if (foundId == id) {
                    found = true;
                }
            }
            if (found) {
                selectedIds.push_back(id);
            }
            else {
                cout << "Такой трубы среди найденных нет" << endl;
            }
        }
    }

    if (!selectedIds.empty()) {
        int action;
        cout << "1. В ремонт" << endl;
        cout << "2. Из ремонта" << endl;
        cout << "3. Удалить" << endl;
        cin >> action;
        Logger::write(action);
        for (int id : selectedIds) {
            if (action == 1) {
                pipes.at(id).setRepair(true);
            }
            else if (action == 2) {
                pipes.at(id).setRepair(false);
            }
            else if (action == 3) {
                pipes.erase(id);
            }
        }
    }
}

void Manager::searchStations() {
    if (stations.empty()) {
        cout << "КС нет" << endl;
        return;
    }
    int searchChoice;
    vector<int> foundIds;
    cout << "1. По названию" << endl;
    cout << "2. По проценту незадействованных цехов" << endl;
    cin >> searchChoice;
    Logger::write(searchChoice);
    cin.ignore(100, '\n');
    if (searchChoice == 1) {
        string text;
        cout << "Введите название: ";
        getline(cin, text);
        Logger::write(text);
        foundIds = findMatches(stations, [&](const CompressorStation& obj) {
            return obj.matchesName(text);
        });
    }
    else if (searchChoice == 2) {
        double percent;
        cout << "Введите минимальный процент: ";
        cin >> percent;
        Logger::write(percent);
        cin.ignore(100, '\n');
        foundIds = findMatches(stations, [&](const CompressorStation& obj) {
            return obj.matchesIdlePercent(percent);
        });
    }
    if (foundIds.empty()) {
        cout << "Ничего не найдено" << endl;
        return;
    }
    int id;
    cout << "Введите ID КС: ";
    cin >> id;
    Logger::write(id);
    bool found = false;
    for (int foundId : foundIds) {
        if (foundId == id) {
            found = true;
        }
    }

    if (found) {
        int action;
        cout << "1. Запустить цех" << endl;
        cout << "2. Остановить цех" << endl;
        cout << "3. Удалить КС" << endl;
        cin >> action;
        Logger::write(action);
        if (action == 1) {
            stations.at(id).startWorkshop();
        }
        else if (action == 2) {
            stations.at(id).stopWorkshop();
        }
        else if (action == 3) {
            stations.erase(id);
        }
    }
    else {
        cout << "Такой КС среди найденных нет" << endl;
    }
}
void Manager::saveData() {
    string filename;

    cout << "Введите имя файла: ";
    getline(cin, filename);
    Logger::write(filename);

    ofstream file(filename);

    if (!file) {
        cout << "Ошибка файла" << endl;
        return;
    }

    if (pipes.empty()) {
        file << 0 << endl;
    }
    else {
        file << 1 << endl;
        file << pipes.size() << endl;

        for (const auto& pair : pipes) {
            file << pair.second;
        }
    }

    if (stations.empty()) {
        file << 0 << endl;
    }
    else {
        file << 1 << endl;
        file << stations.size() << endl;

        for (const auto& pair : stations) {
            file << pair.second;
        }
    }

    cout << "Данные сохранены" << endl;
}

void Manager::loadData() {
    string filename;

    cout << "Введите имя файла: ";
    getline(cin, filename);
    Logger::write(filename);

    ifstream file(filename);

    if (!file) {
        cout << "Файл не найден" << endl;
        return;
    }

    int marker;
    int count;

    unordered_map<int, Pipe> newPipes;
    unordered_map<int, CompressorStation> newStations;

    file >> marker;

    if (marker == 1) {
        file >> count;
        file.ignore(100, '\n');

        for (int i = 0; i < count; i++) {
            Pipe pipe;
            file >> pipe;

            if (file.fail()) {
                cout << "Ошибка чтения труб" << endl;
                return;
            }

            newPipes.emplace(pipe.getId(), pipe);
        }
    }
    else if (marker == 0) {
        file.ignore(100, '\n');
    }
    else {
        cout << "Ошибка файла" << endl;
        return;
    }

    file >> marker;

    if (marker == 1) {
        file >> count;
        file.ignore(100, '\n');

        for (int i = 0; i < count; i++) {
            CompressorStation cs;
            file >> cs;

            if (file.fail()) {
                cout << "Ошибка чтения КС" << endl;
                return;
            }

            newStations.emplace(cs.getId(), cs);
        }
    }
    else if (marker == 0) {
        file.ignore(100, '\n');
    }
    else {
        cout << "Ошибка файла" << endl;
        return;
    }

    pipes = newPipes;
    stations = newStations;

    cout << "Данные загружены" << endl;
}

void Manager::run() {
    int choice;

    while (true) {
        cout << endl;
        cout << "1. Добавить трубу" << endl;
        cout << "2. Добавить КС" << endl;
        cout << "3. Просмотреть все объекты" << endl;
        cout << "4. Поиск труб" << endl;
        cout << "5. Поиск КС" << endl;
        cout << "6. Сохранить" << endl;
        cout << "7. Загрузить" << endl;
        cout << "0. Выход" << endl;

        cin >> choice;

        while (cin.fail() || choice < 0 || choice > 7) {
            cin.clear();
            cin.ignore(100, '\n');

            cout << "Введите пункт меню еще раз: ";
            cin >> choice;
        }

        Logger::write(choice);
        cin.ignore(100, '\n');

        if (choice == 0) {
            break;
        }

        if (choice == 1) {
            addPipe();
        }
        else if (choice == 2) {
            addStation();
        }
        else if (choice == 3) {
            showObjects();
        }
        else if (choice == 4) {
            searchPipes();
        }
        else if (choice == 5) {
            searchStations();
        }
        else if (choice == 6) {
            saveData();
        }
        else if (choice == 7) {
            loadData();
        }
    }
}